#ifndef TRACKINGMANAGER_H
#define TRACKINGMANAGER_H

#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;
using namespace cv;

class TrackingManager
{
public:
    char* wnd_name;
    Mat frame;
    TrackingManager();
    bool getFrame();
    void releaseCamera();
    void renderFrame();

private:
    VideoCapture *vc;
};

#endif // TRACKINGMANAGER_H
