#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <iostream>
#include <GL/glut.h>
#include "opencv/highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

using namespace cv;
using namespace std;

class GlManager
{
private:
    static Mat frame;
    static vector<vector<Point> > square;
    static void reshape(int w, int h);
    static void idle();

    void sphereTexture();
    static void vertex(double th2, double ph2);
public:
    GlManager();
    void glInit(int , char **);
    void render(Mat , vector<vector<Point> >);
    static void display(void*);

};

#endif // GLMANAGER_H
