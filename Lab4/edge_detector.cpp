// header inclusion
#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <math.h>

using namespace cv;
using namespace std;

void Convolute(
	cv::Mat &input,
	uchar kernel[3][3],
	cv::Mat &output,
  double derivatives[600][600]
);

void Magnitude(
	cv::Mat &edgesX,
	cv::Mat &edgesY,
	cv::Mat &output
);

int main( int argc, char** argv )
{
  char* imageName = argv[1];

  Mat image;
  image = imread( imageName, 1 );

  if( argc != 2 || !image.data )
  {
    printf( " No image data \n " );
    return -1;
  }

  Mat gray_image;
  cvtColor( image, gray_image, CV_BGR2GRAY );

  Mat edgesX, edgesY, magnitude;
  double derivativesX[600][600];
  double derivativesY[600][600];

  uchar kernelX[3][3] = {{-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1}};
  uchar kernelY[3][3] = {{-1, -2, -1},
                         { 0,  0,  0},
                         { 1,  2,  1}};

  Convolute(gray_image, kernelX, edgesX, derivativesX);
  imwrite( "edgesX.jpg", edgesX );

  Convolute(gray_image, kernelY, edgesY, derivativesY);
  imwrite( "edgesY.jpg", edgesY );

	// Magnitude(edgesX, edgesY, magnitude);
	// imwrite( "magnitude.jpg", magnitude );

 return 0;
}

void Magnitude(cv::Mat &edgesX,cv::Mat &edgesY,cv::Mat &output)
{
	output.create(edgesX.size(), edgesX.type());
	int count = 0;
  double min = 10000, max = -10000;
  double matrix[600][600];
  
	for(int i = 0; i < edgesX.rows; i++)
	{
		for(int j = 0; j < edgesY.cols; j++)
		{
			double x_2 = edgesX.at<uchar>(i, j) * edgesX.at<uchar>(i, j);
			double y_2 = edgesY.at<uchar>(i, j) * edgesY.at<uchar>(i, j);
			double magnitude = sqrt(x_2 + y_2);
      
      matrix[i][j] = magnitude;

			if(magnitude > max)
      {
        max = magnitude;
      }
      if(magnitude < min)
      {
        min = magnitude;
      } 
		}
	}
  cout << "max: " << max << endl;
  cout << "min: " << min << endl;
  double oldrange = max - min;
  double newmin=0;
  double newmax=255;
  double newrange = newmax - newmin;

  for( int i = 0; i < output.rows; i++ )
	{
		for( int j = 0; j < output.cols; j++ )
    {
      double scale = (matrix[i][j] - min) / oldrange;
      // cout << (newrange * scale) + newmin << " ";
      output.at<uchar>(i, j) = (newrange * scale) + newmin;
    }
  }
}

void Convolute(cv::Mat &input, uchar kernel[3][3], cv::Mat &output, double derivatives[600][600])
{
	// intialise the output using the input
	output.create(input.size(), input.type());
	int kernelSize = 3;

	int kernelRadiusX = ( kernelSize - 1 ) / 2;
	int kernelRadiusY = ( kernelSize - 1 ) / 2;

	cv::Mat paddedInput;
	cv::copyMakeBorder( input, paddedInput,
		kernelRadiusX, kernelRadiusX, kernelRadiusY, kernelRadiusY,
		cv::BORDER_REPLICATE );

  double min = 10000, max = 10000;

	// now we can do the convoltion
	for ( int i = 0; i < input.rows; i++ )
	{
		for( int j = 0; j < input.cols; j++ )
		{
			double sum = 0.0;
			for( int m = -kernelRadiusX; m <= kernelRadiusX; m++ )
			{
				for( int n = -kernelRadiusY; n <= kernelRadiusY; n++ )
				{
					// find the correct indices we are using
					int imagex = i + m + kernelRadiusX;
					int imagey = j + n + kernelRadiusY;
					int kernelx = m + kernelRadiusX;
					int kernely = n + kernelRadiusY;

					// get the values from the padded image and the kernel
					int imageval = ( int ) paddedInput.at<uchar>( imagex, imagey );
					double kernalval = kernel[kernelx][kernely];

					// do the multiplication
					sum += imageval * kernalval;
				}
			}
      derivatives[i][j] = sum;
      if(sum > max)
      {
        max = sum;
      }
      if(sum < min)
      {
        min = sum;
      }
		}
	}
  // cout << "max: " << max << endl;
  // cout << "min: " << min << endl;
  double oldrange = max - min;
  double newmin=0;
  double newmax=255;
  double newrange = newmax - newmin;

  for( int i = 0; i < output.rows; i++ )
	{
		for( int j = 0; j < output.cols; j++ )
    {
      double scale = (derivatives[i][j] - min) / oldrange;
      // cout << (newrange * scale) + newmin << " ";
      output.at<uchar>(i, j) = (newrange * scale) + newmin;
    }
  }
}

 