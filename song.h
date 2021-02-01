#ifndef SONG_H
#define SONG_H
#include <vector>
#include <QTime>
#include <QString>

class Song {
public:
    Song(const QString& str);

    QString path, filename, extension, name, artist, album;
    unsigned int bit_rate, freq, duration, size, number;
    bool is_empty = true;
};

#endif // SONG_H
