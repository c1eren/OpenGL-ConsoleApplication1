/*---------------------------------------------------------*/

    //vertex
const char* vertexShaderSource1 = "#version 460 core\n"
"layout(location = 0) in vec3 position;\n"
"out vec4 vertexColor;\n"
"void main(){\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"   vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"}";

//const char* src = vertexShaderSource.c_str();

vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource1, NULL);
glCompileShader(vertexShader);

//check shader compilation
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

if (!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX1::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
}

//fragment1
const char* fragmentShaderSource1 = "#version 460 core\n"
"in vec4 vertexColor;\n"
"out vec4 color;\n"
"void main(){\n"
"   color = vertexColor;\n"
"}";

fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
glCompileShader(fragmentShader);

glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

if (!success)
{
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT1::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
}

//shader program1
GLuint shaderProgram1;
shaderProgram1 = glCreateProgram();
glAttachShader(shaderProgram1, vertexShader);
glAttachShader(shaderProgram1, fragmentShader);
glLinkProgram(shaderProgram1);

glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
if (!success)
{
    glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" <<
        infoLog << std::endl;
}

//delete shaders
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

/*---------------------------------------------------------*/

GLfloat vertices1[] = {
    //second triangle
    0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -1.0f, 0.0f,0.0f
};

//triangle 2 
GLuint VAO1;
glGenVertexArrays(1, &VAO1);

glBindVertexArray(VAO1);

GLuint VBO1;
glGenBuffers(1, &VBO1);
glBindBuffer(GL_ARRAY_BUFFER, VBO1);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);

glBindVertexArray(0);

//in render loop
glUseProgram(shaderProgram1);

glBindVertexArray(VAO1);
glDrawArrays(GL_TRIANGLES, 0, 3);
glBindVertexArray(0);

/*--------------------------------------------------------------------------*/
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

int main()
{
    //initialistion boilerplate
    std::cout << "Hello World!\n";
    if (glfwInit() == NULL)
    {
        std::cout << "Window initialisation bungled mate" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "howdy partner", nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Window create fail!" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    //this piece of code allows us to use OpenGL functions
    //only call once in the main code
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl; //printing the version 

    /*
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    */

    //viewport
    glViewport(0, 0, 800, 600);

    //intialisation boilerplate

    glfwSetKeyCallback(window, key_callback);

    /*-----------------------------------------------------------------------------*/

       //shader
   /*
       //vertex
      const char* vertexShaderSource = "#version 460 core\n"
          "layout(location = 0) in vec3 position;\n"
          "out vec4 vertex_Position;\n"
          "void main(){\n"
          "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
          "    vertex_Position = gl_Position;\n"
          "}";

      //const char* src = vertexShaderSource.c_str();

       GLuint vertexShader;
       vertexShader = glCreateShader(GL_VERTEX_SHADER);
       glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
       glCompileShader(vertexShader);

       //check shader compilation
       GLint success;
       GLchar infoLog[512];
       glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

       if (!success)
       {
           glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
           infoLog << std::endl;
       }

       //fragment
       const char* fragmentShaderSource = "#version 460 core\n"
           "in vec4 vertex_Position;\n"
           "out vec4 color;\n"
           "uniform vec4 ourColor;\n"
           "void main(){\n"
           "   color = vertex_Position + 0.2;\n"
           "}";

       GLuint fragmentShader;
       fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
       glCompileShader(fragmentShader);

       glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

       if (!success)
       {
           glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
           infoLog << std::endl;
       }

       //shader program
       GLuint shaderProgram;
       shaderProgram = glCreateProgram();
       glAttachShader(shaderProgram, vertexShader);
       glAttachShader(shaderProgram, fragmentShader);
       glLinkProgram(shaderProgram);

       glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
       if (!success)
       {
           glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" <<
           infoLog << std::endl;
       }

       //delete shaders
       glDeleteShader(vertexShader);
       glDeleteShader(fragmentShader);
       */

       /*-----------------------------------------------------------------------------*/

    Shader shader("res/shaders/shader.vs", "res/shaders/shader.frag");

    /*-----------------------------------------------------------------------------*/

       //vertex data
       /*GLfloat vertices[] = {
           0.5f, 0.5f, 0.0f,   //Top Right
           0.5f, -0.5f, 0.0f,  //Bottom Right
           -0.5f, -0.5f, 0.0f, //Bottom Left
           -0.5f, 0.5f, 0.0f   //Top Left
       };*/

    GLfloat vertices[] = {
        //first triangle
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };

    //indices data
    GLuint indices[] = {
        0, 1, 3, //First Triangle
        1, 2, 3  //Second Triangle
    };

    //Vertex Array Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    //bind vertex array object
    glBindVertexArray(VAO);

    //Vertex buffer object
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Element buffer object
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);




    while (!glfwWindowShouldClose(window))
    {
        //check and call events
        glfwPollEvents();

        //rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        //uniform

        //make a changing colour variable
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue));

        //get location and set uniform value
        /*
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */
        GLint offsetLocation = glGetUniformLocation(shader.m_Program, "offset");
        glUniform1f(offsetLocation, greenValue);

        //draw the dang triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //swap the bufferss
        glfwSwapBuffers(window);

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, // closing the application

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

//----

double cursor_xpos;
double cursor_ypos;

glfwGetCursorPos(window, &cursor_xpos, &cursor_ypos);
//std::cout << "Cursor Position at (" << (float)cursor_xpos / 800 << " : " << (float)cursor_ypos / 600 << std::endl;
GLuint cursorPosLocation = glGetUniformLocation(shader.m_Program, "cursorXY");
glUniform2f(cursorPosLocation, ((float)cursor_xpos / 800), ((float)cursor_ypos / 600));

//----

/*-----------------------------------------------------------------------------*/

    //shader
/*
    //vertex
   const char* vertexShaderSource = "#version 460 core\n"
       "layout(location = 0) in vec3 position;\n"
       "out vec4 vertex_Position;\n"
       "void main(){\n"
       "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
       "    vertex_Position = gl_Position;\n"
       "}";

   //const char* src = vertexShaderSource.c_str();

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //check shader compilation
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }

    //fragment
    const char* fragmentShaderSource = "#version 460 core\n"
        "in vec4 vertex_Position;\n"
        "out vec4 color;\n"
        "uniform vec4 ourColor;\n"
        "void main(){\n"
        "   color = vertex_Position + 0.2;\n"
        "}";

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }

    //shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" <<
        infoLog << std::endl;
    }

    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    */

    /*-----------------------------------------------------------------------------*/

 //make a changing colour variable
GLfloat timeValue = glfwGetTime();
GLfloat offsetValue = (sin(timeValue));
GLint offsetLocation = glGetUniformLocation(shader.m_Program, "offset");
glUniform1f(offsetLocation, offsetValue);

glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
trans = glm::rotate(trans, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

//uniforms
unsigned int transformLoc = glGetUniformLocation(shader.m_Program, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

float t_offset = (float)glfwGetTime();
float s_offset = (sin(t_offset));
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(s_offset, s_offset, 0.0f));
trans = glm::rotate(trans, t_offset, glm::vec3(0.0f, 0.0f, 1.0f));

float t_offset = (float)glfwGetTime();
float s_offset = (sin(t_offset));
glm::mat4 trans1 = glm::mat4(1.0f);
trans1 = glm::translate(trans1, glm::vec3(s_offset * -1, s_offset, 0.0f));
trans1 = glm::rotate(trans1, t_offset, glm::vec3(0.0f, 0.0f, 1.0f));
trans1 = glm::scale(trans1, glm::vec3(s_offset * -1, s_offset, 0.0f));
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans1));
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


//Vertex Array Object
GLuint VAO;
glGenVertexArrays(1, &VAO);

//bind vertex array object
glBindVertexArray(VAO);

//Vertex buffer object
GLuint VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//vertex attribute pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);                       //we have 5 * float(components)
//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));   //starts 3 * float(components) in
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));   //starts 3 * float(components) in

glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);
glEnableVertexAttribArray(2);

//Element buffer object
GLuint EBO;
glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glBindVertexArray(0);

float camX = sin(glfwGetTime()) * radius;
float camZ = cos(glfwGetTime()) * radius;
float camY = sin(glfwGetTime()) * radius;
view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(-3.0f, 3.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f));

// Camera 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // cameraTarget (what's right in front of us)
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX = 400; // Center of screen, so half the window values
float lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
float roll = 0.0f;

bool firstMouse = 1;
const float sensitivity = 0.1f;


// Initial cursor jump negation
if (firstMouse)
{
    lastX = xpos;
    lastY = ypos;
    firstMouse = 0;
}

float xoffset = xpos - lastX; // This frames x-coord, minus the last frames x-coord
float yoffset = lastY - ypos; // reversed: y ranges bottom to top
lastX = xpos;
lastY = ypos;

xoffset *= sensitivity;
yoffset *= sensitivity;

yaw += xoffset;
pitch += yoffset;

// Pitch constraints
if (pitch > 89.0f)
{
    pitch = 89.0f;
}
if (pitch < -89.0f)
{
    pitch = -89.0f;
}

// Create direction vector, and apply to cameraFront (which is already part of view matrix in render loop)
direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
direction.y = sin(glm::radians(pitch));
direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
cameraFront = glm::normalize(direction); // Sets cameraFront to our new coordinate directions


// Yaw:   x and z
// Pitch: y and z
// Roll:  y and x 

const float cameraSpeed = 200.0f * deltaTime; // adjust accordingly
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, worldUp)); // Get perpendicular axis, relative to the camera in the world

glm::vec3 flatFront = glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));
glm::vec3 flatRight = glm::normalize(glm::cross(flatFront, worldUp)); // FPS implementation

/*
glm::mat4 model = glm::mat4(1.0f);
//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
GLuint modelLoc = glGetUniformLocation(shader.m_Program, "model");
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
*/

// Camera

// Camera position in world space
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

// What the camera is looking at
//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

// Figure out camera direction (normalised so no strength, only direction)
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

// Get "up" vector in world space
//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

// Cross product direction vector and up, to get perpendicular ("right") x-axis vector
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); //normalize only gives us direction

// Do the same for worldUp using cross product of cameras x-axis
//glm::vec3 worldUp = glm::cross(cameraDirection, cameraRight); //products are already normalized

// The above lines are just for learning, glm::lookAt does all this automatically with a Position, Target, and Up(worldspace) vector


    //set the texture filtering/wrapping options (on currently bound texture)
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTextureParameteri(texture2, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTextureParameteri(texture2, GL_TEXTURE_MAG_FILTER, GL_NEAREST); probably use glTextureParameter() from now on pls


//vector array
std::array<glm::vec3, 30> cubePositions = {
    glm::vec3(-6.0f, 3.5f,  2.5f),
    glm::vec3(6.0f, 2.5f, -5.0f),
    glm::vec3(0.0f, 6.0f,  1.5f),
    glm::vec3(-7.0f, 1.5f, -3.0f),
    glm::vec3(4.0f, 6.0f,  2.0f),
    glm::vec3(-3.0f, 3.0f,  7.0f),
    glm::vec3(5.5f, 0.0f, -6.5f),
    glm::vec3(-6.5f, 4.5f,  4.5f),
    glm::vec3(2.5f,  4.0f, -1.5f),
    glm::vec3(-1.5f, 5.0f, -6.5f),

    glm::vec3(7.0f,  2.5f,  3.5f),
    glm::vec3(-3.5f, 7.0f,  0.0f),
    glm::vec3(1.5f,  7.0f, -2.5f),
    glm::vec3(-5.0f, 1.5f,  6.5f),
    glm::vec3(6.0f,  4.5f, -3.5f),
    glm::vec3(-1.5f, 2.0f,  5.5f),
    glm::vec3(4.0f, 7.0f, -1.5f),
    glm::vec3(-7.0f,  6.0f,  2.5f),
    glm::vec3(0.0f, 5.5f,  6.0f),
    glm::vec3(2.0f,  1.5f, -7.0f),

    glm::vec3(-6.5f,  7.0f, -3.5f),
    glm::vec3(5.0f, 3.5f,  6.0f),
    glm::vec3(-1.5f,  2.5f, -5.0f),
    glm::vec3(3.5f, 1.0f,  7.0f),
    glm::vec3(-2.5f, 6.0f,  3.5f),
    glm::vec3(7.0f,  3.0f,  0.0f),
    glm::vec3(-2.0f,  6.0f, -6.0f),
    glm::vec3(6.0f, 7.0f,  3.5f),
    glm::vec3(-4.0f,  0.0f, -7.0f),
    glm::vec3(0.0f, 3.0f,  5.0f)
};


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

GLuint VAO, VBO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(GL_ARRAY_BUFFER, cubeNormals.size() * sizeof(float), &cubeNormals[0], GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeInd.size() * sizeof(unsigned int), &cubeInd[0], GL_STATIC_DRAW);

// Vertex positions
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
// Vertex normals
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
// Vertex texture coords
glEnableVertexAttribArray(2);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

glBindVertexArray(0);

GLuint VAO, VBO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(GL_ARRAY_BUFFER, squareBlade.size() * sizeof(float), &squareBlade[0], GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, squareInd.size() * sizeof(unsigned int), &squareInd[0], GL_STATIC_DRAW);

// Vertex positions
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
// Vertex normals
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

glBindVertexArray(0);



glDisable(GL_CULL_FACE);
// Windows
std::map<float, glm::vec3> windowPosSorted;
for (unsigned int i = 0; i < windowPos.size(); i++)
{
    float distance = glm::length(camera.cameraPos - windowPos[i]);
    windowPosSorted[distance] = windowPos[i];
}

for (std::map<float, glm::vec3>::reverse_iterator it = windowPosSorted.rbegin(); it != windowPosSorted.rend(); it++)
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, it->second);
    depthShader.setMat4("model", model);
    o_window.Draw(depthShader);
}