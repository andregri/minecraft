#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

class Camera {
    public:
        Camera();
        void update(float deltaTime, const bool keys[], int winX, int winY, double mouseX, double mouseY);

        // Getters
        glm::mat4 getViewMatrix();

    private:
        double m_mouseX;
        double m_mouseY;
        double m_prevMouseX;
        double m_prevMouseY;

        glm::vec3 m_cameraPos;
        glm::vec3 m_cameraFront;
        glm::vec3 m_cameraUp;

        bool m_firstMouseUpdate;
        float m_yaw;
        float m_pitch;

        glm::mat4 m_viewMat;

        const float m_cameraSpeed = 50.0f;
        const float m_mouseSensitivity = 0.01f;

        glm::vec3 updateDirection(int winX, int winY, double mouseX, double mouseY);
};

#endif