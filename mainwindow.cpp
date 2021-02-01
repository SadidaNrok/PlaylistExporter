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

    connect(m_quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(btn_open, &QPushButton::clicked, this, &MainWindow::f_open);
    connect(btn_save_to, &QPushButton::clicked, this, &MainWindow::f_save_to);
    connect(btn_save, &QPushButton::clicked, this, &MainWindow::f_save);
}

void MainWindow::f_open() {
    auto path = QFileDialog::getOpenFileName(nullptr,
                "Open Playlist", "", "Playlist files (*.aimppl4 *.PLC)");

    auto file = new QFile(path);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "File was not opened!");
        return;
    }

    QTextStream in(file);
    in.setCodec("UTF-16");

    playlist = Playlist(file);
    le_open->setText(path);

    while (!in.atEnd()) {
        QString line;
        line = in.readLine();

        Song song(line);
        if (!song.is_empty) {
            playlist.add(song);
            auto qtext = get_record(song);
            list->addItem(qtext);
            playlist.size += song.size;
            playlist.duration += song.duration;
        }
    }

    if (!le_save_to->text().isEmpty())
        btn_save->setEnabled(true);

    group->setEnabled(true);
    statusBar()->showMessage(QString("Playlist was loaded. Total size: %1 Mb, duration: %2")
            .arg(playlist.size / (1024.0 * 1024), 3, 'f', 2, '0' )
            .arg(QTime(0, 0, 0, 0).addMSecs(playlist.duration).toString("hh:mm:ss")));
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
    int degree = playlist.size / 100;

    for (auto& song : playlist) {
        auto file = new QFile(song.path);
        int zeros = log10(playlist.count()) + 1;
        bool copied = false;

        if (sequence->isChecked())
            copied = file->copy(QString("%1\\%2-%3")
                       .arg(destination)
                       .arg(song.number, zeros, 'g', -1, '0')
                       .arg(song.filename));
        else
            copied = file->copy(QString("%1\\%3")
                       .arg(destination)
                       .arg(song.filename));

        if (!copied) {
            QMessageBox::warning(this, "Warning", "File was not copied!");
            progress->setVisible(false);
            return;
        }

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
