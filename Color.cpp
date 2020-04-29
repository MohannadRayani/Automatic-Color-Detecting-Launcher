#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;


int main() { // Start of main methode

	VideoCapture VideoFeed; // This declares the video capture  class as video feed
	VideoFeed.open(0);  //http://192.168.1.101:8080/video?x.mjpeg This is where our code calls the video 0 is default  camera but we can place an IP camera here

	if (!VideoFeed.isOpened()) { // This will make it so that if there is no feed it will close the application and tell us wh

		printf("Android camera could not be found");

			return -1;
	} // end of video feed not found condition

	namedWindow("Adjuster", WINDOW_NORMAL); //create a window called Adjuster that will allow us to adjust the values manualy
	
	Mat Image; // This will store all the frames we get from the video feed

	while(1) {

		bool x = VideoFeed.read(Image); // this will tell us if video frame was read successfully 	

		if (!x) { // if the individual frame of the video is not read successfully then it will end the loop
			printf("Could not be processed");
			break; // exits the loop

		}  // end of boolean check

		/*imshow("Trace image", Image);*/

		if (waitKey(30) == 27) { // this starts the program so we can select a color
			
			printf("Please enter a color (enter number) : \n 1. Red \n 2. Blue \n 3. Orange \n 4. Yellow \n 5. Magenta \n 6. Green \n 7. White \n");
			break;

		} // end of esc loop


	} // end of while loop

	int Entered; // This will allow us to choose the color
	cin >> Entered; // Detects Input



	// These are so we can change detect the color based of what was selected.
	int HueLow;
	int HueHigh;

	int SatLow;
	int SatHigh;

	int ValueLow;
	int ValueHigh;



	if (Entered == 1) { //Red Detection
		cout << "You have selected Red";
		HueLow = 160;
		HueHigh = 179;

		SatLow = 164 ;
		SatHigh = 255 ;

		ValueLow = 82;
		ValueHigh = 255;

	} // End of red loop

	else if (Entered == 2) { // Blue Detection
		cout << "You have enntred Blue";
		HueLow = 75;
		HueHigh = 130;

		SatLow = 164;
		SatHigh = 255;

		ValueLow = 82;
		ValueHigh = 255;

	} // End of blue

	else if (Entered == 3) { // Orange Detection
		cout << "you have selected Orange";
		HueLow = 0;
		HueHigh = 22;

		SatLow = 143;
		SatHigh = 255;

		ValueLow = 108;
		ValueHigh = 255;
		
	}// End of Orange

	else if (Entered == 4) { //Yellow Detection
		cout << "you have selected Yellow";
		HueLow = 21;
		HueHigh = 38;

		SatLow = 65;
		SatHigh = 255;

		ValueLow = 59;
		ValueHigh = 155;

	} // End of Yellow
	else if (Entered == 5) { // Magenta (or whatever color i have) Detection
		cout << "you have selected Magenta";
		HueLow = 130;
		HueHigh = 160;

		SatLow = 108;
		SatHigh = 255;

		ValueLow = 0;
		ValueHigh = 122;

	}// end of Magenta

	else if (Entered == 6) { // Green Detection
		cout << "you have selected Green";
		HueLow = 50;
		HueHigh = 108;

		SatLow = 47;
		SatHigh = 255;

		ValueLow = 26;
		ValueHigh = 255;

	} // End of Green

	else if (Entered == 7) { // White Detection
		cout << "you have selected White";
		HueLow = 54;
		HueHigh = 128;

		SatLow = 0;
		SatHigh = 102;

		ValueLow = 150;
		ValueHigh = 255;

	}// End of white


	int lowerValue = ValueLow; // This declared lower value and assigns it to Value lower which is determined above
	int HighVal = ValueHigh; // This declared higher value and assigns it to Value higher which is determined above


	int LowerSaturation = SatLow; // Lower saturation range is assigned here
	int HighSaturation = SatHigh; // higher saturation range is assigned here

	int LowerHue = HueLow; // lower hue range is assigned here
	int HigherHue = HueHigh; // higher hue range  is assigned here

						
	 // The following values will allow us to change the hue, saturation and value in a trackbar

	// Track bars to adjust Hue
	 cvCreateTrackbar("LowerHue", "Adjuster", &LowerHue, 179); 
	 cvCreateTrackbar("HigherHue", "Adjuster", &HigherHue, 179); 

	 // Track bars to adjust Saturation
	 cvCreateTrackbar("LowerSaturation",   "Adjuster", &LowerSaturation, 255); 
	 cvCreateTrackbar("HighSaturation",   "Adjuster", &HighSaturation, 255);

	 // Track bars to adjust Value
	 cvCreateTrackbar(  "lowerValue",   "Adjuster", &lowerValue, 255); 
	 cvCreateTrackbar( "HighVal",   "Adjuster", &HighVal, 255);


	int PastX = -1;
	int PastY = -1;

	//temporary image from the camera
	Mat Temp;                             
	Mat LineTrace = Mat::zeros(Temp.size(), CV_8UC3);; //this will creat a black image for contrasting
	VideoFeed.read(Temp);


	while (true) { //start of binary while loop
		Mat FirstFrame; // Defines a matrice called First frame
		bool bSuccess = VideoFeed.read(FirstFrame); // process a new frame from video

		if (!bSuccess) { //if it can not process a new frame the loop will stop
			cout << "Cannot read a frame from video stream" << endl;
			break; 
		} // end of !bSuccess loop

		Mat ImagesHueStaturationValue; // declares a matrix  to get the HSV (Hue Saturation Values) from the frames
		Mat BinaryImaging; // decclares a matrix calles Binary imaging that will get the treshold of images and make them so that the computer can process them.

		cvtColor(FirstFrame, ImagesHueStaturationValue, COLOR_BGR2HSV); //this will convert the Blue Green Red Values (or Red Green Blue Values) to HSV (Hue Saturation Values)

		// Checks if array elements lie between the elements of two other arrays.
		inRange(ImagesHueStaturationValue, Scalar(LowerHue, LowerSaturation, lowerValue), Scalar(HigherHue, HighSaturation, HighVal), BinaryImaging); 
		 
		
		Mat GSE = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));


		// "erodes the image so that it becmes smaller and can process objects better
		erode(BinaryImaging, BinaryImaging, GSE); 
		dilate(BinaryImaging, BinaryImaging, GSE);

		// "dialates" the background to fill in holes and make an easier processing
		dilate(BinaryImaging, BinaryImaging, GSE);
		erode(BinaryImaging, BinaryImaging, GSE);


		//Calculate the moments of the thresholded image
		Moments Counter = moments(BinaryImaging);

		double ArrayMoment = Counter.m01;
		double BooleanMoment = Counter.m10;
		double AreaOfPixels = Counter.m00;


		// This reduces the amount of random dots in the video stream
		if (AreaOfPixels > 9825)
		{
			// Traces the object based on the  X/Y axis and the amount of pixels
			int Xaxis = BooleanMoment / AreaOfPixels;
			int Yaxis = ArrayMoment / AreaOfPixels;

			if (PastX >= 0 && PastY >= 0 && Xaxis >= 0 && Yaxis >= 0)
			{
				//Draw a green line that floows the object and direction
				arrowedLine(LineTrace, Point(Xaxis, Yaxis), Point(PastX, PastY), Scalar(0, 255, 0), 2);
			}

			PastX = Xaxis;
			PastY = Yaxis;
		}

		FirstFrame = FirstFrame + LineTrace;

		imshow("Unchanged video", FirstFrame); //show the original image + tracer lines
		imshow("Singled out color ", BinaryImaging); //Creates a window so we can see the color that we are detecting
		BinaryImaging = FirstFrame + LineTrace;

		if (waitKey(30) == 27) // Just as above this will end the program if we hold the escape button for more than 30 milli seconds
		{
			break;
		}
	}
	
	return 0;
}
