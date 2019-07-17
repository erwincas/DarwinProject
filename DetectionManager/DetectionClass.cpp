#include "DetectionClass.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;
using namespace cv;

/*
 * @brief Constructor of the DetectionClass class
 *  
 * In this function the Haar cascades will be loaded in, a picture will be taken and the center
 * of the picture will be calculated.
 */
DetectionClass::DetectionClass()
{
    //constructor
    
    this->frontofcup_cascade.load("/home/robotis/Project/Herassessment/DetectionManager/cascades/frontofcupcascade.xml");
    if(frontofcup_cascade.empty() )
     {
      cerr<<"Error Loading Cascades"<<endl;
     }

}

/*
 * @brief Function for calculating the center of a rectangle
 * 
 * @param width the width of the rectangle
 * @param height the height of the rectangle
 * @param x the horizontal offset
 * @param y the vertical offset
 *
 * @return Point
 */
Point DetectionClass::getCenter(int width, int height, int x, int y) {
        //Get center of rectangle +its x and y position to return the center of the rectangle within the image
        return Point((width/2+x),(height/2+y)) ;

}

/*
 * @brief Function for taking a picture from the standard camera on Darwin
 * 
 * This function will open the videocapture on the standard camera and save a frame
 * to the photo variable in this class. If it fails to do so, it will throw an error
 *
 * @return void
 */
void DetectionClass::getPhoto(void) {

    VideoCapture cap; //open videocapture from standard camera
    if(!cap.open(0))
    {
        cerr<<"Failed to open camera"<<endl;
    }
    cap >> this->photo; //set frame as photo
    cap.release(); //stop capturing
}

/*
 * @brief Function for filtering out all the red shades in a picture 
 *
 * This function will take the photo taken in the init class and put it through multiple masks.
 * This way the function will cover multiple shades of red, effectively increasing the results.
 * 
 * @return Mat
 */
Mat DetectionClass::filterRed(void) {
    //Declare masks
    Mat red;
    Mat mask2;
    Mat mask3;
    Mat mask4;

    //Set masks to cover different shades of red
    inRange(this->photo, Scalar(0, 0, 185), Scalar(140, 140, 255), red);
    inRange(this->photo, Scalar(0, 0, 140), Scalar(100, 100, 255), mask2);
    inRange(this->photo, Scalar(0, 0, 120), Scalar(70, 70, 255), mask3);
    inRange(this->photo, Scalar(0, 0, 85), Scalar(45, 45, 255), mask4);

    //Combine masks
    red = red | mask2 | mask3 | mask4;

    //Set rate of erosion
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(6,6));
    //Set rate of Dilation
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(41,41));

    //Erode to filter out small red spots
    erode (red, red, erodeElement);
    //Dilate to make red spots easily findable
    dilate(red, red,dilateElement);

    //Return filtered mask
    return red;
}


/*
 * @brief Function for finding the region of interest using the contours of the matrix containing the filtered frame
 *
 * @param filtered the matrix of the filtered frame
 *
 * @return Vector array of type RotatedRect
 */
vector<RotatedRect> DetectionClass::detectRoi(Mat filtered) {
    //declare countour points
    vector<vector<Point> > contours;
    //find contours in filtered mask RETR external to only get outer contours, APPROX simple to get only the endpoints of the countours
    findContours( filtered, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    //declare rotated rectangles
    vector<RotatedRect> Rois( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
     {
      //get minimalrectangle for each of the found contours
        Rois[i] = minAreaRect( Mat(contours[i]) );
     }
     //return regions of interest
     return Rois;
}

/*
 * @brief Function for drawing the region of interest on a frame. Only used for testing.
 *
 * @param Roi vector array of type RotatedRect
 * @param RoiIndex the index of the RotatedRect in the vector array
 *
 * @return void
 */
void DetectionClass::drawRoi(vector<RotatedRect> Roi, int RoiIndex) {

   Point2f rect_points[4]; Roi[RoiIndex].points( rect_points );//get points of region of interest

   for( int j = 0; j < 4; j++ )
   {
      //draw rectangle
      line( this->photo, rect_points[j], rect_points[(j+1)%4], Scalar(0, 255, 0), 2, 8 );
   }

}

/*
 * @brief Function for getting a rectangle out of 4 2D points.
 * 
 * @param rect_points[] array containing 4 2d points
 * 
 * @return Rectangle
 */
Rect DetectionClass::getRect(Point2f rect_points[4]) {

    Rect rectangle = Rect(0,0,0,0); //declare rectangle

    //declare largest y/x, smallest y/x,
    int ly = 0;
    int sy = 0;
    int lx = 0;
    int sx = 0;

    //find largest y/x, smallest y/x,
    for( int j = 0; j < 4; j++ )
    {
        if(rect_points[j].y > ly || ly==0)
        {
            ly=rect_points[j].y;
        }
        if(rect_points[j].y < sy || sy==0)
        {
            sy=rect_points[j].y;
        }

        if(rect_points[j].x > lx || lx==0)
        {
            lx=rect_points[j].x;
        }
        if(rect_points[j].x < sx || sx==0)
        {
            sx=rect_points[j].x;
        }
    }

    //calculate difference between largest and smallest x/y to get width/height in pixels
    int difx = lx - sx;
    int dify = ly - sy;


    //if rectangle is not 0 and is smaller than size of photo set rectangle
    if((sx > 0 && sy > 0)&& ((sx+difx)<this->photo.size().width && (sy+dify) < this->photo.size().height))
    {
      rectangle = Rect(sx,sy,difx,dify);
    }
    //return rectangle
    return rectangle;

}

/*
 * @brief Function for detecting the cup. Uses all the functionality above.
 * 
 * @param Rois vector array of type RotatedRect
 *
 * @return Rectangle containing the region of the cup
 */
Rect DetectionClass::detectCup(vector<RotatedRect> Rois) {
    //declare cupheight variable , rectangle for possible cup
    int cupHeight=0;
    Rect cup = Rect(-1,-1,-1,-1);
    //per Roi filter cup, filter biggest cup
    for(int i=0; i < Rois.size(); i++)
    {
        Point2f rect_points[4]; Rois[i].points( rect_points );//get points of region of interest

        Rect roi_rectangle = getRect(rect_points);//get rectangle of these points


        Mat ROI(this->photo, roi_rectangle);//cut roi from photo

        vector<Rect> cups;

        this->frontofcup_cascade.detectMultiScale(ROI, cups); //check if roi contains cup

        //if so compare to earlier found cup or standard values to eventually return the closest cup (biggest in photo)
        if(0 < cups.size())
        {
            int roiCupHeight  = roi_rectangle.height;
            if(roi_rectangle.width > roi_rectangle.height)
            {
                roiCupHeight = roi_rectangle.width;
            }
            if(roiCupHeight > cupHeight)
            {
                cup = roi_rectangle;
            }

        }

    }

    return cup;

}

/*
 * @brief Function for detecting the biggest Region of interest
 * 
 * @param Rois vector array of type RotatedRect
 *
 * @return Rectangle containing the region of the biggest Region of interest
 */


Rect DetectionClass::biggestROI(vector<RotatedRect> Rois) {
    //declare cupheight variable , rectangle for possible cup
    int ROIHeight=0;
    Rect biggestROI = Rect(-1,-1,-1,-1);
    //per Roi filter cup, filter biggest cup
    for(int i=0; i < Rois.size(); i++)
    {
        Point2f rect_points[4]; Rois[i].points( rect_points );//get points of region of interest

        Rect roi_rectangle = getRect(rect_points);//get rectangle of these points
   
        int curROIHeight  = roi_rectangle.height;//set height of current roi to height of the rectangle of the roi

        if(roi_rectangle.width > roi_rectangle.height)//if width is bigger than height set current height to width to match the heigt of a possibly turnedobject
        {
            curROIHeight = roi_rectangle.width;
        }
        if(curROIHeight > ROIHeight)//compare the height of the current ROI with the current biggest ROI if bigger current becomes biggest ROI
        {
            biggestROI = roi_rectangle;
        }

    }
    //return biggest roi
    return biggestROI;

}

/*
 * @brief Function for getting the focal length for calculating distance using triangle equality
 * 
 * @param int perceived height of object, int actual distance to object
 *
 * @return int focalLength that can be used to calculate the distance to an object
 */

int DetectionClass::calibrate(int PerceivedWidth, int distance)
    {
        int focalLength;

        focalLength = (PerceivedWidth*distance)/this->actualWidth;
        return focalLength;
    }

/*
 * @brief Function for calculating the distance to an object using triangle equality
 * 
 * @param int perceived height of the object
 *
 * @return int distance containing the calculated distance to the object
 */
int DetectionClass::calculateDistance(int perceivedWidth)
    {
        int distance = 0;
        
        distance = ((this->focalLength*this->actualWidth)/perceivedWidth);
        return distance;
    }



DetectionClass::~DetectionClass()
{
    //destructor
}
