#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    myPlayer = new Player();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updatePlayerUI(QImage)));
    ui->setupUi(this);
}



//Play the video
void MainWindow::on_pushButton_clicked()
{
        if (myPlayer->isStopped())
        {
            myPlayer->Play();
            ui->pushButton->setText(tr("Stop"));
        }
        else
        {
            myPlayer->Stop();
            ui->pushButton->setText(tr("Play"));
        }

}

// Load the video
void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".",
                                                    tr("Video Files (*.avi *.mpg *.mp4)"));
    if (!filename.isEmpty())
    {
        if (!myPlayer->loadVideo(filename.toStdString()))
        {
            cout<<filename.toStdString()<<endl;

            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}
// will change the threshold
void MainWindow::on_spinBox_valueChanged(int arg1)
{
   myPlayer->setThreshold(arg1);
   myPlayer->Play();
}

void MainWindow::updatePlayerUI(QImage img)
{
    if(!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img.scaled(ui->label->size(),
                                  Qt::KeepAspectRatio, Qt::FastTransformation)));

    }

}

MainWindow::~MainWindow()
{

    delete myPlayer;
    delete ui;
}



