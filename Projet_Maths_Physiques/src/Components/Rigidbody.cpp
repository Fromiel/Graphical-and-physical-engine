#include "Components/Rigidbody.h"

Rigidbody::Rigidbody(Entity entityparent, float angularDamping, float invmasse, float linearDamping, ObjectTypeEnum type_objet) : entity(entityparent) {
	m_angularDamping = angularDamping;
	m_linearDamping = linearDamping;
	inverseMasse = invmasse;
	accel_lineaire = Vecteur3D(0, 0, 0);
	accel_rotation = Vecteur3D(0, 0, 0);
	std::vector<double> content = {};
	float scale_x,scale_y,scale_z = 0;
	switch (type_objet) {
		case SphereMesh:
			scale_x = 2/5*(1/inverseMasse)*pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_x(), 2);
			content = { scale_x,0,0,0,scale_x,0,0,0,scale_x };
			inertie = Matrix3D(content);
			break;
		case CubeMesh:
			scale_x = pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_x(), 2);
			scale_y = pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_y(), 2);
			scale_z = pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_z(), 2);
			content = {1/12*(1/inverseMasse)*(scale_y+scale_z),0,0,0,1/12*(1/inverseMasse)*(scale_x+scale_z),0,0,0,1/12*(1/inverseMasse)*(scale_x+scale_y)};
			inertie = Matrix3D(content);
			break;
		case CylinderMesh:
			scale_x = 1/12*(1/inverseMasse)* pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_z(), 2);
			scale_y = 1/2*(1/inverseMasse)* pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_x(), 2);
			scale_z = 1/4 * (1 / inverseMasse) * pow(Coordinator::getInstance()->getComponent<Transform>(entity).getScaling().get_x(), 2);
			content = {scale_x+scale_z,0,0,0,scale_y,0,0,0,scale_x+scale_z};
			inertie = Matrix3D(content);
			break;
		default:
			inertie = Matrix3D();
			std::cout << "Type de rigidbody non reconnu" << std::endl;
	}
	//content.push_back(0);
	//content.push_back(0);
	//content.push_back(0);
	std::vector<double> newcontent = { content[0],content[1],content[2],0,content[3],content[4],content[5],0,content[6],content[7],content[8],0 };
	Matrix34 newinertie(newcontent);
	Matrix34 transfo = Coordinator::getInstance()->getComponent<Transform>(entity).getModelMatrix();
	inertie_transfo = transfo * newinertie.inverse() * transfo.inverse();
	clearAccumulator();
}

/*Rigidbody::Rigidbody(const Rigidbody& rb) {
	m_linearDamping = rb.getLinearDamping();
	m_angularDamping = rb.getAngularDamping();
	m_forceAccum = rb.getForceAccum();
	m_torqueAccum = rb.getTorqueAccum();
	inverseMasse = rb.getinverseMasse();
	accel_lineaire = Vecteur3D(0, 0, 0);
	accel_rotation = Vecteur3D(0, 0, 0);
	inertie = rb.inertie;
	inertie_transfo = rb.inertie_transfo;
}*/

Vecteur3D Rigidbody::getPos() const
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getPosition();
}

Quaternion Rigidbody::getOrientation() const 
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getOrientation();
}

Matrix34 Rigidbody::getModelMatrix() const
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getModelMatrix();
}


void Rigidbody::setVelocity(const Vecteur3D Velocity) {
	velocity = Velocity;
}

void Rigidbody::setRotation(const Vecteur3D Rotation)
{
	rotation = Rotation;
}

void Rigidbody::addForce(const Vecteur3D& force) {

	m_forceAccum = m_forceAccum + force;

}

void Rigidbody::addForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldpoint) {
	m_forceAccum = m_forceAccum + force;
	m_torqueAccum = m_torqueAccum + vectorial_product(worldpoint,force);
}

void Rigidbody::addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localpoint) {
	Vecteur3D w_point = convertToWorld(localpoint);
	addForceAtPoint(force, w_point);
}

void Rigidbody::clearAccumulator() {
	m_forceAccum = Vecteur3D(0, 0, 0);
	m_torqueAccum = Vecteur3D(0, 0, 0);
}

void Rigidbody::CalculateDerivatedData() {
	// On normalise l'orientation

	Quaternion recup = getOrientation();
	recup.normalize();

	Coordinator::getInstance()->getComponent<Transform>(entity).setOrientation(recup);

	// TODO : Calculer la nouvelle valeur de I^(-1)
	Matrix34 transfo = Coordinator::getInstance()->getComponent<Transform>(entity).getModelMatrix();

	//std::cout << "Matric de transfo = " << transfo << std::endl;
	//std::cout << "inertie_transfo init = " << inertie_transfo << std::endl;
	//std::cout << "Matric Inverse = " << transfo.inverse() << std::endl;

	//TODO : Faire la formule
	//inertie_transfo = transfo * inertie.invert() * transfo.inverse();
}

void Rigidbody::Integrate(float duration) {
	accel_lineaire = inverseMasse * m_forceAccum;
	accel_rotation = inertie_transfo * m_torqueAccum;

	if (m_torqueAccum.get_x() == 0 && m_torqueAccum.get_y() == 0 && m_torqueAccum.get_z() == 0) accel_rotation = Vecteur3D(0, 0, 0);

	//DEBUG ROTATION
	//std::cout << "torque accum = " << m_torqueAccum << std::endl;
	//std::cout << "inertie_transfo = " << inertie_transfo << std::endl;
	
	// Vitesse
	velocity = velocity + (accel_lineaire * duration);
	velocity = velocity * pow(m_linearDamping, duration);

	//DEBUG ROTATION
	//std::cout << "previous rotation : " << rotation << std::endl;

	rotation = rotation + accel_rotation * duration;


	//DEBUG ROTATION
	//std::cout << "new rotation : " << rotation << std::endl;

	rotation = rotation * pow(m_angularDamping, duration);

	// Position 
	Vecteur3D pos_res = getPos();
	pos_res = pos_res + velocity * duration;
	Coordinator::getInstance()->getComponent<Transform>(entity).setPosition(pos_res);

	Quaternion ori = getOrientation();

	ori.updateByAngularVelocity(rotation, duration);

	Coordinator::getInstance()->getComponent<Transform>(entity).setOrientation(ori);

	CalculateDerivatedData();
	clearAccumulator();

	std::cout << "Nouvelle position du rigidbody : " << getPos() << std::endl;
	//std::cout << "Nouvelle rotation du rb : " << getRotation() << std::endl;
}

Vecteur3D Rigidbody::convertToWorld(const Vecteur3D& localPoint)
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getModelMatrix() * localPoint;
}

