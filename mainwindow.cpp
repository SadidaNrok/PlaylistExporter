#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    auto m_quit = new QAction("&Quit");
    auto m_settings = new QAction("&Settings");
    QMenu* menu;
    menu = menuBar()->addMenu("&File");
    menu->addAction(m_quit);
    menu->addAction(m_settings);

    auto main_widget = new QWidget(this);
    setCentralWidget(main_widget);
    statusBar()->showMessage("Ready");

    auto grid = new QGridLayout(main_widget);

    le_open = new QLineEdit();
    le_save_to = new QLineEdit();
    btn_open = new QPushButton("Open");
    btn_save_to = new QPushButton("Save to");
    group = new QGroupBox("Playlist items:");
    auto group_grid = new QGridLayout();
    list = new QListWidget();
    btn_add = new QPushButton();
    btn_delete = new QPushButton();
    btn_up = new QPushButton();
    btn_down = new QPushButton();
    sequence = new QCheckBox("Keep file sequence");
    btn_save = new QPushButton("Save");
    progress = new QProgressBar();

    grid->addWidget(new QLabel("Source:"), 0, 0, 1, 5);
    grid->addWidget(le_open, 1, 0, 1, 5);
    grid->addWidget(btn_open, 1, 5, 1, 1);
    grid->addWidget(new QLabel("Destination:"), 2, 0, 1, 5);
    grid->addWidget(le_save_to, 3, 0, 1, 5);
    grid->addWidget(btn_save_to, 3, 5, 1, 1);
    grid->addWidget(group, 4, 0, 1, 6);
    grid->addWidget(sequence, 5, 0, 1, 3);
    grid->addWidget(btn_save, 5, 5, 1, 1);
    grid->addWidget(progress, 6, 0, 1, 6);
    grid->setRowStretch(4, 1);

    group->setLayout(group_grid);
    group_grid->addWidget(list, 0, 0, 1, 7);
    group_grid->addWidget(btn_add, 1, 0, 1, 1);
    group_grid->addWidget(btn_delete, 1, 1, 1, 1);
    group_grid->addWidget(btn_up, 1, 2, 1, 1);
    group_grid->addWidget(btn_down, 1, 3, 1, 1);

    le_open->setReadOnly(true);
    le_save_to->setReadOnly(true);
    group->setEnabled(false);
    btn_add->setFixedSize({25, 25});
    btn_delete->setFixedSize({25, 25});
    btn_up->setFixedSize({25, 25});
    btn_down->setFixedSize({25, 25});
    btn_save->setEnabled(false);
    progress->setVisible(false);

//    open_pl = new QPushButton();
//    open_pl->setFixedSize({40, 40});
//    open_pl->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
//    main_grid->addWidget(open_pl, 0, 0, 1, 1);

//    save_pl =  new QPushButton();
//    save_pl->setFixedSize({40, 40});
//    save_pl->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
//    main_grid->addWidget(save_pl, 0, 1, 1, 1);

//    save_files = new QPushButton();
//    save_files->setFixedSize({40, 40});
//    save_files->setIcon(this->style()->standardIcon(QStyle::SP_DriveHDIcon));
//    main_grid->addWidget(save_files, 0, 2, 1, 1);

//    exit_app = new QPushButton();
//    exit_app->setFixedSize({40, 40});
//    exit_app->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
//    main_grid->addWidget(exit_app, 0, 5, 1, 1);

//    auto playlist_lbl = new QLabel("Playlist: ");
//    main_grid->addWidget(playlist_lbl, 1, 0, 1, 6);

//    list = new QListWidget();
//    list->setFont(QFont("Arial"));
//    main_grid->addWidget(list, 2, 0, 1, 6);

//    add_file = new QPushButton("Add");
//    add_file->setFixedSize({40, 40});
//    main_grid->addWidget(add_file, 3, 0, 1, 1);

//    delete_file = new QPushButton("Delete");
//    delete_file->setFixedSize({40, 40});
//    main_grid->addWidget(delete_file, 3, 1, 1, 1);

//    move_up = new QPushButton();
//    move_up->setFixedSize({40, 40});
//    move_up->setIcon(this->style()->standardIcon(QStyle::SP_ArrowUp));
//    main_grid->addWidget(move_up, 3, 2, 1, 1);

//    move_down = new QPushButton();
//    move_down->setFixedSize({40, 40});
//    move_down->setIcon(this->style()->standardIcon(QStyle::SP_ArrowDown));
//    main_grid->addWidget(move_down, 3, 3, 1, 1);
    connect(m_quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(btn_open, &QPushButton::clicked, this, &MainWindow::f_open);
    connect(btn_save_to, &QPushButton::clicked, this, &MainWindow::f_save_to);
    connect(btn_save, &QPushButton::clicked, this, &MainWindow::f_save);

    total_size = 0;
    total_dur = 0;
}

void MainWindow::f_open() {
    auto path = QFileDialog::getOpenFileName(nullptr, "Open Playlist", "", "Playlist files (*.aimppl4 *.PLC)");
    source = path;
    le_open->setText(path);
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

        Playlist play_list;
        
        Song song(line);
        if (!song.is_empty) {
            playlist.push_back(song);
            auto qtext = get_record(song);
            list->addItem(qtext);
            total_size += song.size;
            total_dur += song.duration;
        }
    }

    if (!le_save_to->text().isEmpty())
        btn_save->setEnabled(true);

    group->setEnabled(true);
    statusBar()->showMessage(QString("Playlist was loaded. Total size: %1 Mb, duration: %2")
            .arg(total_size / (1024.0 * 1024), 3, 'f', 2, '0' )
            .arg(QTime(0, 0, 0, 0).addMSecs(total_dur).toString("hh:mm:ss")));
}

void MainWindow::f_save_to() {
    auto path = QFileDialog::getExistingDirectory(nullptr, "Choose folder", "", QFileDialog::ShowDirsOnly);
    destination = path;
    le_save_to->setText(path);

    if (!le_open->text().isEmpty())
        btn_save->setEnabled(true);
}

void MainWindow::f_save() {
    if (QMessageBox::question(nullptr, "Save files",
        QString("Are you sure you want to copy all files to the folder: \n%1")
            .arg(destination), QMessageBox::Cancel | QMessageBox::Yes)
            == QMessageBox::Cancel)
        return;

    progress->setVisible(true);
    int ready = 0;
    int degree = total_size / 100;

    for (auto& song : playlist) {
        auto file = new QFile(song.path);
        int zeros = log10(playlist.size()) + 1;
        if (sequence->isChecked())
            file->copy(QString("%1\\%2-%3")
                       .arg(destination)
                       .arg(song.number, zeros, 'g', -1, '0')
                       .arg(song.filename));
        else
            file->copy(QString("%1\\%3")
                       .arg(destination)
                       .arg(song.filename));

        ready += song.size;
        progress->setValue(ready / degree);
    }

    progress->setVisible(false);
    statusBar()->showMessage("Files have been copied");
}

QString MainWindow::get_record(Song& song) {
    QString qtext = QString("%1. %2 - %3")
            .arg(song.number, 2, 'g', -1, '0')
            .arg(song.artist)
            .arg(song.name);

    QFontMetrics qfm = QFontMetrics(list->font());

    auto list_width = list->width() - 40;
    bool chopped = false;

    while (qfm.width(qtext) > list_width) {
        qtext.truncate(qtext.size() - 1);
        chopped = true;
    }

    if (chopped)
        qtext += "...";

    qtext += QString("\n%1 :: %2 kHz, %3 kbps, %4 Mb, %5")
            .arg(song.extension.toUpper())
            .arg(song.freq / 1000)
            .arg(song.bit_rate)
            .arg(song.size / (1024 * 1024.0), 3, 'f', 2, '0')
            .arg(QTime(0, 0, 0, 0).addMSecs(song.duration).toString("mm:ss"));

    return qtext;
}
