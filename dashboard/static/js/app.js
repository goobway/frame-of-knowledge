document.addEventListener('DOMContentLoaded', () => {
    // Get the student progress canvas element
    const studentProgressCanvas = document.getElementById('student-progress');

    // Define an array of student data objects
    const studentData = [
        { id: 'A', scores: [70, 75, 80, 85, 90, 95], borderColor: 'rgb(75, 192, 192)' },
        { id: 'B', scores: [60, 65, 70, 75, 80, 85], borderColor: 'rgb(255, 99, 132)' },
        { id: 'C', scores: [50, 55, 60, 65, 70, 75], borderColor: 'rgb(255, 205, 86)' }
    ];

    // Map the student data to Chart.js datasets
    const datasets = studentData.map(student => ({
        label: `Student ${student.id}`,
        data: student.scores,
        fill: false,
        borderColor: student.borderColor,
        tension: 0.1
    }));

    // Create a new Chart.js chart for student progress
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

    // Get the areas of improvement canvas element
    const areasImprovementCanvas = document.getElementById('areas-improvement-chart');

    // Create a new Chart.js chart for areas of improvement
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

// Display submitted drawings
document.addEventListener('DOMContentLoaded', () => {
    // Get the drawings array from local storage
    const drawings = JSON.parse(localStorage.getItem('drawings')) || [];

    // Display each drawing in the submitted-drawings-container
    const submittedDrawingsContainer = document.getElementById('submitted-drawings-container');
    drawings.forEach(drawingData => {
        // Create an image element for the drawing
        const drawingImg = document.createElement('img');
        drawingImg.src = `data:image/png;base64,${drawingData}`; // Include the MIME type and encoding
        drawingImg.classList.add('submitted-drawing'); // for applying CSS styles later

        // Add an event listener to open the image in a new window when clicked
        drawingImg.addEventListener('click', () => {
            window.open(drawingImg.src, '_blank');
        });

        // Append the image
        submittedDrawingsContainer.appendChild(drawingImg);
    });
});
