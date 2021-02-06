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
    btn_add = new QPushButton("+");
    btn_delete = new QPushButton("-");
    btn_up = new QPushButton("U");
    btn_down = new QPushButton("D");
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
    connect(btn_delete, &QPushButton::clicked, this, &MainWindow::f_delete);
    connect(btn_up, &QPushButton::clicked, this, &MainWindow::f_up);
    connect(btn_down, &QPushButton::clicked, this, &MainWindow::f_down);
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

    playlist = Playlist(file);
    le_open->setText(path);
    int num = 1;

    for (const auto& song : playlist) {
        auto item = new QListWidgetItem(list);
        item->setSizeHint(QSize(250, 40));
        list->setItemWidget(item, new SongWidget(song, num));
        ++num;
    }

    if (le_save_to->text().isEmpty()) {
        le_save_to->setText(playlist.path);
        group->setEnabled(true);
        btn_save->setEnabled(true);
    }

    file->close();
    f_show_message();
}

void MainWindow::f_save_to() {
    auto path = QFileDialog::getExistingDirectory(nullptr, tr("Choose folder"), "", QFileDialog::ShowDirsOnly);
    destination = path;
    le_save_to->setText(path);

    if (!le_open->text().isEmpty())
        btn_save->setEnabled(true);
}

void MainWindow::f_save() {
    if (QMessageBox::question(nullptr, tr("Save files"),
        QString(tr("Are you sure you want to copy all files to the folder: \n%1"))
            .arg(destination), QMessageBox::Cancel | QMessageBox::Yes)
            == QMessageBox::Cancel)
        return;

    progress->setValue(0);
    progress->setVisible(true);
    int ready = 0;
    int degree = playlist.full_size / 100;
    int zeros = log10(playlist.count()) + 1;
    int num = 1;

    auto answer = QMessageBox::No;
    for (const auto& song : playlist) {
        auto file = new QFile(song.path);

        bool copied = false;
        QString new_filename;
        if (sequence->isChecked())
            new_filename = QString("%1\\%2-%3")
                           .arg(destination)
                           .arg(num, zeros, 'g', -1, '0')
                           .arg(song.filename);
        else
            new_filename = QString("%1\\%3")
                           .arg(destination)
                           .arg(song.filename);

        if (answer == QMessageBox::YesAll)
            QFile(new_filename).remove();
        copied = file->copy(new_filename);

        if (!copied) {
            if (answer != QMessageBox::YesAll) {
                answer = QMessageBox::question(nullptr, "Warning",
                                      "Perhaps files with names from the playlist"
                                      "\nalready exist in the destination folder."
                                      "\nOverwrite them?",
                                      QMessageBox::YesAll | QMessageBox::Cancel);

                if (answer == QMessageBox::Cancel) {
                    progress->setVisible(false);
                    return;
                }
                else {
                    QFile(new_filename).remove();
                    file->copy(new_filename);
                }
            }
        }
        ready += song.size;
        progress->setValue(ready / degree);
        ++num;
    }
    progress->setVisible(false);
}

void MainWindow::f_delete() {
    playlist.del(list->currentRow());
    delete list->takeItem(list->currentRow());
    int num = list->currentRow() + 1;
    for (int i = list->currentRow(); i < list->count(); ++i) {
        auto item = list->item(i);
        auto wid = static_cast<SongWidget*>(list->itemWidget(item));
        wid->number->setText(QString::number(num));
        ++num;
    }
    f_show_message();
}

void MainWindow::f_up() {
    auto row = list->currentRow();
    if (row == 0)
        return;

    delete list->takeItem(row);
    auto item = new QListWidgetItem();
    item->setSizeHint(QSize(250, 40));
    list->insertItem(row - 1, item);
    list->setCurrentItem(item);
    list->setItemWidget(item, new SongWidget(playlist[row], row));
    SongWidget* pp = static_cast<SongWidget*>(list->itemWidget(list->item(row)));
    pp->number->setText(QString::number(row + 1));

    std::swap(playlist[row], playlist[row - 1]);
}

void MainWindow::f_down() {
    auto row = list->currentRow();
    if (row == list->count() - 1)
        return;

    delete list->takeItem(row);
    auto item = new QListWidgetItem();
    item->setSizeHint(QSize(250, 40));
    list->insertItem(row + 1, item);
    list->setCurrentItem(item);
    list->setItemWidget(item, new SongWidget(playlist[row], row + 2));
    SongWidget* pp = static_cast<SongWidget*>(list->itemWidget(list->item(row)));
    pp->number->setText(QString::number(row + 1));

    std::swap(playlist[row], playlist[row + 1]);
}

void MainWindow::f_show_message() {
    statusBar()->showMessage(QString("The size of the loaded playlist: %1 Mb, duration: %2")
            .arg(playlist.full_size / (1024.0 * 1024), 3, 'f', 2, '0' )
            .arg(QTime(0, 0, 0, 0).addMSecs(playlist.duration).toString("hh:mm:ss")));
}
