#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <song.h>
#include <QVector>
#include <QFile>

class Playlist {
public:
    Playlist(QFile* file = nullptr);
    Song& operator[] (int ind);
    void add(const Song& song);
    QVector<Song>::const_iterator begin();
    QVector<Song>::const_iterator end();
    size_t count();

    QString path;
    QString filename;
    QString extension;
    int size;
    int duration;

private:
    QVector<Song> data;
};

#endif // PLAYLIST_H
