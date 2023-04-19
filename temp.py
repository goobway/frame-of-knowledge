img = Image.open(handInput)
numpyarr = np.asarray(img)
flatarr = np.reshape(numpyarr[:, :, 0], (32**2, 1))

model = keras.models.load_model('saved_models/' + model_name + '/' + model_name + '_model')
preproc = keras.models.load_model('saved_models/' + model_name + '/' + model_name + '_preproc')
class_names = load_classList('saved_models/' + model_name + '/class_list.txt')
num_classes = len(class_names)
######################################################################################
# image preprocessing
preproc_out = preproc.predict(np.expand_dims(flatarr, axis=0))[0]
normalized = (255-preproc_out)/255
# /image preprocessing
# make output of the above model the input of the below model
# prediction
pred = model.predict(np.expand_dims(normalized, axis=0))[0]  # predict the class
top_pred_idx = (-pred).argsort()[:10]
# /prediction
######################################################################################