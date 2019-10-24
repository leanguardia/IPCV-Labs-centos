/////////////////////////////////////////////////////////////////////////////
//
// COMS30121 - thr.cpp
// TOPIC: RGB explicit thresholding
//
// Getting-Started-File for OpenCV
// University of Bristol
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main() {

  // Read image from file
  Mat image = imread("mandrill0.jpg", 1);

  // Threshold by looping through all pixels
  for(int y=0; y<image.rows; y++) {
    for(int x=0; x<image.cols; x++) {
      uchar green = image.at<Vec3b>(y,x)[0]; // Blue
      uchar red = image.at<Vec3b>(y,x)[1]; // Green
      uchar blue = image.at<Vec3b>(y,x)[2]; // Red
      image.at<Vec3b>(y,x)[0] = blue; // Blue
      image.at<Vec3b>(y,x)[1] = green;
      image.at<Vec3b>(y,x)[2] = red; // Red
    }
  }

  //Save reconsstructed image
  imwrite("reconstruct0.jpg", image);

  return 0;
}
