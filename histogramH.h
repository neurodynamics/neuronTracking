// functions to calc and draw RGB histogram

#include "/home/helton/work/OpenCV-2.4.1/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/nonfree/include/opencv2/nonfree/features2d.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/calib3d/include/opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// draw histogram

IplImage* DrawHistogram(CvHistogram *hist, float scaleX=1, float scaleY=1){

	float histMax = 0;
    cvGetMinMaxHistValue(hist, 0, &histMax, 0, 0);
	IplImage* imgHist = cvCreateImage(cvSize(256*scaleX, 64*scaleY), 8 ,1);
    cvZero(imgHist);
		for(int i=0;i<255;i++){
        	float histValue = cvQueryHistValue_1D(hist, i);
        	float nextValue = cvQueryHistValue_1D(hist, i+1);
 
        	CvPoint pt1 = cvPoint(i*scaleX, 64*scaleY);
        	CvPoint pt2 = cvPoint(i*scaleX+scaleX, 64*scaleY);
        	CvPoint pt3 = cvPoint(i*scaleX+scaleX, (64-nextValue*64/histMax)*scaleY);
        	CvPoint pt4 = cvPoint(i*scaleX, (64-histValue*64/histMax)*scaleY);
 
        	int numPts = 5;
        	CvPoint pts[] = {pt1, pt2, pt3, pt4, pt1};
 
        	cvFillConvexPoly(imgHist, pts, numPts, cvScalar(255));
    	}
return imgHist;
}


// calc histogram
int histogramH(IplImage *img){
	
	//inicialize with 256 bins
    int numBins = 256;
    float range[] = {0, 255};
    float *ranges[] = { range };
 	
	//create histogram object
    CvHistogram *hist = cvCreateHist(1, &numBins, CV_HIST_ARRAY, ranges, 1);
    cvClearHist(hist);

	//create channels RGB
	IplImage* imgRed = cvCreateImage(cvGetSize(img), 8, 1);
    IplImage* imgGreen = cvCreateImage(cvGetSize(img), 8, 1);
    IplImage* imgBlue = cvCreateImage(cvGetSize(img), 8, 1);
 
    cvSplit(img, imgBlue, imgGreen, imgRed, NULL);
	
	//calc histograms
    cvCalcHist(&imgRed, hist, 0, 0);
    IplImage* imgHistRed = DrawHistogram(hist);
    cvClearHist(hist);

	cvCalcHist(&imgGreen, hist, 0, 0);
    IplImage* imgHistGreen = DrawHistogram(hist);
    cvClearHist(hist);
 
    cvCalcHist(&imgBlue, hist, 0, 0);
    IplImage* imgHistBlue = DrawHistogram(hist);
    cvClearHist(hist);

	// Display histograms results
	
	cvNamedWindow("Image");
	cvNamedWindow("Red");
    cvNamedWindow("Green");
    cvNamedWindow("Blue");

	cvShowImage("Image", img);
    cvShowImage("Red", imgHistRed);
    cvShowImage("Green", imgHistGreen);
    cvShowImage("Blue", imgHistBlue);

//    cvWaitKey(0);

return 0;
}
