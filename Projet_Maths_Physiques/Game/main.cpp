#include "OpenGLManager.h"

#include "Matrix3D.h"
#include "Matrix4D.h"
#include "Sphere.h"
#include "Cube.h"
#include "Scene.h"
#include "GameObject.h"

#include <cstdio>
#include <iostream>


static Particule particule1(Vecteur3D(-5, 0, 0), Vecteur3D(20, 20, 0), 1, 10);
static Particule particule2(Vecteur3D(-5, 0, 0), Vecteur3D(40, 40, 0), 1, 20);
static Particule particule3(Vecteur3D(-5, 0, 0), Vecteur3D(10, 10, 0), 1, 5);

void createParticule(int i) {
    Sphere sphereMesh(1, Vecteur3D(-5, 0, 0));
    Particule p(particule1);
    switch (i) {
    case 1:
        break;
    case 2:
        p = particule2;
        break;
    case 3:
        p = particule3;
        break;
    default:
        break;
    }
    GameObject sphere(sphereMesh, p);
    OpenGLManager::getInstance()->addGameObject(sphere);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        createParticule(1);
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        createParticule(2);
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        createParticule(3);
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
    //------------------initialisation------------------------

    OpenGLManager* openGLManager = OpenGLManager::getInstance();

    Scene scene(Camera(0.1, 10000, Vecteur3D(5, 5, 25), 90), Light(Vecteur3D(0, 0, 1000)));

    //Particule particule = askUser();

    Sphere sphereMesh(1, Vecteur3D(-5, 0, 0));

    Cube cubeMesh(1, Vecteur3D(0, 0, 0), Vecteur3D(200, 0.01, 200));

    //GameObject sphere(sphereMesh, particule);
    GameObject cube(cubeMesh);

    scene.addGameObject(cube);
    //scene.addGameObject(sphere);

    openGLManager->initAndCreateWindow();
    
    Shader shader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
    
    openGLManager->setKeyCallback(key_callback);

    openGLManager->setIdProgram(shader.getIDProgram());

    openGLManager->loadScene(scene);

    clock_t current_ticks, delta_ticks;
    double frameRate = 1.0 / 60.0;

    //----------------Fin initialisation--------------------


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(openGLManager->getWindow()))
    {
        current_ticks = clock();

        /*if (openGLManager->getScene().getGameObjects()[1].getMesh().getPosition().get_y() >= 0) {
            std::cout << "Update Particle" << std::endl;
            openGLManager->updateScene(frameRate);
        }
        else {
            particule = askUser();
            Sphere sMesh(1, Vecteur3D(-5, 0, 0));
            GameObject s(sMesh, particule);
            openGLManager->setGameObject(1, s);
            current_ticks = clock();
        }*/

        openGLManager->updateScene(frameRate);

        //openGLManager.getScene().applyForces(frameRate);
        /* Render here */
        openGLManager->Render(shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(openGLManager->getWindow());

        /* Poll for and process events */
        glfwPollEvents();

        /* Frame Rate Update */
        delta_ticks = clock() - current_ticks;
        frameRate = (double)delta_ticks / (double)CLOCKS_PER_SEC;

    }

    return 0;
}
