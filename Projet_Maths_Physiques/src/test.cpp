#include "OpenGLManager.h"

#include "Matrix_Full.h"
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
    /* Vecteur3D test1(1, 2, 3);
    Vecteur3D test2(4, 5, 6);
    
    Vecteur3D test_copie(test1);
    double res = test1.norm();
    double res2 = test1.norm_squared();
    test1 = test1.normalized();
    test2 = test2.scalar_multiplication(2);
    std::cout << test_copie << std::endl;
    std::cout << res << std::endl;
    std::cout << res2 << std::endl;
    std::cout << test1 << std::endl;
    std::cout << test2 << std::endl;

    Vecteur3D test_plus = test1 + test2;
    Vecteur3D test_moins = test1 - test2;
    Vecteur3D test_fois = test1 * test2;
    double test_ps = scalar_product(test1, test2);
    Vecteur3D test_pv = vectorial_product(test1, test2);
    std::cout << test_plus << std::endl;
    std::cout << test_moins << std::endl;
    std::cout << test_fois << std::endl;
    std::cout << test_ps << std::endl;
    std::cout << test_pv << std::endl; */

    OpenGLManager openGLManager;

    Sphere sphere(0.2f, Vecteur3D(0.0f, 0.0f, 0.0f), 36, 18);

    openGLManager.initAndCreateWindow();
    
    Shader shader("./../../../src/Shaders/shader.vert", "./../../../src/Shaders/shader.frag");
    
    openGLManager.setKeyCallback(key_callback);

    openGLManager.setLightPosition(Vecteur3D(0, 0, 0.2));

    openGLManager.loadVertices(sphere.getVertices(), sphere.getIndices(), shader.ID);
 
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(openGLManager.getWindow()))
    {

        /* Render here */
        openGLManager.Render(shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(openGLManager.getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}