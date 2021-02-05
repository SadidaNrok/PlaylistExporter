#ifndef SONG_H
#define SONG_H

#include <QTime>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLayout>


class SongWidget;

class Song {
public:
    Song(const QString& str);

    QString path, filename, extension, name, artist, album;
    unsigned int bit_rate, freq, duration, size, number;
    bool is_empty = true;

    SongWidget* wid;
};

class SongWidget : public QWidget {
public:
    SongWidget(Song* song);

    QLabel* number;
    QLabel* top;
    QLabel* bottom;
    QLabel* duration;
};

#endif // SONG_H
