#ifndef DETECTIONCLASS_H
#define DETECTIONCLASS_H

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

class DetectionClass
{
    public:
        //Variables
        Point center;
        //constructor destructor
        DetectionClass();
        virtual ~DetectionClass();
        //functions
        Point getCenter(int width, int height, int x, int y);
        vector<RotatedRect>  detectRoi(Mat filtered);
        void drawRoi(vector<RotatedRect>  Roi, int RoiIndex);
        Mat filterRed(void);
        Rect detectCup(vector<RotatedRect>  Rois);
        Rect detectTop(void);
        Rect biggestROI(vector<RotatedRect>  Rois);
        void getPhoto(void);
        int calibrateAt50cm(int PerceivedHeight);
        int calibrateAt100cm(int PerceivedHeight);
        int calibrateAt150cm(int PerceivedHeight);
        int calculateDistance(int perceivedHeight);
        //Mat photo;
        
    protected:
    //Variables

    //functions

    private:
    //Variables
    const int actualHeight = 10000;
    const int focalLength = 10000; 
    CascadeClassifier frontofcup_cascade;
    CascadeClassifier topofcup_cascade;
    Mat photo;

    //functions
    Rect getRect(Point2f rect_points[4]);
};

#endif // DETECTIONCLASS_H
