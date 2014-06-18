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

Mat image, standardImage, subMatImage;
VideoCapture cap(1);
SimpleBlobDetector::Params params; // parameter for the Simpleblobdetector, to make sure only the squares are modified
SimpleBlobDetector simple;
vector<KeyPoint>keypoints;
Point p;
IplImage* imgP;


Orientation::Orientation()
{
	params.minArea = 400;
	params.maxArea = 500;
	params.filterByArea = true;
	params.minDistBetweenBlobs = 100;
	params.filterByColor = true;

	simple = SimpleBlobDetector(params);

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
		ofactor.yPos = ((orientPos.yPos - centerPos.yPos) / boundary);
	else
		ofactor.yPos = ((centerPos.yPos - orientPos.yPos) / boundary)*-1;
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
	cap.read(image);

	flip(image, image, 1); // mirrors the image

	subMatImage = image(Rect(270, 150, 120, 120));

	simple.detect(subMatImage, keypoints);

	for each (KeyPoint key in keypoints)
	{
		//cout << "blob: X " << key.pt.x << " Y " << key.pt.y << " + size: " << key.size << " center: X " << centerPos.xPos << " Y " << centerPos.yPos << endl;
		if (key.size < 15)
		{
			p = Point(key.pt.x, key.pt.y);
			orientPos.xPos = key.pt.x;
			orientPos.yPos = key.pt.y;
		}
	}

	if (!image.empty())
	{
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
	imgP = cvCloneImage(&(IplImage)image);
	return imgP;
}

Point Orientation::getMiddlePointLocation()
{
	return p;
}

void Orientation::releaseImageData()
{
	cvReleaseImage(&imgP);
}
