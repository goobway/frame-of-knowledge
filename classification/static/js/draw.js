const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
let isDrawing = false;
let lastX = 0;
let lastY = 0;
const prompts = {
    doodles: ['Apple', 'Bird', 'Banana', 'Chair', 'Door', 'Eye', 'Envelope', 'Fish', 'Fork', 'Grapes', 'Hand', 'Hat', 'Ice Cream', 'Jacket', 'Jail', 'Key', 'Keyboard', 'Leaf', 'Lightbulb', 'Lollipop', 'Moon', 'Mountain', 'Nose', 'Octopus', 'Owl', 'Pizza', 'Rainbow', 'School Bus', 'Sheep', 'Spoon', 'Table', 'Tree', 'Umbrella', 'Vase', 'Wheel', 'Yoga', 'Zebra'],
    letters: ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'],
    numbers: ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
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

// Submit drawing and convert to matrix
function submit() {
    const data = ctx.getImageData(0, 0, canvas.width, canvas.height).data;
    const matrix = [];
    for (let i = 0; i < 1024; i++) {
        matrix.push(data[i * 4] / 255);
    }
    console.log(matrix);
    clear(); // clear the canvas
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