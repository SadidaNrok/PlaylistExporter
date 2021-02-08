#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QListWidget>
#include <QVector>
#include "song.h"

class PlaylistWidget : public QListWidget {
    Q_OBJECT

public:
    PlaylistWidget();
    void addSong (const Song&);
    void insertSong (int, const Song&);
    void deleteSong (int);
    void swap(const Song&, const Song&);

private:
    void checkItemNumber(int);
    QListWidgetItem* createItem(QListWidget* = nullptr);

    QVector<Song> playlist;
    QString path;
    QString filename;
    QString extension;
    int full_size;
    int duration;
};

#endif // PLAYLISTWIDGET_H
