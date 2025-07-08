// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>

#include "camera.h"
#include "constants.h"
#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "textureClass.h"
#include "shapes.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float mix = 0.0f;
float mix_lateral = 0.0f;

Camera camera;

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

    //stbi image flip
    stbi_set_flip_vertically_on_load(true);

    // Hide and capture cursor when application has focus
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    Shader shader("res/shaders/shader.vs", "res/shaders/shader.frag");

 /*-----------------------------------------------------------------------------*/
 /*-----------------------------------------------------------------------------*/
    

    //Vertex Array Object
    VertexArrayObject VAO;
    
        //Vertex buffer object
        VertexBufferObject VBO;
        VBO.bufferData(cubeVert);

        //vertex attribute pointers
        VAO.setAttribPointer({ 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0 }); //pass in attribs struct for initialiser list
        VAO.setAttribPointer({ 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)) });

        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));   //starts 3 * float(components) in
      
        //Element buffer object
        ElementBufferObject EBO;
        EBO.bufferData(cubeInd);


    VAO.unbind();

    // Floor VAO test

    VertexArrayObject VAOFloor;
        VertexBufferObject VBOFloor;
        VBOFloor.bufferData(floorVert);
        VAOFloor.setAttribPointer({ 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0 }); 
        VAOFloor.setAttribPointer({ 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)) }); 
    VAOFloor.unbind();

    //textures
    Texture texture1({ "textures/container.jpg", GL_RGB, GL_TEXTURE_2D, GL_RGB });
    Texture texture2({ "textures/awesomeface.png", GL_RGB, GL_TEXTURE_2D, GL_RGBA });
    
    // Floor Texture
    Texture texture3({ "textures/wall.jpg", GL_RGB, GL_TEXTURE_2D, GL_RGB });

    glTextureParameteri(texture1.texId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture1.texId, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(texture2.texId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture2.texId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(texture3.texId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture3.texId, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
    shader.Use();
    shader.setInt("f_texture1", texture1.textureUnit); //set f_texture1 in the fragment shader to GL_TEXTURE_2D::GL_TEXTURE0
    shader.setInt("f_texture2", 1); // class textureUnit not working
    shader.setInt("f_texture3", 2); // Change these to texture class internal textureUnit value 

    /*-----------------------------------------------------------------------------*/

    //matrix/translation stuff
    /*
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    */

    //rotation and scaling
   // glm::mat4 trans = glm::mat4(1.0f); //initialise identity matrix
    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); //rotate on 'z' axis (that's what the vec3 with the 1.0 in 'z' does)
    //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); //scale by 0.5 on every axis

    //uniform
   /* GLint transformLoc = glGetUniformLocation(shader.m_Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    */
    //unsigned int transformLoc = glGetUniformLocation(shader.m_Program, "transform");
    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);


    //vector array
    std::array<glm::vec3, 30> cubePositions = {
        glm::vec3(-6.0f,  3.5f,  2.5f),
        glm::vec3(6.0f, -2.5f, -5.0f),
        glm::vec3(0.0f,  6.0f,  1.5f),
        glm::vec3(-7.0f,  1.5f, -3.0f),
        glm::vec3(4.0f, -6.0f,  2.0f),
        glm::vec3(-3.0f,  3.0f,  7.0f),
        glm::vec3(5.5f,  0.0f, -6.5f),
        glm::vec3(-6.5f, -4.5f,  4.5f),
        glm::vec3(2.5f,  4.0f, -1.5f),
        glm::vec3(-1.5f, -5.0f, -6.5f),
        
        glm::vec3(7.0f,  2.5f,  3.5f),
        glm::vec3(-3.5f, -7.0f,  0.0f),
        glm::vec3(1.5f,  7.0f, -2.5f),
        glm::vec3(-5.0f, -1.5f,  6.5f),
        glm::vec3(6.0f,  4.5f, -3.5f),
        glm::vec3(-1.5f, -2.0f,  5.5f),
        glm::vec3(4.0f, -7.0f, -1.5f),
        glm::vec3(-7.0f,  6.0f,  2.5f),
        glm::vec3(0.0f, -5.5f,  6.0f),
        glm::vec3(2.0f,  1.5f, -7.0f),
        
        glm::vec3(-6.5f,  7.0f, -3.5f),
        glm::vec3(5.0f, -3.5f,  6.0f),
        glm::vec3(-1.5f,  2.5f, -5.0f),
        glm::vec3(3.5f, -1.0f,  7.0f),
        glm::vec3(-2.5f, -6.0f,  3.5f),
        glm::vec3(7.0f,  3.0f,  0.0f),
        glm::vec3(-2.0f,  6.0f, -6.0f),
        glm::vec3(6.0f, -7.0f,  3.5f),
        glm::vec3(-4.0f,  0.0f, -7.0f),
        glm::vec3(0.0f, -3.0f,  5.0f)
    };

    /*-----------------------------------------------------------------------------*/

    // LookAt matrix
    glm::mat4 view;
    GLuint viewLoc = glGetUniformLocation(shader.m_Program, "view");

    glm::mat4 projection;
    GLuint projectionLoc = glGetUniformLocation(shader.m_Program, "projection");

    double currentTime = glfwGetTime();
    float currentFrame = glfwGetTime();     // get current time 

    // Camera style
    camera.camFPS = 1;

    while (!glfwWindowShouldClose(window))
    {
        //rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        //view matrix

        // Camera
        view = camera.getViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));



        //projection matrix
        projection = glm::perspective(glm::radians(camera.camZoom), (float)viewport_width / (float)viewport_height, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        VAOFloor.bind();

        glm::mat4 modelFloor = glm::mat4(1.0f);
        modelFloor = glm::translate(modelFloor, glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", modelFloor);
        shader.setInt("u_ObjectType", 1);

        //shader.setInt("f_texture1", 2); //set f_texture1 in the fragment shader to GL_TEXTURE_2D::GL_TEXTURE0

        glDrawArrays(GL_TRIANGLES, 0, 6);
        VAOFloor.unbind();



        //bind VAO
        VAO.bind();

        GLfloat f_mix = 0.0f;
        
        GLuint fmixLocation = glGetUniformLocation(shader.m_Program, "f_mix");
        glUniform1f(fmixLocation, f_mix);

                        //matrices

        //model matrix
        
        for (unsigned int i = 0; i < cubePositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i + 1);
            if (!(i % 2))
            {
                f_mix = 0.5f;
            }
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            
            shader.setMat4("model", model);
            shader.setInt("u_ObjectType", 0);

            glUniform1f(fmixLocation, f_mix);

            //glDrawArrays(GL_TRIANGLES, 0, 36);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            f_mix = 0.0f;
            
        }


        //GLint f_mixLocation = glGetUniformLocation(shader.m_Program, "f_mix");
        //glUniform1f(f_mixLocation, mix);

        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //unbind VAO
        VAO.unbind();

        //swap the bufferss
        glfwSwapBuffers(window);


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
            std::cout << "FPS: " << frameCount << std::endl;

            frameCount = 0;
            previousTime = currentTime;
        }

        

        //check and call events
        glfwPollEvents();  

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, // closing the application

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, GL_TRUE);
 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

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






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
