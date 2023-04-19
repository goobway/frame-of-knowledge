const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
let isDrawing = false;
let lastX = 0;
let lastY = 0;
const prompts = {
    doodles: ['apple', 'boat_(sailboat)', 'camera', 'door', 'envelope', 'flower', 'giraffe', 'house', 'ice_cream', 'jacket', 'key', 'ladder', 'mountain', 'necklace', 'octopus', 'pencil', 'queen_(crown)', 'rainbow', 'see_saw', 'turtle_(sea turtle)', 'umbrella', 'van', 'water_(ocean)', 'x_(axe)', 'yoyo_(lollipop)', 'zebra'],
    numbers: ['0_number', '1_number', '2_number', '3_number', '4_number', '5_number', '6_number', '7_number', '8_number', '9_number'],
    letters: ['a_lower', 'A_upper', 'b_lower', 'B_upper', 'C_upper', 'd_lower', 'D_upper', 'e_lower', 'E_upper', 'f_lower', 'F_upper', 'g_lower', 'G_upper', 'h_lower', 'H_upper', 'i_lower', 'I_upper', 'j_lower', 'J_upper', 'k_lower', 'L_upper', 'm_lower', 'M_upper', 'n_lower', 'N_upper', 'P_upper', 'Q_upper', 'r_lower', 'R_upper', 'S_upper', 't_lower', 'T_upper', 'U_upper', 'V_upper', 'W_upper', 'x_lower', 'Y_upper', 'z_lower']
};


// Generate random prompt
function generatePrompt() {
    const categories = Object.keys(prompts);
    const randomCategory = categories[Math.floor(Math.random() * categories.length)];
    const randomPrompt = prompts[randomCategory][Math.floor(Math.random() * prompts[randomCategory].length)];
    const promptContainer = document.getElementById('prompt-container');
    promptContainer.innerHTML = `Draw a ${randomPrompt}`;
}

generatePrompt();

// Start drawing
function startDraw(e) {
    isDrawing = true;
    lastX = e.offsetX;
    lastY = e.offsetY;
}

// Draw line
function draw(e) {
    if (!isDrawing) return;
    ctx.beginPath();
    ctx.moveTo(lastX, lastY);
    ctx.lineTo(e.offsetX, e.offsetY);
    ctx.stroke();
    lastX = e.offsetX;
    lastY = e.offsetY;
}

// Stop drawing
function stopDraw() {
    isDrawing = false;
}

// -- CLASSIFICATION -- 

let model;

async function loadModel() {
    model = await tf.loadLayersModel('/model/model.json');
}

loadModel();

// async function preprocessDrawing(imageData) {
//     // Convert the image data to a tensor
//     const imageTensor = tf.browser.fromPixels(imageData);

//     // Convert the image tensor to grayscale
//     const grayscaleTensor = imageTensor.mean(2);

//     // Expand dimensions to make the tensor rank 3
//     const expandedTensor = grayscaleTensor.expandDims(2);

//     // Resize the expanded tensor to 28x28
//     const resizedTensor = tf.image.resizeBilinear(expandedTensor, [28, 28], true);

//     // Invert the pixel values
//     const invertedTensor = tf.scalar(255).sub(resizedTensor);

//     // Normalize the pixel values to be between -1 and 1
//     const normalizedTensor = invertedTensor.div(tf.scalar(127.5)).sub(tf.scalar(1));

//     // Reshape the tensor to match the input shape of the model
//     const reshapedTensor = normalizedTensor.reshape([1, 28, 28, 1]);

//     return reshapedTensor;
// }

// async function predict(model, preprocessedDrawing) {
//     // Convert the preprocessed drawing to a tensor
//     const inputTensor = tf.browser.fromPixels(preprocessedDrawing);

//     // Run the model prediction
//     const outputTensor = model.predict(inputTensor);

//     // Get the prediction result as a JavaScript array
//     const prediction = await outputTensor.data();

//     // Return the prediction result
//     return prediction;
// }

// function comparePredictionWithPrompt(prediction, promptText) {
//     // Find the index of the highest value in the prediction array
//     const maxIndex = prediction.indexOf(Math.max(...prediction));

//     // Get the predicted label based on the index
//     const predictedLabel = prompts.doodles[maxIndex]; // Replace "prompts.doodles" with the appropriate array containing the class labels

//     // Compare the predicted label with the prompt text
//     const isMatch = predictedLabel === promptText;

//     // Return the comparison result
//     return isMatch;
// }

// -- END CLASSIFICATION --

async function submit() {
    // Get the drawing data from the canvas
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);

    // Create a temporary canvas and context to convert the image data to a data URL
    const tempCanvas = document.createElement('canvas');
    tempCanvas.width = canvas.width;
    tempCanvas.height = canvas.height;
    const tempCtx = tempCanvas.getContext('2d');
    tempCtx.putImageData(imageData, 0, 0);
    const dataURL = tempCanvas.toDataURL('image/png');

    // Remove the "data:image/png;base64," part from the data URL
    const base64ImageData = dataURL.split(',')[1];

    // Get the existing drawings from local storage
    let drawings = JSON.parse(localStorage.getItem('drawings')) || [];

    // Add the new drawing to the array
    drawings.push(base64ImageData);

    // Store the updated drawings array in local storage
    localStorage.setItem('drawings', JSON.stringify(drawings));

    clear(); // clear the canvas

    // -- CLASSIFICATION --
    // Preprocess the drawing
    // const preprocessedDrawing = await preprocessDrawing(tempCanvas);

    // // Run the model prediction
    // const prediction = await predict(model, preprocessedDrawing);

    // // Compare the prediction result with the given prompt
    // const promptText = document.getElementById('prompt-container').innerText.slice(8); // Remove "Draw a " from the prompt text
    // const isMatch = comparePredictionWithPrompt(prediction, promptText);

    // // Display the comparison result
    // console.log(isMatch ? 'Correct!' : 'Incorrect!');

    // -- END CLASSIFICATION --

    generatePrompt(); // generate a new prompt
}


// Clear canvas
function clear() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}

canvas.addEventListener('mousedown', startDraw);
canvas.addEventListener('mousemove', draw);
canvas.addEventListener('mouseup', stopDraw);
canvas.addEventListener('mouseout', stopDraw);

const submitBtn = document.getElementById('submitBtn');
submitBtn.addEventListener('click', submit);

const clearBtn = document.getElementById('clearBtn');
clearBtn.addEventListener('click', clear);