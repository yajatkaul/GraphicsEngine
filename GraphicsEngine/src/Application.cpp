#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

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

    glfwSwapInterval(1); //Vsync on

    /* Checking if glew is working fine IMPORTANT HAS TO BE ADDED AFTER CONTEXT*/
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    //Check GL version
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, -0.5f, //0
             0.5f, -0.5f, //1
             0.5f, 0.5f, //2
            -0.5f, 0.5f //3
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

    

        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/BasicShader.shader");
        shader.Bind();
   
        /*
        std::cout << "VERTEX" << std::endl;
        std::cout << source.VertexSource << std::endl;
        std::cout << "FRAGMENT" << std::endl;
        std::cout << source.FragmentSource << std::endl;
        */

        shader.SetUnifrom4f("u_Color", 0.0f, 0.8f, 1.0f, 1.0f);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        
        float r = 0.0f;
        float increment = 0.01f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            shader.SetUnifrom4f("u_Color", r, 0.0f, 1.0f, 1.0f);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f) {
                increment = -0.01f;
            }
            else if (r < 0.0f) {
                increment = 0.01f;
            }

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
