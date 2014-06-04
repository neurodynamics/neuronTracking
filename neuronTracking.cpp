//#include <stdio.h>
#include <iostream>
#include <fstream>
#include "/home/helton/work/opencv-2.4.5/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "/home/helton/work/opencv-2.4.5/modules/nonfree/include/opencv2/nonfree/features2d.hpp"
#include "/home/helton/work/opencv-2.4.5/modules/calib3d/include/opencv2/calib3d/calib3d.hpp"
#include "cv.h"
#include "highgui.h"
#include "histogramH.h"
#include "functionsH.h"

using namespace cv;
using namespace std;

/*-- prototype of functions*/
void readme();

/*-- main*/
int main( int argc, char** argv ){
float timeS, timeE;
//string pathD = "/home/helton/Dropbox/uppsala/proj_jornal_neuro_figuras/dataset/NewData/exp0/experimento0/descriptors/desc1";

DECLARE_TIMING(myTimer);
//START_TIMING(myTimer);
/*-- step 0: Load two Imagens.*/
  if( argc != 7 )
  { readme(); return -1; }

/*read in gray*/
  Mat im1 = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE ); //image
  Mat im2 = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE ); //template

  if( !im1.data || !im2.data )
  { std::cout<< " --(!) Error reading images " << std::endl; return -1; }

/*-- Step 1: Detect the keypoints using SURF Detector */
/*and*/
/*-- Step 2: Calculate descriptors (feature vectors) */
  double mHeesian = 100; //Threshold for the keypoint detector.(qto menor mais pontos se pega)
  int gaussN=3, gaussL=5;
  bool up = false; //true is more fast

  SurfFeatureDetector detector(mHeesian,gaussN,gaussL,up); //declare SURF detector
  //SurfFeatureDetector *detector2; //declare SURF detector

  std::vector<KeyPoint> keyP1, keyP2; //declare vector

  detector.detect( im1, keyP1 );
  detector.detect( im2, keyP2 );

/*-- Step 2: Calculate descriptors (feature vectors) */
  SurfDescriptorExtractor extractor;  //declare SURF extractor, posso testar o sift!
	
  Mat desc1, desc2;
  extractor.compute( im2, keyP2, desc2 );
  
 /*-- Step 2-3: Matching descriptor vectors using FLANN matcher */
  FlannBasedMatcher matcher; //possotestar knnMatch and radiusMatch
  //FlannBasedMatcher matcher2;
  std::vector< DMatch > matches;
  //std::vector< vector<DMatch> > m;

  timeS = START_TIMING(myTimer);

  extractor.compute( im1, keyP1, desc1 ); 
  matcher.match( desc1, desc2, matches ); //match descriptors of the images
  //matcher.radiusMatch(desc1, desc2, m, 3);
  
  timeE = STOP_TIMING(myTimer);
  printf("Execution time: %f ms.\n", GET_TIMING(myTimer) );
  
double max_dist = 0; double min_dist = 100; // posso ajustar distancias menores para ROI
  /*-- Quick calculation of max and min distances between keypoints */
	for( int i = 0; i < desc1.rows; i++ )
	{ 
   		double dist = matches[i].distance;
		if( dist < min_dist ) 
			min_dist = dist;
		if( dist > max_dist ) 
			max_dist = dist;
	}

  printf("-- Max dist : %f \n", max_dist );
  printf("-- Min dist : %f \n", min_dist );

  /*-- Draw only "good" matches (distance is less than mult*min_dist ) */
  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
  double mult = 3;   //-- testar radiusMatch
  std::vector< DMatch > goodMatches;

  for( int i = 0; i < desc1.rows; i++ )
  { 
	//if( matches[i].distance < mult*min_dist )
	if( matches[i].distance < max_dist/mult )
    { goodMatches.push_back( matches[i]); }  //empilha as good matches
  }


/* -- step 4 start Draw only "good" matches */
  Mat img_matches;
  drawMatches( im1, keyP1, im2, keyP2,
               goodMatches, img_matches, Scalar::all(255), Scalar::all(255),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

//==============================================================================
/*
//-- Localize the object
  std::vector<Point2f> obj;
  std::vector<Point2f> scene;

  for( int i = 0; i < goodMatches.size(); i++ )
  {
    //-- Get the keypoints from the good matches
    obj.push_back( keyP1[ goodMatches[i].queryIdx ].pt );
    scene.push_back( keyP2[ goodMatches[i].trainIdx ].pt );
  }

  Mat H = findHomography( obj, scene, 0 );

  //-- Get the corners from the object to be "detected" 

  std::vector<Point2f> obj_corners(4);
  obj_corners[0] = cvPoint(0,0); 
  obj_corners[1] = cvPoint( im2.cols, 0 );
  obj_corners[2] = cvPoint( im2.cols, im2.rows );
  obj_corners[3] = cvPoint( 0, im2.rows );

  std::cout << "corners values" << std::endl;
  std::cout << obj_corners << std::endl;  

  std::vector<Point2f> scene_corners(4);
  perspectiveTransform( obj_corners, scene_corners, H);

  //-- Draw lines between the corners (the mapped object in the scene)
  line( img_matches, scene_corners[0] + Point2f( im2.cols, 0), scene_corners[1] + Point2f( im2.cols, 0), Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[1] + Point2f( im2.cols, 0), scene_corners[2] + Point2f( im2.cols, 0), Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[2] + Point2f( im2.cols, 0), scene_corners[3] + Point2f( im2.cols, 0), Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[3] + Point2f( im2.cols, 0), scene_corners[0] + Point2f( im2.cols, 0), Scalar( 0, 255, 0), 4 );
*/
//imshow( "Good Matches & Object detection", img_matches );

//===================================================================
/*  Mat img_matches;
  drawMatches( im1, keyP1, im2, keyP2,
               matches, img_matches, Scalar::all(255), Scalar::all(255),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
*/
  /* Show detected matches*/
  imshow( "Good Matches", img_matches );	

  /* draw keypoints */            
  drawKeypoints(im1, keyP1, im1, Scalar::all(255),
	DrawMatchesFlags::DEFAULT);
  //namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
  imshow( "Display window1", im1 ); 

  drawKeypoints(im2, keyP2, im2, Scalar::all(255),
	DrawMatchesFlags::DEFAULT);
  //namedWindow( "Display window2", CV_WINDOW_AUTOSIZE );
  imshow( "Display window2", im2 );         
	
/* Step 5 -- print and save log results*/
  ofstream myfile;
  myfile.open (argv[3]);


  for( int i = 0; i < (int)goodMatches.size(); i++ )
  { 
	printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, goodMatches[i].queryIdx, goodMatches[i].trainIdx );
	myfile << i << ' ' << goodMatches[i].queryIdx << ' ' << goodMatches[i].trainIdx << endl;

  }
	myfile.close();

// calcule histogram
/*
int hist;
IplImage* gray = cvLoadImage("template.jpg"); //just for histogram
hist = histogramH(gray);
*/
//--save keyponints, matches and good matches into file

  FileStorage fs1(argv[4], FileStorage::WRITE);
  write( fs1 , "keyP1", keyP1 );
  fs1.release();

  FileStorage fs2(argv[5], FileStorage::WRITE);
  write( fs2 , "desc1", desc1 );
  fs2.release();


/*
  FileStorage fs1("keyP1.yml", FileStorage::WRITE);
  write( fs1 , "keyP1", keyP1 );
  fs1.release();
 
  FileStorage fs2("keyP2.yml", FileStorage::WRITE);
  write( fs2 , "keyP2", keyP2 );
  fs2.release();
*/

/* storage time execution test (start and execution) */
	ofstream myfile2;
	myfile2.open (argv[6]);
	//myfile2 << timeE << endl;
	myfile2 << GET_TIMING(myTimer) << endl;

//DECLARE_TIMING(myTimer);
//START_TIMING(myTimer);
//printf("Hello!\n");


  waitKey(0);
  return 0;
}

//insert release memory on images

//======================================================================


//-- functions
void readme()
{ std::cout << " Usage: ./neuronTracking <img1> <img2>" << std::endl; }
