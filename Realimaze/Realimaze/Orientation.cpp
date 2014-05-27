#include "Orientation.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <cv.h>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat image, standardImage;
VideoCapture cap;
SimpleBlobDetector::Params params; // parameter for the Simpleblobdetector, to make sure only the squares are modified
SimpleBlobDetector simple(params);
vector<KeyPoint>keypoints;

Orientation* orient = NULL;

void modifyImage()
{	orient->modifyImage();}
void runCamera()
{	orient->runCamera();}
//Mat getVideoImage()
//{	orient->getVideoImage();}

Orientation::Orientation()
{
	orient = this;
	
	runCamera();
}

Orientation::~Orientation()
{
}

void Orientation::runCamera(void)
{
	cap.open(1); // 1 is secundary camera

	namedWindow("Window", 1); // creates the window to dispalay the image
	
	// while loop to keep modifying the image
	while (1)
	{
		modifyImage();
	}
}

void Orientation::modifyImage(void)
{
	cap >> image; // copies the data from cap to the image to be modified

	cap >> standardImage;

	flip(image, image, 180); // mirrors the image

	params.minArea = 500;
	params.maxArea = 10000;
	params.filterByArea = true;
	params.minDistBetweenBlobs = 10;
	params.filterByColor = true;

	simple.detect(image, keypoints);

	// shows the blobs over the original image on screen
	drawKeypoints(image, keypoints, image, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	if (!image.empty())
	{
		imshow("Window", image);
	}
}

Mat getVideoImage()
{
	standardImage.resize(2);
	return standardImage;
}
