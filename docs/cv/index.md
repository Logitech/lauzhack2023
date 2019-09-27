# Face Landmarks detection

Code sample is located in [here](https://github.com/Logitech/hackzurich2019/tree/master/cv/logi-cv-toolbox/FacialLandmarkDetection).

This is a quick example of how to use face detection together with facial landmarks detection. Having facial landmarks you can estimate the head position in 3D space. This is also a first step to implement an eye tracking system. You already know where are the eyes. There are [simple ways](https://pysource.com/2019/01/14/eye-gaze-detection-1-gaze-controlled-keyboard-with-python-and-opencv-p-3/) to estimate the gaze direction.

To run this is C++ code, you will need [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/). 

Download a fully configured project [here](https://drive.google.com/open?id=19g7JIRUkZHT6Z7VjYERksPHmYNLx3rpF) (includes OpenCV libs for Windows)

To build this code, you will need to build the OpenCV library for [Windows](https://www.learnopencv.com/install-opencv-3-4-4-on-windows/), [Mac OS](https://www.learnopencv.com/install-opencv-3-4-4-on-macos/) or [Linux](https://www.learnopencv.com/install-opencv-3-4-4-on-ubuntu-18-04/).

![](faceLandmarks.gif)

