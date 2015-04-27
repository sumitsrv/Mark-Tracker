#ifndef TRACKINGMANAGER_H
#define TRACKINGMANAGER_H

#include "opencv2/core/core.hpp"
#include "opencv/highgui.h"

using namespace std;
using namespace cv;

class TrackingManager
{
public:
    Mat frame;
    TrackingManager();
    bool getFrame();
    void releaseCamera();
    void renderFrame();

private:
    VideoCapture *vc;
};

#endif // TRACKINGMANAGER_H
