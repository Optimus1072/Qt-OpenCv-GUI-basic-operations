#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;




class Player : public QThread
{
    Q_OBJECT

private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    QImage img;
    Mat binary;
    Mat RGBframe;
    int thresh; // threshold value to convert to Binary
    bool isBinary; // perform Thresholding operation or not
    Mat homo; // HomoGraphy matrix for warping
signals:
    void processedImage(const QImage &image);

protected:
    void run();
    void msleep(int ms);

public:

    //Constructor
   Player(QObject *parent = 0);

   //Destructor
   ~Player();
   //Load a video from memory
   bool loadVideo(string filename);

   void Play();
   void setHomography();

   void Stop();
   bool isBinaryTrue() const;
   void setBinaryTrue();
   void setBinaryFalse();
   void setThreshold(int val);
   Mat warp();
   bool isStopped() const;
};

#endif // PLAYER_H
