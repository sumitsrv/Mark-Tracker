#include "objectprojector.h"

ObjectProjector::ObjectProjector()
{
    objectPoints = this->generate3DPoint();
    rVec = new Mat(3, 1, DataType<double>::type); // Rotation vector
        rVec->at<double>(0) = 0;
        rVec->at<double>(1) = 0;
        rVec->at<double>(2) = 0;

    tVec = new Mat(3, 1, DataType<double>::type); // Translation vector
        tVec->at<double>(0) = 0;
        tVec->at<double>(1) = 0;
        tVec->at<double>(2) = 0;
}

void ObjectProjector::estimateObjectPose(vector<vector<Point> > square )
{
    Mat Rvec;
    Mat_<float> Tvec;
    Mat raux, taux;
//    solvePnP(square, square, noArray(), noArray(), Rvec, Tvec, false, ITERATIVE );
}

vector<Point3d> ObjectProjector::generate3DPoint()
{
    vector<Point3d> points;

       double x, y, z;

       x = 0.5; y = 0.5; z = -.5;
       points.push_back(Point3d(x, y, z));

       x = .5; y = .5; z = .5;
       points.push_back(Point3d(x, y, z));

       x = .5; y = -.5; z = -.5;
       points.push_back(Point3d(x, y, z));

       x = .5; y = -.5; z = .5;
       points.push_back(Point3d(x, y, z));

       x = -.5; y = .5; z = -.5;
       points.push_back(Point3d(x, y, z));

       x = -.5; y = .5; z = -.5;
       points.push_back(Point3d(x, y, z));

       x = -.5; y = -.5; z = -.5;
       points.push_back(Point3d(x, y, z));

       x = -.5; y = -.5; z = .5;
       points.push_back(Point3d(x, y, z));

       return points;
}

vector<Point2d> ObjectProjector::get2dOject()
{
    cv::Mat intrisicMat(3, 3, cv::DataType<double>::type); // Intrisic matrix
        intrisicMat.at<double>(0, 0) = 6.9578462764705978e+02;
        intrisicMat.at<double>(1, 0) = 0;
        intrisicMat.at<double>(2, 0) = 2.7640015131859042e+02;

        intrisicMat.at<double>(0, 1) = 0;
        intrisicMat.at<double>(1, 1) = 6.4525276774866654e+02;
        intrisicMat.at<double>(2, 1) = 1.8772630404046339e+02;

        intrisicMat.at<double>(0, 2) = 0;
        intrisicMat.at<double>(1, 2) = 0;
        intrisicMat.at<double>(2, 2) = 1;

    cv::Mat distCoeffs(5, 1, cv::DataType<double>::type);   // Distortion vector
        distCoeffs.at<double>(0) = 0;
        distCoeffs.at<double>(1) = 0;
        distCoeffs.at<double>(2) = 0;
        distCoeffs.at<double>(3) = 0;
        distCoeffs.at<double>(4) = 0;
    projectPoints(objectPoints, *rVec, *tVec, intrisicMat, distCoeffs, imagePoints);

    for (unsigned int i = 0; i < imagePoints.size(); ++i)
        {
            std::cout << "Image point: " << objectPoints[i] << " Projected to " << imagePoints[i] << std::endl;
        }
    return imagePoints;
}

void ObjectProjector::overlayObject(Mat frame, vector<vector<Point> > square)
{
//    Mat object(imagePoints);
    vector<Point> testpoints;
    testpoints.push_back(Point(100,100));
    testpoints.push_back(Point(50,50));
    testpoints.push_back(Point(80,80));
    testpoints.push_back(Point(120,120));
    testpoints.push_back(Point(30,30));
    testpoints.push_back(Point(110,110));
    testpoints.push_back(Point(130,130));
    testpoints.push_back(Point(180,180));
    vector<vector<Point2d> > testv;
    testv.push_back(imagePoints);
    Mat test(640, 480, 3);
  drawContours(test, testv, -1, Scalar(128,255,255), 3, CV_AA, noArray(), 10 );

//    const Point* tmp = {&testpoints};
    fillPoly(frame, testv, Scalar(255, 0 , 0 ,0), 8, 0, Point(0,0));
}

void ObjectProjector::drawSphere()
{
    int lats = 10;
    int longs = 10;

            int i, j;
            for(i = 0; i <= lats; i++) {
               double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
               double z0  = sin(lat0);
               double zr0 =  cos(lat0);

               double lat1 = M_PI * (-0.5 + (double) i / lats);
               double z1 = sin(lat1);
               double zr1 = cos(lat1);

               glBegin(GL_QUAD_STRIP);
               for(j = 0; j <= longs; j++) {
                   double lng = 2 * M_PI * (double) (j - 1) / longs;
                   double x = cos(lng);
                   double y = sin(lng);

                   glNormal3f(x * zr0, y * zr0, z0);
                   glVertex3f(x * zr0, y * zr0, z0);
                   glNormal3f(x * zr1, y * zr1, z1);
                   glVertex3f(x * zr1, y * zr1, z1);
               }
               glEnd();
           }
}

void ObjectProjector::sphereTexture()
{
    GLUquadricObj *sphere = NULL;
      sphere = gluNewQuadric();
      gluQuadricDrawStyle(sphere, GLU_FILL);
      gluQuadricTexture(sphere, true);
      gluQuadricNormals(sphere, GLU_SMOOTH);
      //Making a display list
      GLuint mysphereID = glGenLists(1);
      glNewList(mysphereID, GL_COMPILE);
      gluSphere(sphere, 1.0, 20, 20);
      glEndList();
      gluDeleteQuadric(sphere);
}

GLuint ObjectProjector::matToTexture(cv::Mat *mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
{
//    Texture2D *tex = new Texture2D(*mat, true);

    return 0;
//    // Generate a number for our textureID's unique handle
//    GLuint textureID;
//    glGenTextures(1, &textureID);

//    // Bind to our texture handle
//    glBindTexture(GL_TEXTURE_2D, textureID);

//    // Catch silly-mistake texture interpolation method for magnification
//    if (magFilter == GL_LINEAR_MIPMAP_LINEAR  ||
//        magFilter == GL_LINEAR_MIPMAP_NEAREST ||
//        magFilter == GL_NEAREST_MIPMAP_LINEAR ||
//        magFilter == GL_NEAREST_MIPMAP_NEAREST)
//    {
//        cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << endl;
//        magFilter = GL_LINEAR;
//    }

//    // Set texture interpolation methods for minification and magnification
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

//    // Set texture clamping method
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

//    GLenum inputColourFormat = GL_BGR;
//    if (mat->channels() == 1)
//    {
//        inputColourFormat = GL_LUMINANCE;
//    }

//    // Create the texture
//    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
//                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
//                 GL_RGB,            // Internal colour format to convert to
//                 mat->cols,          // Image width  i.e. 640 for Kinect in standard mode
//                 mat->rows,          // Image height i.e. 480 for Kinect in standard mode
//                 0,                 // Border width in pixels (can either be 1 or 0)
//                 inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
//                 GL_UNSIGNED_BYTE,  // Image data type
//                 mat->ptr());        // The actual image data itself

//    return textureID;
}

void ObjectProjector::draw(cv::Mat *camFrame)
{
    // Clear the screen and depth buffer, and reset the ModelView matrix to identity
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Move things back into the screen
    glTranslatef(0.0f, 0.0f, -8.0f);

    // Rotate around the y-axis
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    // Rotate around the x-axis
    static float rateOfChange = 0.01f;
    static float degreesToMoveThrough = 180.0f;
    glRotatef(0, 1.0f, 0.0f, 0.0f);

    // Rotate around the z-axis
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);

    // Quad width and height
    float w = 6.4f;
    float h = 4.8f;

    // Convert image and depth data to OpenGL textures
    GLuint imageTex = matToTexture(camFrame,   GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
//    GLuint depthTex = matToTexture(depthFrame, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP);

    // Draw the textures
    // Note: Window co-ordinates origin is top left, texture co-ordinate origin is bottom left.

    // Front facing texture
    glBindTexture(GL_TEXTURE_2D, imageTex);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex2f(-w/2,  h/2);
        glTexCoord2f(0, 1);
        glVertex2f( w/2,  h/2);
        glTexCoord2f(0, 0);
        glVertex2f( w/2, -h/2);
        glTexCoord2f(1, 0);
        glVertex2f(-w/2, -h/2);
    glEnd();

    // Back facing texture (facing backward because of the reversed the vertex winding)
//    glBindTexture(GL_TEXTURE_2D, depthTex);
//    glBegin(GL_QUADS);
//        glTexCoord2f(1, 1);
//        glVertex2f(-w/2,  h/2);
//        glTexCoord2f(1, 0);
//        glVertex2f(-w/2, -h/2);
//        glTexCoord2f(0, 0);
//        glVertex2f( w/2, -h/2);
//        glTexCoord2f(0, 1);
//        glVertex2f( w/2,  h/2);
//    glEnd();

//    glutSwapBuffers();
    // Free the texture memory
    glDeleteTextures(1, &imageTex);
//    glDeleteTextures(1, &depthTex);

    glDisable(GL_TEXTURE_2D);
}
