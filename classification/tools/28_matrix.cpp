#include <iostream>
#include <vector>

int main() {
  unsigned char matrix[32][32]; // Assume this matrix is already populated with data.
  float resized[28][28];

  // Resize the matrix.
  for (int i = 0; i < 28; ++i) {
    for (int j = 0; j < 28; ++j) {
      float sum = 0.0;
      for (int k = 0; k < 2; ++k) {
        for (int l = 0; l < 2; ++l) {
          sum += static_cast<float>(matrix[i*2+k][j*2+l]);
        }
      }
      resized[i][j] = sum / 4.0f;
    }
  }

  // Print out the resized matrix.
  for (int i = 0; i < 28; ++i) {
    for (int j = 0; j < 28; ++j) {
      std::cout << resized[i][j] << " ";
    }
    std::cout << "\n";
  }
}


// Get output tensor data
std::vector<float> output_data(output_tensor->bytes / sizeof(float));
memcpy(output_data.data(), output_tensor->data.f, output_tensor->bytes);

// Remove unnecessary dimensions
output_data.resize(output_tensor->dims->data[1]);

// Get predicted class index
int predicted_class_index = std::distance(output_data.begin(),
    std::max_element(output_data.begin(), output_data.end()));
