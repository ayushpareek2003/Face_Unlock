#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/video.hpp>
#include <Windows.h>
#include <opencv2/imgproc.hpp>
#include <algorithm>

int main() {



    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video capture." << std::endl;

        return -1;
    }

    cv::Mat frame;
    cv::dnn::Net mod = cv::dnn::readNet("D://Models//yolov8n-face.onnx");


    mod.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    mod.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured." << std::endl;
            break;
        }






        cv::flip(frame, frame, 1); // Flip frame horizontally

        cv::Size inputSize(640, 640);
        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, inputSize);
        cv::Mat blob = cv::dnn::blobFromImage(resizedFrame, 1.0 / 255.0, inputSize, cv::Scalar(0, 0, 0), true, false);

        mod.setInput(blob);

        std::vector<cv::Mat> outputs;
        mod.forward(outputs, mod.getUnconnectedOutLayersNames());

        if (outputs.empty()) {
            std::cerr << "Error: No output received from the network." << std::endl;
            break;
        }

        

        for (const cv::Mat& output : outputs) {
            std::cout << "Output size: " << output.size() << std::endl;

            // Iterate through detections
            for (int i = 0; i < output.size[0]; i++) {
                float confidence = output.at<float>(i, 4);
                if (confidence > 0.5) {
                    float xCenter = output.at<float>(i, 0);
                    float yCenter = output.at<float>(i, 1);
                    float width = output.at<float>(i, 2);
                    float height = output.at<float>(i, 3);

                    // Scale to original frame size
                    int frameWidth = frame.cols;
                    int frameHeight = frame.rows;
                    int x1 = static_cast<int>((xCenter - width / 2)+640 );
                    int y1 = static_cast<int>((yCenter - height / 2)+640);
                    int x2 = static_cast<int>((xCenter + width / 2)+640 );
                    int y2 = static_cast<int>((yCenter + height / 2)+640);


                    // Draw bounding box
                    cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);
                }
            }
        }

        cv::imshow("Webcam", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();

    cv::destroyAllWindows();
    return 0;
}