#pragma once
#include <windows.h>
#include <aclapi.h>
#include <tchar.h>
#include <iostream>
#include <string>

int lockFolder(const std::string& folderPath);

int unlockFolder(const std::string& folderPath);
