//This will contain the 
const form = document.getElementById('dimension-form');
const instruction_1 = document.querySelector('.instruction');
const instruction_2 = document.querySelector('.intruction-2');
const color_submit = document.querySelector('.color-submit');
const footer = document.querySelector('.footer-container');

//Footer should always have the margin of 0vh
footer.style.marginTop = '0vh'

instruction_1.style.display = 'block';
instruction_2.style.display = 'none';
color_submit.style.display = 'none';

//After entering the dimension and clicking on the submit button
form.addEventListener('submit',(e)=>{
    //Form must disappear
    form.style.display = 'none';
    
    //Second instruction apppears
    instruction_1.style.display = 'none';
    instruction_2.style.display = 'block';

    //Submit button for submitting the colors
    color_submit.style.display = 'flex';
    e.preventDefault(); // stops page reload

    //Dimension of the cube
    const n = document.getElementById('dimension').value;
    
    //Add the the string that will be used to send the rubiks cube to the server
    const cube_string = [];

    //The first element that goes into the cube string must be te dimension of cube
    cube_string[0] = n;
    

    const cube = document.querySelector('.cube');

    // Clear old squares
    cube.replaceChildren();
    
    console.log("Dimension of the cube : " + n);

    //This will be used to name the index of each sqaure of the rubiks cube.
    let index = 0;
    //Formation of top face
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            // console.log(i);
            const Blanck_square = document.createElement('div');
            Blanck_square.classList.add('blanck_square');
            cube.appendChild(Blanck_square);
        }
        for (let j = 0; j < n; j++) {
            // console.log(i);
            const Colored_square = document.createElement('div');
            Colored_square.classList.add("color_square",`square_${index+1}`);
            cube.appendChild(Colored_square);
            index++;
        }
        for (let j = 0; j < n; j++) {
            // console.log(i);
            const Blanck_square = document.createElement('div') 
            Blanck_square.classList.add('blanck_square');
            cube.appendChild(Blanck_square);
        }
        cube.appendChild(document.createElement('br'));
    }

    //Formation of left, center and right face
    for(let i = 0 ; i<n ; i++){
        //The left side of rubiks cube
        for(let j=0;j<n*3;j++){
            const Colored_square = document.createElement('div');
            Colored_square.classList.add("color_square", `square_${index+1}`);
            cube.appendChild(Colored_square);
            index++;
        }
        cube.appendChild(document.createElement('br'));
    }

    //Bottom and Back face
    for(let i = 0 ; i<n*2 ; i++){
        for(let i=0;i<n;i++)
        {
            const Blanck_square = document.createElement('div');
            Blanck_square.classList.add("blanck_square");
            cube.appendChild(Blanck_square);
        }
        for(let i=0;i<n;i++){
            const Colored_square = document.createElement('div');
            Colored_square.classList.add("color_square", `square_${index+1}`);
            cube.appendChild(Colored_square);
            index++;
        }
        for(let i=0;i<n;i++)
        {
            const Blanck_square = document.createElement('div');
            Blanck_square.classList.add("blanck_square");
            cube.appendChild(Blanck_square);
        }
        cube.appendChild(document.createElement('br'));
    }
    
    //This function will be used to make the matrix that will store the values of the colors depending on the clicked and color 
    const input_square = document.getElementsByClassName('color_square');
    //Variable to rememebr which sqaure was clicked;
    let memory_square = 0;

    let previous_square_clicked = -1;
    console.log('previously clicked square : ' + previous_square_clicked);

    for(let i=0;i<input_square.length;i++){
        input_square[i].addEventListener('click',function onSquareCick(e){
            if(previous_square_clicked === i){
                e.target.style.transform = 'scale(1)';
                document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
                previous_square_clicked = -1;
                return;
            }
            if(previous_square_clicked !== -1){input_square[previous_square_clicked].style.transform = 'scale(1)';}
            
            previous_square_clicked = i;

            e.target.style.transform = 'scale(1.5)';
            const rect = e.target.getBoundingClientRect();

            //Get the cordinates of the click
            const drop_down = document.getElementsByClassName('color-filler-drop-down')[0];
            //console.log(drop_down);
            //Translate the drop box to that location
            drop_down.style.transform = `translate(${rect.x-10}px,${rect.y-25}px)`;
            drop_down.style.display = 'flex';
            drop_down.style.zIndex = '100';
            memory_square = i;
            // drop_down_opened = true;
        });
        
    }
    //Now once the drop box has appeared i will make make the event listener at the color filler buton
    document.getElementsByClassName('blue-filler')[0].addEventListener('mousedown' , (e_dash)=>{
        input_square[memory_square].style.backgroundColor = '#0000ff';
        document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
        input_square[memory_square].style.transform = 'scale(1)';
        const className = input_square[memory_square].classList[1]; 
        const index = parseInt(className.split('_')[1]);
        cube_string[index] = 2;
        //console.log(cube_string);
        // drop_down_opened = false;
        previous_square_clicked = -1;
    });
    document.getElementsByClassName('green-filler')[0].addEventListener('mousedown' , (e_dash)=>{
        input_square[memory_square].style.backgroundColor = 'rgb(0, 255, 21)';
        document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
        input_square[memory_square].style.transform = 'scale(1)';
        const className = input_square[memory_square].classList[1]; 
        const index = parseInt(className.split('_')[1]);
        cube_string[index] = 5;
        //console.log(cube_string);
        // drop_down_opened = false;
        previous_square_clicked = -1;
    });
    document.getElementsByClassName('orange-filler')[0].addEventListener('mousedown' , (e_dash)=>{
        input_square[memory_square].style.backgroundColor = 'rgba(255, 157, 0, 1)';
        document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
        input_square[memory_square].style.transform = 'scale(1)';
        const className = input_square[memory_square].classList[1]; 
        const index = parseInt(className.split('_')[1]);
        cube_string[index] = 4;
        //console.log(cube_string);
        // drop_down_opened = false;
        previous_square_clicked = -1;
    });
    document.getElementsByClassName('yellow-filler')[0].addEventListener('mousedown' , (e_dash)=>{
        input_square[memory_square].style.backgroundColor = 'rgb(246, 255, 0)';
        document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
        input_square[memory_square].style.transform = 'scale(1)';
        const className = input_square[memory_square].classList[1]; 
        const index = parseInt(className.split('_')[1]);
        cube_string[index] = 6;
        //console.log(cube_string);
        // drop_down_opened = false;
        previous_square_clicked = -1;
    });
    document.getElementsByClassName('white-filler')[0].addEventListener('mousedown' , (e_dash)=>{
        input_square[memory_square].style.backgroundColor = 'rgba(255, 254, 254, 1)';
        document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
        input_square[memory_square].style.transform = 'scale(1)';
        const className = input_square[memory_square].classList[1]; 
        const index = parseInt(className.split('_')[1]);
        cube_string[index] = 1;
        //console.log(cube_string);
        // drop_down_opened = false;
        previous_square_clicked = -1;
    });
    document.getElementsByClassName('red-filler')[0].addEventListener('mousedown' , (e_dash)=>{
        input_square[memory_square].style.backgroundColor = 'rgba(255, 0, 0, 1)';
        document.getElementsByClassName('color-filler-drop-down')[0].style.display = 'none';
        input_square[memory_square].style.transform = 'scale(1)';
        const className = input_square[memory_square].classList[1]; 
        const index = parseInt(className.split('_')[1]);
        cube_string[index] = 3;
        //console.log(cube_string);
        // drop_down_opened = false;
        previous_square_clicked = -1;
    });


    //Now this code is for the post request to the backend of the website
    //This function will checks if all the colors are as expected.
    

    

        color_submit.addEventListener('click',function onColorSubmit(){
        console.log('About to enter the server.');
        console.log(`cube_string = ${cube_string}`)
        console.log(`cube string_for_input = ${cube_string.join(' ')}`);

        //console.log('Color submit is clicked');
        fetch("/solve",{
            method: "POST",
            headers:{ "Content-Type": "application/json" },
            body: JSON.stringify({cube: cube_string})
        })
        .then((res)=>{return res.json();})
        .then((data) => {
            //console.log(data); // data is already the JS object

            // Hide cube UI
            const rubiks_cube_contain = document.querySelector('.rubiks-cube-container');
            rubiks_cube_contain.style.display = 'none';

            // Show steps UI
            const steps = document.querySelector('.steps-container');
            steps.style.display = 'block';

            //This will convert the object to array
            data = data.steps.split(" ").map(Number);

            console.log('Here are the steps printed by computer : ' + data);

            //Steps printing
            //last element in data will be total number of steps
            const total_steps = document.createElement('div');
            total_steps.classList.add('Total_Steps');
            total_steps.innerHTML = `Total Steps : ${data[data.length-1]}`;

            let number_of_steps = 0;

            for(let i=0;i<data.length-1;){
                //Now we will traverse through the data for four data and print the steps
                const stp = document.createElement('div');
                stp.classList.add('step');
                let step = data[i];
                number_of_steps = number_of_steps + 1;
                i = i+1;
                let face_axis = data[i];
                i = i+1;
                let layer_number = data[i];
                i = i+1;
                let direction = data[i];
                i = i+1;

                //Rotation about X axis
                if(face_axis === 1){
                    //Rotation of layer up
                    if(direction === 1){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from LEFT, up</p>`;
                    }
                    //Rotation of layer down
                    else if(direction === 3){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from LEFT, down</p>`;
                    }
                    //Rotation of layer twice
                    else if(direction === 2){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from LEFT, twice</p>`;
                    }
                } 
                //Rotation about Y axis
                else if(face_axis === 2){
                    //Roation to right
                    if(direction === 1){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from BOTTOM, right</p>`;
                    }
                    //Rotation to left
                    else if(direction === 3){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from BOTTOM, left</p>`;
                    }
                    //Roation twice
                    else if(direction === 2){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from BOTTOM, twice</p>`;
                    }
                } 
                //Rotation about Z axis
                else if(face_axis === 3){
                    //Rotation in Anti-Clockwise
                    if(direction === 1){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from FRONT, anticlockwise</p>`;
                    }
                    //Rotation is Clockwise direction
                    else if(direction === 3){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from FRONT, clockwise</p>`;
                    }
                    //Rotation of layer Twice
                    else if(direction === 2){
                        stp.innerHTML = `<p>${number_of_steps}) Rotate ${layer_number + 1}th layer from FRONT, twice</p>`;
                    }
                }

                steps.appendChild(stp);
            }
            
            color_submit.style.display = 'none';

        })
        .catch(err => console.error(err));     
    });
});




