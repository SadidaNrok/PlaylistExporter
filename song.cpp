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

    wid = new SongWidget(this);

//    auto hgrid = new QHBoxLayout;
//    auto vgrid = new QVBoxLayout;

//    hgrid->setSpacing(0);
//    vgrid->setSpacing(0);

//    auto lb_number = new QLabel;
//    auto lb_top = new QLabel;
//    auto lb_bottom = new QLabel;
//    auto lb_duration = new QLabel;

//    lb_number->setFixedWidth(20);
//    lb_duration->setFixedWidth(28);
//    lb_bottom->setFont(QFont("Arial", 6));

//    hgrid->addWidget(lb_number);
//    hgrid->addWidget(lb_top);
//    hgrid->addSpacing(5);
//    hgrid->addWidget(lb_duration);

//    vgrid->addLayout(hgrid);
//    vgrid->addWidget(lb_bottom);

//    wid->setLayout(vgrid);

//    lb_number->setText(QString::number(number));
//    lb_top->setText(artist + " - " + name);
//    lb_bottom->setText(QString("%1 :: %2 kHz, %3 kbps, %4 Mb")
//                         .arg(extension)
//                         .arg(freq / 1000)
//                         .arg(bit_rate)
//                         .arg(size / (1024 * 1024.0), 3, 'f', 2, '0'));
//    lb_duration->setText(QTime(0, 0, 0, 0).addMSecs(duration).toString("mm:ss"));
}

SongWidget::SongWidget(Song* song) {
    auto hgrid = new QHBoxLayout;
    auto vgrid = new QVBoxLayout;

    hgrid->setSpacing(0);
    vgrid->setSpacing(0);

    auto lb_number = new QLabel;
    auto lb_top = new QLabel;
    auto lb_bottom = new QLabel;
    auto lb_duration = new QLabel;

    lb_number->setFixedWidth(20);
    lb_duration->setFixedWidth(28);
    lb_bottom->setFont(QFont("Arial", 6));

    hgrid->addWidget(lb_number);
    hgrid->addWidget(lb_top);
    hgrid->addSpacing(5);
    hgrid->addWidget(lb_duration);

    vgrid->addLayout(hgrid);
    vgrid->addWidget(lb_bottom);

    setLayout(vgrid);

    lb_number->setText(QString::number(song->number));
    lb_top->setText(song->artist + " - " + song->name);
    lb_bottom->setText(QString("%1 :: %2 kHz, %3 kbps, %4 Mb")
                         .arg(song->extension)
                         .arg(song->freq / 1000)
                         .arg(song->bit_rate)
                         .arg(song->size / (1024 * 1024.0), 3, 'f', 2, '0'));
    lb_duration->setText(QTime(0, 0, 0, 0).addMSecs(song->duration).toString("mm:ss"));
}
