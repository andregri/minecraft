#include "camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera() :
    m_mouseX(0.0f), m_mouseY(0.0f),
    m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
    m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_firstMouseUpdate(true), m_yaw(-90.0f), m_pitch(),
    m_viewMat(glm::mat4(1.0f)) {}

void Camera::update(float deltaTime, const bool keys[], int winX, int winY, double mouseX, double mouseY) {
    glm::vec3 direction = updateDirection(winX, winY, mouseX, mouseY);
    m_cameraFront = glm::normalize(direction);

    float cameraSpeed = m_cameraSpeed * deltaTime;
    if (keys[GLFW_KEY_W] == GLFW_PRESS) {
        m_cameraPos += cameraSpeed * m_cameraFront;
    }
    if (keys[GLFW_KEY_S] == GLFW_PRESS) {
        m_cameraPos -= cameraSpeed * m_cameraFront;
    }
    if (keys[GLFW_KEY_A] == GLFW_PRESS) {
        m_cameraPos -= cameraSpeed * glm::normalize(glm::cross(m_cameraFront, m_cameraUp)); 
    }
    if (keys[GLFW_KEY_D] == GLFW_PRESS) {
        m_cameraPos += cameraSpeed * glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
    }

    m_viewMat = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

glm::mat4 Camera::getViewMatrix() {
    return m_viewMat;
}

glm::vec3 Camera::updateDirection(int winX, int winY, double mouseX, double mouseY) {
    if (m_firstMouseUpdate) {
        m_prevMouseX = mouseX;
        m_prevMouseY = mouseY;
        m_firstMouseUpdate = false; 
    }

    // Compute the movement of the mouse
    //float offsetX = mouseX - m_prevMouseX;
    //float offsetY = mouseY - m_prevMouseY;

    // Compute the movement of the mouse
    float offsetX = mouseX - 400.0f;
    float offsetY = mouseY - 300.0f;
    //std::cout << offsetX << " " << offsetY << " " << mouseX << " " << mouseY << " " << winX << " " << winY << std::endl;

    m_yaw   = (220.0f / 800.0f) * (offsetX + 400.0f) - 20.0f; // (-400;400) -> (-20;200)
    //m_yaw   = (178.0f / 800.0f) * (offsetX + 400.0f) + 1.0f; // (-400;400) -> (1;179)
    //m_yaw   = (-178.0f / 800.0f) * (offsetX - 400.0f) + 1.0f; // (-400,400) -> (179;1)
    //m_pitch = (178.0f / 600.0f) * (offsetY - 300.0f) + 89.0f;
    m_pitch = (-178.0f / 600.0f) * (offsetY - 300.0f) - 89.0f; // (-300;300)-> (89;-89)

    //offsetX *= m_mouseSensitivity;
    //offsetY *= m_mouseSensitivity;

    // Update view angles
    //m_yaw += offsetX;
    //m_pitch += offsetY;

    // Constraint camera movements so that direction is not parallel to cameraUp
    if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
    } else if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
    }
    
    // Update previous mouse position
    m_prevMouseX = mouseX;
    m_prevMouseY = mouseY;    

    // Compute direction
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    return direction;
}