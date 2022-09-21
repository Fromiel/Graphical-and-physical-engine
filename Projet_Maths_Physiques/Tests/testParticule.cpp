#include "Particule.h"
using namespace std;

void display(Particule c) {
	cout << "Particule has position " << c.getPos() << " ; has velocity " << c.getVelocity() << " ; has acceleration " << c.getAcc() << "; has R = " << c.getRayon() << " ; has 1/m = " << c.getInverseMasse() << endl;
}

int main() {

	cout << "Début des tests" << endl;

	//Tests constructeurs
	cout << "Tests constructeurs" << endl;
	Vecteur3D pos(0,10,0);
	Vecteur3D vel(1, 1, 0);
	Particule c(pos, vel, 1, 2);
	
	display(c);

	Particule c2(c);

	cout << "Copy : " << endl;
	display(c2);

	//Tests setters

	cout << "Test setters" << endl;
	Vecteur3D newpos(1, 2, 1);
	Vecteur3D newvel(0, 0, 1);
	Vecteur3D newacc(0, 1, 0);
	c.setPos(newpos);
	c.setAcceleration(newacc);
	c.setVelocity(newvel);

	display(c);

	//Tests update position

	cout << "Test update with c2 : " << endl;
	display(c2);

	int limiter = 0;

	while (c2.getPos().get_y() > 1e-10 && limiter < 1000) {
		c2.update();
		//cout << "Position : " << c2.getPos() << endl;
		display(c2);
		limiter++;
	}

	return 0;
}