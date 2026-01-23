/**********************     BACKEND VERSION OF THE CODE *************** */
#include<stdio.h>
#include<stdlib.h>

//If working for deployment
int deploy = 1;

//If testing
int test = 0;

//This is for number of steps
int steps = 0;

/*This will be the data structure i will be using. It represents the cube
And this contains 6 faces each of dimension n*n. N to be
global variables*/
int n; //Dimension of the cube

//This function is to tell the user about precautions
void precaution()
{
    if(test) printf("1.The cube shown below is just to check if it is rightly intialized.\n");
    return;
}

/*This will intialize the cube pointer. Note that it would be a 3D array. And so, the first pointer
which is '***' will point to array of 6 element which would represent faces. Then the next 
pointer that is '**', will point to a X-axis of the face, which would be of lengh n, and then the next pointer 
will point to '*' will point to array of Y-axis of lenght n.*/

int ***cube; //Initialzation will happen in create function.

void create()
{
    //the first index will represent the face
    cube = (int***)malloc(sizeof(int**)*6);
    for(int i = 0;i<6;i++)
    {
        //Second index represents x axis (cartesian)
        cube[i] = (int**)malloc(sizeof(int*)*n);
        for(int j=0;j<n;j++)
        {
            //Third index represent the y axis. (cartesian)
            cube[i][j] = (int*)malloc(sizeof(int)*n);
        }
    }
    return;
}

/**
 * Here is the convention for number that will be filled in the faces
 * Top Face     :   0
 * Front Face   :   1
 * Left Face    :   2
 * Right Face   :   3
 * Bottom Face  :   4
 * Back Face    :   5
 */
//this function will be used to fill the color configuration
void intialize(int* cube_encoded)
{
    int index = 0;
    
    //Now the first I will input the top face
    for(int j=n-1;j>=0;j--)//to scan the rows(i)
    {
        for(int i=0;i<n;i++)//to scan the columns(j)
        {
            cube[0][i][j] = cube_encoded[index];
            index++;
        }
    }
    
    //And now we will fill the left, front and right faces
    for(int row = n-1;row>=0;row--){
        //First the left face
        for(int column=0;column<n;column++){
            cube[2][column][row] = cube_encoded[index];
            index++;
        }
        //Next the front face
        for(int column=0;column<n;column++){
            cube[1][column][row] = cube_encoded[index];
            index++;
        }
        //Next the right face
        for(int column=0;column<n;column++){
            cube[3][column][row] = cube_encoded[index];
            index++;
        }
    }

    //And now the bottom face
    for(int j=n-1;j>=0;j--)//to scan the rows(i)
    {
        for(int i=0;i<n;i++)//to scan the columns(j)
        {
            cube[4][i][j] = cube_encoded[index];
            index++;
        }
    }

    //And now the back face
    for(int j=n-1;j>=0;j--)//to scan the rows(i)
    {
        for(int i=0;i<n;i++)//to scan the columns(j)
        {
            cube[5][i][j] = cube_encoded[index];
            index++;
        }
    }
    return;
}

//This function is to display the cube completely.
void display()
{
    printf("\n");
    int a,b,c;
    //first printing the top face
    for(int i=n-1;i>=0;i--)// 'a' could be used in printing the rows of top face.
    {
        //space for n times
        for(b=0;b<n*2;b++)
        {
            printf(" ");
        }
        //Now print the top face colors from left to right.
        for(c=0;c<n;c++)
        {
            printf("%d ",cube[0][c][i]);
        }
        printf("\n");
    }

    //Now printing the middle three faces in 2d projection of cube
    for(int i=n-1;i>=0;i--)// 'i' will be used for each row.
    {
        //first the columns of face 2(red)
        for(a=0;a<n;a++)
        {
            printf("%d ",cube[2][a][i]);
        }
        //Now the columns of face 1(blue)
        for(b=0;b<n;b++)
        {
            printf("%d ",cube[1][b][i]);
        }
        //Now the columns of face 3(orange)
        for(c=0;c<n;c++)
        {
            printf("%d ",cube[3][c][i]);
        }
        printf("\n");
    }

    //Now printing the bottom face
    for(int i=n-1;i>=0;i--)
    {
        //Space
        for(a=0;a<n*2;a++)
        {
            printf(" ");
        }
        //Now comes columns of bottom face
        for(b=0;b<n;b++)
        {
            printf("%d ",cube[4][b][i]);
        }
        printf("\n");
    }

    //Now printing the back face
    for(int i=n-1;i>=0;i--)
    {
        //Space
        for(a=0;a<n*2;a++)
        {
            printf(" ");
        }
        //Now comes columns of bottom face
        for(b=0;b<n;b++)
        {
            printf("%d ",cube[5][b][i]);
        }
        printf("\n");
    }
    printf("\n");
}

/*Now that i have made the display clear, let me try to make the whole rotation thing possible, since 
That will allow me to work on algorithm part.*/
/*So the rotation will take in the following paramenter:
1.  Which way to rotate:                  left/right,  top/bottom,     front/back.
2.  Which layer of that face to rotate:    p from left, p from bottom,  p from front.
3.  How many times to rotate:              m.
And that's it.
*/
void rot(char way, int p, int m)
{
    int temp;
    /**
     * Here is a quick note on how this algorithm works. For exmaple if we tak about 'l', if the layers are at the extremes not just the colors at 0,1,4,5 face, will move but also the ones that are at the face 2,3. But if the layer is not the extreme one, then the colors at face 2 and 3 will not rotate and we can just carry on with exchanging the colrs at face 0,1,4,5.
     */

    //This means rotation of left face, up.
    if(way == 'l')
    {
        for(int t = 0;t<m;t++)
        {
            steps++;
            //This means rotation of the left most layer.
            if(p==0)
            {
                //This below algorithm is to rotate the red face anticlockwise since the left layer is moved up.
                for(int k=0;k<n/2;k++)
                {
                    for(int i=k;i<n-1-k;i++)
                    {   
                        temp = cube[2][i][k];
                        cube[2][i][k] = cube[2][k][n-1-i];
                        cube[2][k][n-1-i] = cube[2][n-1-i][n-1-k];
                        cube[2][n-1-i][n-1-k] = cube[2][n-1-k][i];
                        cube[2][n-1-k][i] = temp;
                    }
                }
            }
        
            //This means rotation of the right most layer
            else if(p==n-1)
            {
                //This below algorithm is to rotate the orange face clockwise since the right layer is moved up.
                for(int k=0;k<n/2;k++)
                {
                    for(int i=k;i<n-1-k;i++)
                    {
                        temp = cube[3][i][k];
                        cube[3][i][k] = cube[3][n-1-k][i];
                        cube[3][n-1-k][i] = cube[3][n-1-i][n-1-k];
                        cube[3][n-1-i][n-1-k] = cube[3][k][n-1-i];
                        cube[3][k][n-1-i] = temp;
                    }
                }
            }

            //Now that we have taken care of cases of extreme layer rotation
            for(int j=0;j<n;j++)
            {
                temp = cube[1][p][j];
                cube[1][p][j] = cube[4][p][j];
                cube[4][p][j] = cube[5][p][j];
                cube[5][p][j] = cube[0][p][j];
                cube[0][p][j] = temp;
            }
        }
        if(m==1){
            if(test) printf("Rotate %d th layer from left, up\n",p+1);
            if(deploy){printf("%d 1 %d 1 ",steps,p);}
        }
        else if(m==3){
            if(test) printf("Rotate %d th layer from left, down\n",p+1);
            if(deploy){printf("%d 1 %d 3 ",steps,p);}
        }
        else{
           if(test) printf("Rotate %d th layer from left twice\n",p+1);
           if(deploy){printf("%d 1 %d 2 ",steps,p);}
        } 
    }

    //This means rotation of bottom face, right.
    else if(way == 'b')
    {
        for(int t=0;t<m;t++)
        {
            steps++;
            //If the layer is the bottom most layer
            if(p==0)
            {
                /*If thre bottom most layer is moved to right, then the bottom face will
                rotate clockwise.*/
                for(int k=0;k<n/2;k++)
                {
                    for(int i=k;i<n-1-k;i++)
                    {
                        temp = cube[4][i][k];
                        cube[4][i][k] = cube[4][n-1-k][i];
                        cube[4][n-1-k][i] = cube[4][n-1-i][n-1-k];
                        cube[4][n-1-i][n-1-k] = cube[4][k][n-1-i];
                        cube[4][k][n-1-i] = temp;
                    }
                }
            }
            //If the layer is the top most layer
            else if(p==n-1)
            {   
                /*This for loop will rotate the top face(white) anticlockwise*/
                for(int k=0;k<n/2;k++)
                {   
                    for(int i=k;i<n-1-k;i++)
                    {
                        temp = cube[0][i][k];
                        cube[0][i][k] = cube[0][k][n-1-i];
                        cube[0][k][n-1-i] = cube[0][n-1-i][n-1-k];
                        cube[0][n-1-i][n-1-k] = cube[0][n-1-k][i];
                        cube[0][n-1-k][i] = temp;
                    }
                }
            }

            //This will rotate the mid layers according to p.
            for(int j=0;j<n;j++)
            {
                temp = cube[2][j][p];
                cube[2][j][p] = cube[5][n-1-j][n-1-p];
                cube[5][n-1-j][n-1-p] = cube[3][j][p];
                cube[3][j][p] = cube[1][j][p];
                cube[1][j][p] = temp;
            }
        }
        if(m==1){
            if(test) printf("Rotate %d th layer from bottom, right\n",p+1);
            if(deploy) printf("%d 2 %d 1 ",steps,p);
        }
        else if(m==3){
            if(test) printf("Rotate %d th layer from bottom, left\n",p+1);
            if(deploy) printf("%d 2 %d 3 ",steps,p);
        }
        else{
          if(test) printf("Rotate %d th layer from bottom, twice\n",p+1);
          if(deploy) printf("%d 2 %d 2 ",steps,p);
        } 
    }

    //This means rotation of front face, anti-clockwise.
    else if(way == 'f')
    {
        for(int t = 0;t<m;t++)
        {
            steps++;
            //This means we want to rotate the layer that is 0 distance awya from fornt face anticlockwise
            //Which is the front face itself.
            if(p==0)
            {
                /*This is an attempt to rotate the fornt face anticlockwise*/
                for(int k=0;k<n/2;k++)
                {
                    for(int i=k;i<n-1-k;i++)
                    {
                        temp = cube[1][i][k];
                        cube[1][i][k] = cube[1][k][n-1-i];
                        cube[1][k][n-1-i] = cube[1][n-1-i][n-1-k];
                        cube[1][n-1-i][n-1-k] = cube[1][n-1-k][i];
                        cube[1][n-1-k][i] = temp;
                    }
                }
            }
            /*This means rotation of the (n-1)th layer from front which is the 
            back face anticlockwise which means clockwise if seen from the box diagram*/
            else if(p==n-1)
            {
                /*If thre back most layer is moved anticlockwise with respect to front viewer, then the back face will
                rotate clockwise with respect to box diagram*/
                for(int k=0;k<n/2;k++)
                {
                    for(int i=k;i<n-1-k;i++)
                    {
                        temp = cube[5][i][k];
                        cube[5][i][k] = cube[5][n-1-k][i];
                        cube[5][n-1-k][i] = cube[5][n-1-i][n-1-k];
                        cube[5][n-1-i][n-1-k] = cube[5][k][n-1-i];
                        cube[5][k][n-1-i] = temp;
                    }
                }
            }
        
            //this will rotate the mid layers
            for(int j=0;j<n;j++)
            {
                temp = cube[0][j][p];
                cube[0][j][p] = cube[3][p][n-1-j];
                cube[3][p][n-1-j] = cube[4][n-1-j][n-1-p];
                cube[4][n-1-j][n-1-p] = cube[2][n-1-p][j];
                cube[2][n-1-p][j] = temp;
            }
        }
        if(m==1){
            if(test) printf("Rotate %d th layer from front, anticlockwise\n",p+1);
            if(deploy) printf("%d 3 %d 1 ",steps,p);
        }
        else if(m==3){
            if(test) printf("Rotate %d th layer from front, clockwise\n",p+1);
            if(deploy) printf("%d 3 %d 3 ",steps,p);
        }
        else{
          if(test) printf("Rotate %d th layer from front, twice\n",p+1);
          if(deploy) printf("%d 3 %d 2 ",steps,p);
        } 
    }
    
    return;
}

/*Here is the finalized picture of what rot function is:
So the function takes in three parameter. And they are:
1. 'l' , 'b' , 'f' which tells about the face we would like to rotate
2. 'p' is layer from left/bottom/front that we want to rotate.
3. 'm' is the number of times we want to rotata that layer.
Now the important thing to note is 
All the left layer will be moved up
All the bottom layer will be moved to right.
All the front layers will be moved anti-clockwise.*/

/*Now let make the turn function to actually turn the rubiks cube.
Here it can take in three alphabets or characters. 
1. And if it is equal to 'l' this would mean turn the cube up. It will essentially turn all the left layers up.
2. And if it is equal to 'f' this will rotate the cube anticlockwise from front. It will essentially rotate all the front layers anticlockwise.
3. And if it is equal to 'b' this will rotate the cube to right, because all the bottotm layers will be moved to right.
And the value of x will tell us how many times do we have to rotate it.
*/
void turn(char p,int x)
{
    for(int j=0;j<x;j++)
    {
        for(int i=0;i<n;i++)
        {
            rot(p,i,1);
        }
    }
}

                                                       /*CENTER CREATION*/
/****************************************************************************************************************************************/
/*
Now that we have got the turn function working now its time for the real algorithm to kick in.
F       ollowing code is for center peice creation.
Here i am aiming to have
1. Top face with all the 1's
2. Front face with all the 2's
3. Left face with all the 3's
4. Right face with all the 4's
5. Bottom face with all the 5's
6. Back face with all the 6's
*/

/*
moving [1][x][y] to [0][x][y]
*/
void algo1(int x,int y)
{
    //The algorithm here is nothing new.
    if(x!=y)
    {
        rot('l',x,1);   //Rotate the x-th left layer up.
        rot('b',n-1,3); //Rotate the top layer to left
        rot('l',y,1);   //Rotata the y-th layer up
        rot('b',n-1,1); //Rotate the top layer to right
        rot('l',x,3);   //Rotate the x-th layer down
        rot('b',n-1,3); //Rotate the top layer left
        rot('l',y,3);   //Rotate the y-th layer down
        rot('b',n-1,1); //Rotate the top layer right
    }

    /*
    However here there is just one difference and that is 
    that we must rotate the top layer to right rather than left first. And then alternate.
    and also that y = n-1-x when using it in the rot function.
    */
    else
    {
        rot('l',x,1);   //Roatate the x-th left layer up.
        rot('b',n-1,1); //Rotate the top layer to right
        rot('l',n-1-x,1);   //Roata the y-th layer up
        rot('b',n-1,3); //Rotate the top layer to left
        rot('l',x,3);   //Rotate the x-th layer down
        rot('b',n-1,1); //Rotate the top layer right
        rot('l',n-1-x,3);   //Rotate the y-th layer down
        rot('b',n-1,3); //Rotate the top layer left
    }
}
/*
                                                                    Remember, this means 
                                                                    white   =     1
                                                                    blue    =     2
                                                                    red     =     3
                                                                    orange  =     4
                                                                    green   =     5
                                                                    yellow  =     6
*/
void center()
{
    //lets first make the top center which is 1's
    for(int b=0;b<3;b++)
    {
        //First we will scan through the center peices on the rubik's cube.
        //Thus for loop will scan trhough all the faces of color blue, orange, red, green.
    
        for(int a=0;a<4;a++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {   
                    //Check if the spot is white
                    if(cube[1][i][j]==1)
                    {
                        //Check if the spot on the top face is vacant for the white to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==1)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
            if(test) printf("\n*\n");
            turn('b',1);
            if(test) printf("\n*\n");
        }
    
        //Now we will bring all the colors from bottom face(yellow) to front face(blue)
        if(test) printf("\n");
        turn('l',1);//Turn the cube up, so that bottom face is in our front
        if(test) printf("\n");

        for(int i=1;i<n-1;i++)
        {
            for(int j=(n-2);j>=1;j--)
            {
                //If any element in the bottom is equal to white , then bring it at the front.
                if(cube[1][i][j]==1) algo1(i,j);
            }
        }
    
        if(test) printf("\n");
        turn('l',3);//Now turn the cube down, so that we come to our usual setup.
        if(test) printf("\n");

        //Now for the last time we will transfer the white colors from front to top face.
        for(int i=1;i<n-1;i++)
        {
            for(int j=(n-2);j>=1;j--)
            {
                //Check if the spot is white
                if(cube[1][i][j]==1)
                {
                    //Check if the spot on the top face is vacant for the white to occupy which is currently at front face.
                    //This loop will rotate the top layer until corresponding spot is found on the top face.
                    while(cube[0][i][j]!=1)
                    {
                        rot('b',n-1,1);
                    }
                    //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                    algo1(i,j);
                }
            }
        }
 /* 
        //Recheck
        for(int a=0;a<4;a++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is white
                    if(cube[1][i][j]==1)
                    {
                        //Check if the spot on the top face is vacant for the white to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==1)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
            if(test) printf("\n*\n");
            turn('b',1);
            if(test) printf("\n*\n");
        }
*/
        
    }
    if(test) printf("\nCompleted white center\n");
    if(test) display();
    //Now we move on to making the yellow center that is 6's.
    {
        //first we rotate the cube twice, from the front.
        if(test) printf("\n");
        turn('f',2);
        if(test) printf("\n");
        //and now we can perform the scanningn of all the centers.
        for(int a=0;a<8;a++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                //Check if the spot is white
                    if(cube[1][i][j]==6)
                    {
                        //Check if the spot on the top face is vacant for the white to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==6)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
            if(test) printf("\n*\n");
            turn('b',1);
            if(test) printf("\n*\n");
        }
        //Now we bring back the original orientation of cube.
        if(test) printf("\n");
        turn('f',2);
        if(test) printf("\n");
        if(test) display();
        if(test) printf("Completed yellow center\n");
    }

    //Now we start making the red color
    //1. Here we first turn the cube clockwise wrt front.
    //2. And then we will send all the red colors from front face to top face
    //3. Then we will turn the cube to left twice. and again bring all the red colors to top
    //4. Then we will bring all the red colors from bottom and put it in the top again
    //5. Then we will turn the cube twice. And rotate the cube anticlockwise once
    //And our red color will be completed.
    {
        turn('f',3);//Turn the cube clockwise
        if(test) display();
        //Transfer all the colors from blue face to red face
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is red
                    if(cube[1][i][j]==3)
                    {
                        //Check if the spot on the top face is vacant for the red to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==3)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                        if(test) display();
                        if(test) printf("\n");
                    }
                }
            }
        }
        if(test) display();
        turn('b',2);//Turn the cube to left twice to get to green face
        if(test) display();
        //Transfer all the red color from green to red face
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is red
                    if(cube[1][i][j]==3)
                    {
                        //Check if the spot on the top face is vacant for the red to occupy which is currently at green face(back).
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==3)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                        if(test) display();
                        if(test) printf("\n");
                    }
                }
            }
        }
        if(test) display();
        //Now bring all the red color from bottom(orange) to green face
        turn('l',1);//Turn the cube down (facing orange face)
        if(test) display();
        //Transfer all the red color from orange to green face
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is red
                    if(cube[1][i][j]==3)
                    {
                        //Check if the spot on the top face is vacant for the red to occupy which is currently at orange face(right).
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==3)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                        if(test) display();
                        if(test) printf("\n");
                    }
                }
            }
        }
        if(test) display();
        turn('l',3);//Turn the cube up
        if(test) display();
        //Transfer all the red color from green to red face
        for(int t=0;t<2;t++)
        {    
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is red
                    if(cube[1][i][j]==3)
                    {
                        //Check if the spot on the top face is vacant for the red to occupy which is currently at orange face(right).
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==3)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                        if(test) display();
                        if(test) printf("\n");
                    }
                }
            }
        }
        if(test) display();
        turn('f',3);//Turn the cube clockwise
        if(test) display();
        turn('b',2);//Turn the cube to left twice
        if(test) display();
        if(test) printf("\nCompleted red center\n");
    }


    //Blue center
    //Now lets start making the blue center
    //1. We first turn the cube clockwise
    //2. turn the cube down twice and bring the blue from back(green) to top(orange)
    //3. turn the cube up. And bring all the elements from orange to blue. 
    {
        turn('f',3);//turn the cube clockwise from front
        turn('l',1);//Turn the cube down (facing orange face)
        //Bring all the colors from orange face to blue face
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is blue
                    if(cube[1][i][j]==2)
                    {
                        //Check if the spot on the top face is vacant for the blue to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==2)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
        }
        //Now trun the cube down facing the green face
        turn('l',1);
        //Bring all the colors from green face to orange face
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is blue
                    if(cube[1][i][j]==2)
                    {
                        //Check if the spot on the top face is vacant for the blue to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==2)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
        }
        //Turn the cube back to facing the orange face (turn cube up)
        turn('l',3);
        //Bring all the colors from orange to blue face
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is blue
                    if(cube[1][i][j]==2)
                    {
                        //Check if the spot on the top face is vacant for the blue to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==2)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
        }
        //Turn the cube up facing blue
        turn('l',3);
        //rotate the cube anticlokwise
        turn('f',1);
    }


    //Green center
    //1. We first turn the cube right (which means turn three times)
    //2. Then we rotate the cube anti-clockwise
    //3. And we transfer all the green to the top
    //4. then we roate the cube clockwise and turn the cube to left (turn one time) 
   {
        turn('b',3);//turn to right side of the cube
        turn('f',1);//Turn the cube anti-clockwise
        //Transfer all the green colors to top
        for(int t=0;t<2;t++)
        {
            for(int i=1;i<n-1;i++)
            {
                for(int j=(n-2);j>=1;j--)
                {
                    //Check if the spot is red
                    if(cube[1][i][j]==5)
                    {
                        //Check if the spot on the top face is vacant for the red to occupy which is currently at front face.
                        //This loop will rotate the top layer until corresponding spot is found on the top face.
                        while(cube[0][i][j]==5)
                        {
                            rot('b',n-1,1);
                        }
                        //Now that we have the spot on the top layer and the color at the fornt face we will apply the usual algo of moving the color up.
                        algo1(i,j);
                    }
                }
            }
        }
        turn('f',3);//Turn the cube clockwise
        turn('b',1);//Turn to left side of cube
        if(test) printf("\nCompleted the green color center\n");
    }
    if(test) printf("Completed the centers!\n");
}   

                                                    /*EDGE PAIRING ALGORITHM*/
/*****************************************************************************************************************************************/
//This will store the count of edge that is solved.
int critical = 0;

/*
This function is such that it will take in the position of edges in the form of face color around them. And then
the function would return 0 if the edge is not solved and 1 if it is solved.
Remember, this means 
white   =     1
blue    =     2
red     =     3
orange  =     4
green   =     5
yellow  =     6
Here face 1 and face 2 means color and not the face number.
*/
int is_edge_solved(int face1,int face2)
{
    if(test) printf("Into is_edge_solved...\n");
    int color1;
    int color2;
    //Blue - White Edge
    if((face1 == 2 && face2 == 1) || (face1 == 1 && face2 == 2))
    {
        color1 = cube[1][1][n-1];
        color2 = cube[0][1][0];
        for(int i=1;i<n-1;i++)
        {
            if(cube[1][i][n-1] != color1 || cube[0][i][0] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Blue-White) face is solved\n");
        return 1;
    }

    //Blue-Yellow Edge
    else if((face1 == 2 && face2 == 6) || (face1 == 6 && face2 == 2))
    {
        color1 = cube[1][1][0];
        color2 = cube[4][1][n-1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[1][i][0] != color1 || cube[4][i][n-1] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Blue-Yellow) face is solved\n");
        return 1;
    }

    //Blue - Red Edge
    else if((face1 == 3 && face2 == 2) || (face1 == 2 && face2 == 3))
    {
        color1 = cube[1][0][1];
        color2 = cube[2][n-1][1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[1][0][i] != color1 || cube[2][n-1][i] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Blue-red) face is solved\n");
        return 1;
    }

    //Red - White Edge
    else if((face1 == 1 && face2 == 3) || (face1 == 3 && face2 == 1))
    {
        color1 = cube[0][0][1];
        color2 = cube[2][n-2][n-1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[0][0][i] != color1 || cube[2][n-1-i][n-1] !=  color2) return 0;
        }
        if(test) printf("\nThe edge with (White - Red) face is solved\n");
        return 1;
    }

    //Green - Red
    else if((face1 == 3 && face2 == 5) || (face1 == 5 && face2 == 3))
    {
        color1 = cube[2][0][1];
        color2 = cube[5][0][n-2];
        for(int i=1;i<n-1;i++)
        {
            if(cube[2][0][i] != color1 || cube[5][0][n-1-i] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Green-Red) face is solved\n");
        return 1;
    }

    //Red-Yellow
    else if((face1 == 3 && face2 == 6) || (face1 == 6 && face2 == 3))
    {
        color1 = cube[2][1][0];
        color2 = cube[4][0][1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[2][i][0] != color1 || cube[4][0][i] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Red-Yellow) face is solved\n");
        return 1;
    }

    //Blue-Orange
    else if((face1 == 2 && face2 == 4) || (face1 == 4 && face2 == 2))
    {
        color1 = cube[3][0][1];
        color2 = cube[1][n-1][1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[3][0][i] != color1 || cube[1][n-1][i] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Blue-Orange) face is solved\n");
        return 1;
    }

    //White-Orange
    else if((face1 == 1 && face2 == 4) || (face1 == 4 && face2 == 1))
    {
        color1 = cube[0][n-1][1];
        color2 = cube[3][1][n-1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[0][n-1][i] != color1 || cube[3][i][n-1] != color2) return 0;
        }
        if(test) printf("\nThe edge with (White-Orange) face is solved\n");
        return 1;
    }

    //Green-Orange
    else if((face1 == 4 && face2 == 5) || (face1 == 5 && face2 == 4))
    {
        color1 = cube[3][n-1][1];
        color2 = cube[5][n-1][n-2];
        for(int i=1;i<n-1;i++)
        {
            if(cube[3][n-1][i] != color1 || cube[5][n-1][n-1-i] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Green-Orange) face is solved\n");
        return 1;
    }

    //Orange-Yellow
    else if((face1 == 4 && face2 == 6) || (face1 == 6 && face2 == 4))
    {
        color1 = cube[3][1][0];
        color2 = cube[4][n-1][n-2];
        for(int i=1;i<n-1;i++)
        {
            if(cube[3][i][0] != color1 || cube[4][n-1][n-1-i] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Orange-Yellow) face is solved\n");
        return 1;
    }

    //White-Green
    else if((face1 == 1 && face2 == 5) || (face1 == 5 && face2 == 1))
    {
        color1 = cube[0][1][n-1];
        color2 = cube[5][1][0];
        for(int i=1;i<n-1;i++)
        {
            if(cube[0][i][n-1] != color1 || cube[5][i][0] != color2) return 0;
        }
        if(test) printf("\nThe edge with (White-Green) face is solved\n");
        return 1;
    }

    //Green-Yellow
    else if((face1 == 5 && face2 == 6) || (face1 == 6 && face2 == 5))
    {
        color1 = cube[4][1][0];
        color2 = cube[5][1][n-1];
        for(int i=1;i<n-1;i++)
        {
            if(cube[4][i][0] != color1 || cube[5][i][n-1] != color2) return 0;
        }
        if(test) printf("\nThe edge with (Green-Yellow) face is solved\n");
        return 1;
    }

    if(test) printf("Invalid Color\n");
    return -1;
}

//This will transfer the colors from bottom front edge to top front edge. This function will not solve an edge completely. So out of 3 edge pieces if there is just one dge piece in the bottom-front edge and the top and left edge are garbage, then this function will only transfer that one edge piece. So the edge might not be fully solved.
void pair(int top, int front)
{
    if(test) printf("Into Pair Function.\nHere it is assumed that I have Unsolved edge at position (White-Blue) and (Blue-Yellow)\n");
    if(test) display();
    //I starts from 1 because, i = 0 and j = 0 will not be an edge piece but a corner. Similarly for i = n-1
    for(int i=1;i<n-1;i++)
    {
        //Check if the (Blue-Red) edge is solved, then we would like to bring a garbage edge at that position for solving the rubiks cube. But during all of this, since the start of this fucntion, we are assuming that edge (white-blue), and (blue-yellow) are unsolved. So whne bringing some other garbage edge to blue-red edge, we must be cautious about not messing up with blue-yellow and blue-white edge.
        if(is_edge_solved(2,3)==1)
        {
            //Check if the (Red-White) edge is unsolved
            if(is_edge_solved(3,1) == 0)
            {
                rot('l',0,3);//rotate left layer down
            }

            //Check if the (Red-Green) edge is unsolved
            else if(is_edge_solved(3,5) == 0)
            {
                rot('l',0,2);//Rotate the left layer twice
            }

            //Check if the (Red-Yellow) edge is unsolved
            else if(is_edge_solved(3,6) == 0)
            {
                rot('l',0,3);//Rotate left layer up
            }

            //Check if the (Ornage-Blue) edge is unsolved
            else if(is_edge_solved(2,4) == 0)
            {
                rot('l',n-1,3);//Rotate the right layer down
                rot('b',0,2);//Rotate bottom layer twice
                rot('l',0,1);//Rotate left layer up
                rot('b',0,2);//Rotate the bottom layer twice
            }

            //Check if the (Ornage-White) edge is unsolved
            else if(is_edge_solved(1,4) == 0)
            {
                rot('l',n-1,2);//Rotate the right layer twice
                rot('b',0,2);//Rotate bottom layer twice
                rot('l',0,1);//Rotate left layer up
                rot('b',0,2);//Rotate bottom layer twice
            }
            
            //Check if the (Ornage-Green) edge is unsolved
            else if(is_edge_solved(4,5) == 0)
            {
                rot('l',n-1,1);//Rotate the right layer up
                rot('b',0,2);//Rotate bottom layer twice
                rot('l',0,1);//Rotate left layer up
                rot('b',0,2);//Rotate bottom layer twice
            }
            
            //Check if the (Orange-Yellow) edge is unsolved
            else if(is_edge_solved(4,6) == 0)
            {
                rot('b',0,2);//Rotate bottom layer twice
                rot('l',0,1);//Rotate left layer up
                rot('b',0,2);//Rotate bottom layer twice
            }

            //Check if the (White-Green) edge is unsolved
            else if(is_edge_solved(1,5) == 0)
            {
                rot('f',n-1,1);//Rotate the back face anticlockwise 
                rot('l',0,2);//Rotate the left layer twice
            }

            //Check if the (green-Yellow) edge is unsolved
            else if(is_edge_solved(5,6) == 0)
            {
                rot('b',0,1);//Rotate bottom layer to right
                rot('l',0,1);//Rotate left layer up
                rot('b',0,3);//Rotate bottom layer to left
            }
        }

        //Now we are assuming that there is an garbage edge at the position (Blue - Red) Edge.
        if(test) printf("Must be an unsolved edge at the (Blue,Red)\n");
        if(test) display();
        //Proceed to fill one edge piece.
        if(cube[1][i][0] == top && cube[4][i][n-1] == front)
        {
            rot('l',i,1);//Rotate i-th layer form left up
            rot('b',n-1,3);//Rotate top layer to left
            rot('l',0,1);//Rotate the left layer up
            rot('b',n-1,1);//rotate top layer right
            rot('l',i,3);//Rotate the i-th layer down
            rot('l',0,3);//Rotate left layer down
            rot('b',n-1,1);//Rotate the top layer right
            critical =  critical + 1;
        }

        else if(cube[1][i][0] == front && cube[4][i][n-1] == top)
        {
            //To get to the correct orientation of edge piece
            rot('b',0,1);//Rotate the bottom layer to right
            rot('f',0,1);//Rotate the front layer anti-clockwise
            rot('l',n-1,1);//Rotate the right layer up
            rot('f',0,3);//Rotate the front face clockwise

            //Execute the transfer
            rot('l',n-1-i,1);//Rotate (n-1-i)-th layer form left up
            rot('b',n-1,3);//Rotate top layer to left
            rot('l',0,1);//Rotate the left layer up
            rot('b',n-1,1);//Rotate top layer right
            rot('l',n-1-i,3);//Rotate the (n-i)-th layer down
            rot('l',0,3);//Rotate left layer down
            rot('b',n-1,1);//Rotate the top layer right
        
            //Restoring
            rot('b',0,1);//Rotate the bottom layer to right
            rot('f',0,1);//Rotate the front layer anti-clockwise
            rot('l',n-1,1);//Rotate the right layer up
            rot('f',0,3);//Rotate the front face clockwise
        
            critical =  critical + 1;

        }
    }

    if(test) printf("Now the edge at (White-Blue) position must be solved\n");
    if(test) display();
    

    if(test) printf("If the cube is odd, then there is a posibility of having an unsolved edge due to center\n");
    if(test) printf("Solved (1,2) = %d?\n",is_edge_solved(1,2));

    //This is for the odd dimensional cubes only.
    if(n%2 != 0)
    {
        if(cube[1][n/2][n-1] == top && cube[0][n/2][0] == front)
        {
            for(int i=(n/2)+1;i<n-1;i++){rot('l',i,3);}
            rot('b',n-1,2);
            for(int i=1;i<(n/2);i++){rot('l',i,3);}
            rot('f',0,2);
            for(int i=1;i<(n/2);i++){rot('l',i,1);}
            rot('f',0,2);
            for(int i=(n/2)+1;i<n-1;i++){rot('l',i,2);}
            rot('b',n-1,2);
            for(int i=(n/2)+1;i<n-1;i++){rot('l',i,1);}
            rot('b',n-1,2);
            for(int i=(n/2)+1;i<n-1;i++){rot('l',i,3);}
            rot('b',n-1,2);
            rot('f',0,2);
            for(int i=(n/2)+1;i<n-1;i++){rot('l',i,2);}
            rot('f',0,2);

            critical =  critical + 1;
        }
    }
    return;
}

/*
This function will take in the top and front color of the edge that we wish to solve and it will solve it, and return the cube
with the edge of the solved one in top-front. It takes in two argument. Top color is the desired top color of edge at the top face, and front_color
is the desired front color of the edge.
*/
/*So for example we wish to prepare a complete Red-white edge on the (1,2) edge, so in that case the function will assume that there is an garbage edge at posiiton (1,2), and will solve for (white-red) edge at (1,2).But the (1,4) edge might or might not be garbage.*/
void solve_edge(int top_color,int front_color)
{
    if(test) printf("\nInto edge_solve function\n");
    if(test) printf("Critical = %d\n",critical);
    if(test) display();
    //if there are only two edges left to solve, then this function will not work.
    if(critical == n-2) 
    {
        if(test) printf("\nCritical : %d\n",critical);
        return;
    }
    else
    {
        //Here we will bring the desired color edge att he bottom-front edge and we are not going to disturb the top-front edge becuase that is where the edge will be getting solved.
        if(test) printf("Checking for (Red-White) edge\n");
        //Check for the (Red-White) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[0][0][i] == top_color && cube[2][n-1-i][n-1] == front_color) || (cube[0][0][i] == front_color && cube[2][n-1-i][n-1] == top_color))
            {
                rot('l',0,2);
                rot('b',0,1);
                
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }

        if(test) printf("Checking for (Green-Red) edge\n");
        //Check for the (Green-Red) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[2][0][i] == top_color && cube[5][0][n-1-i] == front_color) || (cube[2][0][i] == front_color && cube[5][0][n-1-i] == top_color))
            {
                rot('l',0,1);//Rotate the left layer up
                rot('b',0,1);//Rotate the bottom layer to right
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }

        if(test) printf("Checking for (Yellow-Red) edge\n");
        //Check for the (Yellow-Red) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[2][i][0] == top_color && cube[4][0][i] == front_color) || (cube[2][i][0] == front_color && cube[4][0][i] == top_color))
            {
                rot('b',0,1);//Rotate the bottom layer to right
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }

        if(test) printf("Checking for (Blue-Yellow) edge\n");
        //Check for the (Blue-Yellow) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[1][i][0] == top_color && cube[4][i][n-1] == front_color) || (cube[1][i][0] == front_color && cube[4][i][n-1] == top_color))
            {
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
        
        if(test) printf("Checking for (White-Green) edge\n");
        //Check for the (White-Green) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[0][i][n-1] == top_color && cube[5][i][0] == front_color) || (cube[0][i][n-1] == front_color && cube[5][i][0] == top_color))
            {
                rot('f',n-1,2);//rotate the back face twice
                rot('b',0,2);//Rotate the bottom face twice
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
        
        if(test) printf("Checking for (White-Orange) edge\n");
        //Check for the (White-Ornage) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[0][n-1][i] == top_color && cube[3][i][n-1] == front_color) || (cube[0][n-1][i] == front_color && cube[3][i][n-1] == top_color))
            {
                rot('l',n-1,2);//Rotate the right layer twice
                rot('b',0,3);//Rotate the bottom layer left
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
        
        if(test) printf("Checking for (Blue-Red) edge\n");
        //Check for the (Blue-Red) edge
        for (int i=1; i<n-1;i++)
        {
            if((cube[1][0][i] == front_color && cube[2][n-1][i] == top_color) || (cube[1][0][i] == top_color && cube[2][n-1][i] == front_color))
            {
                rot('l',0,3);//Rotate the left layer down
                rot('b',0,1);//Rotate the bottom layer to right
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
        
        if(test) printf("Checking for (Ornage-Blue) edge\n");
        //Check for the (ornage-blue) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[3][0][i] == top_color && cube[1][n-1][i] == front_color) || (cube[3][0][i] == front_color && cube[1][n-1][i] == top_color))
            {
                rot('l',n-1,3);//Rotate the right layer down
                rot('b',0,3);//Rotate the bottom layer left
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
        
        if(test) printf("Checking for (Orange-Yellow) edge\n");
        //Check for the (orange-yellow) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[3][i][0] == front_color && cube[4][n-1][n-1-i] == top_color) || (cube[3][i][0] == top_color && cube[4][n-1][n-1-i] == front_color))
            {
                rot('b',0,3);//Rotate the bottom layer to left
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
        
        if(test) printf("Checking for (Orange-Green) edge\n");
        //Check for the (orange-green) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[3][n-1][i] == top_color && cube[5][n-1][n-1-i] == front_color) || (cube[3][n-1][i] == front_color && cube[5][n-1][n-1-i] == top_color))
            {
                rot('l',n-1,1);//Rotate the right layer up
                rot('b',0,3);//Rotate the bottom layer left
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return; 
            }
        }
        
        if(test) printf("Checking for (Yellow-Green) edge\n");
        //Check for the (Yellow-Green) edge
        for(int i=1;i<n-1;i++)
        {
            if((cube[4][i][0] == top_color && cube[5][i][n-1] == front_color) || (cube[4][i][0] == front_color && cube[5][i][n-1] == top_color))
            {
                rot('b',0,2);//Rotate the bottom layer twice
                pair(top_color,front_color);
                solve_edge(top_color,front_color);
                return;
            }
        }
    }
    if(test) printf("Solve_Edge_Function_Failed\n");
    return;
}

/*
After a successful attempt to make the centers of cube, now is the time to get to the edges of cube.
after completing the centers successfully, i am going to make the edges now. Starting position is facing the blue center, with white at the top
Here is the nomenclature of edges that i will be using:
*/
//It doesnt check for Blue-Yellow edge. And thus it will remain undistrubed.

void bring_unsolved_top()
{
    if(test) printf("Into bring_unsolved_top...\n");
    //Check if (White-Blue) edge is unsolved
    if (is_edge_solved(1,2) == 0)
    {
       return; 
    }

    //Check if (Blue-Red) edge is unsloved
    else if(is_edge_solved(2,3) == 0)
    {
        rot('l',0,1);//Rotate the left layer up
        rot('b',n-1,1);//Rotate top layer right
    }

    //Check if the (Red-White) edge is unsolved
    else if(is_edge_solved(3,1) == 0)
    {
        rot('b',n-1,1);//Rotate top layer right
    }

    //Check if the (Red-Green) edge is unsolved
    else if(is_edge_solved(3,5) == 0)
    {
        rot('l',0,3);//Rotate the left layer down
        rot('b',n-1,1);//Rotate the top layer right
    }

    //Check if the (Red-Yellow) edge is unsolved
    else if(is_edge_solved(3,6) == 0)
    {
        rot('l',0,2);//Rotate left layer twice
        rot('b',n-1,1);//roate the top layer right
    }

    //Check if the (Ornage-Blue) edge is unsolved
    else if(is_edge_solved(4,2) == 0)
    {
        rot('l',n-1,1);//Rotate the right layer up
        rot('b',n-1,3);//Rotate top layer left
    }

    //Check if the (Ornage-White) edge is unsolved
    else if(is_edge_solved(4,1) == 0)
    {
        rot('b',n-1,3);//Rotate top layer left
    }
            
    //Check if the (Ornage-Green) edge is unsolved
    else if(is_edge_solved(4,5) == 0)
    {
        rot('l',n-1,3);//Rotate the right layer down
        rot('b',n-1,3);//Rotate top layer left
    }
            
    //Check if the (Orange-Yellow) edge is unsolved
    else if(is_edge_solved(4,6) == 0)
    {
        rot('l',n-1,2);//Rotate right layer twice
        rot('b',n-1,3);//Rotate top layer left
    }

    //Check if the (White-Green) edge is unsolved
    else if(is_edge_solved(1,5) == 0)
    {
        rot('b',n-1,2);//Rotate top layer twice
    }

    //Check if the (Green-Yellow) edge is unsolved
    else if(is_edge_solved(5,6) == 0)
    {
        rot('f',n-1,2);//Rotate back face twice
        rot('b',n-1,2);//Rotate top layer twice
    }
    if(test) printf("Now an unsolved should be at the top-front edge\n");
    if(test) display();
    return;
}

//This will take in the integer which is the column number (i) and performs the single edge parity algo on to that column only
void single_edge_parity_algorithm(int i)
{
    rot('l',n-1-i,3);
    rot('b',n-1,2);
    rot('l',i,3);
    rot('f',0,2);
    rot('l',i,1);
    rot('f',0,2);
    rot('l',n-1-i,2);
    rot('b',n-1,2);
    rot('l',n-1-i,1);
    rot('b',n-1,2);
    rot('l',n-1-i,3);
    rot('b',n-1,2);
    rot('f',0,2);
    rot('l',n-1-i,2);
    rot('f',0,2);

}

//this function will solve the single edge parity where the edge itself is present at the front-top edge.
void odd_single_edge_parity()
{
    //This will store the color which is at the front face
    int color1 = cube[1][n/2][n-1];
    int color2 = cube[0][n/2][0];

    for(int i=1;i<n-1;i++)
    {
        //If the rest of the color on the edge is not equal to color 1, then use the parity alogorithm
        if(cube[1][i][n-1] == color2 && cube[0][i][0] == color1)
        {
            if(test) printf("Action...\n");
            single_edge_parity_algorithm(i);
        }
    }
}

//So the problem I am facing right now wiht odd function cubes is that after the solve_egde function is called, the edge is solved, but in case of odd cube, the center edge may be the one which is not flipped. So, this could be done by the safe solve function given below
void safe_solve(){
    if(test) printf("You are into safe function, because of the odd cube edge problem.\n");
    //right down
    for(int i=n/2+1;i<n-1;i++){
        rot('l',i,3);//Rotate half of the left layers down.
    }
    //top twice
    rot('b',n-1,2);//Rotate the top layer twice
    //left down
    for(int i=1;i<n/2;i++){
        rot('l',i,3);//Rotate all the left layer down
    }
    //front twice
    rot('f',0,2);//Rotate the front layer twice
    //left up
    for(int i=1;i<n/2;i++){
        rot('l',i,1);//Rotate all the left layer down
    }
    //front twice
    rot('f',0,2);//Rotate the front layer
    //right twice
    for(int i=n/2+1;i<n-1;i++){
        rot('l',i,2);//Rotate half of the left layers down.
    }
    //top twice
    rot('b',n-1,2);//Rotate the top layer twice
    //right up
    for(int i=n/2+1;i<n-1;i++){
        rot('l',i,1);//Rotate half of the left layers down.
    }
    //top twice
    rot('b',n-1,2);//Rotate the top layer twice
    //right down
    for(int i=n/2+1;i<n-1;i++){
        rot('l',i,3);//Rotate half of the left layers down.
    }
    //top twice
    rot('b',n-1,2);//Rotate the top layer 
    //front twice
    rot('f',0,2);//Rotate the front layer
    //right twice
    for(int i=n/2+1;i<n-1;i++){
        rot('l',i,2);//Rotate half of the left layers down.
    }
    //front twice
    rot('f',0,2);//Rotate the front layer
    return;
}


//So one quick remedy that I get after this is to check if all the edges are solved each time I do something.
//(isEdgeSolved(1,2) && isEdgeSolved(1,3)) return; will be the result of this quick remedy. I am to old to comb through all the code again

/*
This will solve the two edge pairing parity problem. 
*/
void edge_solve_parity()
{
    for(int t=0;t<2;t++)
    {
        //First bring the unsolved edge to the (Blue-White) edge.
        bring_unsolved_top();
        if(test) printf("Into edge_solve_parity...\n");
        turn('f',2);
        bring_unsolved_top();
        turn('f',2);

        if(test) printf("Now there should be two unsolved edges at (1,2) and (2,5) edge position\n");
    
        if(test) display();

        //Now we will see which of the edge peices needs to be transfered to the other edge.
        //n/2 is taken to get rid of the confusion of odd rubiks cube.
        int color1 = cube[1][n/2][n-1];   //Facing Blue
        int color2 = cube[0][n/2][0];     //Facing white
        for(int k=1;k<n-1;k++)
        {
            if(!(cube[1][k][n-1] == color1 && cube[0][k][0] == color2))
            {
                //If the edge peice is in the right postion but wrong orientation and the same is in the (n-1-k) side
                if(cube[1][k][n-1] == color2 && cube[0][k][0] == color1 && cube[1][n-1-k][n-1] == color2 && cube[0][n-1-k][0] == color1)
                {
                    rot('l',n-1-k,3);
                    rot('b',n-1,2);
                    rot('l',k,3);
                    rot('f',0,2);
                    rot('l',k,1);
                    rot('f',0,2);
                    rot('l',n-1-k,2);
                    rot('b',n-1,2);
                    rot('l',n-k-1,1);
                    rot('b',n-1,2);
                    rot('l',n-k-1,3);
                    rot('b',n-1,2);
                    rot('f',0,2);
                    rot('l',n-k-1,2);
                    rot('f',0,2);

                }
                //If the edge peice is in the rigth psition but wrong orientation
                else if(cube[1][k][n-1] == color2 && cube[0][k][0] == color1)
                {
                    if(!(cube[1][k][0] == color1 && cube[4][k][n-1] == color2) || (cube[1][k][0] == color2 && cube[4][k][n-1] == color1))
                    {
                        rot('b',0,1);
                        rot('f',0,1);
                        rot('l',n-1,1);
                        rot('f',0,3);
                    }

                    rot('l',k,1);
                    rot('b',n-1,3);
                    rot('l',0,1);
                    rot('b',n-1,1);
                    rot('f',0,1);
                    rot('l',0,2);
                    rot('f',0,3);
                    rot('l',k,3);
                }
                //If the edge peice needs to be transfered to the other edge.
                else
                {
                    if((cube[1][k][0] == color1 && cube[4][k][n-1] == color2) || (cube[1][k][0] == color2 && cube[4][k][n-1] == color1))
                    {
                        rot('b',0,1);
                        rot('f',0,1);
                        rot('l',n-1,1);
                        rot('f',0,3);
                    }

                    turn('f',2);
                    rot('l',n-1-k,1);
                    rot('b',n-1,3);
                    rot('l',0,1);
                    rot('b',n-1,1);
                    rot('f',0,1);
                    rot('l',0,2);
                    rot('f',0,3);
                    rot('l',n-1-k,3);
                    turn('f',2);
                }
            }
        }
        if(test) printf("I dont know what it does. See it yourself\n");
        if(test) display();
        bring_unsolved_top();
        //printf("So now the unsolved edge is brought to the top\n");
        if(is_edge_solved(1,2)){
            if(test) printf("But if you still don't see the unsolved edge then here we go\n");
            turn('f',2);
        }
        if(test) display();
        if(test) printf("And now the unsolved edge is to be made right with safe function");
        if(n%2!=0 && !is_edge_solved(1,2)){
            safe_solve();
        }
        //If the cube is solved then 
        if(is_edge_solved(1,2) && is_edge_solved(1,3)) return;

        //Now we might still have the edge swapping in the front bottom edge.
        turn('l',1);//Turn the cube to downside, so that the unsolved edge is at front-top edge

        int color3 = cube[1][n/2][n-1];
        for(int k=1;k<n/2;k++)
        {
            if(cube[1][k][n-1] != color3)
            {
                rot('l',n-1-k,3);
                rot('b',n-1,2);
                rot('l',k,3);
                rot('f',0,2);
                rot('l',k,1);
                rot('f',0,2);
                rot('l',n-1-k,2);
                rot('b',n-1,2);
                rot('l',n-k-1,1);
                rot('b',n-1,2);
                rot('l',n-k-1,3);
                rot('b',n-1,2);
                rot('f',0,2);
                rot('l',n-k-1,2);
                rot('f',0,2);

            }
        }
        
 
        turn('l',3);

        if(test) printf("\nEdge solved!\n");

        if(test) printf("Remainder of n divided by 2 is %d\n",n%2);
        //This segement is for odd numbered Rubik's cube.
        //There will be one parity of the middle edge peice, that needs to be solved.
        if(test) display();
        if(n % 2 != 0)
        {
        
            //If the cenetr edge peices of both the (front-top) and (front-bottom) egdes are in worng orientation
            if(cube[1][n/2][n-1] == cube[0][1][0] && cube[0][n/2][n-1] == cube[1][1][n-1])
            {
                rot('l',n/2,1);
                rot('b',n-1,3);
                rot('l',0,1);
                rot('b',n-1,1);
                rot('f',0,1);
                rot('l',0,2);
                rot('f',0,3);
                rot('l',n/2,3);
            }

            //If the centers have switched their location
            else
            {
                for(int i=(n/2)+1;i<n-1;i++){rot('l',i,1);}
                rot('b',n-1,3);
                rot('l',0,1);
                rot('b',n-1,1);
                rot('f',0,1);
                rot('l',0,2);
                rot('f',0,3);
                for(int i=(n/2)+1;i<n-1;i++){rot('l',i,3);}
                if(test) printf("Break1\n");
                if(test) display();

                for(int i=1;i<(n/2);i++){rot('l',i,1);}
                rot('b',n-1,3);
                rot('l',0,1);
                rot('b',n-1,1);
                rot('f',0,1);
                rot('l',0,2);
                rot('f',0,3);
                for(int i=1;i<(n/2);i++){rot('l',i,3);}
                if(test) printf("break2\n");
                if(test) display();
            }

        //there is this problem which is occcuring in every odd numbered cube. And that is of this (front-bottom) edge not being solved.
        //There always exist this single edge parity thta needs to be solved
        }
        bring_unsolved_top();
        if(n%2!=0 && !is_edge_solved(1,2)){
            safe_solve();
        }
        //We will first check if the edge (blue-yellow) is solved
        if(!is_edge_solved(2,6))
        {
            //bring that unsolved edge to the front-top edge
            rot('f',0,2);
            //Then we solve the single edge parity
            odd_single_edge_parity();
            bring_unsolved_top();
            if(n%2!=0 && !is_edge_solved(1,2)){
                safe_solve();
            }
        }


        if(test) printf("Completed the middle edge parity (odd)\n");
        return;
    }
    
    return;
}

//This function will count the no of unsolved edges.
int count_unsolved_edge()
{
    if(test) printf("Into the count function\n");
    int count = 0;
    if(is_edge_solved(1,2) == 0)count++;//White-Blue
    if(is_edge_solved(1,3) == 0)count++;//White-Red
    if(is_edge_solved(1,5) == 0)count++;//White-Green
    if(is_edge_solved(1,4) == 0)count++;//White-Orange
    if(is_edge_solved(2,3) == 0)count++;//Blue-Red
    if(is_edge_solved(2,6) == 0)count++;//Blue-Yellow
    if(is_edge_solved(2,4) == 0)count++;//Blue-Orange
    if(is_edge_solved(4,6) == 0)count++;//Orange-yellow
    if(is_edge_solved(4,5) == 0)count++;//Orange-Green
    if(is_edge_solved(3,5) == 0)count++;//Red-Green
    if(is_edge_solved(3,6) == 0)count++;//Red-Yellow
    if(is_edge_solved(5,6) == 0)count++;//Green-Yellow
    if(test) printf("Count = %d\n",count);
    return count;

}


/*
I have finally decoded the rerquirement of executing the below chuncks of code. So each of then to work properly,
we would need to have atleat two unsolved edges in the entire cube. And there for now i am making a function called count_unsolved
that will just return the no of unsolved egdes nad will return that number. Now there are minimum of 3 unsolved edges required for
algorithm of solve ddge to work(which also include the edge to eb solved). But if it falls below 3, then the code must go intoparity and then return.
*/
void edges()
{
    /*There are 12 edges in a rubiks cube, and in order to get a parity there should be exactly two edges that are unsolved, so i will need to solve atmost 10 edges to get the parity, therefore the value of k goes from 0 to 9. Here for eack k one of the dge is getting solved.*/
    /*But it can so  */
    while(count_unsolved_edge()>=3){
        for(int k=0;k<10;k++)
        {
            //Critical is a global variable.
            critical = 0;
            
            bring_unsolved_top();   //This bring an unsolved edge to the edge (1,2)

            if(test) printf("Now you should have an unsolved edge at edge (1,2)\n");
            if(test) display();              
            
            if(count_unsolved_edge()>=3)
            {
                if(k==0)
                {
                    solve_edge(1,3);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\033[1;31mThis should complete the white red edge.\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }
                
                else if(k==1)
                {
                    solve_edge(1,2);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (White-Blue) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==2)
                {
                    solve_edge(1,5);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (White-Green) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==3)
                {
                    solve_edge(1,4);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (White-Orange) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==4)
                {
                    solve_edge(2,3);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (Blue-Red) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==5)
                {
                    solve_edge(6,3);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (Yellow-Red) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==6)
                {
                    solve_edge(5,3);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (Green-Red) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==7)
                {
                    solve_edge(2,4);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (Blue-Orange) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==8)
                {
                    solve_edge(6,5);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (Yellow-Green) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                else if(k==9)
                {
                    solve_edge(6,4);
                    if(n%2!=0 && !is_edge_solved(1,2)) safe_solve();
                    if(test) printf("\n\033[1;31mCompleted the (Yellow-Orange) edge\033[0m\n");
                    if(test) printf("Critical = %d\n",critical);
                    if(test) printf("Count of unsolved edge = %d\n\n",count_unsolved_edge());
                }

                if(test) printf("For the value of k = %d\nThis is the cube: \n",k);
                if(test) display();
            }
        }       
    }
    if(test) printf("Count_unsolved_edge = %d\n",count_unsolved_edge());
    if(test) display();
    if(test) printf("\nParity ahead!\n");
    edge_solve_parity();
    return;
}


                                                        /* (3 X 3 X 3) REDUCTION */
/***************************************************     3*3*3 RUBIKS CUBE REDUCTION         ****************************************/

/*
Now that the cube has successfully reduced to 3 by 3 rubik's cube, we could try using our previous algorithm for 3*3.
here i will be considering the foloowing peices
*/

//Center positioning
void positionCenters(){
    //First bring the white to top
    if(cube[1][n/2][n/2] == 1) turn('l',1); //Turn the cube up
    else if(cube[2][n/2][n/2] == 1) turn('f',3); //Turn the cube anticlockwise
    else if(cube[3][n/2][n/2] == 1) turn('f',1); //Turn the cube clockwise
    else if(cube[4][n/2][n/2] == 1) turn('l',2); //Turn the cube twice
    else if(cube[5][n/2][n/2] == 1) turn('l',3); //Turn the cube down

    //Now we can position the blue center
    if(cube[2][n/2][n/2] == 2) turn('b',1); //Turn the cube right
    else if(cube[3][n/2][n/2] == 2) turn('b',3);//Turn the cube left
    else if(cube[4][n/2][n/2] == 2) turn('b',2);;//Turn the cube twice

    //printf("\nNow the centers has to be at the right position\n");
    return;
}


/*****************************************************          WHITE PLUS          ******************************************** */
void white_plus()
{
    if(test) printf("Before entering into white_pluss function\n");
    
    for(int i=0;i<8;i++)
    {
        if(test) display();
        if(test) printf("Inside the for loop\n");
        //If the topmid color of the center matrix is white
        if(cube[1][n/2][n-1] == 1)
        {
            if(test) printf("1\n");
            //if the color above the edge peice of the white is blue
            if(cube[0][n/2][0] == cube[1][n/2][n/2])
            {
                rot('f',0,1);
                rot('b',n-1,3);
                rot('l',0,1);
                rot('b',n-1,1);
            }
            //if the color above the edge peice of the white is red
            else if(cube[0][n/2][0] == cube[2][n/2][n/2])
            {
                rot('f',0,1);
                rot('l',0,1);
            }
            //if the color above the edge peice of the white is green
            else if(cube[0][n/2][0] == cube[5][n/2][n/2])
            {
                rot('f',0,1);
                rot('b',n-1,1);
                rot('l',0,1);
                rot('b',n-1,3);
            }
            //if the color above the edge peice of the white is orange
            else if(cube[0][n/2][0] == cube[3][n/2][n/2])
            {
                rot('f',0,3);
                rot('l',n-1,1);
            }   
        }

        //If the leftmid color of the center face is white
        if(cube[1][0][n/2] == 1)
        {
            if(test) printf("2\n");
            //the color left of the white is blue
            if(cube[2][n-1][n/2] == cube[1][n/2][n/2])
            {
                rot('b',n-1,3);
                rot('l',0,1);
                rot('b',n-1,1);
            }
            //the color at the left of white is red
            else if(cube[2][n-1][n/2] == cube[2][n/2][n/2])
            {
                rot('l',0,1);
            }
            //the color at the left of white is orange
            else if(cube[2][n-1][n/2] == cube[3][n/2][n/2])
            {
                rot('f',0,2);
                rot('l',n-1,1);
                rot('f',0,2);
            }
            //the color at the left of white is green
            else if(cube[2][n-1][n/2] == cube[5][n/2][n/2])
            {
                rot('b',n-1,1);
                rot('l',0,1);
                rot('b',n-1,3);
            }
        }
    
        //if the right mid color of the center face is white
        if(cube[1][n-1][n/2] == 1)
        {
            if(test) printf("3\n");
            // if the color to the right of white in the edge peice is blue
            if(cube[3][0][n/2] == cube[1][n/2][n/2])
            {
                rot('b',n-1,1);
                rot('l',n-1,1);
                rot('b',n-1,3);
            }
            // if the color to the right of white in the edge peice is green
            else if(cube[3][0][n/2] == cube[5][n/2][n/2])
            {
                rot('b',n-1,3);
                rot('l',n-1,1);
                rot('b',n-1,1);
            }
            // if the color to the right of white in the edge peice is red
            else if(cube[3][0][n/2] == cube[2][n/2][n/2])
            {
                rot('b',n-1,2);
                rot('l',n-1,1);
                rot('b',n-1,2);
            }
            // if the color to the right of white in the edge peice is orange
            else if(cube[3][0][n/2] == cube[3][n/2][n/2])
            {
                rot('l',n-1,1);
            }
        }
        
        //if the mid bottom color of the center matrix is white
        if(cube[1][n/2][0] == 1)
        {
            if(test) printf("4\n");
            //if the color at the bottom of white in the edge peice is blue
            if(cube[4][n/2][n-1] == cube[1][n/2][n/2])
            {
                rot('b',0,3);
                rot('l',0,1);
                rot('f',0,3);
                rot('l',0,3);
            }
            // if the color to the bottom of white in the edge peice is green
            else if(cube[4][n/2][n-1] == cube[5][n/2][n/2])
            {
                rot('b',0,1);
                rot('l',n-1,3);
                rot('f',n-1,1);
                rot('l',n-1,1);
            }
            //if the color at the bottom of white in the edge peice is red
            else if(cube[4][n/2][n-1] == cube[2][n/2][n/2])
            {
                rot('f',0,3);
                rot('l',0,1);
                rot('f',0,1);
            }
            //if the color at the bottom of white in the edge peice is orange
            else if(cube[4][n/2][n-1] == cube[3][n/2][n/2])
            {
                rot('f',0,1);
                rot('l',n-1,1);
                rot('f',0,3);
            }
        }
    
        //if the the topmid element of bottom matrix is white
        if(cube[4][n/2][n-1] == 1)
        {
            if(test) printf("5\n");
            //if the bottom mid color of the front face is blue
            if(cube[1][n/2][0] == cube[1][n/2][n/2])
            {
                rot('f',0,2);
            }
            //if the bottom mid color of the front face is green
            else if(cube[1][n/2][0] == cube[5][n/2][n/2])
            {
                rot('b',0,2);
                rot('f',n-1,2);
            }
            //if the bottom mid color of the front face is red
            else if(cube[1][n/2][0] == cube[2][n/2][n/2])
            {
                rot('b',0,3);
                rot('l',0,2);
            }
            //if the bottom mid color of the front face is orange
            else if(cube[1][n/2][0] == cube[3][n/2][n/2])
            {
                rot('b',0,1);
                rot('l',n-1,2);
            }
        }
    
        //if the white color matches at the top
        if(cube[0][n/2][0] == 1)
        {
            if(test) printf("6\n");
            //if the color below the edge peice, or the one which is facing the solver is red
            if(cube[1][n/2][n-1] == cube[2][n/2][n/2])
            {
                rot('f',0,1);
                rot('b',n-1,1);
                rot('f',0,3);
                rot('b',n-1,3);
            }
            //if the color below the edge peice, or the one which is facing the solver is green
            else if(cube[1][n/2][n-1] == cube[5][n/2][n/2])
            {
                rot('f',0,1);
                rot('b',n-1,2);
                rot('f',0,3);
                rot('b',n-1,2);
            }
            //if the color below the edge peice, or the one which is facing the solver is orange
            else if(cube[1][n/2][n-1] == cube[3][n/2][n/2])
            {
                rot('f',0,1);
                rot('b',n-1,3);
                rot('f',0,3);
                rot('b',n-1,1);
            }
        }
        
        if(test) printf("For one iteration\n");
        if(test) display();
        turn('b',1);
    }

    if(test) printf("\nDONE WITH FIRST PLUS\n");
    return;
}

/*****************************************************          FIRST LAYER         ******************************************** */
//Now we make the first layer
void first_layer()
{
    for(int k=0;k<8;k++)
    {
        //if the color at the top right of ceter matrix is white
        if(cube[1][n-1][n-1] == 1)
        {
            //when there is a blue at top of white
            if(cube[0][n-1][0] == cube[1][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('b',0,2);
                rot('f',0,1);
                rot('b',0,1);
                rot('f',0,3);
            }
            //when there is a red at top of white
            else if(cube[0][n-1][0] == cube[2][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('b',0,1);
                rot('l',0,1);
                rot('b',0,1);
                rot('l',0,3);
            }
            //when there is orange at the top
            else if(cube[0][n-1][0] == cube[3][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('b',0,3);
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
            }
            //when there is green at the top
            else if(cube[0][n-1][0] == cube[5][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('f',n-1,3);
                rot('b',0,1);
                rot('f',n-1,1);
            }
        }
        //if the color at the top left of center matrix is white
        if(cube[1][0][n-1] == 1)
        {
            //if the color at top of white is green
            if(cube[0][0][0] == cube[5][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('f',n-1,1);
                rot('b',0,3);
                rot('f',n-1,3);
            }
            //if the color at the top of white is blue
            else if(cube[0][0][0] == cube[1][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('b',0,2);
                rot('f',0,3);
                rot('b',0,3);
                rot('f',0,1);
            }
            //if the color at the top is red
            else if(cube[0][0][0] == cube[2][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('b',0,1);
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
            }
            //if the color at the top is orange
            else if(cube[0][0][0] == cube[3][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('l',n-1,1);
                rot('b',0,2);
                rot('l',n-1,3);

            }
        }
        //if the color at the bottom left of center matrix in white
        if(cube[1][0][0] == 1)
        {
            //if the color at the bottom of white is orange
            if(cube[4][0][n-1] == cube[3][n/2][n/2])
            {
                rot('b',0,2);
                rot('f',0,3);
                rot('b',0,3);
                rot('f',0,1);
            }
            //if the color at the bottom of white is blue
            else if(cube[4][0][n-1] == cube[1][n/2][n/2])
            {
                rot('b',0,1);
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
            }
            //if the bottom of white is red
            else if(cube[4][0][n-1] == cube[2][n/2][n/2])
            {
                rot('f',n-1,1);
                rot('b',0,3);
                rot('f',n-1,3);
            }
            //if the color at bottom of white is green
            else if(cube[4][0][n-1] == cube[5][n/2][n/2])
            {
                rot('l',n-1,1);
                rot('b',0,2);
                rot('l',n-1,3);

            }
        }
        //if the color at the bottom right of center matrix is white
        if(cube[1][n-1][0] == 1)
        {
            //if the color at the bottom of white is red
            if(cube[4][n-1][n-1] == cube[2][n/2][n/2])
            {
                rot('b',0,2);
                rot('f',0,1);
                rot('b',0,1);
                rot('f',0,3);

            }
            //if the color at the bottom is blue
            else if(cube[4][n-1][n-1] == cube[1][n/2][n/2])
            {
                rot('b',0,3);
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
            }
            //if the color at bottom of white is green
            else if(cube[4][n-1][n-1] == cube[5][n/2][n/2])
            {
                rot('l',0,1);
                rot('b',0,2);
                rot('l',0,3);
            }
            //if the color at the bottom of white is orange
            else if(cube[4][n-1][n-1] == cube[3][n/2][n/2])
            {
                rot('f',n-1,3);
                rot('b',0,1);
                rot('f',n-1,1);
            }
        }
        //if the color at the top right of bottom matrix is white
        if(cube[4][n-1][n-1] == 1)
        {
            //if the color above the white is orange
            if(cube[1][n-1][0] == cube[3][n/2][n/2])
            {
                rot('b',0,3);
                rot('l',n-1,3);
                rot('b',0,2);
                rot('l',n-1,1);
                rot('b',0,3);
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
            }
            //if the color at the top of white is green
            else if(cube[1][n-1][0] == cube[5][n/2][n/2])
            {
                rot('f',n-1,3);
                rot('b',0,2);
                rot('f',n-1,1);
                rot('b',0,3);
                rot('f',n-1,3);
                rot('b',0,1);
                rot('f',n-1,1);
            }
            //if the color at the top of white is blue
            else if(cube[1][n-1][0] == cube[1][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,2);
                rot('l',0,1);
                rot('b',0,1);
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);

            }
            //if the color at the top of white is red
            else if(cube[1][n-1][0] == cube[2][n/2][n/2])
            {
                rot('f',n-1,1);
                rot('b',0,1);
                rot('f',n-1,3);
                rot('b',0,1);
                rot('f',n-1,1);
                rot('b',0,3);
                rot('f',n-1,3);
            }
        }
        //if the color at the top left of bottom matrix is white
        if(cube[4][0][n-1] == 1)
        {
            //if the color above white is red
            if(cube[1][0][0] == cube[2][n/2][n/2])
            {
                rot('b',0,1);
                rot('l',0,3);
                rot('b',0,2);
                rot('l',0,1);
                rot('b',0,1);
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
            }
            //if the color above white is blue
            else if(cube[1][0][0] == cube[1][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,2);
                rot('l',n-1,1);
                rot('b',0,3);
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
            }
            //if the color above white is orange
            else if(cube[1][0][0] == cube[3][n/2][n/2])
            {
                rot('f',n-1,3);
                rot('b',0,3);
                rot('f',n-1,1);

                rot('b',0,3);

                rot('f',n-1,3);
                rot('b',0,1);
                rot('f',n-1,1);
            }
            //if the color above white is green
            else if(cube[1][0][0] == cube[5][n/2][n/2])
            {
                rot('f',n-1,1);
                rot('b',0,2);
                rot('f',n-1,3);
                rot('b',0,1);
                rot('f',n-1,1);
                rot('b',0,3);
                rot('f',n-1,3);
            }
        }
        //if the color at the bottom left of top matix is white
        if(cube[0][0][0] == 1)
        {
            //If the color at the top left of front matrix is orange
            if(cube[1][0][n-1] == cube[3][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);

            }
            //If the color at the top left of front matrix is red
            else if(cube[1][0][n-1] == cube[2][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('b',0,2);
                rot('l',0,1);
                rot('b',0,1);
                rot('l',0,3);

            }
            //If the color at the top left of front matrix is green
            else if(cube[1][0][n-1] == cube[5][n/2][n/2])
            {
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
                rot('f',n-1,3);
                rot('b',0,2);
                rot('f',n-1,1);
            }
            //If the color at the top left of front matrix is blue then no problem
            

        }
        //If the color at the bottom right of the top matrix is white
        if(cube[0][n-1][0] == 1)
        {
            //If the color at the top right of front matrix is orange
            if(cube[1][n-1][n-1] == cube[3][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('b',0,2);
                rot('l',n-1,1);
                rot('b',0,3);
                rot('l',n-1,3);
            }
            //If the color at the top right of front matrix is red
            else if(cube[1][n-1][n-1] == cube[2][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('l',0,3);
                rot('b',0,3);
                rot('l',0,1);
            }
            //If the color at the top right of front matrix is green
            else if(cube[1][n-1][n-1] == cube[5][n/2][n/2])
            {
                rot('l',n-1,3);
                rot('b',0,1);
                rot('l',n-1,1);
                rot('f',n-1,1);
                rot('b',0,2);
                rot('f',n-1,3);

            }
            //If the color at the top right of front matrix is blue no problem
        }
        turn('b',1);
    }
    if(test) printf("First Layer complete\n");
    return;
}


/*****************************************************          SECOND LAYER         ******************************************** */
//Now we are making the second layer
void second_layer_left()
{
    rot('b',0,1);
    rot('l',0,3);
    rot('b',0,3);
    rot('l',0,1);
    rot('b',0,3);
    rot('f',0,1);
    rot('b',0,1);
    rot('f',0,3);
}
void second_layer_right()
{
    rot('b',0,3);
    rot('l',n-1,3);
    rot('b',0,1);
    rot('l',n-1,1);
    rot('b',0,1);
    rot('f',0,3);
    rot('b',0,3);
    rot('f',0,1);
}
void second_layer()
{
    if(test) printf("Welcome to second layer function...\n");
    if(test) printf("before entering the loop: \n");
    if(test) display();
    for(int t=0;t<8;t++)
    {
        if(test) printf("Iteration\n");
        //if the left mid of center face is blue and to its left its orange
        if(cube[1][0][n/2] == cube[1][n/2][n/2] && cube[2][n-1][n/2] == cube[3][n/2][n/2])
        {
            if(test) printf("if the left mid of center face is blue and left to it is orange\n");
            second_layer_left();
            turn('b',3);
            rot('b',0,3);
            second_layer_left();
            turn('b',1);
            if(test) display();
        }
        //if the color at the right mid is blue and to its right its red
        if(cube[1][n-1][n/2] == cube[1][n/2][n/2] && cube[3][0][n/2] == cube[2][n/2][n/2])
        {
            if(test) printf("if the color at the right mid is blue and right to it is red\n");
            second_layer_right();
            turn('b',1);
            rot('b',0,1);
            second_layer_right();
            turn('b',3);
            if(test) display();
        }
        //if the color to the left of left mid is blue
        if(cube[2][n-1][n/2] == cube[1][n/2][n/2])
        {
            if(test) printf("if the color to the left of left mid is blue\n");
            second_layer_left();
            rot('b',0,2);
            if(test) display();
            if(cube[4][n/2][n-1] == cube[2][n/2][n/2])
            {
                if(test) printf("now if the color with blue is red\n");
                second_layer_left();
            }
            else if(cube[4][n/2][n-1] == cube[3][n/2][n/2])
            {
                if(test) printf("Now if the color with blue is ornage\n");
                second_layer_right();
            }
            if(test) display();
        }
        //if the color to the right of right mid is blue
        if(cube[3][0][n/2] == cube[1][n/2][n/2])
        {
            if(test) printf("if the color to the right of right mid is blue\n");
            second_layer_right();
            rot('b',0,2);
            if(cube[4][n/2][n-1] == cube[2][n/2][n/2])
            {
                second_layer_left();
            }
            else if(cube[4][n/2][n-1] == cube[3][n/2][n/2])
            {
                second_layer_right();
            }
            if(test) display();
        }
        //loop for the color at the bottom mid
        for(int i=0;i<5;i++)
        {
            if(test) printf("Sub_iteration\n");
            //If blue is at the bottom mid matrix of front face
            if(cube[1][n/2][0] == cube[1][n/2][n/2])
            {
                //If the bottom of blue is red
                if(cube[4][n/2][n-1] == cube[2][n/2][n/2])
                {
                    second_layer_left();
                }
                //If the bottom of blue is orange
                else if(cube[4][n/2][n-1] == cube[3][n/2][n/2])
                {
                    second_layer_right();
                }
            }
            rot('b',0,1);
            if(test) printf("After one sub-iteration...\n");
            if(test) display();
        }
        turn('b',1);
        if(test) printf("After one iteration...\n");
        if(test) display();
    }
    if(test) printf("Second Layer Complete\n");
    return;
}


/****************************************************           YELLOW PLUS          ********************************************* */
//This function will solve the single edge parity problem. One thing to note is brign that edge to the top-front edge
void one_edge_parity_problem()
{
    // printf("Entered into parity\n");
    // display();
    for(int i=(n/2);i<n-1;i++) {rot('l',i,3);}
    rot('b',n-1,2);
    for(int i=1;i<n/2;i++) {rot('l',i,3);}
    rot('f',0,2);
    for(int i=1;i<n/2;i++) {rot('l',i,1);}
    rot('f',0,2);
    for(int i=(n/2);i<n-1;i++) {rot('l',i,2);}
    rot('b',n-1,2);
    for(int i=(n/2);i<n-1;i++) {rot('l',i,1);}
    rot('b',n-1,2);
    for(int i=(n/2);i<n-1;i++) {rot('l',i,3);}
    rot('b',n-1,2);
    rot('f',0,2);
    for(int i=(n/2);i<n-1;i++) {rot('l',i,2);}
    rot('f',0,2);
    // display();
}
//This function will have the agorithm to solve the I pattern
void I_to_plus()
{
    rot('f',0,3);
    rot('l',n-1,1);
    rot('b',n-1,3);
    rot('l',n-1,3);
    rot('b',n-1,1);
    rot('f',0,1);
}
void L_to_plus()
{
    rot('f',0,3);
    rot('b',n-1,3);
    rot('l',n-1,1);
    rot('b',n-1,1);
    rot('l',n-1,3);
    rot('f',0,1);

}
//Now after making the second layer we can move on to make the yellow plus. Now here are some chances of getting the parity
void yellow_plus()
{
    if(test) printf("Before entering the yellow plus...\n");
    if(test) display();
    //bring yellow face to the top
    turn('f',2);

    //We will first check if there exist parity. For which we will count the no of yellow edge facing downwards. If its even then 
    //there exist no parity. But if the those no of edges are odd, then parity alert
    int count_yellow_edge = 0;
    if(cube[0][n/2][n-1] == 6) count_yellow_edge++;
    if(cube[0][n-1][n/2] == 6) count_yellow_edge++;
    if(cube[0][0][n/2] == 6) count_yellow_edge++;
    if(cube[0][n/2][0] == 6) count_yellow_edge++;

    //Now we will check for parity
    if(test) printf("\nNo of yellow edge at the top = %d\n",count_yellow_edge);
    if(count_yellow_edge%2!=0)
    {
        one_edge_parity_problem();
    }
    if(test) printf("Parity solved\n");
    if(test) display();
    //Now we will solve the plus of yellow
    for(int i=0;i<4;i++)
    {
        //if the color at the top mid of bottom marix is yellow. here is where the formula lies
        if(cube[0][n/2][0] == 6)
        {
            //if the plus is already made
            if(cube[0][n/2][n-1] == 6 && cube[0][0][n/2] == 6) 
            {
                turn('f',2);
                return;
            }
            //there is a correct I formed when the cube is seen from bottom wrt to user
            else if(cube[0][n/2][n-1] == 6)
            {
                rot('b',n-1,1);
                I_to_plus();
                turn('f',2);
                return;
            }
            //If there is a L forming
            else if(cube[0][n-1][n/2] == 6)
            {
                rot('b',n-1,2);
                L_to_plus();
                turn('f',2);
                return;
            }
            else if(cube[0][0][n/2] == 6)
            {
                rot('b',n-1,3);
                L_to_plus();
                turn('f',2);
                return;
            }
        }
        else rot('b',n-1,1);
    }
    //There is no yellow pattern (I or L) forming
    I_to_plus();
    rot('b',n-1,2);
    L_to_plus();

    turn('f',2);
    
    if(test) display();
    return;
}


/***************************************************          COMPLETE PLUS         ***********************************************/
void flip()
{
    rot('b',n-1,1);
    rot('l',0,1);
    rot('b',n-1,1);
    rot('l',0,3);
    rot('b',n-1,1);
    rot('l',0,1);
    rot('b',n-1,2);
    rot('l',0,3);

}
//Now lets make the complete plus 
void complete_yellow_plus()
{
    //We will first turn the cube such that the yellow face, faces to the top
    turn('f',2);
    if(test) display();
    for(int i=0;i<4;i++)
    {
        //if the color does match the center color (blue)
        if(cube[1][n/2][n-1] == cube[1][n/2][n/2])
        {
            //if three colors are solved then its sure that the its done
            if(cube[3][n/2][n-1] == cube[3][n/2][n/2] && cube[2][n/2][n-1] == cube[2][n/2][n/2]) 
            {
                if(test) printf("if three colors are solved them its sure that the its done\n");
                turn('f',2);
                return;
            }
            //if the opposite colors matchs only
            if(cube[5][n/2][0] == cube[5][n/2][n/2])
            {
                if(test) printf("if the opposite colors matchs only\n");
                rot('b',n-1,3);
                flip();
                rot('b',n-1,2);
                flip();
                rot('b',n-1,2);
                if(test) display();
                turn('f',2);
                return;
            }
            //if there is a green below the orange center
            if(cube[2][n/2][n-1] == cube[5][n/2][n/2])
            {
                if(test) printf("If there is a green below the orange center\n");
                //Now after this we will have two cases if blue and red edges are solved
                if(cube[3][n/2][n-1] == cube[3][n/2][n/2])
                {
                    if(test) printf("Now after this we will have two cases if blue and red edges are solved\n");
                    rot('b',n-1,1);
                    flip();
                    rot('b',n-1,3);
                    if(test) display();
                    turn('f',2);
                    return;
                }
                //Or only blue edge is solved
                else
                {   
                    if(test) printf("Or only blue edge is solved\n");
                    rot('b',n-1,3);
                    flip();
                    if(test) display();
                    turn('f',2);
                    return;
                }
                
            }
            //if green is below the red center
            if(cube[3][n/2][n-1] == cube[5][n/2][n/2])
            {
                if(test) printf("if green is below the red center\n");

                //now if the orange edge is solved
                if(cube[2][n/2][n-1] == cube[2][n/2][n/2])
                {
                    rot('b',n-1,2);
                    flip();
                    rot('b',n-1,2);
                    if(test) display();
                    turn('f',2);
                    return;
                }

                //Now if only blue edge is solved
                else
                {
                    flip();
                    rot('b',n-1,1);
                    if(test) display();
                    turn('f',2);
                    return;
                }
                
            }
        }
        //If the color blue has not reached rotate the top layer
        rot('b',n-1,1);
    }
    if(test) printf("May have entered wrong colors\n");
    return;
}


/****************************************************      CORNER POSITIONING       ******************************************** */
//Now is the time for corner positioning. And here its important to note the parity
//we will first make a function that will check if corner at a juction of face color_1, color_2, and color_3 are located correclty
int check_atleast_one_corner_positioned()
{
    int check = 0;
    //Check if (0-1-2) corner are correctly placed
    if(cube[1][0][n-1] == cube[1][n/2][n/2] || cube[1][0][n-1] == cube[2][n/2][n/2] || cube[1][0][n-1] == cube[0][n/2][n/2])
    {
        if(cube[2][n-1][n-1] == cube[2][n/2][n/2] || cube[2][n-1][n-1] == cube[1][n/2][n/2] || cube[2][n-1][n-1] == cube[0][n/2][n/2])
        {
            if(cube[0][0][0] == cube[0][n/2][n/2] ||cube[0][0][0] == cube[1][n/2][n/2] ||cube[0][0][0] == cube[2][n/2][n/2])
            {
                check++;
            }
        }
    }

    //Check of (1-0-3) corner is correctly placed
    if(cube[1][n-1][n-1] == cube[1][n/2][n/2] || cube[0][n-1][0] == cube[1][n/2][n/2] || cube[3][0][n-1] == cube[1][n/2][n/2])
    {
        if(cube[1][n-1][n-1] == cube[0][n/2][n/2] || cube[0][n-1][0] == cube[0][n/2][n/2] || cube[3][0][n-1] == cube[0][n/2][n/2])
        {
            if(cube[1][n-1][n-1] == cube[3][n/2][n/2] || cube[0][n-1][0] == cube[3][n/2][n/2] || cube[3][0][n-1] == cube[3][n/2][n/2])
            {
                check++;
            }
        }
    }
    
    //Check if (0-5-3) corner is placed correctly
    if(cube[0][n-1][n-1] == cube[0][n/2][n/2]||cube[3][n-1][n-1] == cube[0][n/2][n/2]||cube[5][n-1][0] == cube[0][n/2][n/2])
    {
        if(cube[0][n-1][n-1] == cube[3][n/2][n/2]||cube[3][n-1][n-1] == cube[3][n/2][n/2]||cube[5][n-1][0] == cube[3][n/2][n/2])
        {
            if(cube[0][n-1][n-1] == cube[5][n/2][n/2]||cube[3][n-1][n-1] == cube[5][n/2][n/2]||cube[5][n-1][0] == cube[5][n/2][n/2])
            {
                check++;
            }
        }
    }
    
    //Check if (0-2-5) corner is placed correctly
    if(cube[0][0][n-1] == cube[0][n/2][n/2]||cube[2][0][n-1] == cube[0][n/2][n/2]||cube[5][0][0] == cube[0][n/2][n/2])
    {
        if(cube[0][0][n-1] == cube[2][n/2][n/2]||cube[2][0][n-1] == cube[2][n/2][n/2]||cube[5][0][0] == cube[2][n/2][n/2])
        {
            if(cube[0][0][n-1] == cube[5][n/2][n/2]||cube[2][0][n-1] == cube[5][n/2][n/2]||cube[5][0][0] == cube[5][n/2][n/2])
            {
                check++;
            }
        }
    }
    
    return check;
}
//This function will take in the cube just the way you do, in that same posititon and will apply the corner parity algorithm.
void solve_corner_parity()
{
    /*You have to ensure before calling this function that corner that are just faceing you 
    that is (0-1-2) and (1-0-3) are to be exchanged.
    */
    for(int i=n/2;i<n-1;i++){rot('l',i,2);}
    rot('b',n-1,2);
    for(int i=n/2;i<n-1;i++){rot('l',i,2);}
    for(int i=n/2;i<n;i++){rot('b',i,2);}
    for(int i=n/2;i<n-1;i++){rot('l',i,2);}
    for(int i=n/2;i<n;i++){rot('b',i,2);}

    //we will bring the white face to the top (Correct position of cube)
    turn('f',2);
    //Then the only thing we will be left with is the yellow plus.
    complete_yellow_plus();
    //then we again invert the cube (yellow facing the top)
    turn('f',2);
    //And we return this cube
    return;
}
//This function will take the cube(yellow facing the top) and return the side of edge that is to be swapped
void bring_swapping_corner_front()
{
    for(int i=0;i<4;i++)
    {
        int check = 0;
        //This section will check if the color at the corner (0-1-2) should suppose to go to corner (0-1-3)
        //If any one color of the (0-1-2) corner has the color of red (remember the cube is inverted)
        if(cube[2][n-1][n-1] == cube[3][n/2][n/2] || cube[1][0][n-1] == cube[3][n/2][n/2] || cube[0][0][0] == cube[3][n/2][n/2])
        {
            //If any color of corner at (0-1-2) has the color yellow (remember the cube is inverted) 
            if(cube[2][n-1][n-1] == cube[0][n/2][n/2] || cube[1][0][n-1] == cube[0][n/2][n/2] || cube[0][0][0] == cube[0][n/2][n/2])
            {
                //if any color of corner at (0-1-2) has the color blue
                if(cube[2][n-1][n-1] == cube[1][n/2][n/2] || cube[1][0][n-1] == cube[1][n/2][n/2] || cube[0][0][0] == cube[1][n/2][n/2])
                {
                    check++;
                }
            }
        }

        //This section will check if the color at the corner (0-1-3) should suppose to go to corner (0-1-2)
        //If any one color of the (0-1-3) corner has the color of ornage (face2) (remember the cube is inverted)
        if(cube[0][n-1][0] == cube[2][n/2][n/2] || cube[3][0][n-1] == cube[2][n/2][n/2] || cube[1][n-1][n-1] == cube[2][n/2][n/2])
        {
            //If any color of corner at (0-1-2) has the color yellow (remember the cube is inverted) 
            if(cube[0][n-1][0] == cube[0][n/2][n/2] || cube[3][0][n-1] == cube[0][n/2][n/2] || cube[1][n-1][n-1] == cube[0][n/2][n/2])
            {
                //if any color of corner at (0-1-2) has the color blue
                if(cube[0][n-1][0] == cube[1][n/2][n/2] || cube[3][0][n-1] == cube[1][n/2][n/2] || cube[1][n-1][n-1] == cube[1][n/2][n/2])
                {
                    check++;
                }
            }
        }

        //Now if check is equal to 2 this means all the corners are placed correctly.
        if(check == 2)
        {
            if(test) printf("Corners are placed correclty to be acted by parity algorithm\n");
            return;
        }
        //if not, then we turn the cube and check again
        turn('b',1);
    }
    if(test) printf("Logical Error\n");
    return;
}
//This is the final corner positioning function
void corners_positioning()
{
    if(test) printf("Into corner positioning\n");
    //here before entering we are assuming the cube is such that white is pointing up and blue, front.
    turn('f',2);
    //Now from here on the cube is inverted wit blue facing front and yellow at the top
    if(test) printf("This goes into the function\n");
    if(test) display();

    int check = check_atleast_one_corner_positioned();
    
    //This means all the corners are correctly positioned
    if(check == 4)
    {
        if(test) printf("All the corners are positioned properly (check = 4)\n");
        turn('f',2);
        return;
    }
    //This means only there corners are correctly placed which is kind of impossible
    else if(check == 3)
    {
        if(test) printf("Not Possible (check = 3)\n");
        turn('f',2);
        return;
    }
    //This means only two corners are correctly placed. And this is the siglnal of parity
    else if(check == 2)
    {
        if(test) printf("Parity alert (check = 2)\n");
        //Now the task is to bring the corners that are to be swapped just infront.
        //this function should bring those parity corner to the front. (remember that yellow face is facing the top)
        bring_swapping_corner_front();

        solve_corner_parity();
        /*After calling this solve corner parity function, we will finally be at the stage where just the corners need to be placed
        properly. And this time hopefully there won't be any case of parity. So we agin pass it to this function*/
        //But before caling we will have to invert this cube (white facing the top)
        turn('f',2);

        //lets first ensure that the cube is correctly faced. that is blue is facing front. And this will adjust the cube correctly.
        while(cube[1][n/2][n/2] != 2)
        {
            turn('b',1);
        }

        //And then call the function
        corners_positioning();
        //Now the solved cube will be solved and in corrrect 
        return;
    }
    //This means only one corner is placed correclty 
    else if(check = 1)
    {
        if(test) printf("check = 1\n");
        if(test) printf("Before bringing the unsolved peice at (0-1-3)\n");
        if(test) display();
        //We will first bring the corner that is solved to the (0-1-3) position
        for(int i=0;i<4;i++)
        {
            if(cube[1][n-1][n-1] == cube[0][n/2][n/2] || cube[3][0][n-1] == cube[0][n/2][n/2] | cube[0][n-1][0] == cube[0][n/2][n/2])
            {
                if(cube[1][n-1][n-1] == cube[3][n/2][n/2] || cube[3][0][n-1] == cube[3][n/2][n/2] | cube[0][n-1][0] == cube[3][n/2][n/2])
                {
                    if(cube[1][n-1][n-1] == cube[1][n/2][n/2] || cube[3][0][n-1] == cube[1][n/2][n/2] | cube[0][n-1][0] == cube[1][n/2][n/2])
                    {
                        if(test) printf("Now the corner is at the (0-1-3) corner\n");
                        break;
                    }
                }
            }
            //if the solved corner is not present at the (0-1-3) then turn the cube and see again
            turn('b',1);
        }
        
        if(test) printf("Now the solved peice is at (0-1-3)\n");
        if(test) display();

        //Now we can apply the corner switching algorithm and call the same function again after correctly orienting the cube
        rot('b',n-1,3);
        rot('l',n-1,1);
        rot('b',n-1,1);
        rot('l',0,1);
        rot('b',n-1,3);
        rot('l',n-1,3);
        rot('b',n-1,1);
        rot('l',0,3);

        if(test) printf("After applying the formula\n");
        if(test) display();
        //this will bring the cube to its default orientaion (blue fornt, and white top)
        while(cube[1][n/2][n/2] != 2) {turn('b',1);}
        if(cube[0][n/2][n/2] != 1) turn('f',2);
        if(test) printf("Now the cube should be brought to it default position\n");
        if(test) display();
        if(test) printf("And now it again goes into corner_positioning function\n");
        //then we pass the rubiks cube back into this corner positioning function
        corners_positioning();
        //and then we return
        return;
    }
    //if no corner is at it's correct posiiton
    else if(check == 0)
    {
        //Now we can apply the corner switching algorithm to any corner no matter
        rot('b',n-1,3);
        rot('l',n-1,1);
        rot('b',n-1,1);
        rot('l',0,1);
        rot('b',n-1,3);
        rot('l',n-1,3);
        rot('b',n-1,1);
        rot('l',0,3);

        turn('f',2);
        corners_positioning();
        return;
    }

    else
    {
        if(test) printf("logical error\n");
        turn('f',2);
        return;
    }
}


/*****************************************************          FINALE MOVE         ******************************************** */
//Now we can finally move on to make our Finale move. here we are assuming that all the corners are corretly placed and the cube's 
// orientation is as white : top and blue : front
void signature_move()
{
    //here we are assuming that corner that needs to be swapped is at (0-1-3) corner.
    for(int i=0;i<2;i++)
    {
        rot('l',n-1,3);
        rot('b',0,3);
        rot('l',n-1,1);
        rot('b',0,1);
    }
    return;
}
//this function willl make the main call
void finale()
{
    turn('f',2);
    if(test) printf("The cube is now inverted and just needs the corners swapped\n");
    if(test) display();
    for(int i=0;i<4;i++)
    {
        if(cube[0][n-1][0] != 6)
        {
            while(cube[0][n-1][0] != 6)
            {
                signature_move();
            }
        }
        rot('b',n-1,1);
    }
    turn('f',2);
    return;
}

//This function will just calculate the entropy of the current ste of rubiks cube and stores it in the txt file.
//So along with the 
void entropy()
{
    
    return;
}

//Main function
int main(int argc, char*argv[])
{
    n = atoi(argv[1]);//Dimension of rubiks cube

    int* cube_encoded = (int*)malloc(sizeof(int)*(argc-2));
    for(int i=2;i<argc;i++){
        cube_encoded[i-2] = atoi(argv[i]); 
    }

    int expected = 2 + 6 * n * n;
    if(argc!=expected){
        printf("Problem with the input\n");
        return 2;
    }
    
    create();
    intialize(cube_encoded);
    //display();

    //printf("\nCube is initialized\n");

    // printf("\n****************************************************\n");
    // printf("\033[1:33mCENTER CREATION\n\033[0m");
    if(deploy || test) center();
    //display();
    //display();
    //printf("\nCenters are Formed\n");

    // printf("\n****************************************************\n");
    // printf("\033[1:33mEDGE PAIRING\n\033[0m");
    if(deploy || test) edges();
    //printf("\nEdges are completely solved\n");
    //display();

    // printf("\nEdges are formed but parity is not solved\n");

    // printf("No of edges not solved : %d\n",count_unsolved_edge());

    //Here we will bring the centers to the right locations
    //White to the top anbd blue to front.
    positionCenters();

    int ask = 1;        //Set this to one and you solve the White plus
    int break1 = 1;     //Set this to one and you solve First Layer
    int break2 = 1;     //Set this to one and you solve Second Layer
    int break3 = 1;     //Set this to one and you solve yellow Plus
    int break4 = 1;     //Set this to one and you solve Complete Plus
    int break5 = 1;     //Set this to one and you solve corner Positioning
    int break6 = 1;     //set this to one and you solve Finale

    if(ask)
    {
        // printf("\n****************************************************\n");
        //printf("\033[1:33mWHITE PLUS\n\033[0m");
        white_plus();
        //display();

        if(break1)
        {
            // printf("\n****************************************************\n");
            //printf("\033[1:33mFIRST LAYER\n\033[0m");
            first_layer();
            //display();

            if(break2)
            {
                // printf("\n****************************************************\n");
                //printf("\033[1:33mSECOND LAYER\n\033[0m");
                // printf("Before entering\n");
                if(test) display();
                second_layer();
                // printf("After completing\n");
                //display();

                if(break3)
                {
                    // printf("\n****************************************************\n");
                    //printf("\033[1:33mYELLOW PLUS\n\033[0m");
                    // printf("Before entering\n");
                    if(test) display();
                    yellow_plus();
                    // printf("After completing\n");
                    //display();

                    if(break4)
                    {
                        // printf("\n****************************************************\n");
                        //printf("\033[1:33mCOMPLETE PLUS\n\033[0m");
                        // printf("Before entering\n");
                        if(test) display();
                        complete_yellow_plus();
                        // printf("After completing\n");
                        //display();

                        if(break5)
                        {
                            // printf("\n****************************************************\n");
                            //printf("\033[1:33mCORNER POSITIONING\n\033[0m");
                            // printf("Before entering\n");
                            if(test) display();
                            corners_positioning();
                            // printf("After completing\n");
                            //display();

                            if(break6)
                            {
                                // printf("\n****************************************************\n");
                                //printf("\033[1:33mFINALE\n\033[0m");
                                finale();
                            }
                        }
                    }
                }
            }
        }
    }

    //printf("\n****************************************************\n");
    //display();

    //Last thing printed will be total number of steps
    if(deploy) printf("%d ",steps);


    //printf("\nNo. of step = %d\n",steps);
    //printf("\nThe code executed successfully\n"); 

        
    free(cube);
    return 0;
}

//Example for 10*10 Rubik's cube
/*
Top faces
3 2 2 4 1 2 4 3 2 3
2 3 5 1 3 2 2 6 2 

*/

//Example for 9*9 Rubiks cube
/*
    Top face 
    3 2 5 2 4 2 3 2 4
    3 1 3 4 4 2 3 2 1
    4 2 3 4 4 4 4 1 6
    5 5 4 6 1 6 1 1 4
    3 6 5 2 1 2 3 2 1
    3 5 3 3 4 5 6 4 1
    3 4 4 1 5 2 3 5 2
    6 6 1 1 5 3 2 4 4
    3 2 5 2 2 3 1 4 4

    Fornt face
    5 3 4 3 6 5 2 1 2
    2 6 2 2 1 1 6 2 2
    3 3 1 6 3 1 5 1 2
    3 5 5 3 6 3 3 1 1
    5 6 2 6 2 5 1 1 2
    3 2 1 2 6 5 3 2 2
    4 6 6 4 6 2 6 6 3
    1 3 2 1 5 1 3 6 3
    1 6 3 4 3 6 1 3 1


    Left Face
    1 1 2 1 1 1 1 5 1
    6 3 4 1 4 6 4 4 6
    2 5 2 2 1 2 3 6 5
    3 2 1 4 2 2 5 5 6
    3 5 6 6 3 3 4 6 6
    6 5 5 1 3 4 6 3 6
    4 4 2 3 6 3 5 4 1
    2 6 2 3 1 2 1 2 2
    5 4 4 5 4 2 3 4 2

    Right Face
    6 6 4 2 5 5 2 4 6
    3 3 2 6 6 6 6 1 6
    6 3 6 2 2 2 4 3 3
    3 6 4 5 4 3 5 6 2
    1 3 1 2 4 5 3 2 3
    1 3 6 1 5 4 2 3 6
    2 3 2 2 3 6 1 3 5
    5 5 4 4 4 4 5 2 5
    5 6 1 1 4 5 5 3 2

    Bottom face
    4 5 6 1 6 4 4 6 4
    5 5 4 3 1 4 1 4 4
    6 5 6 6 6 6 5 6 2
    4 1 1 1 1 2 3 3 4
    6 4 4 3 6 1 2 3 2
    6 4 4 2 4 4 5 6 4
    5 2 1 5 4 1 1 2 6
    5 5 1 4 3 2 5 1 5
    3 1 5 6 4 5 6 5 3

    Back Face
    6 3 1 4 1 1 4 1 6
    1 4 1 6 5 2 6 5 1
    6 5 4 1 5 3 2 6 6
    2 5 3 1 4 6 4 4 5
    2 3 5 1 5 5 2 2 5
    5 6 4 6 3 5 5 5 3
    3 5 5 6 1 5 3 4 5
    2 3 1 3 2 5 5 1 3
    2 4 1 6 5 4 1 4 5
*/

//Exmaple for 8*8 Rubiks cube
/*
    Top face
    2 4 4 4 4 3 4 6
    5 2 4 4 1 1 5 5
    5 6 5 3 6 4 5 6
    3 6 4 4 1 5 5 3
    6 3 4 3 1 3 1 6
    2 3 4 3 5 4 5 5
    2 3 2 3 1 4 6 1
    6 6 4 3 5 1 1 5

    Front face
    4 4 5 6 6 2 3 6
    6 1 2 2 5 6 5 2
    3 5 3 1 1 6 5 1
    5 4 4 5 2 2 1 6
    1 5 5 4 1 6 3 2
    6 2 1 2 6 2 2 1
    3 3 1 1 5 5 5 3
    4 4 6 6 3 5 5 4

    left face
    3 1 4 1 5 4 4 5
    2 1 4 5 4 3 4 2
    4 1 2 6 5 1 6 2
    6 2 6 3 3 4 1 1
    4 1 2 3 5 3 2 4
    2 2 2 2 6 5 3 3
    3 5 2 2 4 6 4 6
    5 2 2 1 5 5 3 5

    Right face
    3 5 6 2 1 2 6 2
    1 6 1 3 2 3 6 5
    5 6 5 5 1 6 3 3
    2 3 5 6 4 1 3 5
    1 4 2 2 1 1 4 4
    5 2 3 1 3 1 6 6
    2 3 1 3 6 6 2 3
    6 5 6 3 4 3 6 4

    Bottom Face
    1 1 4 4 2 6 4 2
    5 6 6 6 6 2 3 6
    3 5 3 4 5 6 3 2
    1 1 2 4 6 4 2 5
    2 2 3 5 6 6 5 2
    4 5 4 3 6 2 4 2
    4 4 4 5 2 3 2 2
    1 1 4 3 3 3 4 1

    Back Face
    3 3 1 2 5 5 1 2
    2 1 1 6 5 4 2 6
    1 5 3 3 4 5 4 3
    1 4 5 5 6 1 3 2
    3 6 2 2 2 4 6 4
    6 1 6 2 1 1 4 1
    1 4 3 6 4 1 1 3
    1 5 1 5 6 1 6 3
*/

//Exmaple of 6*6 Rubiks cube
/*
    Top Face
    5 3 1 2 2 2
    1 4 1 6 6 6
    1 5 3 2 4 6
    4 1 6 6 2 3
    3 5 3 3 1 2
    2 3 2 6 4 6

    front face
    1 2 6 5 1 5
    4 3 5 5 6 2
    6 1 1 5 3 3
    2 1 2 2 1 1
    5 5 2 4 3 5
    2 3 2 4 5 2

    left face
    4 2 2 5 2 4
    5 2 6 4 4 2
    4 5 4 1 2 5
    2 6 5 1 1 4
    3 5 3 6 3 4
    5 3 3 3 5 1

    right face
    4 6 5 3 4 6
    6 4 3 2 2 1
    5 5 1 5 2 2
    5 2 6 4 6 2
    4 2 1 3 6 6
    6 5 6 4 3 6

    bottom face
    3 6 1 6 6 3
    1 1 2 4 4 1
    1 4 4 3 5 3
    1 5 5 2 6 1
    5 3 3 4 5 5
    1 2 5 6 1 3

    back face
    3 4 1 4 4 5
    1 6 6 4 1 4
    3 3 3 4 4 3
    5 1 6 3 6 6
    6 1 2 5 2 3
    1 6 4 4 1 4
*/

//Example of 6*6 Rubiks cube
/*
    Top face
    1 5 4 4 1 1
    5 1 4 2 3 6
    2 1 2 1 6 2
    2 5 6 1 2 5
    4 1 2 2 3 1
    5 3 4 2 1 1

    Front Face
    3 6 6 6 4 3
    5 1 6 4 6 6
    5 1 3 2 1 2
    3 6 2 3 6 6
    2 2 3 2 1 2
    2 4 1 6 3 4

    Left Face
    3 3 1 4 5 6
    1 6 1 4 4 1
    3 5 4 1 4 4
    1 5 3 3 6 1
    1 6 6 5 2 3
    6 3 5 4 3 4

    Right Face
    2 4 3 3 4 4
    2 4 4 4 5 6
    1 3 5 6 3 5
    5 6 2 5 3 2
    4 2 1 3 4 3
    6 4 4 4 4 3

    Bottom Face
    1 5 5 5 6 2
    2 4 4 6 3 2
    6 5 4 6 5 5
    1 2 5 5 5 2
    5 2 1 3 3 6
    5 6 2 3 2 6

    Back Face
    5 5 3 6 6 2
    2 5 3 5 5 1
    3 4 4 6 1 6
    6 1 1 4 2 3
    2 6 3 2 5 5
    5 1 1 1 3 5
*/



//Example for 6*6 Rubik's cube
/*
    Top face
    2 2 1 6 6 4
    3 2 1 4 4 6
    1 3 2 5 3 5
    6 4 4 1 6 2
    4 6 3 6 3 1
    5 1 5 2 5 1

    Fornt Face
    3 4 4 1 4 2
    4 2 6 6 2 1
    1 3 6 4 5 1
    2 5 5 6 2 5
    2 3 4 1 3 5
    5 5 2 3 4 6

    Left Face
    4 1 5 4 5 6
    1 5 2 4 1 2
    5 5 6 2 4 3
    1 3 4 6 6 6
    5 6 1 1 4 6
    3 6 3 2 1 3

    Right Face
    4 3 4 4 3 5
    4 5 3 1 3 2
    4 2 1 2 4 3
    1 4 3 5 1 3
    1 1 5 3 5 4
    4 2 4 3 3 3

    Bottom Face
    1 3 6 6 6 5
    2 5 6 3 4 4
    3 2 1 3 2 2
    5 6 3 5 4 2
    3 4 2 2 1 2
    2 2 6 4 6 2

    Back Face
    6 6 4 1 5 1
    3 6 5 6 1 6
    2 5 3 4 2 6
    6 5 2 1 1 5
    5 6 5 1 2 1
    6 3 3 5 5 1
*/

//Example of 4*4 Rubik's cube 
/*
    Top Face
    4 3 2 3
    1 3 5 6
    4 4 4 6
    2 6 6 5

    Front Face
    4 5 5 1
    4 6 6 5
    3 6 2 4
    3 6 1 3

    Left Face
    2 2 6 6
    3 1 2 2
    5 1 2 1
    3 5 1 2

    Right Layer
    4 3 2 5
    1 4 1 2
    6 3 3 2
    2 3 5 6

    Bottom Layer
    1 2 5 6
    4 5 6 6
    4 3 5 3
    5 2 4 5

    Back Layer
    1 3 1 4
    4 5 4 1
    1 1 2 3
    1 5 4 6

*/

//Example for 5*5 Rubiks cube
/*
    Top Face
    3 6 3 2 2
    3 6 2 1 5
    1 4 1 2 5
    1 2 3 6 4
    3 6 6 2 5

    Front Face
    5 3 4 6 6
    6 3 5 4 3
    1 6 2 1 3
    4 2 5 3 2
    4 5 5 5 6

    Left Face
    1 6 4 5 1
    2 2 2 2 4
    4 3 3 4 2
    1 1 6 5 5
    5 4 5 1 1

    Right Face
    3 6 1 1 6
    5 4 5 3 3
    1 4 4 6 5
    1 4 3 5 3
    3 1 6 4 5

    Bottom Face
    2 6 3 6 2
    3 5 3 4 2
    4 4 6 2 2
    2 3 6 1 1
    6 4 6 2 1

    Back Face
    4 5 3 3 4
    4 5 1 1 5
    2 1 5 5 6
    3 6 1 6 1
    2 2 2 4 4

*/

//Example of 8*8*8 Rubiks cube
/*
    Top Face
    2 2 5 5 2 1 1 2
    6 3 4 6 1 3 6 1
    3 3 4 1 4 3 2 1
    3 5 1 5 4 6 4 3
    6 4 2 5 4 5 5 6
    2 6 4 4 1 6 6 1
    3 3 4 5 2 3 5 2
    3 4 5 1 4 6 6 6

    Front Face
    1 5 1 4 2 4 2 3
    4 1 6 1 3 5 3 5
    2 3 6 5 3 1 5 3
    4 5 2 3 2 4 6 1
    6 
*/


//Example of 5*5 Rubiks cube
/*
Top face
4 4 2 1 4
1 1 5 6 2
6 6 1 3 2
5 3 1 5 5
6 6 4 1 2

Front Face
2 3 5 3 1
2 4 3 6 6
3 2 2 1 1
5 6 5 3 4
4 6 5 2 5

Left Face
1 3 4 3 4
4 3 1 5 6
6 1 3 3 5
4 2 3 4 1
5 6 4 1 6

Right Face
3 3 3 3 1
3 1 6 2 6
2 6 4 2 6
6 5 2 2 2
1 5 3 5 3

Bottom Face
5 2 1 1 3
5 4 2 3 4
1 4 6 4 6
5 5 5 2 4
3 4 1 3 6

Back Face
6 1 3 2 2
2 1 4 4 1
2 6 5 4 5
2 1 5 6 5
5 6 4 4 2

*/

//Example for 3*3 Rubiks cube
/*
    Top Face
    5 4 5
    4 1 4
    1 6 1

    Front face
    3 3 2
    2 2 2
    2 5 2

    Left Face
    3 5 5
    1 3 6
    2 4 6

    Right Face
    4 6 1
    3 4 3
    3 5 6

    Back Face
    4 1 1
    2 6 6
    6 3 5

    Back Face
    3 5 4
    2 5 1
    6 1 4
*/


/* Conclusion*/
/*
The project has been sussessful. And congratulations for that! Now hree are some further direction in which we can move our project to.
1.  To use Open CV library in python to scan the ciube into the C code. Because with increasing dimension of cube, it could be really difficult to entrr the number manually. And to ease that process we could make this happen through cameras.
2.  The second thing is to make a function that will take in the cube, and find the maximum no of color proesent at each face and i will define something called entropy. Which will tell us how much is the cube cluttered. And as the algorithm progress by which I mean as the algorithm progress after each move we can calculate the entropy and print that on some notepad. This will make it easy to visualize how the program convergences its solution.

3.  The third thing is to use time library and calcuate the total time taken for executing the code. Now I would need a function that
    will map list of numbers to a move on rubiks cube. Likewise in python it is possible to use the random function to generate list of 
    random numbers and scramble a solved rubiks cube of N dimension. this will help us in genrating many samples of scrambled rubiks cube

4.  And once this data is generated, we could take average of time taken to solve some i-th dimesional rubik's cube and we could later 
    plot the time vs dimension of rubiks cube plot. And likewise we could estimate the time complexity of the code.
*/

