//
//  ReflectionDetection.cpp
//
//  Created by Waqas Haider Sheikh on 02/06/2019.
//  Copyright © 2019 Waqas Haider Sheikh. All rights reserved.
//

#include "Utils.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "ReflectionDetection.hpp"

using namespace std;

/**
 this function detect reflection in matrix
 reference: https://www.pyimagesearch.com/2016/10/31/detecting-multiple-bright-spots-in-an-image-with-python-and-opencv/
 
 @param source matrix
 @return true/false
 */
bool ReflectionDetection::detectReflection(cv::Mat source) {
    
    // smooth the image using a 11x11 Gaussian
    cv::GaussianBlur(source, source, cvSize(11,11), 0);
    
    // threshold the image to reveal light regions in the blurred image
    cv::Mat mrzThresh;
    cv::threshold(source, mrzThresh, 200, 255, cv::THRESH_BINARY);
    
    // perform a series of erosions and dilations to remove any small blobs of noise from the thresholded image
    cv::erode(mrzThresh, mrzThresh, cv::Mat(), cv::Point(-1,-1), 2);
    cv::dilate(mrzThresh, mrzThresh, cv::Mat(), cv::Point(-1,-1), 4);
    
    float largest_radius = 0.0;
    float threshold = 20.0;
    
    // vector for storing contours
    vector<vector<cv::Point>> contours;
    
    // find the contours in the image
    findContours(mrzThresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    // sort contours by descending order
    std::sort(contours.begin(), contours.end(), compareContourAreas);
    
    // iterate through each contour.
    for(int i = 0; i< contours.size(); i++) {
        
        cv::Point2f point;
        float radius;
        
        cv::minEnclosingCircle(contours[i], point, radius);
        
        if (radius > largest_radius) {
            largest_radius = radius;
        }
    }
    
    // release mrz thresh
    mrzThresh.release();
    
    return largest_radius > threshold;
}

// comparison function object
bool compareContourAreas ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2) {
    double i = fabs( contourArea(cv::Mat(contour1)));
    double j = fabs( contourArea(cv::Mat(contour2)));
    return ( i > j );
}
