const express = require('express');
const app = express();
const bodyParser = require('body-parser');

app.use(bodyParser.json());

app.post('/submitDrawing', (req, res) => {
    // Get the base64-encoded drawing data from the request body
    const base64ImageData = req.body.drawingData;

    // Convert the base64-encoded drawing data to binary data
    const binaryImageData = Buffer.from(base64ImageData, 'base64');

    // Process the binary drawing data (using TensorFlow.js)
    // ...

    res.sendStatus(200);
});

app.listen(3000, () => {
    console.log('Server started on port 3000');
});

