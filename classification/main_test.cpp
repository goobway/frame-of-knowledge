#include <iostream>
#include <vector>

// Bilinear interpolation function
float interpolate(float a, float b, float t) {
    return a * (1 - t) + b * t;
}

std::vector<std::vector<float>> resize(const std::vector<std::vector<int>>& input, int new_width, int new_height) {
    int width = input.size();
    int height = input[0].size();

    std::vector<std::vector<float>> output(new_height, std::vector<float>(new_width));

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            float gx = (float)(width - 1) * x / (new_width - 1);
            float gy = (float)(height - 1) * y / (new_height - 1);

            int gxi = (int)gx;
            int gyi = (int)gy;

            float dx = gx - gxi;
            float dy = gy - gyi;

            output[y][x] = interpolate(
                interpolate(input[gyi][gxi], input[gyi][gxi + 1], dx),
                interpolate(input[gyi + 1][gxi], input[gyi + 1][gxi + 1], dx),
                dy
            );
        }
    }

    return output;
}

int main() {
    // Create a 32x32 vector of 1s and 0s
    std::vector<std::vector<int>> input(32, std::vector<int>(32));
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            input[i][j] = (i + j) % 2;
        }
    }

    // Resize the input vector to 28x28
    std::vector<std::vector<float>> resized = resize(input, 28, 28);

    // Print the resized vector
    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 28; ++j) {
            std::cout << resized[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
