#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "/home/helton/work/OpenCV-2.4.1/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/nonfree/include/opencv2/nonfree/features2d.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/calib3d/include/opencv2/calib3d/calib3d.hpp"

#include "cv.h"
#include "highgui.h"


using namespace cv;
using namespace std;

double 	alpha = 1; 		/**< Simple contrast control */
int		beta  = 1;  	/**< Simple brightness control */
string  aa,bb;
string cc 	  = ".tif";

int main( int argc, char** argv )
{
 /// Read image given by user
 Mat image = imread( argv[1] );
 Mat new_image = Mat::zeros( image.size(), image.type() );

for (beta=1;beta<=100;beta++){   //insert 100 levels of beta
aa = static_cast<ostringstream*>( &(ostringstream() << beta) )->str();
bb = argv[2]+aa+cc;
cout << bb << endl;

 /// Initialize values
 /*
 std::cout<<" Basic Linear Transforms "<<std::endl;
 std::cout<<"-------------------------"<<std::endl;
 std::cout<<"* Enter the alpha value [1.0-3.0]: ";std::cin>>alpha;
 std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;
*/
 /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
for( int y = 0; y < image.rows; y++ ) { 
	for( int x = 0; x < image.cols; x++ ) {
		 for( int c = 0; c < 3; c++ ) {
      		new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
         }
	}
}

	/*write image*/
	imwrite(bb,new_image);	
}

	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// Wait until user press some key
	//waitKey();

return 0;
}
