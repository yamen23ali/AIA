#ifndef __YOURS_H_
#define __YOURS_H_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace yours {

Mat toFreqDomain(Mat& image);
void drawz(Mat &image);

// shows hough space, eg. as a projection of angle- and scale-dimensions down to a single image
/*
  houghSpace:   the hough space as generated by generalHough(..)
*/
Mat visualizeHoughSpace(vector< vector<Mat> >& houghSpace);


// creates the fourier-spectrum of the scaled and rotated template
/*
  templ:    the object template; binary image in templ[0], complex gradient in templ[1]
  scale:    the scale factor to scale the template
  angle:    the angle to rotate the template
  fftMask:  the generated fourier-spectrum of the template (initialized outside of this function)
*/
void makeFFTObjectMask(vector<Mat>& templ, double scale, double angle, Mat& fftMask);


// computes the hough space of the general hough transform
/*
  gradImage:    the gradient image of the test image
  templ:        the template consisting of binary image and complex-valued directional gradient image
  scaleSteps:   scale resolution
  scaleRange:   range of investigated scales [min, max]
  angleSteps:   angle resolution
  angleRange:   range of investigated angles [min, max)
  return:       the hough space: outer vector over scales, inner vector of angles
*/
vector< vector<Mat> > generalHough(Mat& gradImage, vector<Mat>& templ, double scaleSteps, double* scaleRange, double angleSteps, double* angleRange);


// creates binary image from gradient images
/*
  src:              gradient image
  threshold:        threshold for binarization (thresh*max(gradient amplitude))
  return:           the computed binary
*/
Mat binarizeGradientImage(Mat& src, double threshold);



}

#endif // __YOURS_H_
