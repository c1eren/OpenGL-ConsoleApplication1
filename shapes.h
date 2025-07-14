#pragma once
#include <array>
#include <glad/glad.h>


std::array<GLfloat, 32> squareVert = {
    // Position          // Colors            // Texture Coords
    0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,   // Top Right
    0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,   // Bottom Right
   -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,   // Bottom Left
   -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f    // Top Left
};

std::array<GLuint, 6> squareInd = {
        0,  1, 3, //First Triangle
        1, 2, 3  //Second Triangle
};

std::array<GLfloat,  120> cubeVert = {

  // Position             // Texture Coords
  
    // Back plane
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,   // back bot left
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,   // back bot right 
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,   // back top right
 //  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,   // back top right again
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,   // back top left
 // -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,   // back bot left again

    // Front plane
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,   // front bot left
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,   // front bot right
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,   // front top right
 //  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,   // front top right again
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,   // front top left
 // -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,   // front bot left again

    // Side left plane
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  // top left front
    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  // top left back
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  // bot left back
 // -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  // bot left front
 // -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

    // Side right plane
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
 //  0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
 //  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

     // Bottom plane
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
 //  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
 // -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,

    // Top plane
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
 //  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f
 // -0.5f,  0.5f, -0.5f,  0.0f,  1.0f

};

std::array<GLuint, 36> cubeInd = {
    // Back
    0,  1, 3,
    1, 2, 3,

    // Front
    4, 5, 7,
    5, 6, 7,

    // Left
    8, 9,  11,
    9,  10,  11,

    // Right
    12,  13,  15,
    13,  14,  15,

    // Bottom
    16,  17,  19,
    17,  18,  19,

    // Top
    20, 21, 23,
    21, 22, 23
};

std::array<GLfloat, 30> floorVert = {
     10.5f,  0.0f,  10.5f,  10.0f,  0.0f,   // Front Right
     10.5f,  0.0f, -10.5f,  10.0f,  10.0f,  // Back Right
    -10.5f,  0.0f,  10.5f,  0.0f,   0.0f,  // Front Left
                                    
     10.5f,  0.0f, -10.5f,  10.0f,  10.0f,  // Back Right
    -10.5f,  0.0f, -10.5f,  0.0f,   10.0f,  // Back Left
    -10.5f,  0.0f,  10.5f,  0.0f,   0.0f    // Front Left
};

std::array<GLfloat, 30> flatSquareVert = {
    // Position     // Texture Coords
 0.5f,  0.5f,  0.0f,  1.0f,  1.0f,   // Top Right
 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   // Bottom Right
  -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Top Left

   0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   // Bottom Right
-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,   // Bottom Left
-0.5f,  0.5f,  0.0f,  0.0f,  1.0f    // Top Left
};

std::array<GLfloat,  108> cubeStandard = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

std::array<GLfloat, 288> cubeNormals {
// positions         // normals           // texture coords
-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
-0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

-0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
-0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
-0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
-0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
-0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

std::array<GLfloat, 48> squareNormals{
    // Position          // Normals           // TexCoords
    -10.5f,  0.0f, -10.5f,  0.0f,  1.0f,  0.0f,  0.0f,  10.0f,
     10.5f,  0.0f, -10.5f,  0.0f,  1.0f,  0.0f,  10.0f,  10.0f,
     10.5f,  0.0f,  10.5f,  0.0f,  1.0f,  0.0f,  10.0f,  0.0f,
     10.5f,  0.0f,  10.5f,  0.0f,  1.0f,  0.0f,  10.0f,  0.0f,
    -10.5f,  0.0f,  10.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -10.5f,  0.0f, -10.5f,  0.0f,  1.0f,  0.0f,  0.0f,  10.0f
};