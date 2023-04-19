import numpy as np
import tensorflow as tf
import argparse
import cv2

# Load the TensorFlow Lite model.
interpreter = tf.lite.Interpreter(model_path='model.tflite')
interpreter.allocate_tensors()

# Get input and output tensors.
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Define function to preprocess the input image.
def preprocess_image(image):
    # Convert the image to grayscale.
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # Resize the image to 28x28.
    image = cv2.resize(image, (28, 28))
    # Invert the pixel values.
    image = 255 - image
    # Normalize the pixel values to be between -1 and 1.
    image = (image / 127.5) - 1.0
    # Reshape the image to match the input shape of the model.
    image = np.reshape(image, input_details[0]['shape'])
    # print(image.shape)
    # Convert the image to a tensor and return it.
    return tf.convert_to_tensor(image, dtype=input_details[0]['dtype'])

# Define a function to classify an input image.
def classify_image(image):
    # Preprocess the image.
    input_data = preprocess_image(image)
    # Set the input tensor to the preprocessed image.
    interpreter.set_tensor(input_details[0]['index'], input_data)
    # Run the model.
    interpreter.invoke()
    # Get the output tensor and convert it to a numpy array.
    output_data = interpreter.get_tensor(output_details[0]['index'])
    output_data = np.squeeze(output_data)
    # Return the predicted class label.
    return np.argmax(output_data)

# Define a function to print the binary matrix of an input image.
def print_binary_matrix(image):
    # Convert the image to grayscale.
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # Resize the image to 32x32.
    resized_image = cv2.resize(gray_image, (32, 32))
    # Threshold the image to create a binary image.
    ret, binary_image = cv2.threshold(resized_image, 127, 255, cv2.THRESH_BINARY)
    # Print the binary matrix.
    for row in binary_image:
        for pixel in row:
            if pixel == 0:
                print('1', end=' ')
            else:
                print('0', end=' ')
        print('')

# Parse command line arguments.
parser = argparse.ArgumentParser(description='Classify an image using a TensorFlow Lite model.')
parser.add_argument('image_file', type=str, help='the path to the input image file (PNG or JPEG format)')
args = parser.parse_args()

# Load the input image.
image = cv2.imread(args.image_file)

# Print the binary matrix.
print_binary_matrix(image)

# Classify the image.
class_label = classify_image(image)

# Print the predicted class label.
with open('class_list.txt') as f:
    lines = f.readlines()
    lns = [line.strip() for line in lines]
    print('Class label:', lns[class_label])
