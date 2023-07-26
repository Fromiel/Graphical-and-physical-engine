#include <gtest/gtest.h>
#include "Components/Particule.h"

/*bool TestsParticule::constructor() {
	Vecteur3D acceleration = Vecteur3D(0, -9.81, 0);
	Vecteur3D pos_initiale = Vecteur3D(1, 2, 3);
	Vecteur3D vel_initiale = Vecteur3D(1, 2, 3);
	double r = 4;
	double m = 5;
	Particule particule = Particule(pos_initiale, vel_initiale, r, m);

	bool testsPass = true;

	if (particule.getPos().get_x() 			!= pos_initiale.get_x()	) testsPass = false;
	if (particule.getPos().get_y() 			!= pos_initiale.get_y()	) testsPass = false;
	if (particule.getPos().get_z() 			!= pos_initiale.get_z()	) testsPass = false;
	if (particule.getVelocity().get_x() 	!= vel_initiale.get_x()	) testsPass = false;
	if (particule.getVelocity().get_y() 	!= vel_initiale.get_y()	) testsPass = false;
	if (particule.getVelocity().get_z() 	!= vel_initiale.get_z()	) testsPass = false;
	if (particule.getAcc().get_x() 			!= acceleration.get_x()	) testsPass = false;
	if (particule.getAcc().get_y() 			!= acceleration.get_y()	) testsPass = false;
	if (particule.getAcc().get_z() 			!= acceleration.get_z()	) testsPass = false;
	if (particule.getRayon() 				!= r			) testsPass = false;
	if (particule.getInverseMasse() 		!= m			) testsPass = false;

	return testsPass;
}*/

TEST(test, testtesttest)
{
	EXPECT_TRUE(true);
}
