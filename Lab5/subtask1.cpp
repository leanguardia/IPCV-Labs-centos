#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );
void importGroundTruth();

/** Global variables */
string cascade_name = "frontalface.xml";
CascadeClassifier cascade;

/** @fstd::unction main */
int main( int argc, const char** argv )
{
  // 1. Read Input Image
	Mat frame = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	// 2. Load the Strong Classifier in a structure called `Cascade'
	if( !cascade.load( cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

	// faces = importGroundTruth();
	importGroundTruth();
	// for(int i = 0; i < faces.size(); i++) {
	// 	int x = faces[i][0];
	// 	int y = faces[i][1];
	// 	rectangle(frame, Point(x, y), Point(x+ faces[i][2], y+faces[i][3]), Scalar(0, 0, 255), 2);
	// }

	// 3. Detect Faces and Display Result
	detectAndDisplay( frame );

	// 4. Save Result Image
	imwrite( "detected.jpg", frame );

	return 0;
}

void importGroundTruth() {
	string line;
  ifstream faces("gt/faces1.txt");
  if (faces.is_open()) {
    while ( getline(faces, line) ) {
			cout << line << '\n';
    }
    faces.close();
  }
  else cout << "Unable to open file";
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
	std::vector<Rect> faces;
	Mat frame_gray;

	// 1. Prepare Image by turning it into Grayscale and normalising lighting
	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	// 2. Perform Viola-Jones Object Detection
	cascade.detectMultiScale( frame_gray, faces, 1.1, 1, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500,500) );

  // 3. Print number of Faces found
	std::cout << faces.size() << std::endl;

  // 4. Draw box around faces found
	for( int i = 0; i < faces.size(); i++ )
	{
		// Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), // point 2
		rectangle(
			frame, // image
			Point(faces[i].x, faces[i].y), // point 1
			Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), // point 2
			Scalar( 0, 255, 0 ), // color
			2 // thickness
		);
	}
}
