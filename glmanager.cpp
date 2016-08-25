#include "glmanager.h"

GlManager::GlManager()
{
}

Mat GlManager::frame;
vector<vector<Point> > GlManager::square;

void GlManager::glInit(int argc, char** argv)
{
    glutInit( &argc, argv );
}

void GlManager::render(Mat img, vector<vector<Point> > sq)
{
    img.copyTo(frame);
    sq.swap(square);
    return;
}

void GlManager::display(void *)
{
    Point2f center;
    float radius;

    glClear( GL_DEPTH_BUFFER_BIT );

    Mat tempimage;
    flip(frame, tempimage, 0);
    glDrawPixels( tempimage.cols, tempimage.rows, GL_BGR, GL_UNSIGNED_BYTE, tempimage.data );

    if(square.at(0).size() == 4){
        minEnclosingCircle(square.at(0), center, radius);
        int glCenterX = center.x ;
        int glCenterY = tempimage.rows - center.y ;
        int viewRadius = radius;
        glViewport(glCenterX - viewRadius, glCenterY - viewRadius , viewRadius * 2 , viewRadius * 2 );
    }
    else {
        glViewport(0, 0, tempimage.cols, tempimage.rows);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glPushMatrix();
    int th2, ph2, i, j, k;
    int DEF_D = 5;

    for (ph2=-90;ph2<90;ph2+=DEF_D) {
        glBegin(GL_LINE_STRIP);
        for (th2=0;th2<=360;th2+=2*DEF_D) {
            glColor3f(0.0,1.0,0.0); //green
            vertex(th2,ph2);
            glColor3f(0.0,0.0,1.0); //blue
            vertex(th2,ph2+DEF_D);
        }
        glEnd();
    }
    glPopMatrix();

}

void GlManager::vertex(double th2,double ph2)
{
    double x = Sin(th2)*Cos(ph2);
    double y = Cos(th2)*Cos(ph2);
    double z =          Sin(ph2);
    glVertex3d(x,y,z);
}
