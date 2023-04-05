// app.js
document.addEventListener('DOMContentLoaded', () => {
    const studentProgressCanvas = document.getElementById('student-progress');

    const studentData = [
        { id: 'A', scores: [70, 75, 80, 85, 90, 95], borderColor: 'rgb(75, 192, 192)' },
        { id: 'B', scores: [60, 65, 70, 75, 80, 85], borderColor: 'rgb(255, 99, 132)' },
        { id: 'C', scores: [50, 55, 60, 65, 70, 75], borderColor: 'rgb(255, 205, 86)' }
    ];

    const datasets = studentData.map(student => ({
        label: `Student ${student.id}`,
        data: student.scores,
        fill: false,
        borderColor: student.borderColor,
        tension: 0.1
    }));

    const studentProgressChart = new Chart(studentProgressCanvas, {
        type: 'line',
        data: {
            labels: ['Week 1', 'Week 2', 'Week 3', 'Week 4', 'Week 5', 'Week 6'],
            datasets: datasets
        },
        options: {
            scales: {
                y: {
                    suggestedMin: 0,
                    suggestedMax: 100
                }
            }
        }
    });


    const areasImprovementCanvas = document.getElementById('areas-improvement-chart');
    const areasImprovementChart = new Chart(areasImprovementCanvas, {
        type: 'bar',
        data: {
            labels: ['Letters', 'Numbers', 'Doodles'],
            datasets: [{
                label: 'Number of Struggling Students',
                data: [5, 7, 15],
                backgroundColor: ['rgba(75, 192, 192, 0.2)', 'rgba(255, 99, 132, 0.2)', 'rgba(255, 205, 86, 0.2)'],
                borderColor: ['rgba(75, 192, 192, 1)', 'rgba(255, 99, 132, 1)', 'rgba(255, 205, 86, 1)'],
                borderWidth: 1
            }]
        },
        options: {
            scales: {
                y: {
                    beginAtZero: true
                }
            }
        }
    });
});

// Submitted Drawings
document.addEventListener('DOMContentLoaded', () => {
    // ... rest of the existing code

    // Get the drawings array from local storage
    const drawings = JSON.parse(localStorage.getItem('drawings')) || [];

    // Display each drawing in the submitted-drawings-container
    const submittedDrawingsContainer = document.getElementById('submitted-drawings-container');
    drawings.forEach(drawingData => {
        const drawingImg = document.createElement('img');
        drawingImg.src = `data:image/png;base64,${drawingData}`; // Include the MIME type and encoding
        drawingImg.classList.add('submitted-drawing'); // for applying CSS styles later

        // Add an event listener to open the image in a new window when clicked
        drawingImg.addEventListener('click', () => {
            window.open(drawingImg.src, '_blank');
        });

        submittedDrawingsContainer.appendChild(drawingImg);
    });
});

function displaySubmittedDrawings() {
    const drawings = JSON.parse(localStorage.getItem('drawings')) || [];
    const drawingsContainer = document.getElementById('submitted-drawings');

    drawingsContainer.innerHTML = '';

    drawings.forEach((drawing, index) => {
        const drawingElement = document.createElement('div');
        drawingElement.classList.add('drawing-thumbnail');

        const img = document.createElement('img');
        img.src = 'data:image/png;base64,' + drawing.image;
        img.alt = 'Submitted drawing ' + (index + 1);
        img.onclick = () => {
            window.location.href = `/drawing-info.html?index=${index}`;
        };

        const promptElement = document.createElement('p');
        promptElement.innerText = drawing.prompt;

        const accuracyElement = document.createElement('p');
        accuracyElement.innerText = `Accuracy: ${drawing.accuracy}%`;

        drawingElement.appendChild(img);
        drawingElement.appendChild(promptElement);
        drawingElement.appendChild(accuracyElement);

        drawingsContainer.appendChild(drawingElement);
    });
}


