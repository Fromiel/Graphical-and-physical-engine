#ifndef MATERIAL_H
#define MATERIAL_H

#include "CoreECS/Coordinator.h"
#include "Shader.h"
#include "Maths/Vector3D.h"

/// <summary>
/// Component repr�sentant le mat�riaux d'un objet
/// </summary>
class Material
{
	private:
		//Couleur du materiaux sous lumiere ambiante
		Vector3D ambient_;
		//Couleur de la r�flexion de la lumiere � la surface
		Vector3D specular_;
		//Couleur du mat�riaux avec la lumiere diffuse
		Vector3D diffuse_;
		//Impact la taille du "rond de reflexion de la lumiere"
		float alpha_;
		//Transparence du material
		float transparency_;
		//Shader
		Shader shader_;

	public:
		Material() {}
		/// <summary>
		/// Constructeur de Material
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="ambient"></param>
		/// <param name="specular"></param>
		/// <param name="diffuse"></param>
		/// <param name="alpha"></param>
		Material(Shader shader, Vector3D ambient = Vector3D(1, 1, 1), Vector3D specular = Vector3D(1, 1, 1), Vector3D diffuse = Vector3D(1, 1, 1), float alpha = 32, float transparency = 1.0f);

		/// <summary>
		/// Getter du shader
		/// </summary>
		/// <returns></returns>
		Shader getShader() const { return shader_; }

		/// <summary>
		/// Getter de ambient
		/// </summary>
		/// <returns></returns>
		Vector3D getAmbient() const { return ambient_; }

		/// <summary>
		/// Getter de specular
		/// </summary>
		/// <returns></returns>
		Vector3D getSpecular() const { return specular_; }

		/// <summary>
		/// Getter de diffuse
		/// </summary>
		/// <returns></returns>
		Vector3D getDiffuse() const { return diffuse_; }

		/// <summary>
		/// Getter de alpha
		/// </summary>
		/// <returns></returns>
		float getAlpha() const { return alpha_; }

		/// <summary>
		/// Getter de transparency
		/// </summary>
		/// <returns></returns>
		float getTransparency() const { return transparency_; }

		/// <summary>
		/// Setter du shader
		/// </summary>
		/// <param name="shader"></param>
		void setShader(Shader shader) { shader_ = shader; }

		/// <summary>
		/// Set ambient (chaque valeur du vecteur3D doit �tre entre 0 et 1)
		/// </summary>
		/// <param name="ambient"></param>
		void setAmbient(Vector3D ambient) { ambient = ambient_; }

		/// <summary>
		/// Set specular (chaque valeur du vecteur3D doit �tre entre 0 et 1)
		/// </summary>
		/// <param name="specular"></param>
		void setSpecular(Vector3D specular) { specular_ = specular; }

		/// <summary>
		/// Set diffuse (chaque valeur du vecteur3D doit �tre entre 0 et 1)
		/// </summary>
		/// <param name="diffuse"></param>
		void setDiffuse(Vector3D diffuse) { diffuse_ = diffuse; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="alpha"></param>
		void setAlpha(float alpha) { alpha_ = alpha; }



	//Static
	private:
		//Materiaux par defaut
		static Material* default_;

	public:
		/// <summary>
		/// Retourne le materiaux par defaut
		/// </summary>
		/// <returns></returns>
		static Material& getDefault();
};


#endif