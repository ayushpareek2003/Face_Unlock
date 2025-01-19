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

std::vector<float> infer_cuDNN::embGen(cv::Mat img)
{
	cv::Mat resized,normalised;
	cv::resize(img, resized, cv::Size(160, 160));

	resized.convertTo(resized, CV_32F, 1.0 / 127.5, -1.0);
	resized.convertTo(normalised, CV_32F, 1.0 / 127.5, -1.0);

	// Convert HWC (height, width, channels) to NCHW (batch size, channels, height, width)
	cv::Mat blob = cv::dnn::blobFromImage(normalised, 1.0, cv::Size(160, 160), cv::Scalar(), true, false);

	// Set the blob as input to the model
	modelRecog.setInput(blob);

	// Forward pass through the network to get the embedding
	cv::Mat embedding = modelRecog.forward();

	// Convert the embedding to a vector
	std::vector<float> embeddingVec;
	embedding = embedding.reshape(1, 1); // Flatten the 128x1 embedding into a vector
	embedding.copyTo(embeddingVec);

	return embeddingVec;
}



bool infer_cuDNN::recogFace(cv::Mat& inp) {
	

	cv::Mat source = cv::imread("D:\\PRojects\\Media_Face_ID\\FaceData.png");

	std::vector<float> embeddingVec = embGen(inp);

	std::vector<float> sourceEmb = embGen(source);



	

	float sum = 0;
	for (size_t i = 0; i < embeddingVec.size(); ++i) {
		float diff = embeddingVec[i] - sourceEmb[i];
		sum += diff * diff;
	}
	sum=sqrt(sum);


	if (sum < 0.8) {
		return true;
	}
	return false;


}

cv::Mat infer_cuDNN::unlockFace(int amount) {
	cv::VideoCapture cam(0);
	cv::namedWindow("Face Data", cv::WINDOW_AUTOSIZE);
	
	cv::Mat backupFace;
	int f = 0;
	while (true) {
		cv::Mat inpFrame;
		cam >> inpFrame;

		if (inpFrame.empty()) {
			std::cerr << "WEBCAM khrab h tera" << std::endl;
		}
		cv::flip(inpFrame, inpFrame, 1);


		cv::Mat temp = faceROI(inpFrame);
		cv::Mat faceFinal;
		for (int j = 0; j < temp.rows; j++) {

			if (temp.at<float>(j, 4) > 0.5) {

				int x = static_cast<int>(temp.at<float>(j, 0) * inpFrame.cols);
				int y = static_cast<int>(temp.at<float>(j, 1) * inpFrame.rows);
				int X = static_cast<int>(temp.at<float>(j, 2) * inpFrame.cols);
				int Y = static_cast<int>(temp.at<float>(j, 3) * inpFrame.rows);


				float shrinkFactor = 0.8;

				int newWidth = static_cast<int>(X * shrinkFactor);
				int newHeight = static_cast<int>(Y * shrinkFactor);


				int newX = x + (X - newWidth) / 2;
				int newY = y + (Y - newHeight) / 2;

				if (newX >= 0 && newY >= 0 && newWidth > 0 && newHeight > 0 &&
					newX + newWidth <= inpFrame.cols && newY + newHeight <= inpFrame.rows) {

					faceFinal = inpFrame(cv::Rect(newX, newY, newWidth, newHeight)).clone();
				}

				cv::rectangle(inpFrame, cv::Point(newX, newY), cv::Point(newX + newWidth, newY + newHeight), cv::Scalar(0, 255, 0), 2);

			}

		}

		cv::imshow("Face Data", inpFrame);

		
		int key = cv::waitKey(1);
		if (key == 'q') {
			break;
		}
		else if (key == ' ') {

			if (faceFinal.rows > 0 && amount) {
				f = 1;
				backupFace = faceFinal.clone();
				cv::imshow("Selected Frame", faceFinal);

				if (amount==0) {
					cv::imwrite("D:\\PRojects\\Media_Face_ID\\FaceData.png", backupFace);
					
				}
		
				
			}

		}
	}

	cv::destroyWindow("Face Data");

	if (f == 1) {
		cv::destroyWindow("Selected Frame");
	}
	return backupFace;

}


