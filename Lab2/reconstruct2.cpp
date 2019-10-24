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

uchar abs(uchar x)
{
  if (x < 0)
  {
    return -x;
  }
  else
  {
    return x;
  }
}

int main() {

  // Read image from file
  Mat image = imread("mandrill2.jpg", 1);

  // Threshold by looping through all pixels
  for(int y=0; y<image.rows; y++) {
    for(int x=0; x<image.cols; x++) {
      uchar blue = image.at<Vec3b>(y,x)[0]; // Blue
      uchar green = image.at<Vec3b>(y,x)[1]; // Green
      uchar red = image.at<Vec3b>(y,x)[2]; // Red
      image.at<Vec3b>(y,x)[0]; abs(blue - 255); // Blue
      image.at<Vec3b>(y,x)[1]; abs(green - 255); // Green
      image.at<Vec3b>(y,x)[2]; abs(red - 255); // Red
    }
  }

  //Save reconsstructed image
  imwrite("reconstruct1.jpg", image);

  return 0;
}
