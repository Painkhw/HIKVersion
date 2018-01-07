#include "featuretracker.h"

FeatureTracker::FeatureTracker()
{
    max_count = 500;
    qlevel = 0.01;
    minDist = 10.0;
}

void FeatureTracker::process(cv::Mat &frame, cv::Mat &output)
{
    //转换成灰度图像
    cv::cvtColor(frame,gray,CV_BGR2GRAY);
    frame.copyTo(output);

    //1.如果必须添加新的特征点
    if(addNewPoints())
    {
        //检测特征点
        detectFeaturePoints();
        //在当前跟踪列表中添加检测到的点
        points[0].insert(points[0].end(),features.begin(),features.end());
        initial.insert(initial.end(),features.begin(),features.end());
    }
    //对于序列中的第一个图像
    if(gray_prev.empty())
        gray.copyTo(gray_prev);

    //2.跟踪特征
    cv::calcOpticalFlowPyrLK(gray_prev,  //2个连续图像
                             gray,       //输入第一个图像的特征点位置
                             points[0],  //输出第二个图像的特征点位置
                             points[1],  //跟踪成功
                             status,err);//跟踪误差

    //3. 循环检查被跟踪的特征点，剔除部分
    int k=0;
    for(int i=0; i<points[1].size();i++)
    {
        //是否保留这个特征点？
        if(acceptTrackedPoint(i))
        {
           //在向量中保留这个特征点
            initial[k] = initial[i];
            points[1][k++] = points[1][i];
        }
    }

    //剔除跟踪失败的特征点
    points[1].resize(k);
    initial.resize(k);

    //4.处理已经认可的被跟踪特征点
    handleTrackedPoints(frame,output);

    //5.当前特征点和图像变成一个
    std::swap(points[1],points[0]);
    cv::swap(gray_prev,gray);

}

//特征点检测方法

void FeatureTracker::detectFeaturePoints()
{
    //检测特征点
    cv::goodFeaturesToTrack(gray,       //图像
                            features,   //输出检测到的特征点
                            max_count,  //特征点的最大数量
                            qlevel,     //质量等级
                            minDist     //特征点之间的最小差距
                            );

}

//判断是否需要添加新的特征点

bool FeatureTracker::addNewPoints()
{
    //如果特征点数量太小
    return points[0].size()<=10;
}

//判断需要保留的特征点

bool FeatureTracker::acceptTrackedPoint(int i)
{
    return status[i]&&(abs(points[0][i].x-points[1][i].x)
                        +
                      (abs(points[0][i].y-points[1][i].y))>2);

}


//处理当前跟踪的特征点
void FeatureTracker::handleTrackedPoints(cv::Mat &frame, cv::Mat &output)
{
    //遍历所有特征点
    for(int i=0; i<points[1].size(); i++)
    {
        //画线和圆
        cv::line(output,
                 initial[i],        //初始位置
                 points[1][i],      //新位置
                 cv::Scalar(255,255,255)
                );
        cv::circle(output,points[1][i],3,cv::Scalar(255,255,255),-1);
    }
}
