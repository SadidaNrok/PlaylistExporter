#include "song.h"
#include <QPainter>

Song::Song() {
    duration = 0;
    size = 0;
}

Song::Song(const QString& str) {
    auto list = str.split('|');

    if (list.size() < 2)
        return;

    path = list[0];
    filename = path.split('\\').last();
    extension = path.split('.').last();
    name = list[1];
    artist = list[2];
    bit_rate = list[11].toUInt();
    freq = list[13].toUInt();
    duration = list[14].toUInt();
    size = list[15].toUInt();
    is_empty = false;
    is_exist = (QFile(path).exists() ? true : false);
}

Song::Song(QFile* file) {
    path = file->fileName();
    filename = path.split('/').last();
    extension = path.split('.').last();

    duration = 0;
    size = file->size();
    is_empty = false;
}

SongWidget::SongWidget(const Song& song, int num) {
    number = new QLabel;
    top = new QLabel;
    bottom = new QLabel;
    duration = new QLabel;

    if (!song.is_exist) {
        number->setStyleSheet("QLabel { color : red; }");
        top->setStyleSheet("QLabel { color : red; }");
        bottom->setStyleSheet("QLabel { color : red; }");
        duration->setStyleSheet("QLabel { color : red; }");
    }

    QFont font;
    font.setPixelSize(9);

    number->setFixedWidth(20);
    duration->setFixedWidth(28);
    bottom->setFont(font);

    auto hgrid = new QHBoxLayout;
    auto vgrid = new QVBoxLayout;
    hgrid->setSpacing(0);
    vgrid->setSpacing(0);

    hgrid->addWidget(number);
    hgrid->addWidget(top);
    hgrid->addSpacing(5);
    hgrid->addWidget(duration);
    vgrid->addLayout(hgrid);
    vgrid->addWidget(bottom);

    setLayout(vgrid);

    number->setText(QString::number(num));
    if (song.name.isEmpty() || song.artist.isEmpty())
        top->setText(song.filename);
    else
        top->setText(song.artist + " - " + song.name);
    bottom->setText(QString("%1 :: %2 kHz, %3 kbps, %4 Mb")
                         .arg(song.extension)
                         .arg(song.freq / 1000)
                         .arg(song.bit_rate)
                         .arg(song.size / (1024 * 1024.0), 3, 'f', 2, '0'));
    duration->setText(QTime(0, 0, 0, 0).addMSecs(song.duration).toString("mm:ss"));
}
