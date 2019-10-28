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
	cv::Mat &output
);

void Magnitude(
	cv::Mat &edgesX,
	cv::Mat &edgesY,
	cv::Mat &output
);

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 char* imageName = argv[1];

 Mat image;
 image = imread( imageName, 1 );

 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }

 // CONVERT COLOUR, BLUR AND SAVE
 Mat gray_image;
 cvtColor( image, gray_image, CV_BGR2GRAY );

 Mat edgesX, edgesY, magnitude;

 uchar kernelX[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
 Convolute(gray_image, kernelX, edgesX);
 Mat normalizedX;
//  edgesX.convertTo(normalizedX, CV_32F, 1.0 / 255);
 imwrite( "edgesX.jpg", edgesX );

 uchar kernelY[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
 Convolute(gray_image, kernelY, edgesY);
 imwrite( "edgesY.jpg", edgesY );

	Magnitude(edgesX, edgesY, magnitude);
	imwrite( "magnitude.jpg", magnitude );


 return 0;
}

void Magnitude(cv::Mat &edgesX,cv::Mat &edgesY,cv::Mat &output)
{
	output.create(edgesX.size(), edgesX.type());
	int count = 0;
	for(int i = 0; i < edgesX.rows; i++)
	{
		for(int j = 0; j < edgesY.cols; j++)
		{
			double x_2 = edgesX.at<uchar>(i, j) * edgesX.at<uchar>(i, j);
			double y_2 = edgesY.at<uchar>(i, j) * edgesY.at<uchar>(i, j);
			double magnitude = sqrt(x_2 + y_2);

			if(magnitude > 255 || magnitude < 0)
			{
				count++;
			}
			output.at<uchar>(i, j) = (uchar)magnitude;
		}
	}
	// cout << count;
}

void Convolute(cv::Mat &input, uchar kernel[3][3], cv::Mat &output)
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
			// set the output value as the sum of the convolution
			output.at<uchar>(i, j) = (uchar) sum;
		}
	}
}
