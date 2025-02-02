#include "Components/Light.h"

Light::Light(Vector3D color, Vector3D specular) : color_(color), specular_(specular)
{

}

void Light::setColor(const Vector3D& color, bool IsBetweenOAnd1)
{ 
	if (IsBetweenOAnd1)
	{
		if (color.get_x() > 1.0f || color.get_x() < 0.0f || color.get_y() > 1.0f || color.get_y() < 0.0f || color.get_z() > 1.0f || color.get_z() < 0.0f)
			throw "Color not in the good format";
		color_ = color;
	}
	else
	{
		if (color.get_x() > 255 || color.get_x() < 0.0f || color.get_y() > 255 || color.get_y() < 0.0f || color.get_z() > 255 || color.get_z() < 0.0f)
			throw "Color not in the good format";

		color_ = Vector3D(color.get_x() / 255.0f, color.get_y() / 255.0f, color.get_z() / 255.0f);
	}
}