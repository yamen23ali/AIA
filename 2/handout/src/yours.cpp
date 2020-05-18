//
// Implement the required functions here.
//
#include "yours.hpp"
#include "given.hpp"

using namespace cv;

void yours::preprocessImage(Mat& src, Mat& dst, int bin_thresh, int n_erosions) {

    Mat tmp = src;
    if(src.channels() > 1)
        cvtColor(src, tmp, cv::COLOR_BGR2GRAY);

    Mat binaryImage;
    Mat erodedImage;

    // Binarize Image
    threshold(tmp, binaryImage, bin_thresh, 255, 1);

    // use erosion to get rid of small objects and break connections between leafs
    // use a 3x3 structuring element (cv::Mat::ones(3, 3, CV_8UC1))
    erode( binaryImage, dst, Mat::ones(3, 3, CV_8UC1), Point(-1, -1), n_erosions, 1, 1);
}

Mat yours::getFourierDescriptor(const Mat& contour) {

    Mat contourF;
    // convert to flaot
    contour.convertTo(contourF, CV_32F);

    // prepare output matrices ( one for magnitude and the other for phase)
    Mat planes[] = {Mat::zeros(contourF.size(), CV_32F), Mat::zeros(contourF.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    // perform DFT
    dft(contourF, complexI);
    
    return complexI;
}

Mat yours::normalizeFourierDescriptor(const Mat& fd, int n) {

    // translation invariance F(0) = 0
    Mat translationInv = fd.rowRange(1, fd.rows);


    // rotation invariance F = |F|
    // There are some useful OpenCV functions such as cartToPolar
    std::vector<Mat> channels(2);
    Mat magnitued;
    Mat angle;

    split(translationInv, channels);
    cartToPolar(channels[0], channels[1], magnitued, angle);

    // scale invariance F(i) = F(i)/|F(1)|
    // What if |F(1)| = 0?
    int scalarInd = 0;
    
    // in case F(0) is zero choose the nth component F(n), but what if F(n) is also zero ?
    if(magnitued.at<int>(scalarInd,0) == 0){ 
        scalarInd = n - 1;
    }

    float scalar = 1.0f / abs(magnitued.at<float>(scalarInd,0));
    Mat scaleInv = magnitued * scalar;


    // smaller sensitivity for details
    // This one is a bit tricky. How does your descriptor look like?
    // Where are the high frequencies and where are the negative indices?
    if(n > scaleInv.rows){
        return scaleInv;
    }else{
        return scaleInv.rowRange(0,n);
    }
}

int yours::classifyFourierDescriptor(const Mat& fd, const std::vector<Mat>& class_templates, float thresh) {
    // loop over templates and find closest, return index
    // use cv::norm as a disctance metric

    double minDistance =  std::numeric_limits<double>::max();
    int minIndex = -1;

    for(std::vector<int>::size_type i = 0; i != class_templates.size(); i++) {
        double distance = norm(fd, class_templates[i].rowRange(0, fd.rows));

        if(distance < minDistance && distance <= thresh){
            minDistance = distance;
            minIndex = i;
        }
    }

    return minIndex;
}
