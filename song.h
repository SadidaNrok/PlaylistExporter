#ifndef SONG_H
#define SONG_H
#include <string>
#include <vector>
#include <QTime>
#include <QString>


class Song {
public:
    Song(const std::wstring& str);

    QString path, filename, extension, name, artist, album;
    unsigned int bit_rate, chanels, freq, duration, size, number;
    bool is_empty = true;
};

using Playlist = std::vector<Song>;

#endif // SONG_H
