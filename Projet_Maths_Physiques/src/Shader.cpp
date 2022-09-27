#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. On charge les codes sources vertex/fragment à partir du chemin de leur fichier
    /*std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    // on s'assure que l'objet ifstream peut renvoyer des exceptions:
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // on ouvre les fichiers
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;
        // lit le contenu des fichiers dans un Stream
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        // ferme les fichiers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // on convertit les Stream en String
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    */
    const char* vertexShaderCode =
        "#version 330 core\n"
        "uniform vec3 posLumiere;\n"
        "uniform vec3 posCamera;\n"
        "uniform mat4 MVP;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat3 normalMatrix;\n"

        "attribute vec3 normal;\n"
        "attribute vec3 vPos;\n"
        "attribute vec3 vCol;\n"

        "out vec3 d;\n"
        "out vec3 n;\n"
        "out vec3 r;\n"
        "out vec3 v;\n"

        "void main()\n"
        " {\n"
        "vec4 c1 = vec4(1, 0, 0, 0);\n"
        "vec4 c2 = vec4(0, 1, 0, 0);\n"
        "vec4 c3 = vec4(0, 0, 1, 0);\n"
        "vec4 c4 = vec4(2, 0, 0, 1);\n"
        "mat4 model2 = mat4(c1, c2, c3, c4);\n"
        "vec4 pos = modelMatrix * vec4(vPos, 1.0);\n"
        "gl_Position = MVP * vec4(vPos, 1.0);\n"
        "d = posLumiere - (pos.xyz / pos.w);\n"
        "n = normalMatrix * normal;\n"

        "v = posCamera - pos.xyz / pos.w;\n"
        "r = reflect(-d, n);\n"
        "};\n";
        
        //vertexCode.c_str();
    const char* fragmentShaderCode =
        "#version 330 core\n"
        "uniform vec3 coulLumiere;\n"
        "uniform vec3 coulObjet;\n"
        "uniform vec3 specLumiere;\n"
        "uniform vec3 specObjet;\n"
        "uniform float alpha;\n"

        "in vec3 d;\n"
        "in vec3 n;\n"
        "in vec3 r;\n"
        "in vec3 v;\n"

        " void main()\n"
        "{\n"

        "float valueC = -dot(normalize(n), normalize(d));\n"
        "float valueR = max(dot(normalize(r), normalize(v)), 0.0f);\n"

        "vec3 reflet = specObjet * specLumiere * pow(valueR, 10);\n"
        "vec3 couleur = coulObjet * coulLumiere * valueC;\n"

        "gl_FragColor = vec4(couleur + reflet + vec3(0.1, 0.25, 0.05), 1.0);\n"

        "};\n";
        
        //fragmentCode.c_str();

    // 2. on compile les shaders
    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);
    // On print les erreurs s'il y en a
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);
    // On print les erreurs s'il y en a
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // shader Program
    IDProgram_ = glCreateProgram();
    glAttachShader(IDProgram_, vertex);
    glAttachShader(IDProgram_, fragment);
    glLinkProgram(IDProgram_);
    // On print les erreurs s'il y en a
    glGetProgramiv(IDProgram_, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(IDProgram_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // on supprime les shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use()
{
    glUseProgram(IDProgram_);
}


//Les méthodes pour charger une variable uniforme : 

void Shader::setUniformBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(IDProgram_, name.c_str()), (int)value);
}
void Shader::setUniformInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(IDProgram_, name.c_str()), value);
}
void Shader::setUniform1f(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(IDProgram_, name.c_str()), value);
}

void Shader::setUniformMatrix4fv(const std::string& name, const GLfloat* matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(IDProgram_, name.c_str()),1, GL_FALSE, matrix);
}

void Shader::setUniformMatrix3fv(const std::string& name, const GLfloat* matrix) const
{
    glUniformMatrix3fv(glGetUniformLocation(IDProgram_, name.c_str()), 1, GL_FALSE, matrix);
}

void Shader::setUniform3f(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(IDProgram_, name.c_str()), x, y, z);
}
