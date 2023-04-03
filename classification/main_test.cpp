#include <iostream>
#include <vector>

// Add this function to perform bilinear interpolation
float bilinear_interpolate(const std::vector<std::vector<int>> &input, float x, float y)
{
    int x1 = (int)x;
    int y1 = (int)y;
    int x2 = x1 + 1;
    int y2 = y1 + 1;

    float r1 = (x2 - x) * input[y1][x1] + (x - x1) * input[y1][x2];
    float r2 = (x2 - x) * input[y2][x1] + (x - x1) * input[y2][x2];

    return (y2 - y) * r1 + (y - y1) * r2;
}

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<float>> normalize(const std::vector<std::vector<float>>& input) {
    const int numRows = 28;
    const int numCols = 28;

    // Find the minimum and maximum values in the input vector
    float minValue = input[0][0];
    float maxValue = input[0][0];

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            minValue = std::min(minValue, input[i][j]);
            maxValue = std::max(maxValue, input[i][j]);
        }
    }

    // Calculate the range (max - min) of the input values
    float range = maxValue - minValue;

    // Create a new 2D vector to store the normalized values
    std::vector<std::vector<float>> normalized(numRows, std::vector<float>(numCols));

    // Normalize the input values by subtracting the minimum and dividing by the range
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            normalized[i][j] = (input[i][j] - minValue) / range;
        }
    }

    return normalized;
}

int main()
{
    // Your input code here

    int oldWidth = 32;
    int oldHeight = 32;
    int newWidth = 28;
    int newHeight = 28;
    float scaleX = (float)oldWidth / (float)newWidth;
    float scaleY = (float)oldHeight / (float)newHeight;

    std::vector<std::vector<float>> output(newHeight, std::vector<float>(newWidth));

    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            float srcX = j * scaleX;
            float srcY = i * scaleY;

            output[i][j] = bilinear_interpolate(input, srcX, srcY) / 255.0f;
        }
    }

    // Your output code here

    return 0;
}
