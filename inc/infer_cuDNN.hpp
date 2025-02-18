#pragma once

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>


class infer_cuDNN
{
public:
	cv::dnn::Net modelDetect;
	cv::dnn::Net modelRecog;

	infer_cuDNN(const std::string pathToYolo,const std::string pathToFacenet);

	cv::Mat faceROI(cv::Mat& inpFrame);

	bool recogFace(cv::Mat& inp,cv::Mat& src);

	/*bool cosineSimi(cv::Mat& inp,cv::)*/

	int instructionFrames(std::string ins);

	std::vector<float> embGen(cv::Mat img);

	cv::Mat unlockFace(int amount);
};

