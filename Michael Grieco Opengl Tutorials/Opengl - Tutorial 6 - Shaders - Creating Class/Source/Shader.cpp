#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    int success;
    char infolog[512];
     
    GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(id, 512, NULL, infolog);
        std::cout << "Shader Program Compile ERROR: " << std::endl << infolog << std::endl;
        
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate(){
    glUseProgram(id);
}

// Load Shader Src File
std::string Shader::loadShaderSrc(const char* filename){
    std::ifstream file(filename, std::ios::binary);

    if(file){
        std::string contents;
		file.seekg(0, std::ios::end);
		contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return(contents);
    }
    throw(errno);

}


GLuint Shader::compileShader(const char* filepath, GLenum type){
    int success;
    char infolog[522];

    GLuint ret = glCreateShader(type);
    std::string shaderSource = loadShaderSrc(filepath);
    const GLchar* shader = shaderSource.c_str();
    glShaderSource(ret, 1, &shader, NULL);
    glCompileShader(ret);

    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);

    if(!success){
       glGetShaderInfoLog(ret, 512, NULL, infolog);
       std::cout << "Vertex Shader Compile ERROR: " << std::endl << infolog << std::endl;
    }

    return ret;
}

void Shader::setMat4( const std::string& name, glm::mat4 val){
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}