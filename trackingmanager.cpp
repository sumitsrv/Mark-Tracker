#include "trackingmanager.h"

TrackingManager::TrackingManager()
{
    vc = new VideoCapture();
    if( !vc->isOpened() )
    {
        vc->set(CV_CAP_PROP_FPS, 30.0);
        vc->set(CV_CAP_PROP_FRAME_HEIGHT, 480.0);
        vc->set(CV_CAP_PROP_FRAME_WIDTH, 640.0);
        vc->open( CV_CAP_ANY );
    }
    namedWindow("Frame", WINDOW_NORMAL);
}

bool TrackingManager::getFrame()
{
    *vc >> frame;
    if(this->frame.empty()) {
        return false;
    }
    return true;
}

void TrackingManager::releaseCamera()
{
    vc->release();
}

void TrackingManager::renderFrame()
{
    imshow("Frame", frame);
}
