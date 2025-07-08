//vertex data
GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f,   //Top Right
    0.5f, -0.5f, 0.0f,  //Bottom Right
    -0.5f, -0.5f, 0.0f, //Bottom Left
    -0.5f, 0.5f, 0.0f   //Top Left
};

/*GLfloat vertices[] = {
    //first triangle
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};*/
float vertices[] = {

    // Position          // Texture Coords

      // Back plane
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // back bot left
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // back bot right 
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // back top right
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // back top right again
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   // back top left
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // back bot left again

      // Front plane
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // front bot left
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // front bot right
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // front top right
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // front top right again
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // front top left
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // front bot left again

      // Side left plane
      -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  // top left front
      -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  // top left back
      -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  // bot left back
      -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

      // Side right plane
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

       // Bottom plane
      -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,

      // Top plane
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f

};
