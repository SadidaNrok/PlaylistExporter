#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include "song.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

private:
    void open_fun();
    QString text_build(Song& song);

    QPushButton* open_pl;
    QPushButton* save_pl;
    QPushButton* save_files;
    QPushButton* exit_app;

    QListWidget* list;

    QPushButton* add_file;
    QPushButton* delete_file;
    QPushButton* move_up;
    QPushButton* move_down;

    Playlist playlist;
};
#endif // MAINWINDOW_H
