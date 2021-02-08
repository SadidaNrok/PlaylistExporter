#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "song.h"

#include <QVector>
#include <QTextStream>

class Playlist : public QVector<Song> {
public:
    Playlist(QFile* file = nullptr);
    void add(const Song&);
    void del(int);
    void paste(int, const Song&);

    QString path;
    QString filename;
    QString extension;
    int full_size;
    int duration;
};

#endif // PLAYLIST_H
