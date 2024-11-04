#include "Shader.h"


Shader::Shader( const char* vertexPath, const char* fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    // ################ Get shader file data

    try
    {
    
        // Open shader files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Read file data in streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // Convert streams into strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_OPEN_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // ################ Compile shaders

    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPLIATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPLIATION_FAILED\n" << infoLog << std::endl;
    }


    // ################ Linke Shaders to Shader Program


    ID = glCreateProgram();

    glAttachShader( ID, vertexShader);
    glAttachShader( ID, fragmentShader);
    glLinkProgram( ID );

    // Print linking errors
    glGetProgramiv( ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog( ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << std::endl;
    }

    // Delete Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ################ Create shaders
    
}

void Shader::activate()
{
    glUseProgram( ID );
}

void Shader::setBool( const std::string &name, bool value) const
{
    glUniform1i( glGetUniformLocation( ID, name.c_str()), (int)value);
}

void Shader::setInt( const std::string &name, int value) const
{
    glUniform1i( glGetUniformLocation( ID, name.c_str()), value);
}

void Shader::setFloat( const std::string &name, float value) const
{
    glUniform1f( glGetUniformLocation( ID, name.c_str()), value);
}

void Shader::setMat4( const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv( glGetUniformLocation( ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3( const std::string &name, const glm::vec3 &vec) const
{
    glUniform3fv( glGetUniformLocation( ID, name.c_str()), 1, &vec[0]);
}