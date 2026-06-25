/*
 * Copyright (c) 2026, MAliffadlan
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <AK/Vector.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDateTime>

namespace Ladybird {

struct DownloadEntry {
    QString filename;
    QString path;
    QString url;
    QString status; // "Downloading", "Completed", "Failed"
    QDateTime timestamp;
    u64 id;
};

class DownloadItemWidget final : public QWidget {
    Q_OBJECT

public:
    explicit DownloadItemWidget(DownloadEntry const& entry, QWidget* parent = nullptr);
    void update_status(QString const& status);

private:
    QLabel* m_filename_label { nullptr };
    QLabel* m_status_label { nullptr };
    QPushButton* m_open_button { nullptr };
    QString m_path;
};

class DownloadManagerWidget final : public QWidget {
    Q_OBJECT

public:
    explicit DownloadManagerWidget(QWidget* parent = nullptr);
    void add_download(DownloadEntry const& entry);
    void update_download(u64 id, QString const& status);

signals:
    void close_requested();

private:
    void clear_completed();

    QVBoxLayout* m_list_layout { nullptr };
    QWidget* m_list_widget { nullptr };
    QLabel* m_empty_label { nullptr };
    Vector<DownloadItemWidget*> m_items;
    u64 m_next_id { 1 };
};

}
