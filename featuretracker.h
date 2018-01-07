#ifndef FEATURETRACKER_H
#define FEATURETRACKER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class FeatureTracker
{
    cv::Mat gray;           //当前灰度图像
    cv::Mat gray_prev;      //上一个灰度图像

    std::vector<cv::Point2f> points[2];  //被跟踪的特征0到1
    std::vector<cv::Point2f> initial;    //被跟踪特征点的初始位置
    std::vector<cv::Point2f> features;    //被检测的特征

    int max_count;      //检测特征点的最大个数
    double qlevel;      //检测特征点的质量等级
    double minDist;     //两个特征点之间的最小差距

    std::vector<uchar>  status; //被跟踪特征的状态
    std::vector<float>  err;    //跟踪中出现的误差

public:
    FeatureTracker();
    //处理过程包括
    //1，如果需要就检测特征点
    //2,跟踪特征点剔除无法跟踪或不需要跟踪的特征点
    //3, 准备处理跟踪成功的特征点
    //4,当前的帧和特征点作为下一个迭代项的上一帧和上一批特征点


    void process(cv::Mat &frame,cv::Mat &output);               //在处理序列中的每个帧时被调用
    void detectFeaturePoints();                                 //特征点检测方法
    bool addNewPoints();                                        //判断是否需要检测新的点
    bool acceptTrackedPoint(int i);                             //根据程序定义的条件剔除部分被跟踪的特征点
    void handleTrackedPoints(cv::Mat &frame, cv::Mat &output);  //处理被跟踪的点，做法时在当前帧画直线
                                                                //连接特征点和它们的初始位置

};

#endif // FEATURETRACKER_H
