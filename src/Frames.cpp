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


int height;
int width;

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
            std::cout << "Button 3 clicked!" << std::endl;
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
       

        char key = (char)cv::waitKey(10);
        if (key == 'q' || key == 27) {
            break;
        }
    }

    cv::destroyAllWindows();

}


void Face_Data_Frame() {
    

    ///onnx model for infer using dnn or tensor rt which ever is fast
    cv::VideoCapture cam(0);
    cv::namedWindow("Face Data", cv::WINDOW_AUTOSIZE);
    while (true) {
        cv::Mat frm;
        cam>> frm;

        if (frm.empty()) {
            std::cerr<<"WEBCAM khrab h tera" << std::endl;
        }
        cv::flip(frm, frm, 1);
        cv::imshow("Face Data", frm);

        if (cv::waitKey(1) == 'q') {
            break;
        }


    }

    cv::destroyWindow("Face Data");
   

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
    std::string pathtoFolder = inputBOX();
    struct stat info;
    stat(pathtoFolder.c_str(), &info);

    if (info.st_mode && S_IFDIR) {






    }
    

}




