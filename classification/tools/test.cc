#include <iostream>
#include <fstream>
#include <vector>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"

int main()
{
    // Load the tflite model.
    std::unique_ptr<tflite::FlatBufferModel> model =
        tflite::FlatBufferModel::BuildFromFile("model31.tflite");

    // Create an interpreter and allocate memory for input and output tensors.
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder builder(*model, resolver);
    std::unique_ptr<tflite::Interpreter> interpreter;
    builder(&interpreter);
    interpreter->AllocateTensors();

    // Load the input tensor with your input data.
    float input_data[] = {1.0, 2.0, 3.0, 4.0};
    TfLiteTensor *input_tensor = interpreter->input_tensor(0);
    memcpy(input_tensor->data.f, input_data, 4 * sizeof(float));

    // ------------------
    // Define the shape of the input tensor
    const int input_height = 32;
    const int input_width = 32;
    const int input_channels = 1;
    const int input_batch_size = 1;

    // Allocate memory for the input tensor
    std::vector<float> input_tensor(input_batch_size * input_height * input_width * input_channels);

    // Load the data from PRINT_A into the input tensor
    for (int i = 0; i < input_height; i++)
    {
        for (int j = 0; j < input_width; j++)
        {
            unsigned char pixel_value = PRINT_A[i][j];
            input_tensor[i * input_width + j] = static_cast<float>(pixel_value) / 255.0f;
        }
    }

    // Create the input tensor object
    auto input = Ort::Value::CreateTensor<float>(memory_info, input_tensor.data(), input_tensor.size(), input_shape.data(), input_shape.size());

//     #include <iostream>
// #include <vector>
// #include "Eigen/Dense" // Eigen library for matrix operations

// using namespace Eigen;

// int main() {
//     unsigned char PRINT_A[32][32] = {...}; // 32x32 input data array

//     // Create a 32x32 matrix from the input data array
//     Matrix<unsigned char, 32, 32, RowMajor> input_matrix;
//     for(int i=0; i<32; i++) {
//         for(int j=0; j<32; j++) {
//             input_matrix(i,j) = PRINT_A[i][j];
//         }
//     }

//     // Flatten the matrix into a 1D vector
//     std::vector<unsigned char> input_vec(32*32);
//     Map<VectorXd>(input_vec.data(), input_vec.size()) = Map<const MatrixXd>(input_matrix.data(), input_matrix.size()).cast<double>();

//     // Create a tensor with the flattened vector as data
//     Eigen::Tensor<unsigned char, 2> input_tensor(input_vec.data(), Eigen::array<Eigen::Index, 2>{32, 32});

//     // Print the input tensor
//     std::cout << input_tensor << std::endl;

//     return 0;
// }

    // Run inference using the input tensor

    // ------------------

    // Run the inference using the interpreter.
    interpreter->Invoke();

    // Retrieve the output tensor values.
    TfLiteTensor *output_tensor = interpreter->output_tensor(0);
    float *output_data = output_tensor->data.f;

    // Load the class list.
    std::ifstream class_list_file("class_list.txt");
    std::vector<std::string> class_list;
    std::string class_name;
    while (std::getline(class_list_file, class_name))
    {
        class_list.push_back(class_name);
    }

    // Determine the predicted class.
    int predicted_class_index = std::distance(output_data,
                                              std::max_element(output_data,
                                                               output_data + output_tensor->bytes));
    std::string predicted_class = class_list[predicted_class_index];
    std::cout << "Predicted class: " << predicted_class << std::endl;

    return 0;
}
