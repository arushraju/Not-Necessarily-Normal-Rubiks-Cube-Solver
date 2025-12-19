#include<stdio.h>
#include<stdlib.h>

/*NOTE THAT THIS IS THE CODE THAT WILL BE USED AT THE BACKEND AND THUS THERE ARE SOME MODIFICATIONS REQUIRED IN THIS CODE.*/


/*The most important assumption.
when starting to solve the rubiks cube, imagine that the blue center is facing the solver and 
white color is at the top */

/* RULE TO FILL THE COLOR
    White   =   1
    Blue    =   2
    Green   =   3
    Red     =   4
    Orange  =   5
    Yellow  =   6 */

 /*arr[k][j][i]*/


//this variable is to count the number of steps
int step = 0;

//this function will just check the if the center colors are entered in the correct way or not
int check(int cube[6][6][6]) 
{
    int t = 0;
    if(cube[3][4][3] == 1)t++;
    if(cube[0][3][3] == 2)t++;
    if(cube[3][3][0] == 4)t++;
    if(cube[4][3][3] == 3)t++;
    if(cube[3][3][4] == 5)t++;
    if(cube[3][0][3] == 6)t++;

    if(t==6)
    {
        //printf("\ncheck passed\n");
        return 1;
    }
    else
    {
        //printf("\nBhai ya unki Behen, dekh life me ab sirf do chize ho sakte hai yaa to tu BSDK hai, ya fir tu BSDK hai. Ese andha dhun number mat daal!!!!\n");
        //printf("centers colors wrong entered");
        return 0;
    }
}

//scanning input cube configuration
void input(int cube[6][6][6],int cube_string[54])
{
    int cube_string_index = 0;
    //Top Matrix
    for(int k=5;k>=1;k = k - 2)
    {
        for(int i=1 ; i<=5 ; i = i+2)
        {
            cube[k][4][i] = cube_string[cube_string_index];
            cube_string_index++;
        }
        
    }
    // printf("Top Matrix has been entered\n");

    //Now when filling the left and front and the right faces convention is a bit different
    for(int j = 5 ; j >= 1 ; j = j - 2){
        for(int k = 5 ; k > 0 ; k = k - 2){
            cube[k][j][0] = cube_string[cube_string_index];
            cube_string_index++;
        }
        for(int i = 1 ; i<=5 ; i = i+2){
            cube[0][j][i] = cube_string[cube_string_index];
            cube_string_index++;
        }
        for(int k = 1 ; k<=5 ; k = k+2){
            cube[k][j][4] = cube_string[cube_string_index];
            cube_string_index++;
        }
    }
    // printf("The Left, Center and Right matrix has been entered\n");
    
    
    for(int k=1;k<=5;k = k+2)
    {
        for(int i=1;i<=5;i = i+2)
        {
            cube[k][0][i] = cube_string[cube_string_index];
            cube_string_index++;
        }
    }
    // printf("Bottom Matrix has been entered\n");
    
    for(int j=1;j<=5;j = j+2)
    {
        for(int i=1;i<=5;i = i+2)
        {
            cube[4][j][i] = cube_string[cube_string_index];
            cube_string_index++;
        }
    }
    // printf("Back Matrix has been entered\n");
}

//n represents the number of turns
//c represents the plane of rotation
//t represents the plane to be rotated
void rot(int cube[6][6][6],int n,char c,int t)
{
    
    if(c=='i')//rotation of jk plane
        {
            //if t=4,n=0 means downward motion of the right layer in front view
            //if t=0,n=1 means downward motion of the left layer in front view
            //by the way in the above example n is taken for the sake of understanding
            for(int j=0;j<n;j++)
            {
            //rotation of plane mapping
            int temp;
            temp = cube[5][5][t];
            cube[5][5][t] = cube[5][1][t];
            cube[5][1][t] = cube[1][1][t];
            cube[1][1][t] = cube[1][5][t];
            cube[1][5][t] = temp;
            temp = cube[3][1][t];
            cube[3][1][t] = cube[1][3][t];
            cube[1][3][t] = cube[3][5][t];
            cube[3][5][t] = cube[5][3][t];
            cube[5][3][t] = temp;

            //rotation of layer(type 1)
            temp = cube[5][4][t+1];
            cube[5][4][t+1] = cube[4][1][t+1];
            cube[4][1][t+1] = cube[1][0][t+1];
            cube[1][0][t+1] = cube[0][5][t+1];
            cube[0][5][t+1] = temp;
            //rotation of layer(type 2)
            temp = cube[3][4][t+1];
            cube[3][4][t+1] = cube[4][3][t+1];
            cube[4][3][t+1] = cube[3][0][t+1];
            cube[3][0][t+1] = cube[0][3][t+1];
            cube[0][3][t+1] = temp;
            //rotation of layer(type 3)
            temp = cube[1][4][t+1];
            cube[1][4][t+1] = cube[4][5][t+1];
            cube[4][5][t+1] = cube[5][0][t+1];
            cube[5][0][t+1] = cube[0][1][t+1];
            cube[0][1][t+1] = temp;
            }

            if(t==0&&n==1) {printf("L' "); step++;}
            else if(t==0&&n==2) {printf("L2 "); step++;}
            else if(t==0&&n==3) {printf("L "); step++;}
            else if(t==4&&n==1) {printf("R' "); step++;}
            else if(t==4&&n==2) {printf("R2 "); step++;}
            else if (t==4&&n==3) {printf("R "); step++;}
        }
    
    if(c=='k')//rotation of ij plane
        {
            //if t=4,n=1 means anticlockwise motion of the back layer in front view
            //if t=0,n=1 means anticlockwise motion of the front layer in front view
            //rotation of plane mapping
            for(int j=0;j<n;j++)
            {
            
            int temp;
            temp = cube[t][5][5];
            cube[t][5][5] = cube[t][1][5];
            cube[t][1][5] = cube[t][1][1];
            cube[t][1][1] = cube[t][5][1];
            cube[t][5][1] = temp;
            temp  = cube[t][5][3];
            cube[t][5][3] = cube[t][3][5];
            cube[t][3][5] = cube[t][1][3];
            cube[t][1][3] = cube[t][3][1];
            cube[t][3][1] = temp;
            //rotation of the layer(type 1)
            temp = cube[t+1][5][0];
            cube[t+1][5][0] = cube[t+1][4][5];
            cube[t+1][4][5] = cube[t+1][1][4];
            cube[t+1][1][4] = cube[t+1][0][1];
            cube[t+1][0][1] = temp;
            //rotation of the layer (type 2)
            temp = cube[t+1][3][0];
            cube[t+1][3][0] = cube[t+1][4][3];
            cube[t+1][4][3] = cube[t+1][3][4];
            cube[t+1][3][4] = cube[t+1][0][3];
            cube[t+1][0][3] = temp;
            //rotation of the layer (type 3)
            temp = cube[t+1][1][0];
            cube[t+1][1][0] = cube[t+1][4][1];
            cube[t+1][4][1] = cube[t+1][5][4];
            cube[t+1][5][4] = cube[t+1][0][5];
            cube[t+1][0][5] = temp;
            }
            
            if(t==0&&n==1) {printf("F' "); step++;}
            else if(t==0&&n==2) {printf("F2 "); step++;}
            else if(t==0&&n==3) {printf("F "); step++;}
            else if(t==4&&n==1) {printf("B "); step++;}
            else if (t==4&&n==2){printf("B2 "); step++;}
            else if (t==4&&n==3){printf("B' "); step++;}
        }

    if(c=='j')//rotation of ik plane
        {
            //rotate the upper layer to left for t=4 and n=1
            //rotate the lower layer to left for t=4 and n=1
            for(int j=0;j<n;j++)
            {
                //rotation of plane
                int temp;
                temp = cube[5][t][1];
                cube[5][t][1] = cube[1][t][1];
                cube[1][t][1] = cube[1][t][5];
                cube[1][t][5] = cube[5][t][5];
                cube[5][t][5] = temp;
                temp = cube[1][t][3];
                cube[1][t][3] = cube[3][t][5];
                cube[3][t][5] = cube[5][t][3];
                cube[5][t][3] = cube[3][t][1];
                cube[3][t][1] = temp ;

                //roation of layer(type 1)
                temp = cube[0][t+1][1];
                cube[0][t+1][1] = cube[1][t+1][4];
                cube[1][t+1][4] = cube[4][t+1][5];
                cube[4][t+1][5] = cube[5][t+1][0];
                cube[5][t+1][0] = temp;
                //rotation of layer (type 2)
                temp = cube[0][t+1][3];
                cube[0][t+1][3] = cube[3][t+1][4];
                cube[3][t+1][4] = cube[4][t+1][3];
                cube[4][t+1][3] = cube[3][t+1][0];
                cube[3][t+1][0] = temp;
                //rotation of layer (type 3)
                temp = cube[0][t+1][5];
                cube[0][t+1][5] = cube[5][t+1][4];
                cube[5][t+1][4] = cube[4][t+1][1];
                cube[4][t+1][1] = cube[1][t+1][0];
                cube[1][t+1][0] = temp;

            }
            
            if(t==0&&n==1) {printf("D' ");step++;}
            else if(t==0&&n==2) {printf("D2 ");step++;}
            else if(t==0&&n==3) {printf("D ");step++;}
            else if(t==4&&n==1) {printf("U' ");step++;}
            else if(t==4&&n==2) {printf("U2 ");step++;}
            else if(t==4&&n==3) {printf("U ");step++;}
        }
    return;
}

//to turn the cube left once
//this mean all the three layer will be turned towards left wrt j axis
//but it seems that the cube will turn to right althought the indivisual layer have moved to left
void turn_left(int cube[6][6][6])
{
    int temp;
    //to turn the middle layer to left
        //rotation of plane (type1)
            temp = cube[0][3][1];
            cube[0][3][1] = cube[1][3][4];
            cube[1][3][4] = cube[4][3][5];
            cube[4][3][5] = cube[5][3][0];
            cube[5][3][0] = temp;
            //rotation of the plane(type2)
            temp = cube[0][3][3];
            cube[0][3][3] = cube[3][3][4];
            cube[3][3][4] = cube[4][3][3];
            cube[4][3][3] = cube[3][3][0];
            cube[3][3][0] = temp;
            //rotation of the plane (type3)
            temp = cube[0][3][5];
            cube[0][3][5]=cube[5][3][4];
            cube[5][3][4] = cube[4][3][1];
            cube[4][3][1] = cube[1][3][0];
            cube[1][3][0] = temp;

    // to turn the top layer to left
    for(int t=0;t<=4;t = t+4)
    {
        temp = cube[5][t][1];
                cube[5][t][1] = cube[1][t][1];
                cube[1][t][1] = cube[1][t][5];
                cube[1][t][5] = cube[5][t][5];
                cube[5][t][5] = temp;
                temp = cube[1][t][3];
                cube[1][t][3] = cube[3][t][5];
                cube[3][t][5] = cube[5][t][3];
                cube[5][t][3] = cube[3][t][1];
                cube[3][t][1] = temp ;

                //roation of layer(type 1)
                temp = cube[0][t+1][1];
                cube[0][t+1][1] = cube[1][t+1][4];
                cube[1][t+1][4] = cube[4][t+1][5];
                cube[4][t+1][5] = cube[5][t+1][0];
                cube[5][t+1][0] = temp;
                //rotation of layer (type 2)
                temp = cube[0][t+1][3];
                cube[0][t+1][3] = cube[3][t+1][4];
                cube[3][t+1][4] = cube[4][t+1][3];
                cube[4][t+1][3] = cube[3][t+1][0];
                cube[3][t+1][0] = temp;
                //rotation of layer (type 3)
                temp = cube[0][t+1][5];
                cube[0][t+1][5] = cube[5][t+1][4];
                cube[5][t+1][4] = cube[4][t+1][1];
                cube[4][t+1][1] = cube[1][t+1][0];
                cube[1][t+1][0] = temp;
    }
    printf("X ");
    return;
}

/*WHITE PLUS*/
//this function execute the first step of solving
void white_plus(int cube[6][6][6])
{
    for(int f=0;f<2;f++)
    {
        for(int i=0;i<4;i++)
        {
       
            //if the white color does match at the top
                    
            if(cube[0][5][3]==1)//if the topmid color of the center matrix is white
            {
                if  (cube[1][4][3]==cube[0][3][3])//if the color above the edge peice of the white is blue
                {
                    rot(cube,2,'k',0);//rotate the front face twice
                    rot(cube,1,'j',0);//rotate the bottom layer to left
                    rot(cube,3,'i',0);//rotate te left layer up once
                    rot(cube,3,'k',0);//rotate the front layer clockwise once
                    rot(cube,1,'i',0);//rotate the left layer down once
                    //printf("\n1\n");
                }
                else if(cube[1][4][3]==cube[3][3][0])//if the color above the edge peice of the white is red
                {
                    rot(cube,1,'k',0);//rotate the front layer anticlockwise once
                    rot(cube,3,'i',0);//rotate the left layer up once
                    //printf("\n2\n");
                }
                else if(cube[1][4][3]==cube[4][3][3])//if the color above the edge peice of the white is green   
                {
                    rot(cube,1,'k',0);//rotate the front face in antclockwise once
                    rot(cube,3,'j',4);//rotate the top layer to right once
                    rot(cube,3,'i',0);//rotate the left layer up once
                    rot(cube,1,'j',4);//rotate the top layer to left once
                    //printf("\n3\n");
                }
                else if(cube[1][4][3]==cube[3][3][4])//if the color above the edge peice of the white is orange
                {
                    rot(cube,3,'k',0);//rotate the front face clockwise once
                    rot(cube,3,'i',4);//rotate the right layer up once
                    //printf("\n4\n");
                }
            }
            if(cube[0][3][1]==1)//if the leftmid color of the center face is white
            {
                if(cube[1][3][0]==cube[0][3][3])//the color left of the white is blue
                {
                    rot(cube,1,'j',4);//rotate the top layer to left once
                    rot(cube,3,'i',0);//rotate the left layer up once
                    rot(cube,3,'j',4);//rotate the top layer to right once
                    //printf("\n6\n");
                }
                else if(cube[1][3][0]==cube[3][3][0])//the color at the left of white is red
                {
                    rot(cube,3,'i',0);//rotate the left layer up once
                    //printf("\n7\n");
                }
                else if(cube[1][3][0]==cube[3][3][4])//the color at the left of white is orange
                {
                    rot(cube,2,'k',0);//rotate the front layer twice
                    rot(cube,3,'i',4);//rotate the right layer up once
                    rot(cube,2,'k',0);//rotate the front layer twice to get back the things
                    //printf("\n8\n");
                }
                else if(cube[1][3][0]==cube[4][3][3])//the color at the left of white is green
                {
                    rot(cube,3,'j',4);//rotate the top layer to right once
                    rot(cube,3,'i',0);//rotate the left layer up once
                    rot(cube,1,'j',4);//rotate the top layer to left once
                    //printf("\n9\n");
                }
            }
            if(cube[0][3][5]==1)//if the right mid color of the center face is white
            {
                if(cube[1][3][4]==cube[0][3][3])// if the color to the right of white in the edge peice is blue
                {
                    rot(cube,3,'k',0);//rotate the front face in clockwise once
                    rot(cube,1,'j',0);//rotate the bottom layer to left once
                    rot(cube,3,'i',0);//rotate the left layer up once
                    rot(cube,3,'k',0);//rotate the front face clockwise once
                    rot(cube,1,'i',0);//rotate the left layer down once to get back things
                    //printf("\n10\n");
                }
                else if(cube[1][3][4]==cube[4][3][3])// if the color to the right of white in the edge peice is green
                {
                    rot(cube,1,'j',4);//rotate the top layer once to left
                    rot(cube,3,'i',4);//rotate the right layer up once
                    rot(cube,3,'j',4);//rotate the top layer to right once
                    //printf("\n11\n");
                }
                else if(cube[1][3][4]==cube[3][3][0])// if the color to the right of white in the edge peice is red
                {
                    rot(cube,2,'k',0);//rotate the front face twice 
                    rot(cube,3,'i',0);//rotate the left layer up
                    rot(cube,2,'k',0);//rotate the front face twice
                    //printf("\n12\n");
                }
                else if(cube[1][3][4]==cube[3][3][4])// if the color to the right of white in the edge peice is orange
                {
                    rot(cube,3,'i',4);//rotate the right layer up once
                    //printf("\n13\n");
                }
            }
            if(cube[0][1][3]==1)//if the mid bottom color of the center matrix is white
            {
                //printf("entered white at bot mid\n");
                if(cube[1][0][3]==cube[0][3][3])//if the color at the bottom of white in the edge peice is blue
                {
                    rot(cube,1,'j',0);//rotate the bottom layer to left once
                    rot(cube,1,'k',0);//rotate the front face anticlockwise once
                    rot(cube,3,'i',0);//rotate the left layer up once
                    rot(cube,3,'k',0);//rotate the front layer clockwise once
                    rot(cube,1,'i',0);//rotate the left layer down to get thing back
                    //printf("\n14\n");
                }
                else if(cube[1][0][3]==cube[4][3][3])// if the color to the bottom of white in the edge peice is green
                {
                    rot(cube,1,'j',0);//rotate the bottom layer to left once
                    rot(cube,1,'i',0);//rotate the left layer down once
                    rot(cube,3,'k',4);//rotate the back layer one in clockwise direction from the solver's perspective
                    rot(cube,3,'i',0);//rotate the right layer one up to get things back
                    //printf("\n-1\n");
                }
                else if(cube[1][0][3]==cube[3][3][0])//if the color at the bottom of white in the edge peice is red
                {
                    rot(cube,3,'k',0);//rotate the front face once in clockwise direction
                    rot(cube,3,'i',0);//rotate the left layer up once
                    rot(cube,1,'k',0);//rotate the front face anticlockwise once to get things done
                    //printf("\n15\n");
                }
                else if(cube[1][0][3]==cube[3][3][4])//if the color at the bottom of white in the edge peice is orange
                {
                    rot(cube,1,'k',0);//rotate the front face once in anticlockwise direction
                    rot(cube,3,'i',4);//rotate the right layer up once
                    rot(cube,3,'k',0);//rotate the front layer once in clockwise direction
                    //printf("\n16\n");
                }
            }
            if(cube[1][0][3]==1)//if the the topmid element of bottom matrix is white
            {
                if(cube[0][1][3]==cube[0][3][3])//if the bottom mid color of the front face is blue
                {
                    rot(cube,2,'k',0);//rotate the front layer twice
                    //printf("\n17\n");
                }
                else if(cube[0][1][3]==cube[4][3][3])//if the bottom mid color of the front face is green
                {
                    rot(cube,2,'j',0);//rotate the bottom layer twice
                    rot(cube,2,'k',4);//rotatethe back layer twice
                    //printf("\n18\n");
                }
                else if(cube[0][1][3]==cube[3][3][0])//if the bottom mid color of the front face is red
                {
                    rot(cube,1,'j',0);//rotate the bottom layer to left once
                    rot(cube,2,'i',0);//rotate the left layer twice
                    //printf("\n19\n");
                }
                else if(cube[0][1][3]==cube[3][3][4])//if the bottom mid color of the front face is orange
                {
                    rot(cube,3,'j',0);//rotate the bottom layer to right once
                    rot(cube,2,'i',4);//rotate the right layer twice
                    //printf("\n20\n");
                }
            }
            if(cube[1][4][3]==1)//if the white color matches at the top
            {
                if(cube[0][5][3]==cube[3][3][0])//if the color below the edge peice, or the one which is facing the solver is red
                {
                    rot(cube,2,'k',0);//rotate the front face twice
                    rot(cube,1,'j',0);//rotate the bottom layer to left once
                    rot(cube,2,'i',0);//rotate the left layer twice
                    //printf("\n21\n");
                }
                else if(cube[0][5][3]==cube[4][3][3])//if the color below the edge peice, or the one which is facing the solver is green
                {
                    rot(cube,2,'k',0);//rotate the front layer twice
                    rot(cube,2,'j',0);// rotate the bottom layer twice
                    rot(cube,2,'k',4); //rotate the back layer twice
                    //printf("\n22\n");
                }
                else if(cube[0][5][3]==cube[3][3][4])//if the color below the edge peice, or the one which is facing the solver is orange
                {
                    rot(cube,2,'k',0);//rotate the front layer twice
                    rot(cube,3,'j',0);//rotate the bottom layer to right once
                    rot(cube,2,'i',4);//rotate the right layer twice
                    //printf("\n23\n");
                }
                //if cube[0][5][3]==2 then the peice is already in the right place
            }

            turn_left(cube);
        }
    }
    //printf("\nDONE WITH FIRST PLUS\n");
    return;
}

/*FIRST LAYER*/
//the following code is for the execution of first layer.
void first_layer(int cube[6][6][6])
{
   for(int i=0;i<6;i++)
   {
    //if the color at the top right of ceter matrix is white
    if(cube[0][5][5]==1)
   {
    //when there is a white at the top right of the center matrix with the blue at center initially.
    //note that there's one of the most precious trick in here. i stiil dont know whats the center of the color facing me.
    //when there is a blue at top of white
    if(cube[1][4][5]==cube[0][3][3])
    {
        rot(cube,1,'i',4);//rotate the right layer down
        rot(cube,3,'j',0);//rotate the bottom layer to right once
        rot(cube,3,'i',4);//rotate the right layer up
        rot(cube,2,'j',0);//rotate the bottom layer twice
        rot(cube,1,'k',0);//rotate the front layer anticlockwise once
        rot(cube,3,'j',0);//rotate the bottom layer to right
        rot(cube,3,'k',0);//rotate the front face clockwise once
    }
    //when there is a green at top of white
    else if(cube[1][4][5]==cube[4][3][3])
    {
        rot(cube,1,'i',4);//right layer down once
        rot(cube,3,'j',0);//rotate the bottom layer to right once
        rot(cube,3,'i',4);//rotate the right layer up once
        rot(cube,3,'k',4);//rotate the back layer clockwise once
        rot(cube,3,'j',0);//rotate the bottom layer to right
        rot(cube,1,'k',4);//rotate the back layer anti clockwise once
    }
    //when there is orange at the top
    else if(cube[1][4][5]==cube[3][3][4])
    {
        rot(cube,1,'i',4);//rotate the right layer down once
        rot(cube,3,'j',0);//rotate the bottom layer to right once
        rot(cube,3,'i',4);//rotate the right layer up once
        rot(cube,1,'j',0);//rotate the bottom layer to left
        rot(cube,1,'i',4);//rotate the right layer down once
        rot(cube,3,'j',0);//rotate the bottom layer to right once
        rot(cube,3,'i',4);//rotate the right layer up once
    }
    //when there is red at the top
    else if(cube[1][5][4]==cube[3][3][0])
    {
        rot(cube,1,'i',4);//rotate the right down once
        rot(cube,1,'j',0);//rotate the bottom layer to left
        rot(cube,3,'i',4);//rotate the right layer up
        rot(cube,2,'j',0);//rotate the bottom layer twice
        rot(cube,3,'i',0);//rotate the left layer up once
        rot(cube,2,'j',0);//rotate the bottom layer twice
        rot(cube,1,'i',0);//rotate the left layer down
        rot(cube,1,'j',0);//rotate the bottom layer to left once
        rot(cube,3,'i',0);//rotate the left layer up once
        rot(cube,3,'j',0);//rotate the bottom layer to right once
        rot(cube,1,'i',0);//rotate the left layer down 
    }
   } 
    
    //if the color at the top left of center matrix is white
    if(cube[0][5][1]==1)
    {
        //if the color at top of white is green
        if(cube[1][4][1]==cube[4][3][3])
        {
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,1,'k',4);//rotate te back ayer anticlockwise once
            rot(cube,1,'j',0);//rotate the bottom layer to left once
            rot(cube,3,'k',4);//rotate the back layer clockwise once
        }
        //if the color at the top of white is blue
        else if(cube[1][4][1]==cube[0][3][3])
        {
            rot(cube,1,'i',0);//rotate the left layer down once
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'k',0);//roate the front face clockwise once
            rot(cube,1,'j',0);//rtate the bottom layer to left once
            rot(cube,1,'k',0);//rotate the front face anticlockwise once
        }
        //if the color at the top is red
        else if(cube[1][4][1]==cube[3][3][0])
        {
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//roate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//roate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the color at the orange
        else if(cube[1][4][1]==cube[1][4][1])
        {
            rot(cube,1,'i',0);//roate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up 
            rot(cube,1,'j',0);//rotate the bottom layer left 
            rot(cube,3,'i',4);//rotate the right layer up once
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'i',4);//rotate the right layer down once
        }
    }
    
    //if the color at the bottom left of center matrix in white
    if(cube[0][1][1]==1)
    {
        //if the color at the bottom of white is orange
        if(cube[1][0][1]==cube[3][3][4])
        {
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'k',0);//rotate the front face clockwise 
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'k',0);//rotate the frnt face clockwise once
        }
        //if the color at the bottom of white is blue
        else if(cube[1][0][1]==cube[0][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//roteate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the bottom of white is red
        else if(cube[1][0][1]==cube[3][3][0])
        {
            rot(cube,1,'k',4);//rotate the back layer anticlockwise once
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'k',4);//roate the back layer clockwise once
        }
        //if the color at bottom of white is green
        else if(cube[1][0][1]==cube[4][3][3])
        {
            rot(cube,1,'j',0);//roate the bottom layer to right
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'j',0);//rotate the bottom layer to right
            rot(cube,1,'i',4);//rotate the right layer down
        }
    }
    
    //if the color at the bottom right of center matrix is white
    if(cube[0][1][5]==1)
    {
        //if the color at the bottom of white is red
        if(cube[1][0][5]==cube[3][3][0])
        {
            rot(cube,2,'j',0);//rotate the bottom layer to left twice
            rot(cube,1,'k',0);//rotate the front layer anticlockwise once
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'k',0);//rotate the front layer clockwise once
        }
        //if the color at the bottom is blue
        else if(cube[1][0][5]==cube[0][3][3])
        {
            rot(cube,1,'j',0);//rotate the bottom layer left once
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,3,'j',0);//rotate the bottom layer right once
            rot(cube,3,'i',4);//rotate the right layer up
        }
        //if the color at bottom of white is green
        else if(cube[1][0][5]==cube[4][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right nce
            rot(cube,3,'i',0);//rotate the left layer up 
            rot(cube,3,'j',0);//roate the bottom layer right
            rot(cube,1,'i',0);//rotate the left layer down
        }
        //if the color at the bottom of white is orange
        else if(cube[1][0][5]==cube[3][3][4])
        {
            rot(cube,3,'k',4);//roate the back face clockwise once
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,1,'k',4);//roate the back face clockwise
        }
    }
    
    //if the color at the top right of bottom matrix is white
    if(cube[1][0][5]==1)
    {
        //if the color above the white is orange
        if(cube[0][1][5]==cube[3][3][4])
        {
            rot(cube,1,'j',0);//roate the bottom layer left
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'j',0);//roate the bottom layer left
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,3,'j',0);//roate the bottom layer right
            rot(cube,3,'i',4);//roate the right layer up
        }
        //if the color at the top of white is green
        else if(cube[0][1][5]==cube[4][3][3])
        {
            rot(cube,3,'k',4);//rotate the back layer clockwise once
            rot(cube,2,'j',0);//roate the bottom layer twice
            rot(cube,1,'k',4);//rotate the back layer anticlockwise once
            rot(cube,1,'j',0);//roate the bottom layer to left
            rot(cube,3,'k',4);//roate the back layer clockwise
            rot(cube,3,'j',0);//roate the bottom layer to right once
            rot(cube,1,'k',4);//roate the back face anticlockwise 
        }
        //if the color at the top of white is blue
        else if(cube[0][1][5]==cube[0][3][3])
        {
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,1,'k',0);//roate the front face anticlockwise once
            rot(cube,2,'j',0);//roate the bottom layer twice
            rot(cube,3,'k',0);//roate the front face clockwise once
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'k',0);//roate the front face anticlockwise once
            rot(cube,3,'j',0);//roate the bottom layer to right once
            rot(cube,3,'k',0);//roate the front face clockwise once 
        }
        //if the color at the top of white is red
        else if(cube[0][1][5]==cube[3][3][0])
        {
            rot(cube,1,'k',4);//rotate the back face anticlockwise
            rot(cube,3,'j',0);//roate the bottom layer to right
            rot(cube,3,'k',4);//rotate the back face clockwise
            rot(cube,2,'j',0);//roate the bottom layer twice
            rot(cube,1,'k',4);//roate the back face anticlockwise
            rot(cube,2,'j',0);//roate the bottom layer twice
            rot(cube,3,'k',4);//roate the back face clockwise 
        }
    
    }
    
    //if the color at the top left of bottom matrix is white
    if(cube[1][0][1]==1)
    {
        //if the color above white is red
        if(cube[0][1][1]==cube[3][3][0])
        {
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,3,'j',0);//rotate the bottom layer right once
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//roate the bottom layer right
            rot(cube,1,'i',0);//roate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the color above white is blue
        else if(cube[0][1][1]==cube[0][3][3])
        {
            rot(cube,1,'i',4);//roate the right layer down
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'i',4);//roate the right layer up
            rot(cube,1,'j',0);//roate the bottom layer to left 
            rot(cube,1,'i',4);//roate the right layer down
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'i',4);//roate the right layer up
        }
        //if the color above white is orange
        else if(cube[0][1][1]==cube[3][3][4])
        {
            rot(cube,3,'k',4);//rotate te back face clockwise
            rot(cube,1,'j',0);//roate the bottom layer to left
            rot(cube,1,'k',4);//roate the back face anticlockwise
            rot(cube,1,'j',0);//roate the bottom layer to left
            rot(cube,3,'k',4);//roate the back layer clockwise
            rot(cube,3,'j',0);//roate the bottom layer to right
            rot(cube,1,'k',4);//roate the back face anticlockwise
        }
        //if the color above white is green
        else if(cube[0][1][1]==cube[4][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,1,'j',0);//roate te bottom layer to left once
            rot(cube,1,'i',0);//roate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer to left once
            rot(cube,3,'i',0);//rotate the right layer up
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//rotate the left layer down  
        }
    }
    
    //if the color at the top of top left is white
    if(cube[1][4][1]==1)
    {
        //if the color at top left is orange
        if(cube[0][5][1]==cube[3][3][4])
        {
    
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,1,'j',0);//rotate the bottom layer right
            rot(cube,3,'i',4);//rotate the right layer up
        }
        //if the color at top left is green
        else if(cube[0][5][1]==cube[4][3][3])
        {
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'k',4);//rotate back layer clockwise
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,1,'k',4);//rotate the back layer anticlockwise
        }
        //if the color at top left is red
        else if(cube[0][5][1]==cube[3][3][0])
        {
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//rotate the bottom layer right
            rot(cube,1,'i',0);//rotate the left layer down       
        }
        //if the color is blue its at the right place
    }
    
    //if the color at the top of top right is white
    if(cube[1][4][5]==1)
    {
        //if the top right color is orange
        if(cube[0][5][5]==cube[3][3][4])
        {
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,3,'k',4);//rotate te back layer clockwise
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,1,'k',4);//rotate the back layer anticlockwise

        }
        //if the color at top right is red
        else if (cube[0][5][5]==cube[3][3][0])
        {
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,3,'j',0);//rotate the bottom layer right
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,1,'j',0);//rotate the botom layer left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the color at the top right is green
        else if (cube[0][5][5]==cube[4][3][3])
        {
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,2,'j',0);//rotate the bottom alyer twice
            rot(cube,3,'i',0);//rotate left layer up
            rot(cube,3,'j',0);//rotate bottom alyer right
            rot(cube,1,'i',0);//rotate left layer down
        }
    }
    
    //if the color at the right of top right of center matrix is white
    if(cube[1][5][4]==1)
    {
        rot(cube,1,'i',4);//rotate the right layer down
        rot(cube,1,'j',0);//rotate the bottom layer to left
        rot(cube,3,'i',4);//rotate the right layer up

        //pasted from the case where bot left color of center matrix is white
        //if the color at the bottom of white is orange
        if(cube[1][0][1]==cube[3][3][4])
        {
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'k',0);//rotate the front face clockwise 
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'k',0);//rotate the frnt face clockwise once
        }
        //if the color at the bottom of white is blue
        else if(cube[1][0][1]==cube[0][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//roteate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the bottom of white is red
        else if(cube[1][0][1]==cube[3][3][0])
        {
            rot(cube,1,'k',4);//rotate the back layer anticlockwise once
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'k',4);//roate the back layer clockwise once
        }
        //if the color at bottom of white is green
        else if(cube[1][0][1]==cube[4][3][3])
        {
            rot(cube,1,'j',0);//roate the bottom layer to right
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'j',0);//rotate the bottom layer to right
            rot(cube,1,'i',4);//rotate the right layer down
        }
    }
    //if the color at the left of top left of center matrix is white
    if(cube[1][5][0]==1)
    {
        rot(cube,1,'i',0);//rotate the left layer down
        rot(cube,1,'j',0);//rotate the bottom layer to left
        rot(cube,3,'i',0);//rotate the left layer up
         //if the color at the top left of bottom matrix is white
      
        //if the color above white is red
        if(cube[0][1][1]==cube[3][3][0])
        {
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,3,'j',0);//rotate the bottom layer right once
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//roate the bottom layer right
            rot(cube,1,'i',0);//roate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the color above white is blue
        else if(cube[0][1][1]==cube[0][3][3])
        {
            rot(cube,1,'i',4);//roate the right layer down
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'i',4);//roate the right layer up
            rot(cube,1,'j',0);//roate the bottom layer to left 
            rot(cube,1,'i',4);//roate the right layer down
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'i',4);//roate the right layer up
        }
        //if the color above white is orange
        else if(cube[0][1][1]==cube[3][3][4])
        {
            rot(cube,3,'k',4);//rotate te back face clockwise
            rot(cube,1,'j',0);//roate the bottom layer to left
            rot(cube,1,'k',4);//roate the back face anticlockwise
            rot(cube,1,'j',0);//roate the bottom layer to left
            rot(cube,3,'k',4);//roate the back layer clockwise
            rot(cube,3,'j',0);//roate the bottom layer to right
            rot(cube,1,'k',4);//roate the back face anticlockwise
        }
        //if the color above white is green
        else if(cube[0][1][1]==cube[4][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,1,'j',0);//roate te bottom layer to left once
            rot(cube,1,'i',0);//roate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer to left once
            rot(cube,3,'i',0);//rotate the right layer up
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//rotate the left layer down  
        }
    }
    //if the color at the right of bot right of center matrix is white
    if(cube[1][1][4]==1)
    {
        rot(cube,1,'j',0);//rotate the bottom layer to left
        //if the color at the bottom left of center matrix in white
       
        //if the color at the bottom of white is orange
        if(cube[1][0][1]==cube[3][3][4])
        {
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'k',0);//rotate the front face clockwise 
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'k',0);//rotate the frnt face clockwise once
        }
        //if the color at the bottom of white is blue
        else if(cube[1][0][1]==cube[0][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//roteate the left layer down
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,3,'i',0);//rotate the left layer up
        }
        //if the bottom of white is red
        else if(cube[1][0][1]==cube[3][3][0])
        {
            rot(cube,1,'k',4);//rotate the back layer anticlockwise once
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'k',4);//roate the back layer clockwise once
        }
        //if the color at bottom of white is green
        else if(cube[1][0][1]==cube[4][3][3])
        {
            rot(cube,1,'j',0);//roate the bottom layer to right
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'j',0);//rotate the bottom layer to right
            rot(cube,1,'i',4);//rotate the right layer down
        }
    }
    //if the color at the left of bot left of center matrix is white
    if(cube[1][1][0]==1)
    {
        rot(cube,3,'j',0);//rotate the bottom layer to right
        //if the color at the bottom right of center matrix is white
    
        //if the color at the bottom of white is red
        if(cube[1][0][5]==cube[3][3][0])
        {
            rot(cube,2,'j',0);//rotate the bottom layer to left twice
            rot(cube,1,'k',0);//rotate the front layer anticlockwise once
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'k',0);//rotate the front layer clockwise once
        }
        //if the color at the bottom is blue
        else if(cube[1][0][5]==cube[0][3][3])
        {
            rot(cube,1,'j',0);//rotate the bottom layer left once
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,3,'j',0);//rotate the bottom layer right once
            rot(cube,3,'i',4);//rotate the right layer up
        }
        //if the color at bottom of white is green
        else if(cube[1][0][5]==cube[4][3][3])
        {
            rot(cube,3,'j',0);//rotate the bottom layer to right nce
            rot(cube,3,'i',0);//rotate the left layer up 
            rot(cube,3,'j',0);//roate the bottom layer right
            rot(cube,1,'i',0);//rotate the left layer down
        }
        //if the color at the bottom of white is orange
        else if(cube[1][0][5]==cube[3][3][4])
        {
            rot(cube,3,'k',4);//roate the back face clockwise once
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,1,'k',4);//roate the back face clockwise
        }
    }
    turn_left(cube);
    turn_left(cube);
   }
   //printf("FIRST LAYER");
   return;
}

/*SECOND LAYER*/
//folowing are the two algorithm to solve for second layer
//this function is to send a color at bottom mid to left mid, and bottom mid to right mid
void second_left(int cube[6][6][6])
{
    rot(cube,3,'j',0);//rotate the bottom layer to right
    rot(cube,1,'i',0);//rotate the left layer down
    rot(cube,1,'j',0);//rotate the bottom layer left
    rot(cube,3,'i',0);//rotate the left layer up
    rot(cube,3,'k',0);//rotate the front face cockwise once
    rot(cube,3,'i',0);//rotate the left layer up
    rot(cube,1,'k',0);//rotate the front face anticlockwise once
    rot(cube,1,'i',0);//roate the left layer down once
    return;
}
void second_right(int cube[6][6][6])
{
    rot(cube,1,'j',0);//rotate the bottom layer to left
    rot(cube,1,'i',4);//rotate the right layer down
    rot(cube,3,'j',0);//rotate the bottom layer to right
    rot(cube,3,'i',4);//rotate the right layer up
    rot(cube,1,'k',0);//rotate the front face anticlockwise
    rot(cube,3,'i',4);//rotate the right layer up
    rot(cube,3,'k',0);//rotate the front face clockwise
    rot(cube,1,'i',4);//rotate the right layer down
}
//thos code will execute the second layer 
void second_layer(int cube[6][6][6])
{
    //the code in this way....
    //start by seeing the bottom mid element of the center face wheter it matches witht the center of center face. 
    //if yes then check for the color below it. if its yellow then leave it and rotate the bottom layer once. if tis not yellow then do accordingly
    //if its no then check for the color at the right mid and left mid of the center wheter they are blue or not.
    //then check if the color at the right of right mid and left of left mid is blue or not and act acordingly.
    //so total of 5 locations to check for before turning the cube.
    
    for(int j=0;j<8;j++)
    {
    /*
    //if the left mid of center face is blue
    if(cube[0][3][1]==cube[0][3][3])
    {
        //if the left of left mid center face is orange
        if(cube[1][3][0]==cube[3][3][4])
        {
            second_layer(cube);
            rot(cube,3,'k',0);//rotate the front face clockwise
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'k',0);//rotate the front face anticlockwise
            rot(cube,1,'j',0);//rotate the bottom layer left
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,3,'j',0);//rotate the bottom layer right
            rot(cube,3,'i',4);//rotate the right layer up
        }
    }
    //if the color to the left of left mid is blue
    if(cube[1][3][0]==cube[0][3][3])
    {
        //if the color at the left mid is red
        if(cube[0][3][1]==cube[3][3][0])
        {
            second_left(cube);//algorithm for second layer
            rot(cube,2,'j',0);//rotate the bottom layer twice
            second_left(cube);//algorithm for second layer
        }
        //if the color at the left mid at orange
        else if(cube[0][3][1]==cube[3][3][4])
        {
            second_left(cube);
            rot(cube,2,'j',0);//rotate the bottom layer twice
            second_right(cube);
        }
    }
    */

    //if the color to the right of right mid is blue
    if(cube[1][3][4]==cube[0][3][3])
    {
        //if the right mid color is orange
        if(cube[0][3][5]==cube[3][3][4])
        {
            second_right(cube);
            rot(cube,2,'j',0);//rotate the bottom layer twice
            second_right(cube);
        }
        //if the right mid color is red
        else if(cube[0][3][5]==cube[3][3][0])
        {
            second_right(cube);
            rot(cube,2,'j',0);//roate the bottom layer twice
            second_left(cube);
        }
    }
    //if the color at the right mid is blue
    if(cube[0][3][5]==cube[0][3][3])
    {
        //if the color at the right of right mid is red
        if(cube[1][3][4]==cube[3][3][0])
        {
            second_right(cube);
            rot(cube,1,'k',0);//roate te front face anticlockwise once
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'k',0);//roate the front face clockwise
            rot(cube,3,'j',0);//rotate the bottom layer to right once
            rot(cube,1,'i',0);//roate the left layer down
            rot(cube,1,'j',0);//roate the bottom layer to left
            rot(cube,3,'i',0);//roate the left layer up
        }
    }
    //if the color at the right mid is green
    if(cube[0][3][5]==cube[4][3][3])
    {
        //if the color to right of green is red
        if(cube[1][3][4]==cube[3][3][0])
        {
            second_right(cube);
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,1,'k',4);//rotate the back layer anticlockwise
            rot(cube,1,'j',0);//rotate the bottom layer to left 
            rot(cube,3,'k',4);//rotate the back face clockwise
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//roate the bottom layer to right
            rot(cube,1,'i',0);//roate the left layer down
        }
        //if the color to the right of green is orange
        else if(cube[1][3][4]==cube[3][3][4])
        {
            second_right(cube);
            rot(cube,2,'j',0);//rotate the bottom layer twice
            rot(cube,3,'k',4);//rotate the back face clockwise
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,1,'k',4);//rotate the back face anticlockwise
            rot(cube,3,'j',0);//roate the bottom layer to right
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'j',0);//roate the bottom layer left
            rot(cube,1,'i',4);//roatate the right layer down
        }
    }
    //if the color at the right of right mid is green
    if(cube[1][3][4]==cube[4][3][3])
    {
        //if the color at the right mid is orange
        if(cube[0][3][5]==cube[3][3][4])
        {
            second_right(cube);
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,3,'i',4);//rotate the right layer up
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,1,'i',4);//rotate the right layer down
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'k',4);//roate the back face clockwise
            rot(cube,3,'j',0);//roate the bottom layer right
            rot(cube,1,'k',4);//rotate the back afce anticlockwise

        }
        //if the color at right mid is red
        else if(cube[0][3][5]==cube[3][3][0])
        {
            second_right(cube);
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'i',0);//rotate the left layer up
            rot(cube,3,'j',0);//rotate the bottom laye right
            rot(cube,1,'i',0);//rotate the left layer down
            rot(cube,3,'j',0);//rotate the bottom layer to right
            rot(cube,1,'k',4);//rotate the back face anticlockwise
            rot(cube,1,'j',0);//rotate the bottom layer to left
            rot(cube,3,'k',4);//rotate the back face clockwise 
        }
    }
    //loop for the color at the bottom mid
    for(int i=0;i<4;i++)
    {
        //if the bottom mid is blue
        if(cube[0][1][3]==cube[0][3][3])
        {
            //if bottom of bottom mid is red
            if(cube[1][0][3]==cube[3][3][0]) {second_left(cube);}
            //if the bottom of bottom of mid is orange
            if(cube[1][0][3]==cube[3][3][4]) {second_right(cube);}
        }
        rot(cube,1,'j',0);//if the bottom mid is not blue rotate the bottom layer
    }
    
    turn_left(cube);
    }
    
    //printf("\nDONE WITH SECOND LAYER\n");
    return;
}

/*YELLOW PLUS*/
//following is the code to solve for the yello plus, after the completion of second layer
/*following are the algorithm to convert an l to plus in yellow. such that when the cube is rotatedby 180 degree along k axis, then you would seen a mirror image of L
basically the L that you have practiced for*/
void L_to_Plus(int cube[6][6][6])
{
    rot(cube,3,'k',0);//roate the front face clockwise
    rot(cube,3,'j',0);//rotate the bottom layer to right
    rot(cube,1,'i',0);//roate the left layer down
    rot(cube,1,'j',0);//rotate the bottom layer to left
    rot(cube,3,'i',0);//rotate the left layer up
    rot(cube,1,'k',0);//rotate the front face anti clockwise
    return;
}
//the following code changes I to plus with the same refernce as you solve, keeping the i horizontal
void I_to_Plus(int cube[6][6][6])
{
    rot(cube,3,'k',0);//rotate the front face clockwise
    rot(cube,1,'i',0);//rotate the left layer down
    rot(cube,3,'j',0);//rotate the bottom layer to right
    rot(cube,3,'i',0);//rotate the left layer up
    rot(cube,1,'j',0);//roate the bottom layer to left
    rot(cube,1,'k',0);//otate the front face anti clockwise
    return;
}
//this is te code for the execution of yellow plus
void yellow_plus(int cube[6][6][6])
{
    for(int i=0;i<4;i++)
    {
        //if the color at the top mid of bottom marix is yellow. here is where the formula lies
        if(cube[1][0][3]==6)
        {
            //if the plus is already made
            if(cube[3][0][5]==6 && cube[5][0][3]==6) return;
            //there is a correct L formed when the cube is seen from bottom wrt to user
            else if (cube[3][0][5]==6)
            {
                rot(cube,3,'j',0);//rotate the bottom layer to right
                L_to_Plus(cube);//then apply yht algorithm
                return;
            }
            //there is a mirror image of L when looked from bottom view
            else if(cube[3][0][1]==6)
            {
                rot(cube,2,'j',0);//rotate the bottom layer twice
                L_to_Plus(cube);//apply ythe algorithm
                return;
            }
            //if its a I when looked from bottom
            else if(cube[5][0][3]==6)
            {
                rot(cube,1,'j',0);//rotate the bottom layer to left once
                I_to_Plus(cube);//apply the algorithm 
                return;
            }
        }
        //if its not yellow then just rotate the layer and do the above commands again, as there in for loop
        else {rot(cube,1,'j',0);}
    }
    //if no color at the bottom view is found yellow
    I_to_Plus(cube);
    rot(cube,2,'j',0);//roate the bottom layer twice
    L_to_Plus(cube);
    return;
}

/*COMPLETE PLUS*/
//this code will execute the action to solve for the plus of all color
void flip(int cube[6][6][6])
{
    rot(cube,3,'j',0);//rotate the bottom layer to right
    rot(cube,1,'i',0);//rotate the left layer down
    rot(cube,3,'j',0);//rotate the bottom layer right
    rot(cube,3,'i',0);//rotate the left layer up 
    rot(cube,3,'j',0);//rotate bottom layer right
    rot(cube,1,'i',0);//rotate the left layer down
    rot(cube,2,'j',0);//roate the bottom layer twice
    rot(cube,3,'i',0);//rotate the left layer up
    rot(cube,3,'j',0);//rotate the bottom layer to right
    return;
}
//this is to execute the yellow plus
void Plus(int cube[6][6][6])
{
    for(int i=0;i<4;i++)
    {
        //if the color does match the center color (blue)
        if(cube[0][1][3]==cube[0][3][3])
        {
            //if three colors are solved them its sure that the its done
            if(cube[3][1][0]==cube[3][3][0] && cube[3][1][4]==cube[3][3][4]) {return;}
            //if the opposite colors matchs only
            else if(cube[4][1][3]==cube[4][3][3])
            {
                flip(cube);
                rot(cube,3,'j',0);//rotate the bottom layer to right
                flip(cube);
                rot(cube,2,'j',0);//rotate the bottom layer twice
                return;
            }
            //if there is a green below the orange center
            else if(cube[3][1][4]==cube[4][3][3])
            {
                //and there is a red below the green center
                if(cube[4][1][3]==cube[3][3][0])
                {
                flip(cube);
                return;
                }
                //if there is a orange below the green center
                else
                {
                    rot(cube,2,'j',0);//rotate the bottom layer twice
                    flip(cube);
                    rot(cube,3,'j',0);//rotate the bottom layer right
                    return;
                }
            }
            //if green is below the red center
            else if(cube[3][1][0]==cube[4][3][3])
            {
                //if there is red below the orange center
                if(cube[3][1][4]==cube[3][3][0])
                {
                    rot(cube,1,'j',0);//rotate the bottom layer to left once
                    flip(cube);
                    rot(cube,1,'j',0);//rotate the bottom layer to left
                    return;
                }
                //if the red is below green center
                else 
                {
                    rot(cube,3,'j',0);//roate the bottom layer to right once
                    flip(cube);
                    rot(cube,2,'j',0);//rotate the bottom layer twice
                    return;
                }
            }
            
        }
        //if the color below the blue center is not blue, then rotate the bottom layer (not the whole cube, so the center wil remain blue facing the user)
        rot(cube,1,'j',0);//rotate the bottom layer to left
    }
    printf("may be you have entered wrong colors");
    return;
}


/*CORNERS POSITIONING*/
//now is te time to position the corners
//algorithm to swap the corners in anticlockwise direction keeping the right corner fixed
void corners_swap(int cube[6][6][6])
{
    rot(cube,3,'j',0);//rotate the bottom layer to right
    rot(cube,1,'i',0);//rotate the left layer down
    rot(cube,1,'j',0);//rotate the bottom layer to left
    rot(cube,1,'i',4);//rotate the right layer down
    rot(cube,3,'j',0);//rotate the bottom layer right
    rot(cube,3,'i',0);//rotate the left layer up
    rot(cube,1,'j',0);//rotate the bottom layer to left
    rot(cube,3,'i',4);//roate te right layer up
    return;
}
//check if the corner at right is at correct position(wrt roated cube along k in 180 degree)
int corner_right_check(int cube[6][6][6])
{
    int arush=0;
    //check if the red color is present in the corner
    if(arush==0)
    {
        if(cube[0][1][1]==cube[3][3][0]){arush++;}
        else if(cube[1][0][1]==cube[3][3][0]){arush++;}
        else if(cube[1][1][0]==cube[3][3][0]){arush++;}
    }
    //check if there is blue in the corner
    if(arush==1)
    {
        if(cube[0][1][1]==cube[0][3][3]){arush++;}
        else if(cube[1][0][1]==cube[0][3][3]){arush++;}
        else if(cube[1][1][0]==cube[0][3][3]){arush++;}
    }

    if(arush==2) return 1;
    else return 0;
}
//check if the corner at the left is at correct position
int corner_left_check(int cube[6][6][6])
{
    int arush=0;
    //check if the orange color is present in the corner
    if(arush==0)
    {
        if(cube[0][1][5]==cube[3][3][4]){arush++;}
        else if(cube[1][0][5]==cube[3][3][4]){arush++;}
        else if(cube[1][1][4]==cube[3][3][4]){arush++;}
    }
    //check if there is blue in the corner
    if(arush==1)
    {
        if(cube[0][1][5]==cube[0][3][3]){arush++;}
        else if(cube[1][0][5]==cube[0][3][3]){arush++;}
        else if(cube[1][1][4]==cube[0][3][3]){arush++;}
    }
    if(arush==2) return 1;
    else return 0;
}
//execute the corner positioning
void yellow_corner(int cube[6][6][6])
{
    for(int i=0;i<4;i++)
    {
        
        if(corner_right_check(cube))
            {
                
                //if the corner left is done then as two peices are at the correct place all the corners are positioned
                if(corner_left_check(cube)){ return;}
                //if not then go on with this
                else 
                {
                    corners_swap(cube);
                    //after one time, if the positioning is done then
                    if(corner_left_check(cube)) {return;}
                    //if till now the positioning is not done, just one more time and its done
                    else
                    {
                        corners_swap(cube);
                        return;
                    }
                }
            }
        else 
        {
            turn_left(cube);
        }
    }
    corners_swap(cube);
    yellow_corner(cube);
}


/*CORNERS ORIENTATINS (LAST STEP)*/
//my signature move
void sign(int cube[6][6][6])
{
    for(int i=0;i<2;i++)
    {
        rot(cube,3,'i',0);//rotate the left layer up
        rot(cube,3,'j',4);//rotate the top layer to right
        rot(cube,1,'i',0);//rotate the left layer down
        rot(cube,1,'j',4);//roate the top layer left
    }
    return;
}
void finale(int cube[6][6][6])
{
    for(int i=0;i<4;i++)
    {
        // if the right corner is not oriented properly
        if(cube[1][0][1] != cube[3][0][3])
        {
            sign(cube);
            //if still its not oriented prperly, then again sign, and it will definitly be oriented this time
            if(cube[1][0][1] != cube[3][0][3]) {sign (cube);}
        }
        //if the orientation of the right corner is OK then move to the next corner by rotating the bottom layer
        rot(cube,1,'j',0);//rotate the bottom layer to left
    }
    //now that the corners are done rotate the last layer to desried color to completly solve the cube
    for(int i=0;i<3;i++)
    {
        if(cube[0][1][3]==cube[0][3][3]) return;
        else rot(cube,1,'j',0);
    }
}

//displays the output at that instant
void display(int cube[6][6][6])
{
    //this dispalys the top mid matrix
    int d=5;
    for(int a=0;a<3;a++)
    {
        for(int b=0;b<5;b++) {printf(" ");}
        for(int k=1;k<=5;k = k+2)
        {
            printf("%d ",cube[d][4][k]);
        }
        d = d-2;
        printf("\n");
    }
    //displays the mid three matrix. left,center,right
    for(int j = 5;j>0;j=j-2)
    {
        for(int k=5;k>0;k=k-2)
        {
            printf("%d ",cube[k][j][0]);
        }
        for(int i=1;i<6;i=i+2)
        {
            printf("%d ",cube[0][j][i]);
        }
        for(int k =1;k<6;k = k+2)
        {
            printf("%d ",cube[k][j][4]);
        }

        printf("\n");
    }
    //displays the bottom matrix
    int e=1;
    for(int a=0;a<3;a++)
    {
        for(int b=0;b<5;b++) {printf(" ");}
        for(int k=1;k<=5;k=k+2)
        {
            printf("%d ",cube[e][0][k]);
        }
        for(int c=0;c<3;c++) {printf(" ");}
        e=e+2;
        printf("\n");
    }
    //displays the bottom most matrix
    int f=1;
    for(int a=0;a<3;a++)
    {
        for(int b=0;b<5;b++) {printf(" ");}
        for(int i=1;i<=5;i=i+2)
        {
            printf("%d ",cube[4][f][i]);
        }
        for(int c=0;c<3;c++) {printf(" ");}
        f=f+2;
        printf("\n");
    }

}

int main(int argc, char* argv[])
{
    int cube_string[54];
    for (int i = 0; i < 54; i++) {
        cube_string[i] = atoi(argv[i + 1]); // convert string to int
    }


    int cube[6][6][6];
    input(cube,cube_string);
    // printf("Now it is about to be displayed\n");
    // display(cube);
    // printf("This is the backend version of Erno's Enigma\n");
    if(!check(cube))
    {
        // display (cube); 
        white_plus(cube);   //printf("\n");   //display(cube);
        first_layer(cube);  //printf("\n");   //display(cube);
        second_layer(cube); //printf("\n");   //display(cube);  
        yellow_plus(cube);  //printf("\n");   //display(cube);
        Plus(cube);         //printf("\n");   //display(cube);
        yellow_corner(cube);//printf("\n");   //display(cube);
        finale(cube);       //printf("\n");   //display(cube);
    }

    //printf("\nno of steps = %d",step);
    //printf("\nsuccessfully compiled");
    
    return 0;
}
