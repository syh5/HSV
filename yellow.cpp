#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"    
#include <vector> 
#include <numeric>


using namespace cv;
using namespace std;


int main( int argc, char** argv )
{

///////////////////////////////////////////////////////// Uncomment here for videocapture
/*
  cv::VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
        //return -1;
*/

///////////////////////////////////////////////////////// Uncomment here for videocapture

//  while(cap.isOpened())	//////////////////////// Uncomment here for videocapture
	{
	  	try
		{    	
		       
		      	Mat image;
			//cap >> image; // get a new frame from camera
			//resize(image,image,size);
		      	
			Mat hsvImg, detected_edges,binaryMat,binaryMat2;// new blank image
			image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);// read the file
		 
			namedWindow( "Display window1", CV_WINDOW_NORMAL );
			resizeWindow("Display window1",640,480);

			cvtColor(image, hsvImg, CV_BGR2HSV);

			inRange(hsvImg,Scalar(0,167,227),Scalar(42,255,255),binaryMat); // HSV values for the given yellow color which can be calibrated

			vector<Point2f> points;
		    	//threshold(tImg, binaryMat, 100, 255, cv::THRESH_BINARY);	// Use threshold if needed

			Mat nonZeroCoordinates;
		    	findNonZero(binaryMat, nonZeroCoordinates);			// Find non zero to extrapolate a line
			//cout<< nonZeroCoordinates.rows << endl;
			  if (nonZeroCoordinates.rows < 100)
			  {
		 		throw std::exception();
			  }
			 
		 	  cv::Vec<float,4> scene_output;
			  fitLine(nonZeroCoordinates, scene_output, CV_DIST_L2, 0, 0.01, 0.01);	// Fit line using the non zero coordinates
				
			  float slope = scene_output[1]/scene_output[0] ;		// Calculate slope, x-intercept and y-intercept for distance calculation
			  float y_intercept = scene_output[3] - slope * scene_output[2];
			  float x_intercept = -(y_intercept/slope);

		      	///////////////////////////////////////////////////// Uncomment for getting distance to the boundary
			  
			line( binaryMat,Point2f(0,y_intercept),Point2f(scene_output[2],scene_output[3]), Scalar( 255, 255, 255), 5, 8, 0);
			line( binaryMat,Point2f(x_intercept,0),Point2f(scene_output[2],scene_output[3]), Scalar( 255, 255, 255), 5, 8, 0);

			///////////////////////////////////////////////////// Define the direction for the drones to go away from the boundary

			/*	///////////////////////////////////////////////////// Uncomment for knowing the direction the drone has to move			

			////// Up or Forward == 1
			////// Right == 2
			////// Down or Backward == 3
			////// Left == 4

			int direction;

			if(scene_output[2] > 320 && scene_output[3] > 240 && scene_output[3] < 360)
				direction = 4;
			else if(scene_output[2] > 320 && scene_output[3] < 360) 
				direction = 3;
			else if(scene_output[2] < 320 && scene_output[3] > 240 && scene_output[3] < 360) 
				direction = 2;
			else if(scene_output[2] < 320 && scene_output[3] > 360) 
				direction = 3;
			else if(scene_output[2] > 320 && scene_output[3] > 120 && scene_output[3] < 240) 
				direction = 4;
			else if(scene_output[2] > 320 && scene_output[3] < 120) 
				direction = 1;
			else if(scene_output[2] < 320 && scene_output[3] > 120 && scene_output[3] < 240) 
				direction = 2;
			else if(scene_output[2] < 320 && scene_output[3] < 120) 
				direction = 1;
	
			*/	///////////////////////////////////////////////////// Uncomment for knowing the direction the drone has to move
	
		    	imshow("Display window1", binaryMat);
			//if(waitKey(30)>=0) break;
			waitKey(0);
		}
	 
		catch(std::exception) {cout << "Bleh" << endl;}
        
	}
	return 0;
}
