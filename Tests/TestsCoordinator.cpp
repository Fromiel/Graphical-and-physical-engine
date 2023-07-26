#include <gtest/gtest.h>

#include "CoreECS/Coordinator.h"
#include "Components.h"
#include "Systems/Time.h"


/*void setUp() {
    Coordinator::resetInstance();
}*/


TEST(testtestffff, TestCoordinator_1)
{
    EXPECT_TRUE(true);
}

/*TEST(registerComponent, TestCoordinator_1) {
    {
        setUp();
        Coordinator* c = Coordinator::getInstance();
        c->registerComponent<Camera>();
        c->registerComponent<Cube>();
        c->registerComponent<Light>();
        c->registerComponent<Object3D>();
        c->registerComponent<Sphere>();
        c->registerComponent<Transform>();

        EXPECT_TRUE(c->getComponentType<Camera>() == 0);
        //EXPECT_TRUE(c->getComponentType<Cube>() == 1);
        //EXPECT_TRUE(c->getComponentType<Light>() == 2);
        //EXPECT_TRUE(c->getComponentType<Object3D>() == 3);
        //EXPECT_TRUE(c->getComponentType<Sphere>() == 4);
        //EXPECT_TRUE(c->getComponentType<Transform>() == 5);

    }
}

TEST(signature, TestCoordinator_1)
{
    setUp();
    Coordinator* c = Coordinator::getInstance();
    Entity e1 = c->createEntity();
    Entity e2 = c->createEntity();
    c->registerComponent<Transform>();
    c->registerComponent<Object3D>();

    auto s = c->registerSystem<Time>();

    Signature signature;
    signature.set(c->getComponentType<Transform>());

    c->setSystemSignature<Time>(signature);

    Transform t;
    c->addComponent<Transform>(e1, t);

    Object3D o;
    c->addComponent<Object3D>(e1, o); //devrait s'ajouter à la signature

    c->addComponent<Object3D>(e2, o); //ne devrait pas s'ajouter à la signature

    EXPECT_TRUE(s->getEntities().size() == 1);

    c->destroyEntity(e1); //on enleve e1 donc le systeme ne devrait plus posséder d'entités

    EXPECT_TRUE(s->getEntities().size() == 0);
}

TEST(hasComponent, TestCoordinator_1)
{
    setUp();
    Coordinator* c = Coordinator::getInstance();
    Entity e1 = c->createEntity();

    c->registerComponent<Camera>();
    c->registerComponent<Object3D>();

    Object3D o;
    c->addComponent<Object3D>(e1, o);

    EXPECT_TRUE(c->hasComponent<Object3D>(e1));
    EXPECT_FALSE(c->hasComponent<Camera>(e1));
}*/

