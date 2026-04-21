#include <core/Shader.h>

unsigned int Shader::compileShader(unsigned int type, const char* source) {
    // Create Shader
    unsigned int s = glCreateShader(type);
    
    // Give the Shader the source code
    glShaderSource(s, 1, &source, nullptr);

    // Compile
    glCompileShader(s);


    int result;
    // Get the Status of the compilation for the shader
    glGetShaderiv(s, GL_COMPILE_STATUS, &result);

    // Failed to Compile
    if (result != GL_TRUE) {
        int length;

        // Gets the log length
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &length);

        // Alocating the message buffer
        char *msg = (char*) alloca(length * sizeof(char));

        // Gets the Log info
        glGetShaderInfoLog(s, length, &length, msg);

        // Loggin the Error
        std::cerr << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << msg << std::endl;

        // Deleting the Shader
        glDeleteShader(s);

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

Shader::Shader(const char * vertexPath, const char * fragmentPath) {
    // Extracting the code
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);
    
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Creatge Program
    id = glCreateProgram();

    // Compiling Vertex Shader
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    // Compiling Fragment Shader
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Link Vertex Shader with the program
    glAttachShader(id, vs);
    // Link Fragment Shader with the program
    glAttachShader(id, fs);
    // Link Window with the program
    glLinkProgram(id);
    // Validate the program
    glValidateProgram(id);

    // Deleting Shader Objects since it was already linked
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::bind() const { glUseProgram(id); }

void Shader::unbind() const { glUseProgram(0); }

unsigned int Shader::getID() const { return id; }
