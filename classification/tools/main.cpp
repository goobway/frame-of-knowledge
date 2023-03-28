#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

#define TFLITE_MINIMAL_CHECK(x)                              \
  if (!(x)) {                                                \
    fprintf(stderr, "Error at %s:%d\n", __FILE__, __LINE__); \
    exit(1);                                                 \
  }

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "minimal <tflite model>\n");
    return 1;
  }
  const char* filename = argv[1];

  // Load the tflite model file and allocate memory for the interpreter
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(filename);
  TFLITE_MINIMAL_CHECK(model != nullptr);

  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder builder(*model, resolver);
  std::unique_ptr<tflite::Interpreter> interpreter;
  builder(&interpreter);
  TFLITE_MINIMAL_CHECK(interpreter != nullptr);

  // Allocate tensor buffers.
  TFLITE_MINIMAL_CHECK(interpreter->AllocateTensors() == kTfLiteOk);
  printf("=== Pre-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(interpreter.get());

  // Run inference
  TFLITE_MINIMAL_CHECK(interpreter->Invoke() == kTfLiteOk);
  printf("\n\n=== Post-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(interpreter.get());

  //interpreter->AllocateTensors();

  // Load the class list from the class_list.txt file
  std::ifstream file("class_list.txt");
  std::vector<std::string> class_list;
  std::string line;
  while (std::getline(file, line)) {
    class_list.push_back(line);
  }

  // Load the image file and resize it to 28x28 pixels
  std::string image_path = "fork.png"; // Replace with image file path
  std::ifstream image_file(image_path, std::ios::binary);
  std::vector<uint8_t> image_data(32 * 32 * 3);
  image_file.read(reinterpret_cast<char*>(image_data.data()), image_data.size());

  // Resize the image to 28x28 pixels
  std::vector<uint8_t> resized_image_data(28 * 28 * 3);
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      for (int k = 0; k < 3; k++) {
        int orig_i = i * 32 / 28;
        int orig_j = j * 32 / 28;
        resized_image_data[(i * 28 + j) * 3 + k] = image_data[(orig_i * 32 + orig_j) * 3 + k];
      }
    }
  }

  // Reshape the image to match the input shape of the model
  int input_index = interpreter->inputs()[0];
  TfLiteIntArray* input_dims = interpreter->tensor(input_index)->dims;
  int input_height = input_dims->data[1];
  int input_width = input_dims->data[2];
  int input_channels = input_dims->data[3];
  TfLiteType input_type = interpreter->tensor(input_index)->type;

  // Check that the input type is uint8_t
  if (input_type != kTfLiteUInt8) {
    std::cerr << "Invalid input type: " << input_type << std::endl;
    return 1;
  }

  // Check that the input shape matches the expected shape
  if (resized_image_data.size() != input_height * input_width * input_channels) {
    std::cerr << "Input shape does not match: " << resized_image_data.size() << " vs " << input_height * input_width * input_channels << std::endl;
    return 1;
  }

  // Copy the input data to the interpreter
  memcpy(interpreter->typed_input_tensor<uint8_t>(0), resized_image_data.data(), resized_image_data.size());

}
// interpreter->Invoke();
// int output_index = interpreter->outputs()[0];
// TfLiteIntArray* output_dims = interpreter->tensor(output_index)->dims;
// int output_size = output_dims->data[1];
// TfLite

