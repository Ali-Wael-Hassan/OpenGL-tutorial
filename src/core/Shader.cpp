#include <core/Shader.h>
#include <utils/GLDebug.h>

unsigned int Shader::compileShader(unsigned int type, const char* source) {
    // Create Shader
    GLCall(unsigned int s = glCreateShader(type));
    
    // Give the Shader the source code
    GLCall(glShaderSource(s, 1, &source, nullptr));

    // Compile
    GLCall(glCompileShader(s));

    int result;
    // Get the Status of the compilation for the shader
    GLCall(glGetShaderiv(s, GL_COMPILE_STATUS, &result));

    // Failed to Compile
    if (result != GL_TRUE) {
        int length;

        // Gets the log length
        GLCall(glGetShaderiv(s, GL_INFO_LOG_LENGTH, &length));

        // Alocating the message buffer
        char *msg = (char*) alloca(length * sizeof(char));

        // Gets the Log info
        GLCall(glGetShaderInfoLog(s, length, &length, msg));

        // Loggin the Error
        std::cerr << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << msg << std::endl;

        // Deleting the Shader
        GLCall(glDeleteShader(s));

        return 0;
    }

    return s;
}

std::string Shader::readFile(const char* filePath) {
    // read the file as binary and point at the end
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return "";
    }

    // get file size (in bytes)
    std::streamsize size = file.tellg();

    // point to the start of the file
    file.seekg(0, std::ios::beg);

    // allocate the buffer
    std::string buffer;
    buffer.resize(size);

    if (file.read(&buffer[0], size)) {
        // close the file
        file.close();

        return buffer;
    }

    // close the file
    file.close();
    return "";
}

int Shader::getUniformLocation(const std::string& name) const {
    // Check if we already found this location before
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(id, name.c_str()));
    if (location == -1)
        LOG_WARN("Uniform '" + name + "' does not exist (or was optimized out)!");

    m_UniformLocationCache[name] = location;
    return location;
}

Shader::Shader(const char * vertexPath, const char * fragmentPath) {
    // Extracting the code
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);
    
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Creatge Program
    GLCall(id = glCreateProgram());

    // Compiling Vertex Shader
    GLCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource));
    // Compiling Fragment Shader
    GLCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource));

    // Link Vertex Shader with the program
    GLCall(glAttachShader(id, vs));
    // Link Fragment Shader with the program
    GLCall(glAttachShader(id, fs));
    // Link Window with the program
    GLCall(glLinkProgram(id));
    // Validate the program
    GLCall(glValidateProgram(id));

    // Deleting Shader Objects since it was already linked
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

void Shader::bind() const { GLCall(glUseProgram(id)); }

void Shader::unbind() const { GLCall(glUseProgram(0)); }

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

unsigned int Shader::getID() const { return id; }
