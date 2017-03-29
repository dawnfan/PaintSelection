#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\ml.hpp>

using namespace cv;

class Selection
{
public:
	Selection();
	~Selection();
private:
	// foreground and bg GMM model
	cv::Ptr<ml::EM> fg_GMM;
	cv::Ptr<ml::EM> bg_GMM;
};
