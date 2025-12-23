const express = require('express');
const { execFile } = require('child_process');
const cors = require('cors');
const path = require('path');

const app = express();
const port = process.env.PORT || 3000;

app.use(cors());
app.use(express.json());
app.use(express.static('public'));

app.post('/solve', (req, res) => {
    const cube = req.body.cube;

    if (!Array.isArray(cube)) {
        return res.status(400).json({ error: 'cube must be an array' });
    }

    const solverPath = path.join(__dirname, 'NNN_Rubiks_Cube_linux_server');

    execFile(
  solverPath,
  cube.map(String),
  (err, stdout, stderr) => {

    if (err) {
        console.error("SOLVER ERROR:", err);
        console.error("SOLVER STDERR:", stderr);
        return res.status(500).json({
            error: err.message,
            stderr: stderr
        });
    }

    if (!stdout || !stdout.trim()) {
        return res.status(500).json({
            error: "Solver returned empty output"
        });
    }

    res.json({ steps: stdout.trim() });
});

});

app.listen(port, () => {
    console.log(`Server running on port ${port}`);
});

