#ifndef OBJECTPROJECTOR_H
#define OBJECTPROJECTOR_H

#include "opencv/highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <GL/glut.h>

using namespace std;
using namespace cv;
using namespace ogl;

class ObjectProjector
{
private:
     vector<Point3d> objectPoints;
     vector<Point2d> imagePoints;
     Mat *rVec, *tVec;

public:
    ObjectProjector();
    void estimateObjectPose(vector<vector<Point> > square);
    vector<Point2d> get2dOject();
    vector<Point3d> generate3DPoint();
    void overlayObject(Mat frame, vector<vector<Point> > square);

    void draw(Mat *camFrame);
    GLuint matToTexture(Mat *mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter);
    void sphereTexture();
    void drawSphere();
};

#endif // OBJECTPROJECTOR_H
