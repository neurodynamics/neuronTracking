/*
argv[1] - The destination image.
argv[2] - Source image to be blended over the destination image.
argv[3] and argv[4] - The (x,y) coordinate of the ROI in both the destination image and the source image to be blended.
argv[5] and argv[6] - Width and Height from the point (x,y) of the ROI.
argv[7] - Alpha, the weight of argv[1].
argv[8] - Beta, the weight of argv[2] to be blended over argv[1].
*/

#include <iostream>
#include <opencv2/highgui/highgui.hpp>

int main( int argc, char** argv ) {
	
    IplImage *img1, *img2, *dst;
	int gamma = 0; 					

    if( argc == 9 && ((img1=cvLoadImage(argv[1],1)) != 0
        )&&((img2=cvLoadImage(argv[2],1)) != 0))
        {
			// atoi~string to int, atof~string to double
            int x 		= atoi(argv[3]); 					
            int y 		= atoi(argv[4]);					
            int width 	= atoi(argv[5]);					
            int height	= atoi(argv[6]);					
            double alpha= (double)atof(argv[7]);			
            double beta = (double)atof(argv[8]);			
            
	    //openCv Operations
	    cvSetImageROI(img1, cvRect(x,y,width,height));
            cvSetImageROI(img2, cvRect(x,y,width,height));
	   //dst = img1*alpha + img2*beta + gamma;
            cvAddWeighted(img1, alpha, img2, beta, gamma, img1);
            cvResetImageROI(img1);        
			
	    //show results
	    cvNamedWindow( "Overlay", 1 ); 		
            cvShowImage( "Overlay", img1 ); 	
            cvWaitKey();
        }
    return 0;
}
