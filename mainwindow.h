#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QTextStream>
#include <QStatusBar>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QFile>

#include <fstream>
#include <iostream>
#include <codecvt>
#include <cmath>
#include <numeric>
#include <functional>

#include "song.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void f_open();
    void f_save_to();
    void f_save();
    QString get_record(Song& song);

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

    Playlist playlist;
    QString source;
    QString destination;
};
#endif // MAINWINDOW_H
