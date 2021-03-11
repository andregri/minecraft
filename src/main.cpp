#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../external/stb/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "shader.h"
#include "quad.h"
#include "texture.h"

bool Keys[1024] = {false};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main(void)
{
    constexpr float WINDOW_WIDTH = 800;
    constexpr float WINDOW_HEIGHT = 600;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Template", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    glfwSetKeyCallback(window, key_callback);


    /* Create a shader */
    Shader shader = Shader("../common/vertex.shader", "../common/fragment.shader");

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -100.0f), // Camera position in World Space
        glm::vec3(0.0f, 0.0f, 0.0f),    // and looks at the origin
        glm::vec3(0.0f, 1.0f, 0.0f)     // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * model;
    shader.Use();
    shader.SetUniformMatrix4f("mvp", mvp);

    Quad quad(16.0f, 16.0f);
    quad.init();

    Quad quad2(16.0f, 16.0f, glm::vec3(20.0f, 20.0f, 0.0f));
    quad2.init();
    
    Texture texture;
    texture.init();
    texture.loadData("../resources/200905210302_terrain.png");

    // deltaTime variables
    // -------------------
    float frameRate = 60.0f;
	float timeStep = 1.0f / frameRate;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;

        if (deltaTime >= timeStep) {
            lastFrame = currentFrame;

            /* Poll for and process events */
            glfwPollEvents();

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glActiveTexture(GL_TEXTURE0);
            texture.bind();
            shader.SetUniform1i("ourTexture", 0);
            quad.draw();
            quad2.draw();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }
    }

    quad.destroy();
    texture.destroy();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Keys[key] = false;
    }
}