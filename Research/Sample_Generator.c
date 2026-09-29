#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_STEPS 100001
#define MAX_DIM 101
#define MAX_SAMPLES 1001


//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

#define COLOR_RESET "\e[0m"
#define CLEAR_CURSOR "\r\033[K"

//Function to make a new cube


//Function to rotate the faces to cube


//This is the title
void title(){
    printf(BCYN UBLK "Generalised Rubiks Cube Solver\n" COLOR_RESET);
    printf("Describe the project\n\n");
}

//This function will be used to rotate the sides of cube
int*** rot(int*** cube,int dim, char way, int p, int m)
{
    int temp;
    int n = dim;

    //This means rotation of left face, up.
    if(way == 'l')
    {
        for(int t = 0;t<m;t++)
        {
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
    }

    //This means rotation of bottom face, right.
    else if(way == 'b')
    {
        for(int t=0;t<m;t++)
        {
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
    }

    //This means rotation of front face, anti-clockwise.
    else if(way == 'f')
    {
        for(int t = 0;t<m;t++)
        {
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
    }
    
    return cube;
}


/*
This function will ask for parameters like the following:
1. Cube Dimension
2. Sample for each Dimension
3. Number of steps for shuffling
*/
int start_dim = 0;
int end_dim = 0;
int samples = 0;
int scramble_steps = 0;

void init(){
    //Display the title
    title();

    //Take in the Start Dimension
    int first_time = 1;
    do{
        if(!first_time){
            printf(RED CLEAR_CURSOR "Dimension must be" BRED " more than 2" RED "and" BRED " a Whole Number!\n");
        }
        printf(BLU "Enter the Start Dimension of Cube : " CYN);
        scanf("%d",&start_dim);
        first_time = 0;
    }  while (!(start_dim > 2 && start_dim <= MAX_DIM));

    //Take in the End Dimension
    first_time = 1;
    do{
        if(!first_time){
            printf(RED CLEAR_CURSOR "Dimension must be" BRED " more than or equal to %d" RED "and" BRED " a Whole Number!\n",start_dim);
        }
        printf(BLU "Enter the End Dimension of Cube : " CYN);
        scanf("%d",&end_dim);
        first_time = 0;
    } while (!(end_dim >= start_dim && end_dim <= MAX_DIM));

    //Take in the Samples
    first_time = 1;
    do{
        if(!first_time){
            printf(RED CLEAR_CURSOR "Samples must be" BRED " less than 50" RED "and" BRED " a Whole Number!\n");
        }
        printf(BLU "Enter the Number of Samples : " CYN);
        scanf("%d",&samples);
        first_time = 0;
    } while (!(samples <= MAX_SAMPLES));


    //Take in the Steps
    first_time = 1;
    do{
        if(!first_time){
            printf(RED CLEAR_CURSOR "Steps must be" BRED " less than 100000" RED "and" BRED " a Whole Number!\n");
        }
        printf(BLU "Enter the Number of Steps : " CYN);
        scanf("%d",&scramble_steps);
        first_time = 0;
    } while (!(scramble_steps <= MAX_STEPS));

    return;
}

//This will generate and return a completely solved rubiks cube
int*** new_cube(int dim)
{
    int*** cube = malloc(sizeof(int**) * 6);

    for(int i = 0; i < 6; i++)
    {
        cube[i] = malloc(sizeof(int*) * dim);

        for(int j = 0; j < dim; j++)
        {
            cube[i][j] = malloc(sizeof(int) * dim);
        }
    }


    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            cube[0][i][j] = 1;
            cube[1][i][j] = 2;
            cube[2][i][j] = 3;
            cube[3][i][j] = 4;
            cube[4][i][j] = 6;
            cube[5][i][j] = 5;
        }   
    }

    return cube;
}

//This structure will store the move of the cube. The feilds of structre is taken from the solver.
struct step {
    char way;
    int p;
    int m;
};
//This function will take in the dimension
struct step * new_string(int dim){
    struct step* s = (struct step*)malloc(sizeof(struct step)*scramble_steps);

    for(int i = 0; i < scramble_steps; i++){
        //Make step one
        
        //Make which face to rotate
        int random = rand() % 10;
        if(random % 3 == 0){
            s[i].way = 'l';
        } else if(random % 3 == 1){
            s[i].way = 'b';
        } else if(random % 3 == 2){
            s[i].way = 'f';
        }

        //Make which layer to rotate (Jere I want to genrate a random numebr from the 0 to dim)
        random = (rand() % dim);
        s[i].p = random;

        //Now rotate the layer from 0 to 3
        random = 1 + (rand() % 3);
        s[i].m = random;
    }

    return s;
}

//This functino will take the string with information about scrambleing and will return the transformed cube
int*** scramble(int*** cube,int dim, struct step* arr){
    for(int s = 0; s < scramble_steps; s++){
        cube = rot(cube, dim, arr[s].way, arr[s].p, arr[s].m);
    }

    return cube;
}

//This function will take the cube that is scrambled and will fill in the file
void fill_cube(FILE* file, int*** cube, int dim){
    fprintf(file, "\n");
    int n = dim;
    int a,b,c;
    //first printing the top face
    for(int i=n-1;i>=0;i--)// 'a' could be used in printing the rows of top face.
    {
        //space for n times
        for(b=0;b<n*2;b++)
        {
            fprintf(file, " ");
        }
        //Now print the top face colors from left to right.
        for(c=0;c<n;c++)
        {
            fprintf(file, "%d ", cube[0][c][i]);
        }
        fprintf(file, "\n");
    }

    //Now printing the middle three faces in 2d projection of cube
    for(int i=n-1;i>=0;i--)// 'i' will be used for each row.
    {
        //first the columns of face 2(red)
        for(a=0;a<n;a++)
        {
            fprintf(file, "%d ",cube[2][a][i]);
        }
        //Now the columns of face 1(BLU)
        for(b=0;b<n;b++)
        {
            fprintf(file, "%d ",cube[1][b][i]);
        }
        //Now the columns of face 3(orange)
        for(c=0;c<n;c++)
        {
            fprintf(file, "%d ",cube[3][c][i]);
        }
        fprintf(file, "\n");
    }

    //Now printing the bottom face
    for(int i=n-1;i>=0;i--)
    {
        //Space
        for(a=0;a<n*2;a++)
        {
            fprintf(file, " ");
        }
        //Now comes columns of bottom face
        for(b=0;b<n;b++)
        {
            fprintf(file, "%d ",cube[4][b][i]);
        }
        fprintf(file, "\n");
    }

    //Now printing the back face
    for(int i=n-1;i>=0;i--)
    {
        //Space
        for(a=0;a<n*2;a++)
        {
            fprintf(file, " ");
        }
        //Now comes columns of bottom face
        for(b=0;b<n;b++)
        {
            fprintf(file, "%d ",cube[5][b][i]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nx------------------------------------x\n");
}

//This function will make the encoded cube
void fill_encoded_cube(FILE* file, int*** cube, int dim){
    //First comes the top face from i = 0 and j = 0 to i = dim-1 and j = dim-1

    //And the sequence of th faces are TOP, FRONT, LEFT, RIGHT, BOTTOM, BACK
    for(int k = 0;k<6;k++){
        for(int j = 0;j<dim;j++){
            for(int i = 0;i<dim;i++){
                fprintf(file,"%d",cube[k][i][j]);
            }
        }
    }

    fprintf(file,"\n");

    return;
        
}

//This function will free the cube
void free_cube(int ***cube, int dim){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < dim; j++){free(cube[i][j]);}
        free(cube[i]);
    }

    free(cube);
}


//This is the function to generate the samples
void generate(){
    //Remove the file first if it exists

    //Open file
    FILE* file = fopen("Sample_Simplified.txt","w");
    FILE* encoded_file = fopen("Encoded_Samples.txt", "w");
    if(file == NULL || encoded_file == NULL)
    {
        printf(RED "Could not open Sample.txt\n" COLOR_RESET);
        exit(0);
    }
    printf(CYN "\n----PROGRESS----\n\n" BLU);
    
    for(int dim = start_dim; dim <= end_dim; dim++){

        fprintf(file, "DIMENSION : %d\n",dim);
        fprintf(encoded_file,"%d\n",dim);

        //Generate the Sample for given dimension.
        for(int samp = 0; samp < samples; samp++){
            //Loading Bar
            printf(CLEAR_CURSOR YEL "Dimension : %d | Sample : %d" COLOR_RESET,dim,samp);

            fprintf(file, "\nSAMPLE : %d\n",samp+1);
            fprintf(encoded_file,"%d\n",samp);

            //Generate a New cube
            int*** cube = new_cube(dim);

            //Generate the Random String with the right convention
            struct step* arr = new_string(dim);

            //Apply the Random String to this New cube to scramble it
            cube = scramble(cube, dim, arr);

            //Open the file and start filling it in this file
            fill_cube(file,cube,dim);
            //Open the encoding file and start filling in this file
            fill_encoded_cube(encoded_file,cube,dim);

            //Free the sample array
            free(arr);

            //Free the entire cube
            free_cube(cube,dim);    
        }
    }

    //Close the file
    fclose(file);
    fclose(encoded_file);

    printf(BGRN "\nSamples generated in Sample.txt!\n" COLOR_RESET);
    return;
}

int main(){
    system("cls");

    srand((unsigned int)time(NULL));

    //Ask for appropriate input parameter
    init();
    //Generate the samples and save it on the file
    generate();
    //Run the Solver.C
    while(1){
        int option;
        printf(CLEAR_CURSOR BLU "To view " BBLU "Sample.txt " BLU "press 1 / To open the encoded file press 2 / To continue press 3  / To end the Program press 0 : " CYN);
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                system("start Sample_Simplified.txt");
                break;
            case 2:
                system("start Encoded_Samples.txt");
                break;
            case 3:
                char input[100];
                sprintf(input, "Solver.exe %d %d %d", start_dim, end_dim, samples);
                system(input);
                return 0;
            case 0:
                printf(COLOR_RESET);
                system("cls");
                exit(0);
            default:
                printf("Invalid option.\n");
                break;
        }
    }

    return 0;
}