#include "song.h"

Song::Song(const QString& str) {
    auto list = str.split('|');

    if (list.size() < 2)
        return;

    path = list[0];
    filename = path.split('\\').last();
    extension = path.split('.').last();
    name = list[1];
    artist = list[2];
    album = list[3];
    bit_rate = list[11].toUInt();
    freq = list[13].toUInt();
    duration = list[14].toUInt();
    size = list[15].toUInt();
    number = list[18].toUInt() + 1;
    is_empty = false;
}
