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
    
    Shader shader("./../../../src/Shaders/shader.vert", "./../../../src/Shaders/shader.frag");
    
    openGLManager->setKeyCallback(key_callback);

    openGLManager->setIdProgram(shader.getIDProgram());

    openGLManager->loadScene(scene);

    clock_t current_ticks, delta_ticks;
    double frameRate = 1.0 / 60.0;

    //----------------Fin initialisation--------------------

/*  
    Test Vecteur3D :
    
    Vecteur3D test1(1, 2, 3);
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
    std::cout << test_pv << std::endl; 

    Test Matrix4D :

    Matrix4D test_mat_0;
    std::vector<double> content = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    Matrix4D test_mat_1(content);
    content = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
    Matrix4D test_mat_2(content);
    Matrix4D test_mat_copie(test_mat_1);

    std::cout << test_mat_0 << std::endl;
    std::cout << test_mat_1 << std::endl;
    std::cout << test_mat_2 << std::endl;
    std::cout << test_mat_copie << std::endl;

    std::vector<double> test_getter = test_mat_copie.getContentAsStdVector();
    for (double i : test_getter) {
        std::cout << i << std::endl;
    }
    std::cout << test_mat_1(1, 1) << std::endl;
    double test_get_elt = test_mat_1(2, 3);
    std::cout << test_get_elt << std::endl;
    Matrix4D test_mat_copie_2 = test_mat_copie;
    std::cout << test_mat_copie << std::endl;
    std::vector<double> test_1 = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    Matrix4D test_mat_plus(test_1);
    test_mat_plus += test_mat_plus;
    Matrix4D test_mat_moins(test_1);
    test_mat_moins -= test_mat_moins;
    std::cout << test_mat_plus << std::endl;
    std::cout << test_mat_moins << std::endl;

    Matrix4D test_transpose = test_mat_1.transpose();
    Matrix4D test_identity = Matrix4D::identity();
    Matrix4D test_invert = test_identity.invert();
    Vecteur3D vect_3(1, 2, 3);
    Matrix4D test_translate = Matrix4D::translation(vect_3);
    Matrix4D test_scaling = Matrix4D::scaling(vect_3);
    Matrix4D test_projection = Matrix4D::projectionMatrix(M_PI, 1, 1, 500);
    std::cout << test_transpose << std::endl;
    std::cout << test_invert << std::endl;
    std::cout << test_identity << std::endl;
    std::cout << test_translate << std::endl;
    std::cout << test_scaling << std::endl;
    std::cout << test_projection << std::endl;

    Matrix4D test_plus = test_mat_1 + test_mat_2;
    Matrix4D test_moins = test_mat_1 - test_mat_2;
    Matrix4D test_fois_1 = test_mat_1 * 4;
    Matrix4D test_fois_2 = 4 * test_mat_1;
    Matrix4D test_fois_3 = test_mat_1 * test_mat_2;

    bool test_egalite = (test_fois_1 == test_fois_2);
    std::cout << test_plus << std::endl;
    std::cout << test_moins << std::endl;
    std::cout << test_fois_1 << std::endl;
    std::cout << test_fois_2 << std::endl;
    std::cout << test_fois_3 << std::endl;
    std::cout << test_egalite << std::endl; */



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