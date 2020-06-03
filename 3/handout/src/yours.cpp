#include "yours.hpp"
#include "given.hpp"


Mat yours::visualizeHoughSpace(vector< vector<Mat> >& houghSpace){


}

void yours::drawz(Mat &image){

	vector<Mat> channels;
	split(image, channels);
	given::showImage(channels[0], "Binary part of template", 0);
	given::showImage(channels[1], "Binary part of template", 0);

}

void yours::makeFFTObjectMask(vector<Mat>& templ, double scale, double angle, Mat& fftMask){

	Mat filter, spectrum, scaledAndRotatedFilter, normalisedFilter, centeredFilter;

	//Get object filter
	vector<Mat> channels;
	split(templ[1], channels);

	//given::showImage(templ[0], "Binary part of template", 0);
	//given::showImage(channels[1], "Binary part of template", 0);
	
	//channels[0] = templ[0].mul(channels[0]);
	//channels[1] = templ[0].mul(channels[1]);

	//given::showImage(channels[0], "Binary part of template", 0);
	//given::showImage(channels[1], "Binary part of template", 0);
    
    merge(channels, filter);


	// Scale and rotate object filter
	scaledAndRotatedFilter = given::rotateAndScale(filter, angle, scale);

	drawz(scaledAndRotatedFilter);
	
	// Normalise object filter
    split(scaledAndRotatedFilter, channels);

    normalisedFilter = scaledAndRotatedFilter  * 1/cv::sum(channels[0])[0];

    

    // Center object filter
    int dx = -normalisedFilter.cols/2;
	int dy = -normalisedFilter.rows/2;

	int cols = normalisedFilter.cols;
	int rows = normalisedFilter.rows;


	if(rows > fftMask.rows){
		rows = fftMask.rows;
	}
	if(cols > fftMask.cols){
		cols = fftMask.cols;
	}

    normalisedFilter(Rect(0, 0, cols, rows)).copyTo(fftMask(Rect(0, 0, cols, rows)));
    given::circShift(fftMask, centeredFilter, 0, 0);

    //drawz(centeredFilter);
    
    dft(centeredFilter, fftMask);
}


vector<vector<Mat> > yours::generalHough(Mat& gradImage, vector<Mat>& templ, double scaleSteps, double* scaleRange, double angleSteps, double* angleRange){

	vector<vector<Mat>> votes;

	double scaleStepSize = ((scaleRange[1] - scaleRange[0]) + 1 )/ scaleSteps;
	double angleStepSize = (angleRange[1] - angleRange[0])/ angleSteps;

	std::cout << "=========================== Scale" << std::endl;
	std::cout<< scaleSteps << std::endl;
	std::cout<< scaleRange[0] << std::endl;
	std::cout<< scaleRange[1] << std::endl;
	std::cout<< scaleStepSize << std::endl;


	std::cout << "=========================== Angle" << std::endl;
	
	std::cout<< angleSteps << std::endl;
	std::cout<< angleRange[0] << std::endl;
	std::cout<< angleRange[1] << std::endl;
	std::cout<< angleStepSize << std::endl;
	std::cout << "===========================" << std::endl;

	for(int i=0; i<= scaleSteps; i++){
		double scale = scaleRange[0] + i*scaleStepSize;
		//std::cout<< scale << std::endl;

		vector<Mat> scaleVotes;

		for(int j=0; j <= angleSteps; j++){
			double angle = angleRange[0] + j*angleStepSize;
			//std::cout<< angle << std::endl;

			Mat fftMask = Mat::zeros(gradImage.rows, gradImage.cols, gradImage.type());
			//drawz(fftMask);
			makeFFTObjectMask(templ, scale, angle, fftMask);
			//drawz(fftMask);
			
			Mat imageSpectrum;
			dft(gradImage, imageSpectrum);

			Mat vote;
			mulSpectrums(imageSpectrum, fftMask, vote, 0, true);

			vector<Mat> channels;
			split(vote, channels);
			channels[0] = cv::abs(channels[0]);

			scaleVotes.push_back(channels[0]);
		}
		votes.push_back(scaleVotes);
	}

	return votes;
}


Mat yours::binarizeGradientImage(Mat& src, double threshold){

	Mat binaryImage;
	vector<Mat> channels;
	split(src, channels);

	channels[0] = cv::abs(channels[0]);

	double min, max;
	cv::minMaxLoc(channels[0], &min, &max);

	cv::threshold(channels[0], binaryImage, threshold*max, 0, 3);

	return binaryImage;
	/*Mat binaryImage;

	src = cv::abs(src);

	double min, max;
	cv::minMaxLoc(src, &min, &max);

	cv::threshold(src, binaryImage, threshold*max, 255, 3);

	return binaryImage;*/
}
