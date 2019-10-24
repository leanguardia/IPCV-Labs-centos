// header inclusion
#include <stdio.h>
#include <algorithm>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;
using namespace std;

void Convolute(
	cv::Mat &input,
	int size,
	cv::Mat &blurredOutput);

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

 Mat carBlurred;
 Convolute(gray_image, 5, carBlurred);

 imwrite( "sharp2.jpg", carBlurred );

 return 0;
}

void Convolute(cv::Mat &input, int size, cv::Mat &blurredOutput)
{
	// intialise the output using the input
	blurredOutput.create(input.size(), input.type());

	// create the Gaussian kernel in 1D
	cv::Mat kX = cv::getGaussianKernel(size, -1);
	cv::Mat kY = cv::getGaussianKernel(size, -1);

	// make it 2D multiply one by the transpose of the other
	cv::Mat kernel = kX * kY.t();

	//CREATING A DIFFERENT IMAGE kernel WILL BE NEEDED
	//TO PERFORM OPERATIONS OTHER THAN GUASSIAN BLUR!!!

	// we need to create a padded version of the input
	// or there will be border effects
	int kernelRadiusX = ( kernel.size[0] - 1 ) / 2;
	int kernelRadiusY = ( kernel.size[1] - 1 ) / 2;

	int area  = size * size;
	int middleIndex = area / 2;

	// SET KERNEL VALUES
	// for( int m = -kernelRadiusX; m <= kernelRadiusX; m++ ) {
	// 	for( int n = -kernelRadiusY; kernelRadiusX <= kernelRadiusY; n++ )
	// 				kernel.at<double>(m+ kernelRadiusX, n+ kernelRadiusY) = (double) 1.0;
	// 		}

	cv::Mat paddedInput;
	cv::copyMakeBorder( input, paddedInput,
		kernelRadiusX, kernelRadiusX, kernelRadiusY, kernelRadiusY,
		cv::BORDER_REPLICATE );

	// now we can do the convoltion
	for ( int i = 0; i < input.rows; i++ )
	{
		for( int j = 0; j < input.cols; j++ )
		{
			int sortedPixels[100];
			int arrayIndex = 0;
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

					// do the multiplication
					sortedPixels[arrayIndex] = imageval;// * kernalval;
					arrayIndex++;
					sort(sortedPixels, sortedPixels + area);
				}
			}
			// set the output value as the sum of the convolutio
			int median = sortedPixels[middleIndex];
			blurredOutput.at<uchar>(i, j) = (float) median;
		}
	}
}
