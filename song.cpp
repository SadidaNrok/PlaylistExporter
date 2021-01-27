#include "song.h"

const size_t FIELDS_COUNT = 20;

Song::Song(const std::wstring& str) {
    std::vector<int> marks;

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '|')
            marks.push_back(i);
    }

    if (marks.size() != FIELDS_COUNT) {
        empty = true;
        return;
    }

    path = str.substr(marks[0], 10);
}
