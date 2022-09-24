#include "OpenGLManager.h"

#include "Matrix3D.h"
#include "Sphere.h"

#include <cstdio>
#include <iostream>


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}


int main(void)
{
    OpenGLManager openGLManager;

    Particule particule(Vecteur3D(-5, 0, 0), Vecteur3D(20, 20, 0), 1, 10);

    Sphere sphere(1.f, Vecteur3D(0.0f, 0.0f, 0.0f), 36, 18);

    openGLManager.initAndCreateWindow();
    
    Shader shader("./../../../src/Shaders/shader.vert", "./../../../src/Shaders/shader.frag");
    
    openGLManager.setKeyCallback(key_callback);

    openGLManager.setLightPosition(Vecteur3D(0, 0, 1000));

    openGLManager.setObject(sphere);

    openGLManager.setCamera(Camera(0.1, 100000, Vecteur3D(5, 5, 17), 90));

    openGLManager.loadVertices(sphere.getVertices(), sphere.getIndices(), shader.getIDProgram());
 
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(openGLManager.getWindow()))
    {
        particule.update();
        sphere.setPosition(particule.getPos());
        openGLManager.setObject(sphere);

        /* Render here */
        openGLManager.Render(shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(openGLManager.getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}