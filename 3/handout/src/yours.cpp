#include "yours.hpp"
#include "given.hpp"


Mat yours::visualizeHoughSpace(vector< vector<Mat> >& houghSpace){


}


void yours::makeFFTObjectMask(vector<Mat>& templ, double scale, double angle, Mat& fftMask){


}


vector<vector<Mat> > yours::generalHough(Mat& gradImage, vector<Mat>& templ, double scaleSteps, double* scaleRange, double angleSteps, double* angleRange){

	vector<vector<Mat>> votes;

	double scaleStepSize = (scaleRange[1] - scaleRange[0])/ scaleSteps;
	double angleStepSize = (angleRange[1] - angleRange[0])/ angleSteps;

	for(int i=0; i<= scaleSteps; i++){
		double scale = scaleRange[0] + i*scaleStepSize;

		for(int j=0; j <= angleSteps; j++){
			double angle = angleRange[0] + j*angleStepSize;

		}
	}

	return votes;
}


Mat yours::binarizeGradientImage(Mat& src, double threshold){

	Mat mergedGrads, binaryImage;
	vector<Mat> channels;
    
    split(src, channels);

    mergedGrads = channels[0] + channels[1];

	cv::threshold(mergedGrads, binaryImage, threshold, 255, 0);

	return binaryImage;
}
