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
