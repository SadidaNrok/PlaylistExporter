#ifndef SONG_H
#define SONG_H
#include <string>
#include <vector>
#include <QTime>

class Song {
public:
    Song(const std::wstring& str);

    bool is_empty() { 
        return empty; 
    };

    std::wstring path, name, artist, album, ganre,
                 year, bit_rate, chanels, freq, duration, size, number;

    QTime dur;

private:
    bool empty = true;
};

using Playlist = std::vector<Song>;

#endif // SONG_H
