// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"  

#include <iostream>
#include <array>
#include <map>

#include "camera.h"
#include "constants.h"
#include "shader.h"
#include "model.h"
#include "cube.h"
#include "VAO.h"
#include "VBO.h"
#include "shapes.h"
#include "helper_functions.h"
#include "skybox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool mouseInWindow = 1;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));

int main()
{
    //initialistion boilerplate
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
    unsigned int viewport_width = 800;
    unsigned int viewport_height = 600;
    glViewport(0, 0, viewport_width, viewport_height);

    //intialisation boilerplate

    //glfw callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);

    //stbi image flip
    stbi_set_flip_vertically_on_load(true);

    // Hide and capture cursor when application has focus
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::vector<std::string> texPaths = {
        "textures/container2_diffuse.png"
    };

    // Model loading
    Model backpack("models/backpack/backpack.obj");
    Cube cube(cubeNormalsNoInd, texPaths);

    // Shader loading
    Shader shader("res/shaders/simple.vs", "res/shaders/simple.fs");
    Shader viewNorm("res/shaders/viewNormals.vs", "res/shaders/viewNormals.fs", "res/shaders/viewNormals.gs");

    // Vertex data
    //float points[] = {
    //-0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // top-left
    // 0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // top-right
    // 0.5f, -0.5f,  0.0f,  0.0f,  1.0f, // bottom-right
    //-0.5f, -0.5f,  1.0f,  1.0f,  0.0f  // bottom-left
    //};
    //
    //
    //GLuint VAO, VBO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //
    //glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    //
    //// Vertex positions
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    //
    //glBindVertexArray(0);

    // Uniform buffer
    unsigned int UBO;
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::mat3x4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4) + sizeof(glm::mat3x4));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)viewport_width / (float)viewport_height, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // FPS and timekeeping
    double currentTime = glfwGetTime();
    float currentFrame = currentTime;     // get current time 
    const float radius = 2.0f;
    const float rotateSpeed = 10.0f;

    // Camera style
    camera.camFPS = 0;
    camera.camZoom = 60.0f;


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
    //glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    const float speed = 10.0f;


/*#####################################################################################################################################################*/
    // RENDER LOOP
/*#####################################################################################################################################################*/


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Send view matrix data to uniform buffer at offset = sizeof(projection matrix)
        glm::mat4 view = camera.getViewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glm::mat4 model = glm::mat4(1.0);
        model = glm::rotate(model, glm::radians((float)(currentTime * speed)), glm::vec3(1.0f, 1.0f, 0.0f));
        shader.setMat4("model", model);
        backpack.Draw(shader);

        // Send normal matrix to uniform block inside vs
        viewNorm.setMat4("model", model);
        glm::mat3x4 paddedNormal = glm::mat3x4(glm::transpose(glm::inverse(view * model))); // This is important, adhere to UBO alignment please
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat3x4), glm::value_ptr(paddedNormal));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        backpack.Draw(viewNorm);

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 3.0f));
        model = glm::rotate(model, glm::radians((float)(currentTime * speed)), glm::vec3(1.0f, 1.0f, 0.0f));
        shader.setMat4("model", model);
        cube.Draw(shader);

        // Send normal matrix to uniform block inside vs
        viewNorm.setMat4("model", model);
        paddedNormal = glm::mat3x4(glm::transpose(glm::inverse(view * model))); // This is important, adhere to UBO alignment please
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat3x4), glm::value_ptr(paddedNormal));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        cube.Draw(viewNorm);
    

        // Swap the buffers
        glfwSwapBuffers(window);

        //------------------------------------------------------------------------------------------------------------------------------//
        
        // Get Framerate
        currentFrame = glfwGetTime();           // get current time 
        deltaTime = currentFrame - lastFrame;   // difference between the time now, and the time it was when we rendered the last frame  
        lastFrame = currentFrame;

        // Measure speed
        currentTime = glfwGetTime();
        frameCount++;
        // If a second has passed.
        if (currentTime - previousTime >= 1.0)
        {
            // Display the frame count here any way you want.
            std::cout << "                                                                  FPS: " << frameCount << std::endl; // 17 tabs across

            frameCount = 0;
            previousTime = currentTime;
        }


        // Check and call events
        glfwPollEvents();

    }

/*#####################################################################################################################################################*/
    // END RENDER LOOP
/*#####################################################################################################################################################*/

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, // closing the application

    // Utility
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.processKeyPress(Direction::FORWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.processKeyPress(Direction::BACKWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.processKeyPress(Direction::LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.processKeyPress(Direction::RIGHT);
    }

    // Mouse context
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        if (mouseInWindow)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouseInWindow = 0;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            mouseInWindow = 1;
        }

    }

    // Flashlight
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        if (camera.flashLightOn)
        {
            camera.flashLightOn = 0;
        }
        else
        {
            camera.flashLightOn = 1;
        }
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (camera.firstMouse)
    {
        camera.lastX = xpos;
        camera.lastY = ypos;
        camera.firstMouse = 0;
    }

    float xoffset = xpos - camera.lastX;           // This frames x-coord, minus the last frames x-coord
    float yoffset = camera.lastY - ypos;           // reversed: y ranges bottom to top
    camera.lastX = xpos;
    camera.lastY = ypos;
    camera.updateEulerValues(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll((float)yoffset);
}



/*
Inversing matrices is a costly operation for shaders, so wherever possible try to avoid
doing inverse operations since they have to be done on each vertex of your scene. For
learning purposes this is fine, but for an efficient application you’ll likely want to calculate
the normal matrix on the CPU and send it to the shaders via a uniform before drawing
(just like the model matrix).
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
