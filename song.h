#ifndef SONG_H
#define SONG_H

#include <QTime>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLayout>

//class SongWidget;

class Song {
public:
    Song(const QString&);

    QString path, filename, extension, name, artist, album;
    unsigned int bit_rate, freq, duration, size;
    bool is_empty = true;

    //SongWidget* wid;
};

class SongWidget : public QWidget {
public:
    SongWidget(const Song&, int);

    QLabel* number;
    QLabel* top;
    QLabel* bottom;
    QLabel* duration;
};

#endif // SONG_H
