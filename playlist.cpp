#include "playlist.h"

Playlist::Playlist(QFile* file) {
    if (file != nullptr) {
        path = file->fileName();
        filename = file->fileName().split('\\').last();
        extension = file->fileName().split('.').last();
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

QVector<Song>::const_iterator Playlist::begin() {
    return data.begin();
}

QVector<Song>::const_iterator Playlist::end() {
    return data.end();
}

size_t Playlist::count() {
    return data.size();
}
