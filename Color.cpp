#include <iostream>
#include <opencv2\opencv.hpp>
#include "opencv2\imgproc\imgproc_c.h"
#include "opencv2\core\core.hpp"
#include "threadpoollegacyapiset.h"
#include "windef.h"


using namespace cv;
using namespace std;


int main(int argc, char** argv) { //start of main method
	VideoCapture VideoFeed(0); //Captures the video from the camera

	if (!VideoFeed.isOpened()) { //If there is no video feed detected close the program
		cout << "Cannot open the camera" << endl; // will print a statement saying that the camera could not be printed
		return -1;
	} // end of if loop

	namedWindow("Adjuster", WINDOW_NORMAL); //create a window called Adjuster that will allow us to adjust the values manualy


	int lowerValue = 0; // Lower value
	int HighVal = 255; // Higher Value

	int LowerSaturation = 0; // Lower saturation value
	int HighSaturation = 255; // higher saturation value

	int LowerHue = 0; // lower hue limit
	int HigherHue = 179; // higher hue limit


					   //The following values will allow us to change the hue, saturation and value of the arrays so we can determine color.
	int CreateTrackbar(const string& LowerHue, const string& Adjuster, &LowerHue, 179); //Hue (0 - 179)
	int CreateTrackbar(const string& HigherHue, const string& Adjuster, &HigherHue, 179); // the bars will be name of bar, parent bar, lower value 

	int CreateTrackbar(const string& LowerSaturation, const string& Adjuster, &LowerSaturation, 255); //Saturation (0 - 255)
	int CreateTrackbar(const string& HighSaturation, const string& Adjuster, &HighSaturation, 255);

    int CreateTrackbar(const string& lowerValue, const string& Adjuster, &lowerValue, 255); //Value (0 - 255)
	int CreateTrackbar(const string&HighVal, const string& Adjuster, &HighVal, 255);


	int PastX = -1;
	int pastY = -1;

	//temporary image from the camera
	Mat imgTmp;
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);; //this will creat a black image for contrasting
	VideoFeed.read(imgTmp);


	while (true) { //start of binary while loop
		Mat FirstFrame; // Defines a matrice called First frame
		bool bSuccess = VideoFeed.read(FirstFrame); // process a new frame from video

		if (!bSuccess) { //if it can not process a new frame the loop will stop
			cout << "Cannot read a frame from video stream" << endl;
			break; // breaks the loop
		} // end of !bSuccess loop

		Mat ImagesHueStaturationValue; // declares a matrix  to get the HSV (Hue Saturation Values) from the frames
		Mat BinaryImaging; // decclares a matrix calles Binary imaging that will get the treshold of images and make them so that the computer can process them.

		cvtColor(FirstFrame, ImagesHueStaturationValue, COLOR_BGR2HSV); //this will convert the Blue Green Red Values (or Red Green Blue Values) to HSV (Hue Saturation Values)
		inRange(ImagesHueStaturationValue, Scalar(LowerHue, LowerSaturation, lowerValue), Scalar(HigherHue, HighSaturation, HighVal), BinaryImaging); //Threshold of the image


		erode(BinaryImaging, BinaryImaging, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); // "erodes the image so that it becmes smaller and can process objects better
		dilate(BinaryImaging, BinaryImaging, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(BinaryImaging, BinaryImaging, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));// "dialates" the background to fill in holes and make an easier processing
		erode(BinaryImaging, BinaryImaging, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Image", BinaryImaging); //show the thresholded image
		imshow("Original", FirstFrame); //show the original image

		if (waitKey(30) == 27) {//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			cout << "esc key is pressed by user" << endl;
			break;
		} // end of exit if loop
	}

	return 0;

