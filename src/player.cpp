#include "player.h"

Player::Player( QObject *parent) : QThread(parent)
{
        stop = true;
        isBinary = false;
        thresh = 0;
}



bool Player::loadVideo(string fileName)
{
    bool isOpen;
   isOpen =  capture.open(fileName);
    if(isOpen)
    {
        frameRate  = (int)capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void Player::Play()
{
    if(!isRunning())
    {
        if(isStopped())
        {
            stop = false;
        }
        start(LowPriority);
    }

}


void Player::setBinaryTrue()
{


    isBinary = true;
}

void Player::setBinaryFalse()
{

    isBinary = false;

}

void Player::setThreshold(int val)
{

    thresh =  val;

}

void Player::run()
{

    int delay = 1000 / frameRate;
    while(!stop )
    {

        if(!capture.read(frame))
            stop = true;
        // convert RGB to gray
        if(frame.channels() == 3)
        {
            if(thresh == 0)
             {
                cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);

             }
            else
            {
                Mat temp;
                cvtColor(frame, temp, CV_BGR2GRAY);
                threshold(temp, binary, thresh, 255, 0);
                //img = QImage((const unsigned char*)(binary.data),
//                                  binary.cols, binary.rows, QImage::Format_Indexed8);




                cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);

                //bool save = img.save("/home/tonbo/binary.png");

                 cout<<"threshold value = "<<thresh<<endl;

                //imshow("Binary", binary);
            }
         }
         else
         {
            if(thresh == 0) // original Image
            {
                img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);

            }
            else // convert to Binary Image
            {

                threshold(frame, binary, thresh, 255, 0);

                img = QImage((const unsigned char*)(binary.data),
                                  binary.cols, binary.rows, QImage::Format_Indexed8);
            }




         }

         emit processedImage(img);
         this->msleep(delay);
    }
}

// destructor
Player::~Player()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();

    wait();
}




void Player::Stop()
{
    stop = true;
}

 void Player::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);

}

bool Player::isStopped() const
{

    return (this->stop);
}


bool Player::isBinaryTrue() const
{

    return ( this->isBinary);
}
