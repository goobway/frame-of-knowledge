#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <cstdio>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

// Helper functions for preprocessing input
float interpolate(float x, float y, const unsigned char a[32][32])
{
  int x1 = static_cast<int>(x);
  int x2 = x1 + 1;
  int y1 = static_cast<int>(y);
  int y2 = y1 + 1;

  float q11 = a[y1][x1];
  float q12 = a[y2][x1]; 
  float q21 = a[y1][x2];
  float q22 = a[y2][x2];

  return (q11 * (x2 - x) * (y2 - y) +
          q21 * (x - x1) * (y2 - y) +
          q12 * (x2 - x) * (y - y1) +
          q22 * (x - x1) * (y - y1));
}

void resize_and_normalize(const unsigned char a[32][32], float b[28][28])
{
  float scale_x = 32.0 / 28.0;
  float scale_y = 32.0 / 28.0;

  for (int i = 0; i < 28; ++i)
  {
    for (int j = 0; j < 28; ++j)
    {
      float x = j * scale_x;
      float y = i * scale_y;
      b[i][j] = interpolate(x, y, a) / 255.0;
    }
  }
}

const int KERNEL_SIZE = 3;
const float GAUSSIAN_KERNEL[KERNEL_SIZE][KERNEL_SIZE] = {
    {1.0 / 16, 2.0 / 16, 1.0 / 16},
    {2.0 / 16, 4.0 / 16, 2.0 / 16},
    {1.0 / 16, 2.0 / 16, 1.0 / 16}};

void apply_gaussian_blur(float image[28][28], float result[28][28])
{
  int offset = KERNEL_SIZE / 2;
  for (int y = 0; y < 28; ++y)
  {
    for (int x = 0; x < 28; ++x)
    {
      float sum = 0.0;
      for (int ky = -offset; ky <= offset; ++ky)
      {
        for (int kx = -offset; kx <= offset; ++kx)
        {
          int iy = y + ky;
          int ix = x + kx;
          if (iy >= 0 && iy < 28 && ix >= 0 && ix < 28)
          {
            sum += image[iy][ix] * GAUSSIAN_KERNEL[ky + offset][kx + offset];
          }
        }
      }
      result[y][x] = sum;
    }
  }
}

void normalize(float image[28][28])
{
  float max_val = 0.0;
  for (int y = 0; y < 28; ++y)
  {
    for (int x = 0; x < 28; ++x)
    {
      if (image[y][x] > max_val)
      {
        max_val = image[y][x];
      }
    }
  }

  if (max_val > 0.0)
  {
    for (int y = 0; y < 28; ++y)
    {
      for (int x = 0; x < 28; ++x)
      {
        image[y][x] /= max_val;
      }
    }
  }
}

// Main program for classifying input matrix, reference in main.cpp
std::tuple<int, float> classify_image(const unsigned char (&input_image)[32][32])
{
    // Load the tflite model
    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("/home/sdp19/tflite/models/classification/model45.tflite");
    if (!model)
    {
        std::cerr << "Failed to load model.\n";
        return;
    }

    // Create an interpreter and allocate memory for input and output tensors
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder builder(*model, resolver);
    std::unique_ptr<tflite::Interpreter> interpreter;
    builder(&interpreter);
    if (!interpreter)
    {
        std::cerr << "Failed to build interpreter.\n";
        return;
    }

    // Allocate memory for input and output tensors
    interpreter->AllocateTensors();
    if (interpreter->AllocateTensors() != kTfLiteOk)
    {
        std::cerr << "Failed to allocate tensors.\n";
        return;
    }

    // Preprocess the input
    float resized[28][28];
    float blurred[28][28];

    resize_and_normalize(input_image, resized);
    apply_gaussian_blur(resized, blurred);
    normalize(blurred);

    // Print out the preprocessed input vector
    // for (int i = 0; i < 28; ++i)
    // {
    //     for (int j = 0; j < 28; ++j)
    //     {
    //         std::cout << blurred[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Get the input tensor
    TfLiteTensor *input_tensor = interpreter->input_tensor(0);

    // Get the dimensions of the input tensor
    int input_size = input_tensor->dims->data[1] * input_tensor->dims->data[2];

    // Get a pointer to the input data buffer
    float *input_data_mem = input_tensor->data.f;

    // Populate the allocated memory with the input data
    for (int i = 0; i < 28; ++i)
    {
        for (int j = 0; j < 28; ++j)
        {
            input_data_mem[i * 28 + j] = blurred[i][j];
        }
    }

    // Copy the input data from the allocated memory to the input tensor
    memcpy(input_tensor->data.f, input_data_mem, input_size * sizeof(float));

    // Run the inference using the interpreter
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk)
    {
        printf("Error invoking the interpreter");
    }

    // Get the output tensor
    TfLiteTensor *output_tensor = interpreter->output_tensor(0);

    // Get the dimensions for the output tensor
    int output_size = output_tensor->dims->data[1];

    // Get a pointer to the output data buffer
    float *output_data = output_tensor->data.f;

    // for (int i = 0; i < output_size; i++)
    // {
    //     printf("Output value %d: %f\n", i, output_data[i]);
    // }

    // Find index of label with highest score
    float highest_score = output_tensor->data.f[0];
    int predicted_class_index = 0;
    for (int i = 1; i < 74; ++i)
    {
        if (output_tensor->data.f[i] >= highest_score)
        {
            highest_score = output_tensor->data.f[i];
            // std::cout << "Highest score: " << highest_score << " at index " << i << std::endl;
            predicted_class_index = i;
        }
    }

    // Load the class list
    std::ifstream class_list_file("/home/sdp19/tflite/models/classification/class_list.txt");
    std::vector<std::string> class_list;
    std::string class_name;
    while (std::getline(class_list_file, class_name))
    {
        class_list.push_back(class_name);
    }

    // Determine predicted class
    // std::cout << predicted_class_index << std::endl;
    std::string predicted_class = class_list[predicted_class_index];
    // std::cout << "Predicted class: " << predicted_class << std::endl;

    // Return index of label and confidence 
    return std::make_tuple(predicted_class_index, highest_score);
}