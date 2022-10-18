/*
 * A C++ framework for OpenGL programming in TNM046 for MT1 2015.
 *
 * This is a small, limited framework, designed to be easy to use
 * for students in an introductory computer graphics course in
 * the first year of a M Sc curriculum. It uses custom code
 * for some things that are better solved by external libraries
 * like GLEW and GLM, but the emphasis is on simplicity and
 * readability, not generality.
 * For the window management, GLFW 3.x is used for convenience.
 * The framework should work in Windows, MacOS X and Linux.
 * Some Windows-specific stuff for extension loading is still
 * here. GLEW could have been used instead, but for clarity
 * and minimal dependence on other code, we rolled our own extension
 * loading for the things we need. That code is short-circuited on
 * platforms other than Windows. This code is dependent only on
 * the GLFW and OpenGL libraries. OpenGL 3.3 or higher is required.
 *
 * Author: Stefan Gustavson (stegu@itn.liu.se) 2013-2015
 * This code is in the public domain.
 */





#include <TriangleSoup.hpp>

// File and console I/O for logging and error reporting
#include <iostream>
// Math header for trigonometric functions
#include <cmath>

// In MacOS X, tell GLFW to include the modern OpenGL headers.
// Windows does not want this, so we make this Mac-only.
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

// In Linux, tell GLFW to include the modern OpenGL functions.
// Windows does not want this, so we make this Linux-only.
#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#endif

// GLFW 3.x, to handle the OpenGL window
#include <GLFW/glfw3.h>
#include "Utilities.hpp"
#include "Shader.hpp"
void  mat4mult(float  M1[], float  M2[], float  Mout[]) {
     float  Mtemp [16];
/*
      // Your  code  goes  here: compute  and  set  each  element  of Mout , e.g.://
    Mtemp [0] = M1[0]*M2[0] + M1[4]*M2[1] + M1[8]*M2[2] + M1 [12]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [1] = M1[0]*M2[4] + M1[4]*M2[5] + M1[8]*M2[6] + M1 [12]*M2[7];
    Mtemp [2] = M1[0]*M2[8] + M1[4]*M2[9] + M1[8]*M2[10] + M1 [12]*M2[11];
    Mtemp [3] = M1[0]*M2[12] + M1[4]*M2[13] + M1[8]*M2[14] + M1 [12]*M2[15];

    Mtemp [4] = M1[1]*M2[0] + M1[5]*M2[1] + M1[9]*M2[2] + M1 [13]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [5] = M1[1]*M2[4] + M1[5]*M2[5] + M1[9]*M2[6] + M1 [13]*M2[7];
    Mtemp [6] = M1[1]*M2[8] + M1[5]*M2[9] + M1[9]*M2[10] + M1 [13]*M2[11];
    Mtemp [7] = M1[1]*M2[12] + M1[5]*M2[13] + M1[9]*M2[14] + M1 [13]*M2[15];

    Mtemp [8] = M1[2]*M2[0] + M1[6]*M2[1] + M1[10]*M2[2] + M1 [14]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [9] = M1[2]*M2[4] + M1[6]*M2[5] + M1[10]*M2[6] + M1 [14]*M2[7];
    Mtemp [10] = M1[2]*M2[8] + M1[6]*M2[9] + M1[10]*M2[10] + M1 [14]*M2[11];
    Mtemp [11] = M1[2]*M2[12] + M1[6]*M2[13] + M1[10]*M2[14] + M1 [14]*M2[15];

    Mtemp [12] = M1[3]*M2[0] + M1[7]*M2[1] + M1[11]*M2[2] + M1 [15]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [13] = M1[3]*M2[4] + M1[7]*M2[5] + M1[11]*M2[6] + M1 [15]*M2[7];
    Mtemp [14] = M1[3]*M2[8] + M1[7]*M2[9] + M1[11]*M2[10] + M1 [15]*M2[11];
    Mtemp [15] = M1[3]*M2[12] + M1[7]*M2[13] + M1[11]*M2[14] + M1 [15]*M2[15];
    */
    Mtemp [0] = M1[0]*M2[0] + M1[4]*M2[1] + M1[8]*M2[2] + M1 [12]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [4] = M1[0]*M2[4] + M1[4]*M2[5] + M1[8]*M2[6] + M1 [12]*M2[7];
    Mtemp [8] = M1[0]*M2[8] + M1[4]*M2[9] + M1[8]*M2[10] + M1 [12]*M2[11];
    Mtemp [12] = M1[0]*M2[12] + M1[4]*M2[13] + M1[8]*M2[14] + M1 [12]*M2[15];

    Mtemp [1] = M1[1]*M2[0] + M1[5]*M2[1] + M1[9]*M2[2] + M1 [13]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [5] = M1[1]*M2[4] + M1[5]*M2[5] + M1[9]*M2[6] + M1 [13]*M2[7];
    Mtemp [9] = M1[1]*M2[8] + M1[5]*M2[9] + M1[9]*M2[10] + M1 [13]*M2[11];
    Mtemp [13] = M1[1]*M2[12] + M1[5]*M2[13] + M1[9]*M2[14] + M1 [13]*M2[15];

    Mtemp [2] = M1[2]*M2[0] + M1[6]*M2[1] + M1[10]*M2[2] + M1 [14]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [6] = M1[2]*M2[4] + M1[6]*M2[5] + M1[10]*M2[6] + M1 [14]*M2[7];
    Mtemp [10] = M1[2]*M2[8] + M1[6]*M2[9] + M1[10]*M2[10] + M1 [14]*M2[11];
    Mtemp [14] = M1[2]*M2[12] + M1[6]*M2[13] + M1[10]*M2[14] + M1 [14]*M2[15];

    Mtemp [3] = M1[3]*M2[0] + M1[7]*M2[1] + M1[11]*M2[2] + M1 [15]*M2[3];// etc. for  the  remaining  15  elements  of  Mtemp [].
    Mtemp [7] = M1[3]*M2[4] + M1[7]*M2[5] + M1[11]*M2[6] + M1 [15]*M2[7];
    Mtemp [11] = M1[3]*M2[8] + M1[7]*M2[9] + M1[11]*M2[10] + M1 [15]*M2[11];
    Mtemp [15] = M1[3]*M2[12] + M1[7]*M2[13] + M1[11]*M2[14] + M1 [15]*M2[15];

    for(int i=0; i<16; i++) {
            Mout[i] = Mtemp[i];

    }
 }

void mat4identity(float M[]){
    for(int i = 0; i < 16; i++){
        if(i == 0 || i == 5 || i == 10 || i == 15){
            M[i] = 1;
        }else{
        M[i] = 0;
        }
    }

}

void  mat4print(float M[]){
     printf("Matrix :\n");
     printf("%6.2f %6.2f %6.2f %6.2f\n", M[0], M[4], M[8], M[12]);
     printf("%6.2f %6.2f %6.2f %6.2f\n", M[1], M[5], M[9], M[13]);
     printf("%6.2f %6.2f %6.2f %6.2f\n", M[2], M[6], M[10], M[14]);
     printf("%6.2f %6.2f %6.2f %6.2f\n", M[3], M[7], M[11], M[15]);
     printf("\n");
     };

void  mat4rotx(float M[], float  angle){
    M[0] = 1;
    M[4] = 0;
    M[8] = 0;
    M[12] = 0;

    M[1] = 0;
    M[5] = cos(angle);
    M[9] = -sin(angle);
    M[13] = 0;

    M[2] = 0;
    M[6] = sin(angle);
    M[10] = cos(angle);
    M[14]= 0;

    M[3] = 0;
    M[7] = 0;
    M[11] = 0;
    M[15] = 1;
}

void  mat4roty(float M[], float  angle){

    M[0] = cos(angle);
    M[4] = 0;
    M[8] = sin(angle);
    M[12] = 0;

    M[1] = 0;
    M[5] = 1;
    M[9] = 0;
    M[13] = 0;

    M[2] = -sin(angle);
    M[6] = 0;
    M[10] = cos(angle);
    M[14]= 0;

    M[3] = 0;
    M[7] = 0;
    M[11] = 0;
    M[15] = 1;
}

void  mat4rotz(float M[], float  angle){

    M[0] = cos(angle);
    M[4] = -sin(angle);
    M[8] = 0;
    M[12] = 0;

    M[1] = sin(angle);
    M[5] = cos(angle);
    M[9] = 0;
    M[13] = 0;

    M[2] = 0;
    M[6] = 0;
    M[10] = 1;
    M[14]= 0;

    M[3] = 0;
    M[7] = 0;
    M[11] = 0;
    M[15] = 1;
}

void mat4translate(float M[] , float x , float y , float z){
    mat4identity(M);
    M[12] = x;
    M[13] = y;
    M[14] = z;
}

void mat4scale(float* m, float scale) {
    mat4identity(m); // First create identity matrix

    m[0] = scale;
    m[5] = scale;
    m[10] = scale;
}

void createIndexBuffer ( const unsigned int *data , int datasize )
{
GLuint bufferID ;
// Generate buffer , activate it and copy the data
glGenBuffers (1 , & bufferID );
// Activate ( bind ) the index buffer and copy data to it.
glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , bufferID );
// Present our vertex indices to OpenGL
glBufferData ( GL_ELEMENT_ARRAY_BUFFER , datasize , data , GL_STATIC_DRAW ) ;
}

void createVertexBuffer ( int location , int dimensions , const float *data , int datasize )
{
GLuint bufferID ;
// Generate buffer , activate it and copy the data
glGenBuffers (1 , & bufferID );
glBindBuffer ( GL_ARRAY_BUFFER , bufferID ) ;
glBufferData ( GL_ARRAY_BUFFER , datasize , data , GL_STATIC_DRAW );
// Tell OpenGL how the data is stored in our buffer
// Attribute location ( must match layout ( location =#) statement in shader )
// Number of dimensions (3 -> vec3 in the shader , 2-> vec2 in the shader ),
// type GL_FLOAT , not normalized , stride 0, start at element 0
glVertexAttribPointer ( location , dimensions , GL_FLOAT , GL_FALSE , 0, NULL ) ;
// Enable the attribute in the currently bound VAO
glEnableVertexAttribArray ( location ) ;
}

void  mat4perspective(float M[], float  vfov , float  aspect , float  znear , float  zfar){

    float f = cos(vfov/2)/sin(vfov/2);
    M[0] = f/aspect; M[4] = 0.0f; M[8] = 0.0f;                          M[12] = 0.0f;
    M[1] = 0.0f;     M[5] = f;    M[9] = 0.0f;                          M[13] = 0.0f;
    M[2] = 0.0f;     M[6] = 0.0f; M[10] = -(zfar+znear)/(zfar-znear);   M[14] = -(2*znear*zfar)/(zfar - znear);
    M[3] = 0.0f;     M[7] = 0.0f; M[11] = -1.0f;                        M[15] =0.0f;



}
/*
 * main(argc, argv) - the standard C++ entry point for the program
 */
int main(int argc, char *argv[]) {

    GLuint vertexArrayID;
    Shader myShader;

    float time;
    GLint location_time;
/*
    const GLuint index_array_data[] = {

        0,3,15, //fram
        0,15,12,

        4,6,18, //höger
        4,18,16,

        7,9,19, //baksida
        9,21,19,

        22,10,1,//vänster
        22,1,13,

        2,11,8,//under
        2,8,5,

        14,20,23,//top
        14,17,20


    };

    const GLfloat color_array_data [] = {
1.0f , 0.0f , 0.0f , //0 Red
1.0f , 1.0f , 1.0f , //1 1Green

1.0f , 1.0f , 0.0f ,
1.0f , 0.0f , 0.0f , //3

0.0f , 0.0f , 1.0f , //4
1.0f , 1.0f , 0.0f,  //5

0.0f , 0.0f , 1.0f ,
0.0f , 1.0f , 0.0f ,//7

1.0f , 1.0f , 0.0f ,
0.0f , 1.0f , 0.0f ,//9

1.0f , 1.0f , 1.0f ,
1.0f , 1.0f , 0.0f,

1.0f , 0.0f , 0.0f , //12 Red
1.0f , 1.0f , 1.0f , // Green

0.0f , 1.0f , 1.0f ,
1.0f , 0.0f , 0.0f , //15

0.0f , 0.0f , 1.0f , //16
0.0f , 1.0f , 1.0f,  //

0.0f , 0.0f , 1.0f ,//18
0.0f , 1.0f , 0.0f ,//19

0.0f , 1.0f , 1.0f ,
0.0f , 1.0f , 0.0f ,

1.0f , 1.0f , 1.0f ,
0.0f , 1.0f , 1.0f


};

GLfloat Translation[16];

GLfloat T[16] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0


};

GLfloat K[16] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0


};

const GLfloat vertex_array_data[] = {

    -1.0f, -1.0f, -1.0f,// V0
    -1.0f, -1.0f, -1.0f,// V1
    -1.0f, -1.0f, -1.0f,// V2

     1.0f, -1.0f, -1.0f,//V3
     1.0f, -1.0f, -1.0f,//V4
     1.0f, -1.0f, -1.0f,//V5

     1.0f, -1.0f,  1.0f, //V6
     1.0f, -1.0f,  1.0f, //V7
     1.0f, -1.0f,  1.0f, //V8

    -1.0f, -1.0f,  1.0f,//V9
   -1.0f, -1.0f,  1.0f,//10
    -1.0f, -1.0f,  1.0f,//11

    -1.0f,  1.0f, -1.0f,//V12
    -1.0f,  1.0f, -1.0f,//V13
    -1.0f,  1.0f, -1.0f,//V14

     1.0f,  1.0f, -1.0f, //V15
     1.0f,  1.0f, -1.0f, //16
     1.0f,  1.0f, -1.0f, //V17

     1.0f,  1.0f,  1.0f, //V18
     1.0f,  1.0f,  1.0f, //V19
     1.0f,  1.0f,  1.0f, //V20

    -1.0f,  1.0f,  1.0f, //V21
   -1.0f,  1.0f,  1.0f, //V22
   -1.0f,  1.0f,  1.0f//V23
};
*/


TriangleSoup myShape;
float rotateAroundX[16];
mat4identity(rotateAroundX);
float Translation[16];
float D[16];
mat4identity(D);
float P[16];
mat4identity(P);
float spin[16];
mat4identity(spin);
float MV[16];
mat4identity(MV);
mat4perspective(MV, M_PI/2, 1.0f,0.1f,100.0f);

/*
float rotationaroundy[16];
float viewportrotaion[16];

mat4mult(T,K,D);
mat4identity(rotationaroundy);
mat4identity(viewportrotaion);
mat4translate(Translation, 2.0f, 0.0f, 0.0f);




*/

    using namespace std;

	int width, height;

    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
	GLFWwindow *window;    // GLFW struct to hold information about the window

    // Initialise GLFW
    glfwInit();

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Make sure we are getting a GL context of at least version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Exclude old legacy cruft from the context. We don't need it, and we don't want it.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a square window (aspect 1:1) to fill half the screen height
    window = glfwCreateWindow(vidmode->height/2, vidmode->height/2, "GLprimer", NULL, NULL);
    if (!window)
    {
        cout << "Unable to open window. Terminating." << endl;
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required, or things will simply not work)
    glfwMakeContextCurrent(window);

    Utilities::loadExtensions();
    myShader.createShader("vertex.glsl", "fragment.glsl");

    GLint  location_P;
    GLint  location_MV;
    GLint  location_D;

    location_MV = glGetUniformLocation(myShader.programID , "MV");
    if(location_MV  ==  -1) { // If the  variable  is not found ,  -1 is  returned
       std::cout  << "Unable  to  locate  variable 'MV' in  shader!" << std::endl;}

    glUseProgram(myShader.programID); //  Activate  the  shader  to set its  variables
    glUniformMatrix4fv(location_MV , 1, GL_FALSE , MV); // Copy  the  value

    location_P = glGetUniformLocation(myShader.programID , "P");
    if(location_P  ==  -1) { // If the  variable  is not found ,  -1 is  returned
       std::cout  << "Unable  to  locate  variable 'P' in  shader!" << std::endl;}

    glUseProgram(myShader.programID); //  Activate  the  shader  to set its  variables
    glUniformMatrix4fv(location_P , 1, GL_FALSE , P); // Copy  the  value

    location_D = glGetUniformLocation(myShader.programID , "D");
    if(location_D  ==  -1) { // If the  variable  is not found ,  -1 is  returned
       std::cout  << "Unable  to  locate  variable 'D' in  shader!" << std::endl;}
    glUseProgram(myShader.programID); //  Activate  the  shader  to set its  variables
    glUniformMatrix4fv(location_D , 1, GL_FALSE , D);

    // Generate 1 Vertex array object , put the resulting identifier in vertexArrayID
glGenVertexArrays (1 , & vertexArrayID );
// Activate the vertex array object
glBindVertexArray ( vertexArrayID ) ;

// Generate buffers
/*
createVertexBuffer ( 0 , 3 , vertex_array_data , sizeof ( vertex_array_data ) );
createVertexBuffer ( 1 , 3 , color_array_data , sizeof ( color_array_data ) );

createIndexBuffer ( index_array_data , sizeof ( index_array_data ));

glBindVertexArray (0) ;
*/
    location_time = glGetUniformLocation(myShader.programID , "time");
    if(location_time  ==  -1) { // If the  variable  is not found ,  -1 is  returned
        cout  << "Unable  to  locate  variable'time'in  shader!" << endl;}



    // Show some useful information on the GL context
    cout << "GL vendor:       " << glGetString(GL_VENDOR) << endl;
    cout << "GL renderer:     " << glGetString(GL_RENDERER) << endl;
    cout << "GL version:      " << glGetString(GL_VERSION) << endl;
    cout << "Desktop size:    " << vidmode->width << "x" << vidmode->height << " pixels" << endl;

    // Get window size. It may start out different from the requested
    // size, and will change if the user resizes the window.
    glfwGetWindowSize( window, &width, &height );
    // Set viewport. This is the pixel rectangle we want to draw into.
    glViewport( 0, 0, width, height ); // The entire window

    glfwSwapInterval(0); // Do not wait for screen refresh between frames

glEnable(GL_CULL_FACE);



myShape.createBox(0.2f,0.2f,0.8f);
mat4translate(Translation,0.0f,0.0f,-2.0f);
    // Main loop
    while(!glfwWindowShouldClose(window))
    {
		// Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ---- Rendering code should go here ---- */





        time = (float)glfwGetTime();//  Number  of  seconds  since  the  program  was  started

        mat4identity(D);
        mat4roty(spin, time*M_PI/2);
        mat4rotx(rotateAroundX, time*M_PI/24);
        mat4mult(D,Translation,D);
        mat4mult(D,spin,D);
        mat4mult(D,rotateAroundX,D);


       // mat4identity(T);
       // mat4roty(T, time*M_PI/2);
        /*
        mat4roty(rotationaroundy,time*M_PI);
        mat4rotx(viewportrotaion, -M_PI/6.0f);


        mat4identity(D);

        mat4mult(D,viewportrotaion, D);
        mat4mult(D,rotationaroundy, D);
        mat4mult(D,Translation,D);

        //mat4roty(D,time*M_PI/2);

*/
        myShape.render();
        glUniformMatrix4fv(location_D , 1, GL_FALSE , D);


        glUseProgram(myShader.programID); //  Activate  the  shader  to set its  variables
        glUniform1f(location_time , time); // Copy  the  value to the  shader  program
        Utilities::displayFPS(window);
        // Activate the vertex array object we want to draw (we may have several )
        glUseProgram ( myShader . programID );
        glBindVertexArray ( vertexArrayID);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glCullFace(GL_BACK);


// Draw our triangle with 3 vertices .
// When the last argument of glDrawElements is NULL , it means
// " use the previously bound index buffer ". ( This is not obvious .)
// The index buffer is part of the VAO state and is bound with it.
glDrawElements ( GL_TRIANGLES , 36, GL_UNSIGNED_INT , NULL );

		// Swap buffers, i.e. display the image and prepare for next frame.
        glfwSwapBuffers(window);

		// Poll events (read keyboard and mouse input)
		glfwPollEvents();

        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
          glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }

    // Close the OpenGL window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
