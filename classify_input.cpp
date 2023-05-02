#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <memory>
#include <cmath>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

// Author: Calista Greenway
// Project: Classification Model Usage in C++
// Last Updated: April 27, 2023

// ---- HELPER FUNCTIONS ----

// Function to read text file containing class labels
std::vector<std::string> read_labels(const std::string &filename)
{
  std::ifstream label_file(filename);
  if (!label_file)
  {
    std::cerr << "Unable to open label file: " << filename << std::endl;
    exit(1);
  }
  std::vector<std::string> labels;
  std::string line;
  while (std::getline(label_file, line))
  {
    labels.push_back(line);
  }
  return labels;
}

// Function to pad matrix drawing with extra 1s
void thicken_drawing(std::vector<std::vector<float>> &matrix)
{
  // Create a temporary matrix to store the updated values to avoid interference with the original matrix during processing.
  std::vector<std::vector<float>> temp_matrix = matrix;

  // Get the number of rows and columns in the matrix.
  int rows = matrix.size();
  int cols = matrix[0].size();

  // Iterate through each element of the matrix.
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      // If the current element is 1.0, update the surrounding cells.
      if (matrix[i][j] == 1.0)
      {
        // Iterate through the 8 neighboring cells.
        for (int k = -1; k <= 1; ++k)
        {
          for (int l = -1; l <= 1; ++l)
          {
            // Calculate the row and column indices of the neighboring cell.
            int new_i = i + k;
            int new_j = j + l;

            // Check if the neighboring cell indices are within the matrix bounds.
            if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols)
            {
              // Set the value of the neighboring cell in the temp_matrix to 1.0.
              temp_matrix[new_i][new_j] = 1.0;
            }
          }
        }
      }
    }
  }
  // Replace the original matrix with the updated temp_matrix.
  matrix = temp_matrix;
}

// Function to generate Gaussian kernel
const int KERNEL_SIZE = 5;
const double SIGMA = 1.0;

void generate_gaussian_kernel(std::vector<std::vector<double>> &kernel)
{
  double sum = 0.0;
  double r, s = 2.0 * SIGMA * SIGMA;

  // Generate the kernel values
  for (int x = -(KERNEL_SIZE / 2); x <= KERNEL_SIZE / 2; x++)
  {
    for (int y = -(KERNEL_SIZE / 2); y <= KERNEL_SIZE / 2; y++)
    {
      r = std::sqrt(x * x + y * y);
      kernel[x + (KERNEL_SIZE / 2)][y + (KERNEL_SIZE / 2)] = (std::exp(-(r * r) / s)) / (M_PI * s);
      sum += kernel[x + (KERNEL_SIZE / 2)][y + (KERNEL_SIZE / 2)];
    }
  }

  // Normalize the kernel
  for (int i = 0; i < KERNEL_SIZE; ++i)
  {
    for (int j = 0; j < KERNEL_SIZE; ++j)
    {
      kernel[i][j] /= sum;
    }
  }
}

// Function to apply Gaussian blur on the input matrix
void apply_gaussian_blur(std::vector<std::vector<float>> &input_matrix, std::vector<std::vector<float>> &blurred_matrix)
{
  int rows = input_matrix.size();
  int cols = input_matrix[0].size();

  // Generate the Gaussian kernel
  std::vector<std::vector<double>> kernel(KERNEL_SIZE, std::vector<double>(KERNEL_SIZE));
  generate_gaussian_kernel(kernel);

  // Apply the Gaussian kernel on the input matrix
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      double sum = 0.0;

      // Multiply the kernel with the input matrix in the neighborhood of the current pixel
      for (int x = -(KERNEL_SIZE / 2); x <= KERNEL_SIZE / 2; x++)
      {
        for (int y = -(KERNEL_SIZE / 2); y <= KERNEL_SIZE / 2; y++)
        {
          int current_row = i + x;
          int current_col = j + y;

          // Check if the current position is inside the input matrix
          if (current_row >= 0 && current_row < rows && current_col >= 0 && current_col < cols)
          {
            sum += input_matrix[current_row][current_col] * kernel[x + (KERNEL_SIZE / 2)][y + (KERNEL_SIZE / 2)];
          }
        }
      }

      // Store the result in the blurred matrix
      blurred_matrix[i][j] = static_cast<float>(sum);
    }
  }
}

// Fill the gaps!!
// Apply dilation to the input matrix
void dilate(const std::vector<std::vector<float>>& input, std::vector<std::vector<float>>& output, float threshold) {
    int rows = input.size();
    int cols = input[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float max_val = 0;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int new_i = i + x;
                    int new_j = j + y;
                    if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols) {
                        max_val = std::max(max_val, input[new_i][new_j]);
                    }
                }
            }
            output[i][j] = max_val;
        }
    }
}

// Apply erosion to the input matrix
void erode(const std::vector<std::vector<float>>& input, std::vector<std::vector<float>>& output, float threshold) {
    int rows = input.size();
    int cols = input[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float min_val = 1;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int new_i = i + x;
                    int new_j = j + y;
                    if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols) {
                        min_val = std::min(min_val, input[new_i][new_j]);
                    }
                }
            }
            output[i][j] = min_val;
        }
    }
}

// Fill gaps in the input matrix using dilation followed by erosion
void fill_gaps(std::vector<std::vector<float>>& input, float threshold) {
    std::vector<std::vector<float>> temp(input.size(), std::vector<float>(input[0].size()));
    std::vector<std::vector<float>> output(input.size(), std::vector<float>(input[0].size()));

    // Apply dilation
    dilate(input, temp, threshold);

    // Apply erosion
    erode(temp, output, threshold);

    // Update input matrix with the result
    input.swap(output);
}

// --- MAIN PROGRAM ---

float classify_image(unsigned char input_image[32][32])
{
  // Load the tflite preprocessing model
  std::unique_ptr<tflite::FlatBufferModel> preproc = tflite::FlatBufferModel::BuildFromFile("/home/sdp19/tflite/models/classification/preproc49.tflite");
  if (!preproc)
  {
    std::cerr << "Failed to load preproc model.\n";
    return -1;
  }

  // Load the tflite classification model
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("/home/sdp19/tflite/models/classification/model49.tflite");
  if (!model)
  {
    std::cerr << "Failed to load classification model.\n";
    return -1;
  }

  // Create an interpreter for each model
  tflite::ops::builtin::BuiltinOpResolver resolver;
  std::unique_ptr<tflite::Interpreter> interpreter1;
  tflite::InterpreterBuilder(*preproc, resolver)(&interpreter1);
  std::unique_ptr<tflite::Interpreter> interpreter2;
  tflite::InterpreterBuilder(*model, resolver)(&interpreter2);

  // Allocate memory for input and output tensors
  interpreter1->AllocateTensors();
  interpreter2->AllocateTensors();

  // Prepare the input for the preproc model
  // unsigned char input[32][32]; ---> replace "input_image" with test unsigned char name
  std::vector<std::vector<float>> input_data1(32, std::vector<float>(32));
  for (size_t i = 0; i < 32; ++i)
  {
    for (size_t j = 0; j < 32; ++j)
    {
      input_data1[i][j] = static_cast<float>(input_image[i][j]);
    }
  }

  // Print drawing (before processing)
  std::cout << "INPUT DRAWING: " << std::endl;
  for (int i = 0; i < 32; ++i)
  {
    for (int j = 0; j < 32; ++j)
    {
      std::cout << input_data1[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // Fill gaps and thicken drawing
  fill_gaps(input_data1, 0.5);
  thicken_drawing(input_data1);

  // Print drawing
  std::cout << "\nFILLED DRAWING: " << std::endl;
  for (int i = 0; i < 32; ++i)
  {
    for (int j = 0; j < 32; ++j)
    {
      std::cout << input_data1[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // Blur drawing
  std::vector<std::vector<float>> blurred_matrix(32, std::vector<float>(32));
  apply_gaussian_blur(input_data1, blurred_matrix);

  // Turn into 1D vector
  std::vector<float> input_data1_1D;
  input_data1_1D.reserve(32 * 32);

  for (size_t i = 0; i < 32; ++i)
  {
    for (size_t j = 0; j < 32; ++j)
    {
      input_data1_1D.push_back(blurred_matrix[i][j]);
    }
  }

  // Copy input data to memory
  float *input1 = interpreter1->typed_input_tensor<float>(0);
  std::copy(input_data1_1D.begin(), input_data1_1D.end(), input1);

  // Invoke the preproc model
  interpreter1->Invoke();

  // Get the output of the preproc model and use it as input for the second
  float *output1 = interpreter1->typed_output_tensor<float>(0);
  int output_size1 = interpreter1->output_tensor(0)->bytes / sizeof(float);
  float *input2 = interpreter2->typed_input_tensor<float>(0);
  std::copy(output1, output1 + output_size1, input2);

  // Invoke the classification model
  interpreter2->Invoke();

  // Get the output of the classification model and obtain the label
  float *output2 = interpreter2->typed_output_tensor<float>(0);
  int output_size2 = interpreter2->output_tensor(0)->bytes / sizeof(float);
  int classification_index = std::distance(output2, std::max_element(output2, output2 + output_size2));

  // Read values from output tensor
  std::vector<std::pair<int, float>> output_values;
  for (int i = 0; i < output_size2; i++)
  {
    output_values.push_back(std::make_pair(i, output2[i]));
  }

  // Sort the output_values vector in descending order based on output values
  std::sort(output_values.begin(), output_values.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b)
            { return a.second > b.second; });

  // Read the labels from the .txt file
  std::vector<std::string> labels = read_labels("/home/sdp19/tflite/models/classification/class_list.txt");

  // Print the top 5 values and their corresponding labels
  for (int i = 0; i < 5; i++)
  {
    std::cout << "Output value " << output_values[i].first << ": " << output_values[i].second << std::endl;
    std::string classification_label = labels[output_values[i].first];
    std::cout << "Classification label: " << classification_label << "\n"
              << std::endl;
  }

  // Generate float value containing label index and confidence percentage
  float output_number = output_values[0].first + output_values[0].second;

  return output_number;
}

// int main()
// {
//   float output_number = classify_image(USED_MATRIX);
//   float label_index_f, confidence;

//   confidence = std::modf(output_number, &label_index_f);
//   int label_index = static_cast<int>(label_index_f);

//   return 0;
// }