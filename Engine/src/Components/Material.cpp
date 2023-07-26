#include "Components/Material.h" 

Material::Material(Shader shader, Vecteur3D ambient, Vecteur3D specular, Vecteur3D diffuse, float alpha, float transparency) : shader_(shader), ambient_(ambient), specular_(specular), diffuse_(diffuse), alpha_(alpha), transparency_(transparency)
{

}

Material* Material::default_ = NULL;

Material& Material::getDefault()
{
	if (default_ == NULL)
		default_ = new Material(Shader("./Shaders/shader.vert", "./Shaders/shader.frag"));
	return *default_;
}