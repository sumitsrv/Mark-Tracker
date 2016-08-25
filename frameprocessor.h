#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include "opencv/highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>

#define FG 255
#define BG 0

using namespace std;
using namespace cv;

class FrameProcessor
{
public:
    FrameProcessor();
    vector<vector<Point> > process(Mat*);
private:
    vector<vector<Point> > findSquares4(Mat *, vector<Vec4i> *);
    double angle(Point *, Point *, Point *);
    void drawSquares(Mat *, vector<vector<Point> >, vector<Vec4i> );
    void remove_loose_ends(Mat *);
};

#endif // FRAMEPROCESSOR_H
