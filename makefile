CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2


OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS := $(shell pkg-config --libs opencv4)


PATH_TO_LOCKED ?= ""
PATH_TO_YOLO ?= ""
PATH_TO_FACENET ?= ""

DEFINES := -DPATH_TO_LOCKED=\"$(PATH_TO_LOCKED)\" \
           -DPATH_TO_YOLO=\"$(PATH_TO_YOLO)\" \
           -DPATH_TO_FACENET=\"$(PATH_TO_FACENET)\"


SRCS := src/infer_cuDNN.cpp src/add_update.cpp src/Frames.cpp
OBJS := $(SRCS:.cpp=.o)


TARGET := main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) -o $@ $^ $(OPENCV_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) $(DEFINES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
