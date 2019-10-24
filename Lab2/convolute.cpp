#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;
using namespace std;

int main() {

  // Read image from file
  Mat image = imread("mandrill.jpg", 1);
  cvtColour()

  Mat result(512, 512, CV_8U, Scalar(0));
  int kernel[3][3] = { {1, 1, 1},
                       {1, 1, 1},
                       {1, 1, 1} };
  float g, factor = 0.111;

  cout << image.rows << " " << image.cols << endl;

  for(int y = 1; y < image.rows -1; y++ ) {
    for(int x = 1; x < image.cols -1; x++ ) {
      g = 0;
      for(int m = y - 1; m <= y + 1; m++) {
        for(int n = x - 1; n <= x + 1; n++) {
          g += image.at<uchar>(m, n);
        }
      }
      result.at<uchar>(y, x) = factor * g;
    }
  }

  imwrite("blurred.jpg", result);

  return 0;
}
