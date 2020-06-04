#include "yours.hpp"
#include "given.hpp"


Mat yours::visualizeHoughSpace(vector< vector<Mat> >& houghSpace){


}



void yours::drawz(Mat &image){

	vector<Mat> channels;
	split(image, channels);
	given::showImage(channels[0], "Binary part of template", 0);
	//given::showImage(channels[1], "Binary part of template", 0);
	//std::cout<< channels[1] << std::endl;
	//given::showImage(channels[1], "Binary part of template", 0);

}

Mat myDFT(Mat src){
	Mat contourF;
    // convert to flaot
    src.convertTo(contourF, CV_32F);

    // prepare output matrices ( one for magnitude and the other for phase)
    Mat planes[] = {Mat::zeros(contourF.size(), CV_32F), Mat::zeros(contourF.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    // perform DFT
    dft(contourF, complexI);
    
    return complexI;
}

void yours::makeFFTObjectMask(vector<Mat>& templ, double scale, double angle, Mat& fftMask){

	Mat filter, centeredFilter;

	// Scale and rotate object filter
	Mat scaledAndRotatedBinary = given::rotateAndScale(templ[0], angle, scale);
	Mat scaledAndRotatedGrad = given::rotateAndScale(templ[1], angle, scale);
	
	// Normalize
	Mat normalisedGrad;
	
	vector<Mat> gradChannels;
	split(scaledAndRotatedGrad, gradChannels);

	normalisedGrad = scaledAndRotatedGrad  * 1/cv::sum( gradChannels[0] )[0];

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

	double scaleStepSize = (scaleRange[1] - scaleRange[0])/(scaleSteps-1);
	double angleStepSize = (angleRange[1] - angleRange[0])/(angleSteps);
	int i = 0 ;

	Mat imageSpectrum;
	dft(gradImage, imageSpectrum);

	while(i < scaleSteps){
		
		double scale = scaleRange[0] + i*scaleStepSize;
		//double scale = 1.0;
		vector<Mat> scaleVotes;
		
		int j = 0 ;
		while(j <  angleSteps){
			double angle = j*(angleRange[1]/angleSteps);
			//double angle = 1.57;

			Mat fftMask = Mat::zeros(gradImage.rows, gradImage.cols, gradImage.type());
			makeFFTObjectMask(templ, scale, angle, fftMask);

			Mat voteSpec;
			
			mulSpectrums(imageSpectrum, fftMask , voteSpec, 0, true);

			Mat vote,magnitued,angleMat;
			dft(voteSpec, vote, cv::DFT_INVERSE);

			std::vector<Mat> voteChannels(2);
			split(vote, voteChannels);
			cartToPolar(voteChannels[0], voteChannels[1], magnitued, angleMat);
			
			//drawz(magnitued);

			vector<Mat> channels;
			split(vote, channels);
			

			scaleVotes.push_back(abs(magnitued));
			//scaleVotes.push_back(abs(channels[1]));
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


    cv::threshold(magnitued, binaryImage, threshold*max, 255, 3);


    return binaryImage;



	/*Mat binaryImage, tempCh0, tempCh1;
	vector<Mat> channels;
	vector<Mat> binaryChannels;
	double min, max;
	
	split(src, channels);

	tempCh0 = abs(channels[0]);
	tempCh1 = abs(channels[1]);
	
	cv::minMaxLoc(tempCh0, &min, &max);
	cv::threshold(tempCh0, tempCh0, threshold*max, 255, 0);
	binaryChannels.push_back(tempCh0);


	cv::minMaxLoc(tempCh1, &min, &max);
	cv::threshold(tempCh1, tempCh1, threshold*max, 255, 0);
	binaryChannels.push_back(tempCh1);


	merge(binaryChannels, binaryImage);

	//yours::drawz(binaryImage);

	//std::cout<< binaryImage << std::endl;


	return binaryImage;
	Mat binaryImage;

	src = cv::abs(src);

	double min, max;
	cv::minMaxLoc(src, &min, &max);

	cv::threshold(src, binaryImage, threshold*max, 255, 3);

	return binaryImage;*/
}
