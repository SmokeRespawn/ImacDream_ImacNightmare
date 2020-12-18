#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

/*#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>*/ //Peut être utile pour la suite

#include "shader.hpp"
#include "mesh.hpp"
#include "model.hpp"

//#include <glm/glm.hpp> Peut être nécessaire pour les structures glm (glm::vec3 par exemple)

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Insérer un nom de projet cool", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}