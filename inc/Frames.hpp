#pragma once
#include <opencv2/opencv.hpp>

#include <fstream>


#define buttonWidth 150
#define buttonHeight 40
#define spacing 100
#define baseHeight 120
#define baseWidth 600


std::map<std::string,int> lockedFolder;

cv::Rect ADD/UPDATE = cv::Rect(550, baseHeight, buttonWidth + 50, buttonHeight);
cv::Rect unLOCK = cv::Rect(baseWidth, baseHeight + buttonHeight + spacing, buttonWidth, buttonHeight);
cv::Rect LOCK = cv::Rect(baseWidth, baseHeight + 2 * (buttonHeight + spacing), buttonWidth, buttonHeight);
cv::Rect back = cv::Rect(baseWidth, baseHeight + 3 * (buttonHeight + spacing), buttonWidth, buttonHeight);


void onMouseClick(int event, int x, int y, int flags, void* userdata);

void mainScreen();

void Face_Data_Frame();

void unLock();

void Lock();


void fill();

void empty();




