#pragma once

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Shader {
private:
    unsigned int id;
    // Cache for Uniform Locations
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
    // Compile Shader
    unsigned int compileShader(unsigned int type, const char* source);

    // Extract Code
    std::string readFile(const char* filePath);

    // Getter for UniformLocation internally
    int getUniformLocation(const std::string& name) const;

public:
    // Initiate the Shaders
    Shader(const char * vertexPath, const char * fragmentPath);

    // Select this program
    void bind() const;

    // Diselect this program
    void unbind() const;

    // Set Uniforms
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void setUniform1i(const std::string& name, int value);

    // Get the id
    unsigned int getID() const;
    
};