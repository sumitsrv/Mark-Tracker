#include "frameprocessor.h"

FrameProcessor::FrameProcessor()
{
}

void FrameProcessor::process(Mat *frame)
{
    vector<Vec4i> hierarchy;
    drawSquares(frame, findSquares4(frame, &hierarchy), hierarchy);
}

double FrameProcessor::angle( Point* pt1, Point* pt2, Point* pt0 )
{
    double dx1 = pt1->x - pt0->x;
    double dy1 = pt1->y - pt0->y;
    double dx2 = pt2->x - pt0->x;
    double dy2 = pt2->y - pt0->y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

vector<vector<Point> > FrameProcessor::findSquares4( Mat* img, vector<Vec4i> *hierarchy)
{
    vector<vector<Point> > contours;
    vector<vector<Point> > result;
    vector<vector<Point> > squares;

    int i, c, l, N = 20;
    CvSize sz = cvSize( img->cols & -2, img->rows & -2 );
    Mat timg = img->clone();
    Mat extimg = img->clone();

    cvtColor(extimg, timg, CV_BGR2HSV);
    Mat* gray = new Mat( sz, 8, 1 );
    Mat* tgray;

    double s, t, ang[4];

    // select the maximum ROI in the image
    // with the width and height divisible by 2
    timg.adjustROI(0, 0, sz.width, sz.height);

    tgray = new Mat( sz, 8, 1 );

    long maxArea = 0;
    vector<Point> largestContour;

    // find squares in every color plane of the image
    for( c = 3; c < 4; c++ )
    {
        // extract the c-th color plane
        if(c<3)
        {
            mixChannels(extimg, *tgray, {c, 0} );
        }
        else
        {
            cvtColor(extimg, *tgray, CV_BGR2GRAY);
        }
        // try several threshold levels
        for( l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading

            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny( *tgray, *gray, 50, 200, 3 );
                //                remove_loose_ends(gray);
            }
            else
            {
                // apply threshold if l!=0:
                threshold( *tgray, *gray, (l+1)*255/N, 255, CV_THRESH_BINARY );
                remove_loose_ends(gray);
            }
            // find contours and store them all as a list
            findContours( *gray, contours, *hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
            result.resize(contours.size());
            // test each contour

            for( size_t k = 0; k < contours.size(); k++ )
            {
                approxPolyDP( Mat(contours[k]), result[k], 20, true );
                int area = contourArea(result[k], false);

                if(area < maxArea){
                    continue;
                }

                if( result[k].size() == 4 && area > 400 && area < 100000 && isContourConvex(result[k]) ) {
                    s=0;
                    ang[0] = 0, ang[1] = 0, ang[2] = 0, ang[3] = 0 ;
                    for( i = 0; i < 4; i++ ) {
                        // find minimum angle between joint
                        // edges (maximum of cosine)
                        if( i >= 2 ) {
                            t = fabs(angle(&result[k].at(i),&result[k].at(i-2),&result[k].at(i-1)));
                        } else {
                            t = fabs(angle(&result[k].at(i),&result[k].at((i+2)%4),&result[k].at((i+3)%4)));
                        }
                        s = s > t ? s : t;
                        ang[i] = t;
                    }

                    // vertices to resultant sequence
                    if( s < 0.2 ) {
                        maxArea = area;
                        largestContour.swap(result[k]);
                    }
                }
            }
        }
    }

    squares.push_back(largestContour);

    gray->release();
    tgray->release();
    timg.release();
    extimg.release();
    return squares;
}

void FrameProcessor::drawSquares( Mat* img, vector<vector<Point> > squares, vector<Vec4i> hierarchy)
{
    drawContours( *img, squares, -1, Scalar(128,255,255), 3, CV_AA, hierarchy, 10 );
}

void FrameProcessor::remove_loose_ends(Mat* canny)
{
    if(canny->empty()) {
        return;
    }
    Mat clone = canny->clone();
    uchar* data= (uchar*)canny->data;
    uchar* cldata= (uchar*)clone.data;

    int height = canny->rows;
    int width = canny->cols;
    int step= width * canny->channels();

    int i, j, k, count = 0;

    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            count = 0;
            if(data[i*step + j] == BG)
            {
                for(k=-1; k<2; k++)
                {
                    if(cldata[(i+k)*step + (j+k)] == BG)
                    {
                        count++;
                    }
                    if(cldata[i*step +j+k] == BG)
                    {
                        count++;
                    }
                    if(cldata[(i+k)*step +j] == BG)
                    {
                        count++;
                    }
                }
                //printf("%d\t",count);
                if(count <4)
                    data[i*step + j] = FG;
            }

        }
    }
    clone.release();
}
