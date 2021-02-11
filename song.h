#ifndef SONG_H
#define SONG_H

#include <QTime>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFile>

class Song {
public:
    Song();
    Song(const QString&);
    Song(QFile*);

    QString path, filename, extension, name, artist;
    unsigned int bit_rate, freq, duration, size;
    bool is_empty = true;
    bool is_exist = false;
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
