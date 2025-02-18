cmake_minimum_required(VERSION 3.22)

project(Face_id LANGUAGES CXX)

find_package(OpenCV REQUIRED)

# Allow users to set the model paths via CMake
set(PATH_TO_LOCKED "" CACHE STRING "Path to locked file (folder.txt)")
set(PATH_TO_YOLO "" CACHE STRING "Path to YOLO model (onnx)")
set(PATH_TO_FACENET "" CACHE STRING "Path to FaceNet model (onnx)")

# Source files
set(source src/infer_cuDNN.cpp
           src/add_update.cpp
           src/Frames.cpp 
)

# Define the executable
add_executable(main ${source})

# Pass the paths as preprocessor definitions to C++
target_compile_definitions(main PRIVATE 
    PATH_TO_LOCKED="${PATH_TO_LOCKED}"
    PATH_TO_YOLO="${PATH_TO_YOLO}"
    PATH_TO_FACENET="${PATH_TO_FACENET}"
)

# Link OpenCV
target_link_libraries(main ${OpenCV_LIBS})
