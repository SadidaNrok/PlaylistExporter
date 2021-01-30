#include "song.h"

const size_t FIELDS_COUNT = 20;

Song::Song(const std::wstring& str) {
    std::vector<int> marks;

    for (size_t i = 0; i < str.size(); ++i)
        if (str[i] == '|')
            marks.push_back(i);

    if (marks.size() == FIELDS_COUNT)
        empty = false;
    else
        return;

    path = str.substr(0, marks[0]);
    name = str.substr(marks[0] + 1, marks[1] - marks[0] - 1);
    artist = str.substr(marks[1] + 1, marks[2] - marks[1] - 1);
    album = str.substr(marks[2] + 1, marks[3] - marks[2] - 1);
    //wrighter?
    //genre
    year = str.substr(marks[5] + 1, marks[6] - marks[5] - 1);
    //number in album?
    //total count in album?
    //co-wrighter?
    //Label?
    bit_rate = str.substr(marks[10] + 1, marks[11] - marks[10] - 1);
    //chanals
    freq = str.substr(marks[12] + 1, marks[13] - marks[12] - 1);
    duration = str.substr(marks[13] + 1, marks[14] - marks[13] - 1);
    size = str.substr(marks[14] + 1, marks[15] - marks[14] - 1);
    //
    //
    number = str.substr(marks[17] + 1, marks[18] - marks[17] - 1);
    //

    auto hh = stoi(duration);
    dur = QTime().addMSecs(hh);
}
