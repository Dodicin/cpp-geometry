#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Setting core profile
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

    // Sync with refresh rate
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
       -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
       -0.5f,  0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Vertex buffer, layout and vertex array
    VertexBuffer vb(positions, 4 * 2 *sizeof(float));
    VertexArray va;
    VertexBufferLayout layout;
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    // Index buffer
    IndexBuffer ib(indices, 6);

    // Reads shaders
    Shader shader("res/shaders/basic.shader");
    shader.bind();
    
    // Set uniform
    shader.setUniform4f("u_Color",  0.2f, 0.3f, 0.8f, 1.0f);
   
    // Unbind everything to use vertex arrays
    vb.unbind();
    ib.unbind();
    va.unbind();
    shader.unbind();

    // Renderer
    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
        
        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.draw(va, ib, shader);

        if(r>1.0f)
            increment = -0.05f;
        else if(r < 0.0f)
            increment = 0.05f;

        r += increment;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}