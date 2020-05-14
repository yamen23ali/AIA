//
// Implement the required functions here.
//
#include "yours.hpp"
#include "given.hpp"


void yours::binarizeImage(const cv::Mat& src, cv::Mat& dst, int thresh) {

	cv::Mat grayScaleImage;

    // TODO: convert image to gray scale
    // https://docs.opencv.org/4.2.0/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab
    cv::cvtColor(src, grayScaleImage, cv::COLOR_BGR2GRAY);

    // TODO: Binarize image
    // https://docs.opencv.org/4.2.0/d7/d1b/group__imgproc__misc.html#gae8a4a146d1ca78c626a53577199e9c57
    cv::threshold(grayScaleImage, dst, thresh, 255, 0);
}

cv::Mat yours::processImage(const cv::Mat& image) {
	cv::Mat smoothedImage;
	cv::Mat finalImage;

    given::smoothImage(image, smoothedImage);
    yours::binarizeImage(smoothedImage, finalImage);

    return finalImage;
}


// TODO: Implement processImage
// use smoothImage from given.hpp
//   (tests only work if you don't change the default value for size)
