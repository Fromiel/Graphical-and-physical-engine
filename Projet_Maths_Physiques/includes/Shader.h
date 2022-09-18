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
public:
    
    unsigned int ID; //L'id du programme

    /// <summary>
    /// Constructeur qui va lire les deux fichiers aux chemins mis en argument et qui va lire puis initialiser les shaders dans un programme
    /// </summary>
    /// <param name="vertexPath">Chemin du fichier pour le vertex shader</param>
    /// <param name="fragmentPath">Chemin du fichier pour le fragment shader</param>
    Shader(const char* vertexPath, const char* fragmentPath);

    /// <summary>
    /// Active le programme utilisant ce shader
    /// </summary>
    void use();

    //Des fonctions permettant de charger des variables uniform au shader
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setUniform1f(const std::string& name, float value) const;
    void setUniformMatrix4fv(const std::string& name, const GLfloat* matrix) const ;
    void setUniformMatrix3fv(const std::string& name, const GLfloat* matrix) const ;
    void setUniform3f(const std::string& name, float x, float y, float z) const;
};

#endif