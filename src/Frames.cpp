#include "Frames.hpp"
#pragma once

#include <filesystem>
#include <Windows.h>
#include <iostream>
#include "Input_Box.hpp"
#include <sys/stat.h>
#include <windows.h>
#include <aclapi.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <filesystem>
#include "modifyACL.hpp"
#include "infer_cuDNN.hpp"

int height;
int width;



    std::string pathToYolo = "D:\\FACE_DUMMY\\assets\\yolov8n-face.onnx";
    std::string pathToFacenet = "D:\\face_id_workshop\\faceNet.onnx";

    infer_cuDNN faceInfer(pathToYolo, pathToFacenet);



int main() {


    mainScreen();

    return 0;
}




void onMouseClick(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Point clickPoint(x, y);

        if (button1.contains(clickPoint)) {
  
            Face_Data_Frame();
             
        }
        else if (button2.contains(clickPoint)) {
            cv::destroyWindow("Face ID");
            unLock();
            cv::destroyAllWindows();
            mainScreen();
        }
        else if (button3.contains(clickPoint)) {
            cv::destroyWindow("Face ID");
            Lock();
            cv::destroyAllWindows();
            mainScreen();
            
            

        }
        else if (button4.contains(clickPoint)) {
            std::cout << "Button 4 clicked!" << std::endl;
        }
    }
}



void mainScreen() {
    std::string path = "D:\\PRojects\\Media_Face_ID\\trails.png";
    cv::Mat image = cv::imread(path);

    

    if (image.empty()) {
        std::cerr << "Error loading image." << std::endl;
        return;
    }
  
    cv::namedWindow("Face ID", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Face ID", onMouseClick, NULL);
   
    height = image.rows;
    width = image.cols;
    std::cout << height << " " << width;





    while (true) {

        cv::Mat displayImage = image.clone();


        rectangle(displayImage, button1, cv::Scalar(0, 0, 0), -1);
        rectangle(displayImage, button2, cv::Scalar(0, 0, 0), -1);
        rectangle(displayImage, button3, cv::Scalar(0, 0, 0), -1);
        rectangle(displayImage, button4, cv::Scalar(0, 0, 0), -1);


        cv::putText(displayImage, "ADD/UPDATE Data", cv::Point(button1.x + 10, button1.y + 25), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
        cv::putText(displayImage, "Unlock", cv::Point(button2.x + 10, button2.y + 25), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(displayImage, "Lock", cv::Point(button3.x + 10, button3.y + 25), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(displayImage, "Back", cv::Point(button4.x + 10, button4.y + 25), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
      
        
        cv::imshow("Face ID", displayImage);
       

        char key = (char)cv::waitKey(0);
        if (key == 'q' || key == 27) {
            break;
        }
    }

    cv::destroyAllWindows();

}


void Face_Data_Frame() {
    

    ///onnx model for infer using dnn or tensor rt which ever is fast
    std::string out = "ADD/UPDATE";
    int sam=faceInfer.instructionFrames(out);
    cv::VideoCapture cam(0);
    cv::namedWindow("Face Data", cv::WINDOW_AUTOSIZE);
    std::vector<cv::Mat> selectedFaces;
    int f = 0;
    while (true) {
        cv::Mat inpFrame;
        cam>> inpFrame;

        if (inpFrame.empty()) {
            std::cerr<<"WEBCAM khrab h tera" << std::endl;
        }
        cv::flip(inpFrame, inpFrame, 1);


        cv::Mat temp= faceInfer.faceROI(inpFrame);
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
       
        cv::Mat backupFace;
        int key = cv::waitKey(1);
        if (key == 'q') {
            break;
        }
        else if (key == ' ') {

            if (faceFinal.rows>0) {
                f = 1;
                backupFace = faceFinal.clone();
                cv::imshow("Selected Frame", faceFinal);

                cv::imwrite("D:\\PRojects\\Media_Face_ID\\FaceData.png", backupFace);
            }

        }


        



    }

    cv::destroyWindow("Face Data");

    if (f == 1) {
        cv::destroyWindow("Selected Frame");
    }


    

   

    return;






}

void unLock()
{
    cv::Mat backGround = cv::Mat::ones(height, width, CV_8UC1) * 255;
    cv::putText(backGround, "Enter The Path and Press ESC once done ", cv::Point(150, 150),cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 0, 0), 2);
    std::string pathFolder = "";
    
    while (true) {
        cv::Mat temp = backGround.clone();
        cv::putText(temp, pathFolder, cv::Point(150, 350), cv::FONT_HERSHEY_SCRIPT_COMPLEX, 1, cv::Scalar(0, 0, 0), 2);


        cv::imshow("Unlock",temp);
        int key = cv::waitKey(0);

        if (key ==27) {

            break; 
        }
        else if (key == 8) {
            pathFolder.pop_back();
        }
        
        else{
            pathFolder += key;

        }

    }

    std::cout << pathFolder << std::endl;
    
    int status=unlockFolder(pathFolder);
   

}

bool folderExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;  // Cannot access path
    }
    else if (info.st_mode & S_IFDIR) {
        return true;   // Path is a directory
    }
    else {
        return false;  // Path exists, but it's not a directory
    }
}

void Lock()
{
    cv::Mat image = cv::imread("D:\\PRojects\\Media_Face_ID\\FaceData.png");  // Try to load the image
    if (image.empty()) {
        int sam=faceInfer.instructionFrames("NoData");
        if (sam == 1) {
            Face_Data_Frame();

        }

        return ;  // Image could not be loaded
    }
    




    cv::Mat backGround = cv::Mat::ones(height, width, CV_8UC1) * 255;
    cv::putText(backGround, "Enter The Path and Press ESC once done ", cv::Point(150, 150), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 0, 0), 2);
    std::string pathFolder = "";

    while (true) {
        cv::Mat temp = backGround.clone();
        cv::putText(temp, pathFolder, cv::Point(150, 350), cv::FONT_HERSHEY_SCRIPT_COMPLEX, 1, cv::Scalar(0, 0, 0), 2);


        cv::imshow("Unlock", temp);
        int key = cv::waitKey(0);

        if (key == 27) {

            break;
        }
        else if (key == 8) {
            pathFolder.pop_back();
        }

        else {
            pathFolder += key;

        }



    }
    std::cout << pathFolder << std::endl;
    
    int status = lockFolder(pathFolder);

    std::string res="Locked Successfully";
    if (status == 1) {
        res = "failed";
    }
    //cv::destroyAllWindows();
    //backGround = cv::Mat::ones(height, width, CV_8UC1) * 255;
    //cv::putText(backGround, res, cv::Point(150, 350), cv::FONT_HERSHEY_COMPLEX, 3, cv::Scalar(0, 0, 0), 2);
    //cv::imshow("Face Unlock", backGround);
    //std::this_thread::sleep_for(std::chrono::seconds(2));


    
    

}




