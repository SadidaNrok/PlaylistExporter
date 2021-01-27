#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <codecvt>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    auto main_widget = new QWidget(this);
    setCentralWidget(main_widget);

    auto main_grid = new QGridLayout(main_widget);

    open_pl = new QPushButton();
    open_pl->setFixedSize({40, 40});
    open_pl->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
    main_grid->addWidget(open_pl, 0, 0, 1, 1);

    save_pl =  new QPushButton();
    save_pl->setFixedSize({40, 40});
    save_pl->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    main_grid->addWidget(save_pl, 0, 1, 1, 1);

    save_files = new QPushButton();
    save_files->setFixedSize({40, 40});
    save_files->setIcon(this->style()->standardIcon(QStyle::SP_DriveHDIcon));
    main_grid->addWidget(save_files, 0, 2, 1, 1);

    exit_app = new QPushButton();
    exit_app->setFixedSize({40, 40});
    exit_app->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
    main_grid->addWidget(exit_app, 0, 5, 1, 1);

    auto playlist_lbl = new QLabel("Playlist: ");
    main_grid->addWidget(playlist_lbl, 1, 0, 1, 6);

    playlist = new QListWidget();
    main_grid->addWidget(playlist, 2, 0, 1, 6);

    add_file = new QPushButton("Add");
    add_file->setFixedSize({40, 40});
    main_grid->addWidget(add_file, 3, 0, 1, 1);

    delete_file = new QPushButton("Delete");
    delete_file->setFixedSize({40, 40});
    main_grid->addWidget(delete_file, 3, 1, 1, 1);

    move_up = new QPushButton();
    move_up->setFixedSize({40, 40});
    move_up->setIcon(this->style()->standardIcon(QStyle::SP_ArrowUp));
    main_grid->addWidget(move_up, 3, 2, 1, 1);

    move_down = new QPushButton();
    move_down->setFixedSize({40, 40});
    move_down->setIcon(this->style()->standardIcon(QStyle::SP_ArrowDown));
    main_grid->addWidget(move_down, 3, 3, 1, 1);

    connect(open_pl, &QPushButton::clicked, this, &MainWindow::open_fun);

}

void MainWindow::open_fun() {
    auto path = QFileDialog::getOpenFileName(nullptr, "Open Playlist", "", "*.aimppl4");
    std::wifstream file(path.toLocal8Bit().constData(),
                        std::ios_base::in | std::ios_base::binary);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t,
                           1114111UL, std::little_endian>));

    if (!file.is_open()) {
        QMessageBox::warning(this, "Warning", "File was not opened!");
        return;
    }

    while (!file.eof()) {
        std::wstring line;
        std::getline(file, line);

        std::wcout << line << std::endl;
        playlist->addItem(QString::fromStdWString(line));
        
        Song song(line);
		if (!song.is_empty())
			playlist.push_back(song);
    }
}

