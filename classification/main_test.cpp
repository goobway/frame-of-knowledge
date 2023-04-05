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
