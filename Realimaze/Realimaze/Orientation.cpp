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
Point p;


Orientation::Orientation()
{
	params.minArea = 10;
	params.maxArea = 25;
	params.filterByArea = true;
	params.minDistBetweenBlobs = 100;
	params.filterByColor = true;

	p = Point(0, 0);
}

Orientation::~Orientation()
{
}

PosF Orientation::getOrientationFactor()
{
	PosF ofactor;
	if (orientPos.xPos > centerPos.xPos)
		ofactor.xPos = ((orientPos.xPos - centerPos.xPos) / boundary)*-1;
	else
		ofactor.xPos = ((centerPos.xPos - orientPos.xPos) / boundary);
	if (orientPos.yPos > centerPos.yPos)
		ofactor.yPos = ((orientPos.yPos - centerPos.yPos) / boundary)*-1;
	else
		ofactor.yPos = ((centerPos.yPos - orientPos.yPos) / boundary);
	return ofactor;
}

string Orientation::getVars()
{
	stringstream strs;
	strs << "centerP(" << centerPos.xPos << ", " << centerPos.yPos << "), orientP(" << orientPos.xPos << ", " << orientPos.yPos << ")" << endl;
	return strs.str();
}

void Orientation::modifyImage()
{
	cap.open(2);

	cap >> image; // copies the data from cap to the image to be modified

	flip(image, image, 1); // mirrors the image

	resize(image, standardImage, image.size() * 2, 0.5, 0.5, 1);

	simple.detect(image, keypoints);

	// shows the blobs over the original image on screen
	drawKeypoints(image, keypoints, image, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	for each (KeyPoint key in keypoints)
	{
		//cout << "The location of the blob is: X " << key.pt.x << " Y " << key.pt.y << " + size: " << key.size << endl;
		if (key.size < 15)
		{
			p = Point(key.pt.x, key.pt.y);
		}
	}

	if (!image.empty())
	{
		imshow("Window", image);
		imshow("BigImage", standardImage);
		//imshow("Window", image);
		//imshow("BigImage", standardImage);
		waitKey(33);
	}
}

Mat getVideoImage()
{
	return standardImage;
}

IplImage* Orientation::getVideoImage()
{
	IplImage* imgP = cvCloneImage(&(IplImage)image);
	return imgP;
}

Point Orientation::getMiddlePointLocation()
{
	return p;
}
