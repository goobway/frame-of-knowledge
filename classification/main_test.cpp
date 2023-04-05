#include <opencv2/opencv.hpp>

cv::Mat preprocess(unsigned char input[32][32]) {
    // Convert the input array to a cv::Mat
    cv::Mat inputMat(32, 32, CV_8UC1, input);

    // Resize the image to 28x28
    cv::Mat resizedMat;
    cv::resize(inputMat, resizedMat, cv::Size(28, 28));

    // Convert the resized image to a float array
    cv::Mat floatMat;
    resizedMat.convertTo(floatMat, CV_32FC1);

    // Normalize the pixel values to be between 0 and 1
    floatMat /= 255.0;

    // Return the float array
    return floatMat;
}

// sudo apt install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
// git clone https://github.com/opencv/opencv.git
// cd opencv
// mkdir build
// cd build
// cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
// make -j$(nproc)
// sudo make install
// pkg-config --modversion opencv
