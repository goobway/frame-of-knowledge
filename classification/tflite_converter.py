import tensorflow as tf

# Path to the TensorFlow SavedModel.
saved_model_dir = 'm49/m49_preproc'

# Create a TFLiteConverter object and specify the input signature.
converter = tf.lite.TFLiteConverter.from_saved_model(saved_model_dir)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS]

# Convert the model to a TFLite model and save it to a file.
tflite_model = converter.convert()
open('preproc49.tflite', 'wb').write(tflite_model)