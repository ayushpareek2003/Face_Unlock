# FaceUnlock for Windows

## Overview
FaceUnlock for Windows is a facial recognition-based authentication system built using **C++**. It leverages **OpenCV (compiled with CUDA)** for real-time face detection and recognition, integrates **Access Control Lists (ACLs)** for security, and provides a **GUI using OpenCV**. The detection model is **YOLOv8**, and recognition is handled using **FaceNet**. The entire project follows an **Object-Oriented Programming (OOP)** approach and is managed using **CMake**.

## Features
- **Real-time Face Detection** using YOLOv8.
- **Face Recognition** using FaceNet.
- **High-performance computation** with OpenCV compiled with CUDA.
- **Windows Access Control List (ACL) integration** for secure authentication.
- **Object-Oriented Codebase** for modular and scalable design.
- **GUI interface** built with OpenCV.
- **CMake-based Build System** for easy compilation and deployment.

## Requirements
### Hardware
- Windows PC with **NVIDIA GPU** (for CUDA acceleration)
- Camera (built-in or external)

### Software & Libraries
- **C++ (MSVC/MinGW compiler)**
- **CMake**
- **OpenCV (compiled with CUDA)**
- **YOLOv8** (for detection)
- **FaceNet** (for recognition)
- **Windows SDK** (for ACL integration)

### How to build
mkdir build
cd build
cmake ..
cmake --build . --config Release

## Installation & Setup
### 1. Clone the Repository
```sh
git clone https://github.com/yourusername/FaceUnlock-Windows.git
cd FaceUnlock-Windows
