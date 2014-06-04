#include "cv.h"
#include <iostream>
#include "/home/helton/work/OpenCV-2.4.1/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/nonfree/include/opencv2/nonfree/features2d.hpp"
#include "/home/helton/work/OpenCV-2.4.1/modules/calib3d/include/opencv2/calib3d/calib3d.hpp"

int main( int argc, char** argv ) {
    IplImage *src1, *src2;
    if( argc == 9 && ((src1=cvLoadImage(argv[1],1)) != 0
        )&&((src2=cvLoadImage(argv[2],1)) != 0))
        {
            int x = atoi(argv[3]);
            int y = atoi(argv[4]);
            int width = atoi(argv[5]);
            int height = atoi(argv[6]);
            double alpha = (double)atof(argv[7]);
            double beta = (double)atof(argv[8]);
            cvSetImageROI(src1, cvRect(x,y,width,height));
            cvSetImageROI(src2, cvRect(x,y,width,height));
            cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
            cvResetImageROI(src1);
            cvNamedWindow( "Alpha_blend", 1 );
            cvShowImage( "Alpha_blend", src1 );
            cvWaitKey();
        }
    return 0;
}

/*
argv[1] - The destination image.
argv[2] - Source image to be blended onto the destination image.
argv[3], argv[4] - The (x,y) coordinate of the ROI in both the
                   destination image and the source image to be blended.
argv[5], argv[6] - Width and Height from the point (x,y) of the ROI.
argv[7] - Alpha, the weight of argv[1].
argv[8] - Beta, the weight of argv[2] to be blended onto argv[1].
*/
