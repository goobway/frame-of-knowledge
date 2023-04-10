#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

std::vector<std::vector<float>> unsignedCharToFloat(const unsigned char src[32][32], int rows, int cols) {
    cv::Mat src_mat(rows, cols, CV_8UC1, (void*)src);
    cv::Mat dst_mat;
    cv::resize(src_mat, dst_mat, cv::Size(28, 28), 0, 0, cv::INTER_NEAREST);

    std::vector<std::vector<float>> dst(dst_mat.rows);
    for (int i = 0; i < dst_mat.rows; i++) {
        dst[i].resize(dst_mat.cols);
        for (int j = 0; j < dst_mat.cols; j++) {
            dst[i][j] = dst_mat.at<unsigned char>(i, j) / 255.0f;
        }
    }
    return dst;
}

int main() {
    unsigned char PRINT_A[32][32] = 
    {
        // ...
    };

    std::vector<std::vector<float>> image = unsignedCharToFloat(PRINT_A, 32, 32);

    for (const auto &row : image)
    {
        for (float value : row)
        {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
