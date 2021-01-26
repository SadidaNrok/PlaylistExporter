#ifndef SONG_H
#define SONG_H
#include <string>
#include <vector>

class Song {
public:
    Song(std::wstring& str);

    bool is_empty() { return empty; };

    std::string path, name, artist, album;
    int year, bit_rate, freq, duration, size;

private:
    bool empty;
};

using Playlist = std::vector<Song>;

#endif // SONG_H
