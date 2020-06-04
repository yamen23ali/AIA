//
// Do not change this file.
//
#include "../test/catch.hpp"
#include <opencv2/opencv.hpp>
#include "../src/yours.hpp"
#include "../src/app.cpp"

using namespace std;
using namespace cv;


// generates the test image as a transformed version of the template image
/*
  temp:         the template image
  angle:    rotation angle
  scale:    scaling factor
  scaleRange:   scale range [min,max], used to determine the image size
*/
Mat makeTestImage(Mat& temp, double angle, double scale, vector<double> scaleRange){

    // rotate and scale template image
    Mat small = given::rotateAndScale(temp, angle, scale);

    // create empty test image
    Mat testImage = Mat::zeros(temp.rows*scaleRange[1]*2, temp.cols*scaleRange[1]*2, CV_32FC1);
    // copy new object into test image
    Mat tmp;
    Rect roi;
    roi = Rect( (testImage.cols - small.cols)*0.5, (testImage.rows - small.rows)*0.5, small.cols, small.rows);
    tmp = Mat(testImage, roi);
    small.copyTo(tmp);

    return testImage;
}

Mat loadTestImage(){
    // load template image as gray-scale
    string path = "data/test_object.png";
    Mat testobj = imread(path, 0);
    if (!testobj.data){
        cerr << "ERROR: Cannot load test object from\n" << path << endl;
        exit(-1);
    }
    // convert 8U to 32F
    testobj.convertTo(testobj, CV_32F);
    return testobj;
}


Mat loadParams(){
        // processing parameter
    double sigma            = 1;        // standard deviation of directional gradient kernel
    double templateThresh   = 0.7;      // relative threshold for binarization of the template image
    double objThresh        = 0.85;         // relative threshold for maxima in hough space
    double scaleSteps       = 5;        // scale resolution in terms of number of scales to be investigated
    double scaleRange[2];               // scale of angles [min, max]
    scaleRange[0]           = 1;
    scaleRange[1]           = 5;
    double angleSteps       = 12;       // angle resolution in terms of number of angles to be investigated
    double angleRange[2];               // range of angles [min, max)
    angleRange[0]           = 0;
    angleRange[1]           = 2*CV_PI;
    return (Mat_<float>(1,9) << sigma, templateThresh, objThresh, scaleSteps, scaleRange[0], scaleRange[1], angleSteps, angleRange[0], angleRange[1]);
}



TEST_CASE("Test rotation", "rotation") {
    // load params
    Mat params = loadParams();

    double testAngle = 7*(2.0*CV_PI/params.at<float>(6));
    double testScale = params.at<float>(4)+0*((params.at<float>(5)-params.at<float>(4))/(params.at<float>(3)-1));

    // load image
    Mat testobj = loadTestImage();
    // generate test image
    Mat testimg = makeTestImage(testobj, testAngle, testScale, {params.at<float>(4), params.at<float>(5)});
    // get object candidates
    vector<Scalar> objList;
    app(testobj, testimg, objList, params);

    SECTION("Multiple Maxima") {
        INFO("There is no problem! More than one maxima found.");
        REQUIRE(objList.size() == 1);
    }
    SECTION("Rotation") {
        INFO("There is a problem! Rotation not correct.");
        REQUIRE(objList[0].val[1] == 7);
    }
}


