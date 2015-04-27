#include <iostream>
#include "trackingmanager.h"
#include "frameprocessor.h"

using namespace std;

int main()
{
    TrackingManager *tm = new TrackingManager();
    FrameProcessor *processor = new FrameProcessor();

    while(tm->getFrame()){
        processor->process(&tm->frame);
        tm->renderFrame();
        int key = waitKey(10);
        if(key == 27){
            tm->releaseCamera();
            break;
        }
    }
    cout << "Hello World!" << endl;
    return 0;
}

