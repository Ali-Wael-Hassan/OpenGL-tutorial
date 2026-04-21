#pragma once

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
private:
    unsigned int id;

    // Compile Shader
    unsigned int compileShader(unsigned int type, const char* source);

    // Extract Code
    std::string readFile(const char* filePath);

public:
    // Initiate the Shaders
    Shader(const char * vertexPath, const char * fragmentPath);

    // Select this program
    void bind() const;

    // Diselect this program
    void unbind() const;

    // Get the id
    unsigned int getID() const;
    
};