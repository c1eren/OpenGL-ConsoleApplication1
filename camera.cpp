#include "constants.h"
#include "camera.h"

unsigned int Camera::camNumber = 0; // To set camId to new value every time

Camera::Camera(glm::vec3 camPosition, glm::vec3 camFront)
    : camYaw(yaw), camPitch(pitch), camZoom(zoom), camSensitivity(sensitivity), camSpeed(speed)
{
	this->camId = camNumber;
	camNumber++;

    updateCameraFrontVectors();
}

void Camera::processKeyPress(Direction dir)
{
    float velocity = camSpeed * deltaTime;

    if (dir == Direction::FORWARD)
    {
        if (camFPS)
        {
            cameraPos += glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)) * velocity; // This works for FPS mode. We set normalized direction values, but only add strength to chosen axis'.
        }
        else
            cameraPos += cameraFront * velocity;
    }
    if (dir == Direction::BACKWARD)
    {
        if (camFPS)
        {
            cameraPos -= glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)) * velocity;
        }
        else
        {
            cameraPos -= cameraFront * velocity;
        }
    }
    if (dir == Direction::LEFT)
    {
        cameraPos -= cameraRight * velocity;
        if (cameraRoll)
        {
            camRoll--;
            if (camRoll < -5.0f)
            {
                camRoll = -5.0f;
            }
        }
    }
    if (dir == Direction::RIGHT)
    {
        cameraPos += cameraRight * velocity;
        if (cameraRoll)
        {
            camRoll++;
            if (camRoll > 5.0f)
            {
                camRoll = 5.0f;
            }
        }
    }
}

void Camera::processMouseScroll(float yoffset)
{
    camZoom -= yoffset / camSensitivity;

    if (camZoom < 1.0f)
    {
        camZoom = 1.0f;
    }
    if (camZoom > 90.0f)
    {
        camZoom = 90.0f;
    }
}

void Camera::updateEulerValues(float xoffset, float yoffset)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camYaw += xoffset;
    camPitch += yoffset;

    // Pitch constraints
    if (camPitch > 89.0f)
    {
        camPitch = 89.0f;
    }
    if (camPitch < -89.0f)
    {
        camPitch = -89.0f;
    }

    updateCameraFrontVectors();
}

void Camera::updateCameraFrontVectors()
{
    glm::vec3 direction;

    direction.x = cos(glm::radians(camYaw)) * cos(glm::radians(camPitch));
    direction.y = sin(glm::radians(camPitch));
    direction.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
    cameraFront = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));                 // Get perpendicular axis, relative to the camera in the world
    
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront)); 

}


glm::mat4 Camera::getViewMatrix()
{

    if (cameraRoll && camRoll != 0.0f)
    {
        glm::vec3 finalRight = cameraRight;
        glm::vec3 finalUp    = cameraUp;

        //roll rotation on camerafront axis
        glm::mat4 rollRotation  = glm::mat4(1.0f);
        rollRotation            = glm::rotate(rollRotation, glm::radians(camRoll), cameraFront);
        finalRight              = glm::mat3(rollRotation) * cameraRight;
        finalUp                 = glm::mat3(rollRotation) * cameraUp;

        return glm::lookAt(cameraPos, cameraPos + cameraFront, finalUp);
    }



    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

