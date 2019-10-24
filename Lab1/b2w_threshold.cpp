#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv2/imgproc/imgproc.hpp>
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

  int threshold = 66;
  int top = 255, bottom = 0;

  Mat image = imread("mandrill.jpg", 1);
  Mat result;
  cvtColor(image, result, CV_BGR2GRAY);

  cout << "Processing ... \n";
  cout << result.cols << " " << result.rows << "\n";

  for(int y = 0; y < result.rows; y++)
  {
    for (int x = 0; x < result.cols; x++)
    {
      uchar pixel = result.at<uchar>(y, x);
      if (pixel > threshold)
        result.at<uchar>(y, x) = top;
      else
        result.at<uchar>(y, x) = 10;
    }
  }

  imwrite("test.jpg", result);

  cout << "Script ended ... \n";

  return 0;
}
