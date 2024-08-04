#include "add_update.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>


//auto yolo_model = cv::dnn::readNet("D://FACE_DUMMY//assets//yolov8n - face.onnx");
void loader() {
    cv::dnn::Net net = cv::dnn::readNet("D://Models//faceNet.onnx");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}




void add_update::Data_au() {
    cv::VideoCapture cap(0);
    
    loader();
    cv::Mat frame;
    std::vector<cv::Mat> face;
    while (true) {
        
        cap >> frame;

        
        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured." << std::endl;
            break;
        }
 
        cv::flip(frame, frame, 1);
        cv::imshow("Webcam", frame);

        
        if (cv::waitKey(1) == 'q') {
            break;
        }
        else if (cv::waitKey(1) == ' ') {
            face.push_back(frame);
        }
    }

    
    cap.release();    
    cv::destroyAllWindows();





}



std::vector<int> add_update::fac_emb(std::vector<cv::Mat> data_2)
{

    ///to generate emmbedings 
    return std::vector<int>();
}
