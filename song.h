#ifndef SONG_H
#define SONG_H
#include <string>
#include <vector>
#include <QTime>
#include <QString>


class Song {
public:
    Song(const std::wstring& str);

    bool is_empty() { return empty; };

    QString path, filename, extension, name, artist, album;
    int bit_rate, chanels, freq, size, number;
    QTime duration;

private:
    bool empty = true;
};

using Playlist = std::vector<Song>;

#endif // SONG_H
