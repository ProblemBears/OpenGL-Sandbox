#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    /* Initialize GLEW*/
    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, -0.5f,       0.0f, 0.0f, //0 Bottom Left
             0.5f, -0.5f,       1.0f, 0.0f, //1 Bottom Right
             0.5f,  0.5f,       1.0f, 1.0f, //2 Top Right
            -0.5f,  0.5f,       0.0f, 1.0f  //3 Top Left
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, sizeof(float) * 4 * 4);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/Bear.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            renderer.Draw(va, ib, shader);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}