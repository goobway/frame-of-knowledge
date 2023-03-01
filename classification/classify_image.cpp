#include <iostream>
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"

int main() {
  // Load the tflite model
  std::unique_ptr<tflite::FlatBufferModel> model =
    tflite::FlatBufferModel::BuildFromFile("model.tflite");

  // Build the interpreter
  tflite::ops::builtin::BuiltinOpResolver resolver;
  std::unique_ptr<tflite::Interpreter> interpreter;
  tflite::InterpreterBuilder(*model, resolver)(&interpreter);

  // Allocate input and output tensors
  interpreter->AllocateTensors();

  // Set the input tensor values
  float* input = interpreter->typed_input_tensor<float>(0);
  // Fill in the input values here

  // Run the tflite model
  interpreter->Invoke();

  // Get the output tensor values
  float* output = interpreter->typed_output_tensor<float>(0);
  // Print the output tensor values
  for (int i = 0; i < output_tensor->bytes / sizeof(float); i++) {
    std::cout << output[i] << " ";
  }
  
  // Cleanup
  interpreter.reset();
  model.reset();
  return 0;
}