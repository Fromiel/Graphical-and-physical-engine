#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/// <summary>
/// Classe gérant les shaders (ici vertex et fragment shaders)
/// </summary>

class Shader
{
    private:
    
        GLuint IDProgram_; //L'id du programme

    public:
        Shader() {}
        /// <summary>
        /// Constructeur qui va lire les deux fichiers aux chemins mis en argument et qui va lire puis initialiser les shaders dans un programme
        /// </summary>
        /// <param name="vertexPath">Chemin du fichier pour le vertex shader</param>
        /// <param name="fragmentPath">Chemin du fichier pour le fragment shader</param>
        Shader(const char* vertexPath, const char* fragmentPath);

        /// <summary>
        /// Retourne l'id du programme
        /// </summary>
        /// <returns></returns>
        GLuint getIDProgram() const { return IDProgram_; }

        /// <summary>
        /// Active le programme utilisant ce shader
        /// </summary>
        void use();

        /// <summary>
        /// Permet de charger un booleen en variable uniforme au shader
        /// </summary>
        /// <param name="name">Nom de la variable uniforme</param>
        /// <param name="value">Valeur de la variable uniforme</param>
        void setUniformBool(const std::string& name, bool value) const;

        /// <summary>
        /// Permet de charger un entier en variable uniforme au shader
        /// </summary>
        /// <param name="name">Nom de la variable uniforme</param>
        /// <param name="value">Valeur de la variable uniforme</param>
        void setUniformInt(const std::string& name, int value) const;

        /// <summary>
        /// Permet de charger un float en variable uniforme au shader
        /// </summary>
        /// <param name="name">Nom de la variable uniforme</param>
        /// <param name="value">Valeur de la variable uniforme</param>
        void setUniform1f(const std::string& name, float value) const;

        /// <summary>
        /// Permet de charger une matrice 4x4 de float en variable uniforme au shader
        /// </summary>
        /// <param name="name">Nom de la variable uniforme</param>
        /// <param name="value">Valeur de la variable uniforme</param>
        void setUniformMatrix4fv(const std::string& name, const GLfloat* matrix) const ;

        /// <summary>
        /// Permet de charger une matrice 3x3 de float en variable uniforme au shader
        /// </summary>
        /// <param name="name">Nom de la variable uniforme</param>
        /// <param name="value">Valeur de la variable uniforme</param>
        void setUniformMatrix3fv(const std::string& name, const GLfloat* matrix) const ;

        /// <summary>
        /// Permet de charger un vec3 en variable uniforme au shader
        /// </summary>
        /// <param name="name">Nom de la variable uniforme</param>
        /// <param name="value">Valeur de la variable uniforme</param>
        void setUniform3f(const std::string& name, float x, float y, float z) const;
};

#endif