#include <iostream>
#include <string>
#include <fstream>
#include "/home/helton/work/OpenCV-2.4.1/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/nonfree/include/opencv2/nonfree/features2d.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/calib3d/include/opencv2/calib3d/calib3d.hpp"
//http://opencv.willowgarage.com/documentation/cpp/imgproc_image_filtering.html#GaussianBlur

#include "cv.h"
#include "highgui.h"

using namespace cv;
using namespace std;

/// Global Variables
Mat src; Mat dst;
string  aa,bb;
string cc 	  = ".tif";
int i;


/* function main */
int main( int argc, char** argv ){


for (i=1;i<=100;i=i+2){
	aa = static_cast<ostringstream*>( &(ostringstream() << i) )->str();
	bb = argv[2]+aa+cc;
	cout << bb << endl;


	/// Load the source image
	src = imread(argv[1], 1 );
	dst = src.clone();

	/// Applying Gaussian blur
    GaussianBlur(src, dst, Size(1,i), 0, 0 ); // size means kernel size

	// write images
	//imwrite(argv[2],dst);
    imwrite(bb,dst);
}

    //waitKey(0);
    return 0;
}
