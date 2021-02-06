#include "playlist.h"

Playlist::Playlist(QFile* file) {
    if (file != nullptr) {
        QString f_name = file->fileName();
        filename = f_name.split('\\').last();
        extension = f_name.split('.').last();
        path = f_name.left(f_name.length() - filename.length() - 1);
    }
    full_size = 0;
    duration = 0;

    QTextStream in(file);
    in.setCodec("UTF-16");

    while (!in.atEnd()) {
        Song song(in.readLine());

        if (!song.is_empty)
            add(song);
    }
}

void Playlist::add(const Song& song) {
    push_back(song);
    full_size += song.size;
    duration += song.duration;
}

void Playlist::del(int ind) {
    full_size -= at(ind).size;
    duration -= at(ind).duration;
    remove(ind);
}
