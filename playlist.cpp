#include "playlist.h"

Playlist::Playlist(QFile* file) {
    if (file != nullptr) {
        filename = file->fileName().split('/').last();
        extension = file->fileName().split('.').last();
        path = file->fileName().left(file->fileName().length()-filename.length() - 1);
    }
    size = 0;
    duration = 0;
    data = QVector<Song>();
}

Song& Playlist::operator[] (int ind) {
    return data[ind];
}

void Playlist::add(const Song& song) {
    data.push_back(song);
}

void Playlist::remove(int ind) {
    data.remove(ind);
}

QVector<Song>::const_iterator Playlist::begin() {
    return data.begin();
}

QVector<Song>::const_iterator Playlist::end() {
    return data.end();
}

size_t Playlist::count() {
    return data.size();
}
