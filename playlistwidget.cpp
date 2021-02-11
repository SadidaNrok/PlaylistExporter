#include "playlistwidget.h"

PlaylistWidget::PlaylistWidget(QMainWindow* prnt)
    : QListWidget(prnt) {}

void PlaylistWidget::addSong (const Song& song) {
    auto item = createItem(this);
    setItemWidget(item, new SongWidget(song, count()));
}

void PlaylistWidget::insertSong (int ind, const Song& song) {
    auto item = createItem();
    insertItem(ind, item);
    setCurrentItem(item);
    setItemWidget(item, new SongWidget(song, ind + 1));
    checkItemNumber(ind);
}

void PlaylistWidget::deleteSong (int ind) {
    delete takeItem(ind);
    checkItemNumber(ind);
}

void PlaylistWidget::checkItemNumber(int ind) {
    for (int i = ind; i < count(); ++i) {
        auto item = this->item(i);
        auto wid = static_cast<SongWidget*>(itemWidget(item));
        wid->number->setText(QString::number(i + 1));
    }
}

QListWidgetItem* PlaylistWidget::createItem(QListWidget* prnt) {
    auto item = new QListWidgetItem(prnt);
    item->setSizeHint(QSize(250, 40));
    return item;
}
