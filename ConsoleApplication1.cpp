// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"  

#include <iostream>
#include <array>

#include "camera.h"
#include "constants.h"
#include "shader.h"
#include "model.h"
#include "VAO.h"
#include "VBO.h"
#include "shapes.h"


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

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    // Shader loading
    Shader modelShader("res/shaders/modelShader.vs", "res/shaders/modelShader.fs");
    Shader cubeShader("res/shaders/lightCubeShader.vs", "res/shaders/lightCubeShader.frag");
    //Shader modelShader("C:/programming/opengl/proj_1/ConsoleApplication1/res/shaders/modelShader.vs", "C:/programming/opengl/proj_1/ConsoleApplication1/res/shaders/modelShader.fs");

    // Model loading
    Model backpack("models/backpack/backpack.obj");
    //Model tree("models/Tree1/Tree1.obj");


    cubeShader.Use();

    // Point light colors
    glm::vec3 lightColor
    //(1.0f, 1.0f, 1.0f);
    (0.70f, 0.67f, 0.53f);
    //(0.39, 0.58, 0.93);
    //(0.50, 0.45, 0.25);

    cubeShader.setVec3("lightColor", lightColor);
    
    modelShader.Use();

    // Point light properties
    modelShader.setVec3("plProperties.ambient", glm::vec3(0.05 * lightColor.x, 0.05 * lightColor.y, 0.05 * lightColor.z));
    modelShader.setVec3("plProperties.diffuse", glm::vec3(lightColor)); // Point light col
    modelShader.setVec3("plProperties.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    modelShader.setFloat("plProperties.constant", 1.0f);
    modelShader.setFloat("plProperties.linear", 0.09f);
    modelShader.setFloat("plProperties.quadratic", 0.032f);

    // Point light positions
    std::vector<glm::vec3> pLightPositions = {
        glm::vec3(0.0f, 0.0f, 2.0f),
        glm::vec3(1.2f, 1.0f, 0.0f),
        glm::vec3(-0.3f, -0.5f, -3.0f)
    };

    for (unsigned int i = 0; i < pLightPositions.size(); i++)
    {
        std::string name = "pointLights[" + std::to_string(i) + "].position";
        modelShader.Use();
        modelShader.setVec3(name.c_str(), pLightPositions[i]);
    }

    //modelShader.setVec3("pointLights[0].position", pLightPositions[0]);
    // Material properties
    modelShader.setFloat("shininess", 32); // Don't set to 0

    // Point light visual cube
    VertexArrayObject(VAO);
    VAO.bind();
    VertexBufferObject(VBO);
    VBO.bufferData(cubeStandard);
    VAO.setAttribPointer({ 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0 });
    VAO.unbind();

    // FPS and timekeeping
    double currentTime = glfwGetTime();
    float currentFrame = currentTime;     // get current time 
    const float radius = 2.0f;
    const float rotateSpeed = 10.0f;

    // Camera style
    camera.camFPS = 0;
    camera.camZoom = 60.0f;

    // View, projection, model matrices
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Rendering commands here
        //glClearColor(-lightColor.x, -lightColor.y, -lightColor.z, 1.0f);
        //glClearColor(0.70f, 0.67f, 0.53f, 1.0f); sage color
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // View & Projection transformations
        view = camera.getViewMatrix();
        projection = glm::perspective(glm::radians(camera.camZoom), (float)viewport_width / (float)viewport_height, 0.1f, 100.0f);
        
        for (unsigned int i = 0; i < pLightPositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            cubeShader.Use();
            model = glm::translate(model, pLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            cubeShader.setMat4("view", view);
            cubeShader.setMat4("projection", projection);
            cubeShader.setMat4("model", model);
            VAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        VAO.unbind();


        modelShader.Use();
        modelShader.setMat4("view", view);
        modelShader.setMat4("projection", projection); 
        glm::mat3 normalMatrix = glm::mat3(1.0);

        // Render loaded models
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians((float)currentTime) * rotateSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
        modelShader.setMat3("normalMatrix", normalMatrix);
        modelShader.setMat4("model", model);

        backpack.Draw(modelShader);

        //model = glm::mat4(1.0f);
        //model = translate(model, glm::vec3(3.0f, -1.0f, 3.0f));
        //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        //normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
        //modelShader.setMat3("normalMatrix", normalMatrix);
        //modelShader.setMat4("model", model);
        //
        //tree.Draw(modelShader); // Draws with the backpacks textures for some reason lmao

        // Swap the buffers
        glfwSwapBuffers(window);

        
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
