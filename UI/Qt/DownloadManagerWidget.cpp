/*
 * Copyright (c) 2026, MAliffadlan
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <UI/Qt/DownloadManagerWidget.h>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

namespace Ladybird {

DownloadItemWidget::DownloadItemWidget(DownloadEntry const& entry, QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(8, 4, 8, 4);

    m_filename_label = new QLabel(entry.filename, this);
    m_filename_label->setStyleSheet("font-weight: bold;");
    layout->addWidget(m_filename_label, 1);

    m_status_label = new QLabel(entry.status, this);
    m_status_label->setStyleSheet("color: gray;");
    layout->addWidget(m_status_label);

    m_open_button = new QPushButton("Open", this);
    m_open_button->setVisible(entry.status == "Completed");
    layout->addWidget(m_open_button);

    m_path = entry.path;

    connect(m_open_button, &QPushButton::clicked, this, [this]() {
        auto path_url = QUrl::fromLocalFile(m_path);
        QDesktopServices::openUrl(path_url);
    });

    setMinimumHeight(36);
}

void DownloadItemWidget::update_status(QString const& status)
{
    m_status_label->setText(status);
    m_open_button->setVisible(status == "Completed");
}

DownloadManagerWidget::DownloadManagerWidget(QWidget* parent)
    : QWidget(parent)
{
    auto* main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);

    // Header
    auto* header = new QWidget(this);
    auto* header_layout = new QHBoxLayout(header);
    header_layout->setContentsMargins(8, 4, 8, 4);

    auto* title = new QLabel("Downloads", this);
    title->setStyleSheet("font-weight: bold; font-size: 14px;");
    header_layout->addWidget(title, 1);

    auto* clear_button = new QPushButton("Clear", this);
    connect(clear_button, &QPushButton::clicked, this, &DownloadManagerWidget::clear_completed);
    header_layout->addWidget(clear_button);

    auto* close_button = new QPushButton("Close", this);
    connect(close_button, &QPushButton::clicked, this, &DownloadManagerWidget::close_requested);
    header_layout->addWidget(close_button);

    header->setStyleSheet("background-color: #f0f0f0; border-bottom: 1px solid #ccc;");
    main_layout->addWidget(header);

    // Scrollable list
    auto* scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_list_widget = new QWidget();
    m_list_layout = new QVBoxLayout(m_list_widget);
    m_list_layout->setContentsMargins(0, 0, 0, 0);
    m_list_layout->setSpacing(0);
    m_list_layout->addStretch();

    m_empty_label = new QLabel("No downloads yet", m_list_widget);
    m_empty_label->setAlignment(Qt::AlignCenter);
    m_empty_label->setStyleSheet("color: gray; padding: 20px;");
    m_list_layout->insertWidget(0, m_empty_label);

    scroll_area->setWidget(m_list_widget);
    main_layout->addWidget(scroll_area, 1);

    setMinimumHeight(200);
    setMaximumHeight(400);
    setStyleSheet("background-color: white; border-top: 1px solid #ccc;");
    hide();
}

void DownloadManagerWidget::add_download(DownloadEntry const& entry)
{
    auto e = entry;
    e.id = m_next_id++;

    m_empty_label->hide();

    auto* item = new DownloadItemWidget(e, m_list_widget);
    m_items.append(item);
    m_list_layout->insertWidget(m_list_layout->count() - 1, item);

    show();
}

void DownloadManagerWidget::update_download(u64 id, QString const& status)
{
    for (auto* item : m_items) {
        // Find the item by position (simplified)
        if (id > 0) {
            item->update_status(status);
            break;
        }
    }
}

void DownloadManagerWidget::clear_completed()
{
    for (auto* item : m_items) {
        item->deleteLater();
    }
    m_items.clear();
    m_empty_label->show();
    hide();
}

}
