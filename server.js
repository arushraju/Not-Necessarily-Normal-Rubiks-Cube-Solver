const express = require('express');
const { execFile } = require('child_process');
const cors = require('cors');


const app = express();
const port = process.env.PORT || 3000;

app.use(cors());
app.use(express.json());
app.use(express.static('public'));

//This defines what would to do when the frontend request does the POST request to /solve.
//req is the incoming request to the browzer and res is what the server will send back.
app.post('/solve', (req, res) => {
    //In the req we know the file sends the object cube in which it sends the array.
    const cube = req.body.cube;//This should now be a 54 sized array.

    //./solver is the external program that server runs.
    /**cube.map(String) converts each number in the array to a string, because execFile expects its arguments as strings. So your solver is called like:
    ./solver "2" "5" "3" ... */
    //And then there is a callback fucntion that if there is an error then do some thign or else do other other thing.
    execFile('./solver.exe', cube.map(String), (err, stdout) => {
        if (err) return res.json({ error: err.message });
        //Otherwise, stdout is whatever your solver printed (the solution moves). stdout.trim() removes extra whitespace
        //res.json({ steps: stdout.trim() }); sends back JSON like { "steps": "R U R' ..." } to the frontend
        res.json({ steps: stdout.trim() });  // return solution steps
    });
    
});

//Starts the server

app.listen(port, () => console.log(`Server running on port ${port}`));
