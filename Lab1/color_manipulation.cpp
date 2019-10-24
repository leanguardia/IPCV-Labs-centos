#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
//#include <opencv/cxcore.h>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

uchar min(uchar a, uchar b)
{
  if (a < b) return a;
  return b;
}

uchar max(uchar a, uchar b)
{
  if (a > b) return a;
  return b;
}

int main()
{
  cout << "Starting Script ... \n";

  int threshold = 128;
  int top = 255, bottom = 0;

  Mat image = imread("mandrillRGB.jpg", 1);
  Mat result(512, 512, CV_8UC3, Scalar(0, 0, 255));

  cout << "Processing ... \n";
  cout << result.cols << " " << result.rows << "\n";

  for(int y = 0; y < result.rows; y++)
  {
    for (int x = 0; x < result.cols; x++)
    {
      // Blue
      uchar pixelBlue = image.at<Vec3b>(y, x)[0];
      result.at<Vec3b>(y, x)[0] = max(pixelBlue - 50, bottom);;

      // Green
      uchar pixelGreen = image.at<Vec3b>(y, x)[1];
      result.at<Vec3b>(y, x)[1] = max(pixelGreen - 50, bottom);

       // Red
      uchar pixelRed = image.at<Vec3b>(y, x)[2];
      result.at<Vec3b>(y, x)[2] = min(pixelRed + 180, top);
    }
  }

  imwrite("test.jpg", result);

  cout << "Script ended ... \n";

  return 0;
}
