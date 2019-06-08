//
//  ReflectionDetection.hpp
//
//  Created by Waqas Haider Sheikh on 02/06/2019.
//  Copyright © 2019 Waqas Haider Sheikh. All rights reserved.
//

#import <opencv2/opencv.hpp>

class ReflectionDetection {
public:
    static bool detectReflection(cv::Mat source);
};
