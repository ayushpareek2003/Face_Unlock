#include "Input_Box.hpp"



std::string inputBOX()
{
	cv::Mat img = cv::Mat::ones(600, 600, CV_8UC1) * 255;

	std::string inputStorage;
	cv::namedWindow("trials", cv::WINDOW_AUTOSIZE);
	while (true) {
		cv::Mat tempIMG = img.clone();


		cv::putText(tempIMG, inputStorage, cv::Point(50, 120), cv::FONT_HERSHEY_COMPLEX, 0.7,cv::Scalar(0,0,0));



		cv::imshow("trials", tempIMG);


		char next = cv::waitKey(0);
		if (next == 8) {
			if (inputStorage.size() > 0) {
				
				inputStorage.pop_back();
				std::cout << inputStorage << std::endl;
			}
		}
		else if(next==27) {
			break;
		}
		else if (next >= 32 && next <= 126) {
			inputStorage.push_back(next);
		}





	}
	cv::destroyAllWindows();



}
