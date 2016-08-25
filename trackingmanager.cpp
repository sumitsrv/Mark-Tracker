#include "trackingmanager.h"

TrackingManager::TrackingManager()
{
    wnd_name = "MarkTracker";
    vc = new VideoCapture();
    if( !vc->isOpened() )
    {
        vc->set(CV_CAP_PROP_FRAME_HEIGHT, 480.0);
        vc->set(CV_CAP_PROP_FRAME_WIDTH, 640.0);
        vc->open( CV_CAP_ANY );
    }
    namedWindow(wnd_name, CV_WINDOW_OPENGL | CV_WINDOW_AUTOSIZE);
    resizeWindow(wnd_name, vc->get(CV_CAP_PROP_FRAME_WIDTH), vc->get(CV_CAP_PROP_FRAME_HEIGHT));
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
    imshow(wnd_name, frame);
}
