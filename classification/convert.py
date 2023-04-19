import tensorflow as tf

# Load the SavedModel
saved_model_path = "m45/m45_model"
model = tf.keras.models.load_model(saved_model_path)

# Save the model in h5 format
h5_output_path = "model.h5"
model.save(h5_output_path)
