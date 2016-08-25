#include <iostream>
#include "trackingmanager.h"
#include "frameprocessor.h"
#include "objectprojector.h"
#include "glmanager.h"

#include <GL/glut.h>
#include <iostream>

using namespace std;

static void renderObject(void *param);

int main(int argc, char **argv)
{
    GlManager *glmanager = new GlManager();
    TrackingManager *tm = new TrackingManager();
    FrameProcessor *processor = new FrameProcessor();
    vector<vector<Point> > square;

    tm->getFrame();
    glmanager->glInit(argc, argv);

    setOpenGlDrawCallback(tm->wnd_name, GlManager::display, 0);

    while(tm->getFrame()){
        square = processor->process(&tm->frame);
        glmanager->render(tm->frame, square);
        updateWindow(tm->wnd_name);
        int key = waitKey(10);
        if(key == 27){
            tm->releaseCamera();
            break;
        }
    }
    setOpenGlDrawCallback(tm->wnd_name, NULL, NULL);

    return 0;
}

static void renderObject(void* param)
{
    glLoadIdentity();

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);

//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,320,240,0,GL_BGR,GL_UNSIGNED_BYTE, img.data);

    glColor3f (1.0, 1.0, 1.0);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
        glTranslated(0.0, 0.0, -1.0);

        glRotatef( 55, 1, 0, 0 );
        glRotatef( 45, 0, 1, 0 );
        glRotatef( 0, 0, 0, 1 );

        static const int coords[6][4][3] = {
            { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
            { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
            { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
            { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
            { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
            { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
        };

        for (int i = 0; i < 6; ++i) {
                    glColor3ub( i*20, 100+i*10, i*42 );
                    glBegin(GL_QUADS);
                    for (int j = 0; j < 4; ++j) {
                            glVertex3d(0.2 * coords[i][j][0], 0.2 * coords[i][j][1], 0.2 * coords[i][j][2]);
                    }
                    glEnd();
        }
}
