#ifndef MATERIAL_H
#define MATERIAL_H

#include "CoreECS/Coordinator.h"
#include "Shader.h"
#include "Maths/Vecteur3D.h"

/// <summary>
/// Component représentant le matériaux d'un objet
/// </summary>
class Material
{
	private:
		//Couleur du materiaux sous lumiere ambiante
		Vecteur3D ambient_;
		//Couleur de la réflexion de la lumiere à la surface
		Vecteur3D specular_;
		//Couleur du matériaux avec la lumiere diffuse
		Vecteur3D diffuse_;
		//Impact la taille du "rond de reflexion de la lumiere"
		float alpha_;
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
		Material(Shader shader, Vecteur3D ambient = Vecteur3D(1, 1, 1), Vecteur3D specular = Vecteur3D(1, 1, 1), Vecteur3D diffuse = Vecteur3D(1, 1, 1), float alpha = 32);

		/// <summary>
		/// Getter du shader
		/// </summary>
		/// <returns></returns>
		Shader getShader() const { return shader_; }

		/// <summary>
		/// Getter de ambient
		/// </summary>
		/// <returns></returns>
		Vecteur3D getAmbient() const { return ambient_; }

		/// <summary>
		/// Getter de specular
		/// </summary>
		/// <returns></returns>
		Vecteur3D getSpecular() const { return specular_; }

		/// <summary>
		/// Getter de diffuse
		/// </summary>
		/// <returns></returns>
		Vecteur3D getDiffuse() const { return diffuse_; }

		/// <summary>
		/// Getter de alpha
		/// </summary>
		/// <returns></returns>
		float getAlpha() const { return alpha_; }

		/// <summary>
		/// Setter du shader
		/// </summary>
		/// <param name="shader"></param>
		void setShader(Shader shader) { shader_ = shader; }

		/// <summary>
		/// Set ambient (chaque valeur du vecteur3D doit être entre 0 et 1)
		/// </summary>
		/// <param name="ambient"></param>
		void setAmbient(Vecteur3D ambient) { ambient = ambient_; }

		/// <summary>
		/// Set specular (chaque valeur du vecteur3D doit être entre 0 et 1)
		/// </summary>
		/// <param name="specular"></param>
		void setSpecular(Vecteur3D specular) { specular_ = specular; }

		/// <summary>
		/// Set diffuse (chaque valeur du vecteur3D doit être entre 0 et 1)
		/// </summary>
		/// <param name="diffuse"></param>
		void setDiffuse(Vecteur3D diffuse) { diffuse_ = diffuse; }

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