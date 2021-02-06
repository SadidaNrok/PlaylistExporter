#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QStatusBar>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QProgressBar>
#include <QMenu>
#include <QMenuBar>
//#include <QUrl>
//#include <QFileInfo>

//#include <cmath>

#include "playlist.h"
//#include <QSound>
//#include <QtMultimedia>
//#include <QtMultimediaWidgets>
//#include <QMediaMetaData>
//#include <QMediaObject>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void f_open();
    void f_save_to();
    void f_save();
    void f_add();
    void f_delete();
    void f_up();
    void f_down();
    void f_show_message();
    //void f_list_changed(QModelIndexList*);
    //QString get_record(Song&);

    QLineEdit* le_open;
    QLineEdit* le_save_to;
    QPushButton* btn_open;
    QPushButton* btn_save_to;
    QGroupBox* group;
    QListWidget* list;
    QPushButton* btn_add;
    QPushButton* btn_delete;
    QPushButton* btn_up;
    QPushButton* btn_down;
    QCheckBox* sequence;
    QPushButton* btn_save;
    QProgressBar* progress;

    Playlist playlist;
    QString destination;
};
#endif // MAINWINDOW_H
