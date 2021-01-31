#include "song.h"

const size_t FIELDS_COUNT = 20;

Song::Song(const std::wstring& str) {
    std::vector<int> marks;

    for (size_t i = 0; i < str.size(); ++i)
        if (str[i] == '|')
            marks.push_back(i);

    if (marks.size() == FIELDS_COUNT)
        empty = false;
    else return;

    path = QString::fromStdWString(str).mid(0, marks[0]);
    filename = path.split("\\").last();
    extension = path.split(".").last();
    name =QString::fromStdWString(str).mid(marks[0] + 1, marks[1] - marks[0] - 1);
    artist = QString::fromStdWString(str).mid(marks[1] + 1, marks[2] - marks[1] - 1);
    album = QString::fromStdWString(str).mid(marks[2] + 1, marks[3] - marks[2] - 1);
    bit_rate = stoi(str.substr(marks[10] + 1, marks[11] - marks[10] - 1));
    freq = stoi(str.substr(marks[12] + 1, marks[13] - marks[12] - 1));
    duration = QTime(0, 0, 0, 0)
            .addMSecs(stoi(str.substr(marks[13] + 1, marks[14] - marks[13] - 1)));
    size = stoi(str.substr(marks[14] + 1, marks[15] - marks[14] - 1));
    number = stoi(str.substr(marks[17] + 1, marks[18] - marks[17] - 1)) + 1;
}
