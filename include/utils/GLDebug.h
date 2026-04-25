#pragma once

#include <utils/Logger.h>
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <string>

// Enable in Debug Mode (Release needs full performance)
#if defined(DEBUG) || defined(_DEBUG)
    #define GLCall(x) GLClearError();\
        x;\
        if (!GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
    #define GLCall(x) x
#endif

// Translate hex codes to strings
static std::string GetGLErrorString(GLenum error) {
    switch (error) {
        case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:                               return "UNKNOWN_ERROR";
    }
}

// clear previously caused errors
static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

// log the error into the terminal
static bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::string errorName = GetGLErrorString(error);
        
        // treat the string as output stream
        std::ostringstream oss;
        oss << "\n  [ OPENGL ERROR ]"
            << "\n  > ERROR    : " << errorName << " (0x" << std::hex << error << ")"
            << "\n  > FUNCTION : " << function 
            << "\n  > FILE     : " << file 
            << "\n  > LINE     : " << std::dec << line;

        LOG_ERROR(oss.str());
        return false;
    }
    return true;
}