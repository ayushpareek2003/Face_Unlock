Cmake_minimum_required(VERSION 3.22)

project(Face_id LANGUAGES CXX)

find_package(OpenCV REQUIRED)

set(source main.cpp
           src/add_update.cpp
           src/Frames.cpp 
    )
 
set(wxwidget_root  "" CACHE PATH "Path to the ONNX Runtime library")    
   
INCLUDE_DIRECTORIES(include
                    # ${wxwidget_root}/include
                    ${wxwidget_root}/include/msvc
)



LINK_DIRECTORIES(${wxwidget_root}/lib/vc_x64_lib)

add_executable(main ${source})

target_link_libraries(main ${OpenCV_LIBS})


