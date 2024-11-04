#ifndef SHADER_H
#define SHADER_H

// GLAD needs to be included to get the neccessary OPENGL headers
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // Program ID
    unsigned int ID;

    // Constructor reads and builds the shader
    Shader( const char* vertexPath, const char* fragmentPath);

    // Activate Shader
    void activate();

    // Set uniform variables to be pass into the shaders
    void setBool( const std::string &name, bool value) const;
    void setInt( const std::string &name, int value) const;
    void setFloat( const std::string &name, float value) const;

};

#endif