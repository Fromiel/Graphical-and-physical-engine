#include "OpenGLManager.h"

#include "Matrix3D.h"
#include "Sphere.h"
#include "Scene.h"

#include <cstdio>
#include <iostream>


static Particule particule1(Vecteur3D(-5, 0, 0), Vecteur3D(20, 20, 0), 1, 10);
static Particule particule2(Vecteur3D(-5, 0, 0), Vecteur3D(40, 40, 0), 1, 20);
static Particule particule3(Vecteur3D(-5, 0, 0), Vecteur3D(10, 10, 0), 1, 5);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}

Particule askUser() {
    int user_input;
    std::cout << "Quelle particule souhaitez vous utiliser ? \n1 = Basique\n2 = Soft\n3 = Lourde\n " << std::endl;
    std::cin >> user_input;
    switch (user_input) {
    case 2:
        return particule2;
        break;
    case 3:
        return particule3;
        break;
    default:
        return particule1;
        break;
    }
}


int main(void)
{
    //initialisation

    OpenGLManager openGLManager;

    Scene scene(Camera(0.1, 100000, Vecteur3D(5, 5, 17), 90), Light(Vecteur3D(0, 0, 1000)));

    Particule particule = askUser();

    Sphere sphere(1, Vecteur3D(-5, 0, 0), particule.getVelocity(), 1 / particule.getInverseMasse());

    scene.addGameObject(sphere);

    openGLManager.initAndCreateWindow();
    
    Shader shader("./../../../src/Shaders/shader.vert", "./../../../src/Shaders/shader.frag");
    
    openGLManager.setKeyCallback(key_callback);

    openGLManager.setIdProgram(shader.getIDProgram());

    openGLManager.loadScene(scene);

    clock_t current_ticks, delta_ticks;
    double frameRate = 1.0 / 60.0;

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


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(openGLManager.getWindow()))
    {
        current_ticks = clock();
       
        if (openGLManager.getScene().getGameObjects()[0].getPosition().get_y() >= 0) {
            std::cout << "Update Particle" << std::endl;
            openGLManager.updateScene(frameRate);
        }
        else {
            particule = askUser();
            Sphere s(1, Vecteur3D(-5, 0, 0), particule.getVelocity(), 1 / particule.getInverseMasse());
            openGLManager.setGameObject(0, s);
            current_ticks = clock();
        }

        //openGLManager.getScene().applyForces(frameRate);
        /* Render here */
        openGLManager.Render(shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(openGLManager.getWindow());

        /* Poll for and process events */
        glfwPollEvents();

        /* Frame Rate Update */
        delta_ticks = clock() - current_ticks;
        frameRate = (double)delta_ticks / (double)CLOCKS_PER_SEC;

    }

    return 0;
}