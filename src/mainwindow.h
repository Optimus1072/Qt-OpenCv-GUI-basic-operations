#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <player.h>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);
    void updatePlayerUI(QImage img);



    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Player *myPlayer;
};

#endif // MAINWINDOW_H
