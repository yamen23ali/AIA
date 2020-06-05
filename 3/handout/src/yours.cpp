#include "yours.hpp"
#include "given.hpp"


Mat yours::visualizeHoughSpace(vector< vector<Mat> >& houghSpace){


}


void yours::drawz(Mat &image){

	vector<Mat> channels;
	split(image, channels);
	given::showImage(channels[0], "Binary part of template", 0);
	given::showImage(channels[1], "Binary part of template", 0);
	//std::cout<< channels[1] << std::endl;
	//given::showImage(channels[1], "Binary part of template", 0);

}

void yours::makeFFTObjectMask(vector<Mat>& templ, double scale, double angle, Mat& fftMask){

	Mat filter, centeredFilter;

	// Scale and rotate object filter
	Mat scaledAndRotatedBinary = given::rotateAndScale(templ[0], angle, scale);
	Mat scaledAndRotatedGrad = given::rotateAndScale(templ[1], angle, scale);
	
	// Normalize
	Mat normalisedGrad;
	normalisedGrad = scaledAndRotatedGrad  * 1/cv::norm(scaledAndRotatedGrad);

	// Make filter
	vector<Mat> normalisedGradChannels;
	split(normalisedGrad, normalisedGradChannels);

	normalisedGradChannels[0] = scaledAndRotatedBinary.mul(normalisedGradChannels[0]);
	normalisedGradChannels[1] = scaledAndRotatedBinary.mul(normalisedGradChannels[1]);
	merge(normalisedGradChannels, filter);

    // Center object filter
    int dx = -filter.cols/2;
	int dy = -filter.rows/2;

	int cols = filter.cols;
	int rows = filter.rows;


	if(rows > fftMask.rows || cols > fftMask.cols){
		dft(fftMask, fftMask);
		return;
	}

    filter.copyTo(fftMask(Rect(0, 0, cols, rows)));
    //drawz(fftMask);
    given::circShift(fftMask, centeredFilter, dx, dy);
    
    dft(centeredFilter, fftMask);
}


vector<vector<Mat> > yours::generalHough(Mat& gradImage, vector<Mat>& templ, double scaleSteps, double* scaleRange, double angleSteps, double* angleRange){

	vector<vector<Mat>> votes;
	Mat imageSpectrum;
	double scaleStepSize = (scaleRange[1] - scaleRange[0])/(scaleSteps-1);
	double angleStepSize = (angleRange[1] - angleRange[0])/(angleSteps);
	
	dft(gradImage, imageSpectrum);

	int i = 0 ;

	while(i < scaleSteps){
		
		double scale = scaleRange[0] + i * scaleStepSize;
		vector<Mat> scaleVotes;
		
		int j = 0 ;
		while(j <  angleSteps){
			//double angle = j * (angleRange[1]/angleSteps);
			double angle = angleRange[0] + j * angleStepSize;

			Mat fftMask = Mat::zeros(gradImage.rows, gradImage.cols, gradImage.type());
			makeFFTObjectMask(templ, scale, angle, fftMask);

			Mat voteSpectrum;
			mulSpectrums(imageSpectrum, fftMask , voteSpectrum, 0, true);

			Mat vote;
			dft(voteSpectrum, vote, cv::DFT_INVERSE);

			std::vector<Mat> voteChannels(2);
			Mat magnitued, angleMat;

			split(vote, voteChannels);
			cartToPolar(voteChannels[0], voteChannels[1], magnitued, angleMat);

			scaleVotes.push_back(magnitued);

			j++;
		}
		i++;
		votes.push_back(scaleVotes);
	}

	return votes;
}


Mat yours::binarizeGradientImage(Mat& src, double threshold){

	std::vector<Mat> channels(2);
    Mat magnitued;
    Mat angle;
    Mat binaryImage;

    split(src, channels);
    cartToPolar(channels[0], channels[1], magnitued, angle);

    double min, max;
    cv::minMaxLoc(magnitued, &min, &max);


    cv::threshold(magnitued, binaryImage, threshold*max, 255, 0);


    return binaryImage;
}
