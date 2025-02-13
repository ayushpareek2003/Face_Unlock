# FaceUnlock for Windows

## Overview
FaceUnlock for Windows is a facial recognition-based authentication system built using **C++** It leverages **OpenCV (compiled with CUDA)** for real-time face detection and recognition, integrates **Access Control Lists (ACLs)** for security, and provides a **GUI using OpenCV** The detection model is **YOLOv8**, and recognition is handled using **FaceNet** The entire project follows an **Object-Oriented Programming (OOP)** approach and is managed using **CMake**

## Features
- **Real-time Face Detection** using YOLOv8
- **Face Recognition** using FaceNet
- **High-performance computation** with OpenCV compiled with CUDA
- **Windows Access Control List (ACL) integration** for secure authentication
- **Object-Oriented Codebase** for modular and scalable design
- **GUI interface** built with OpenCV
- **CMake-based Build System** for easy compilation and deployment

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

## Installation & Setup
### 1 Clone the Repository
```sh
git clone https://githubcom/yourusername/FaceUnlock-Windowsgit
cd FaceUnlock-Windows
```

### 2 Build the Project

#### Using CMake

```sh
mkdir build
cd build
cmake 
cmake --build  --config Release
```

### 3 Run the Application

```sh
/FaceUnlock
```

## Project Structure

```
FaceUnlock-Windows/
│── src/                  # Source Code (OOP-based)
│   ├── maincpp          # Entry point
│   ├── FaceDetectorcpp  # YOLOv8 face detection logic
│   ├── FaceRecognizercpp # FaceNet recognition logic
│   ├── ACLManagercpp    # Windows ACL integration
│   ├── GUIcpp           # OpenCV-based GUI
│── include/              # Header files
│── models/               # YOLOv8 and FaceNet models
│── cmake/                # CMake configuration
│── assets/               # UI assets if needed
│── READMEmd             # Project documentation
```

## Usage

1 Run the executable
2 The application will detect and recognize faces
3 If the recognized face matches the stored identity, access is granted via ACL
4 The GUI will display authentication status

## Contributing

Feel free to fork the repository and submit pull requests with improvements


## Acknowledgments

- OpenCV for computer vision capabilities
- YOLOv8 for fast face detection
- FaceNet for accurate facial recognition
- Windows ACL for system-level authentication

---

For any issues or improvements, feel free to open an issue on GitHub!
