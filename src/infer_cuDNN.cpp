#include "infer_cuDNN.hpp"



infer_cuDNN::infer_cuDNN(const std::string pathToYolo,const std::string pathToFacenet) {
	modelDetect = cv::dnn::readNetFromONNX(pathToYolo);
	modelRecog = cv::dnn::readNetFromONNX(pathToFacenet);

	modelDetect.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
	modelDetect.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

	//modelDetect.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	//modelDetect.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);


	modelRecog.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
	modelRecog.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

}

cv::Mat infer_cuDNN::faceROI(cv::Mat& inpFrame) {
	cv::Mat blob = cv::dnn::blobFromImage(inpFrame, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(0, 0, 0), true, false);
	if (modelDetect.empty()) {
		std::cerr << "Error: Failed to load the YOLO model!" << std::endl;
	}

	modelDetect.setInput(blob);

	std::vector<cv::Mat> outputs;

	modelDetect.forward(outputs);
	
	if (outputs.empty()) {
		std::cerr << "Error: No outputs from YOLO model!" << std::endl;
		return inpFrame;
	}

		cv::Mat temp = outputs[0].reshape(1, outputs[0].total() / 6);

	return temp;
}

int infer_cuDNN::instructionFrames(std::string ins)
{
	
		cv::Mat frm = cv::Mat::ones(200, 480, CV_8UC1) * 255;
		std::string message;
		if (ins == "ADD/UPDATE") {
			 message= "When a green rectangle comes \naround your face properly \nPress space to use that Face \n \nPress 'Q' to close this";
		}
		else if (ins == "NoData") {
			message = "No Face Data Found \nPress Space to setup FacID";
		}

		
		std::vector<std::string> lines;
		std::istringstream stream(message);
		std::string line;
		while (std::getline(stream, line, '\n')) {
			lines.push_back(line);
		}

		int y_offset = 30;
		for (size_t i = 0; i < lines.size(); i++) {
			cv::putText(frm, lines[i], cv::Point(20, y_offset), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0), 2);
			y_offset += 30;  
		}

		cv::imshow("Alert", frm);
		
		int key = cv::waitKey(0);
		if (key == 'Q' || key == 'q') {
			cv::destroyWindow("Alert");
			return 0;
		}
		else if (key == ' ') {
			cv::destroyWindow("Alert");
			return 1;
			
		}
	

	

}
