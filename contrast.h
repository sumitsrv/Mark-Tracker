#ifndef CONTRAST_H
#define CONTRAST_H

#include "opencv/highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define alpha 0.8

using namespace cv;
using namespace std;

class Contrast
{
public:
    Contrast();
    void glg(Mat *img);
private:
    void mergeLevels(Mat *hist_glg, float *max_value, int *hist_size, float left[], float right[]);
    void lookUpTable(float *N, float left[], float right[], int *hist_size, float T[]);
};

#endif // CONTRAST_H
