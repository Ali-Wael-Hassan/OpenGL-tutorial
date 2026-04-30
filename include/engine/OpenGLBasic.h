#pragma once

#include <core/Window.h>
#include <core/Shader.h>
#include <core/VertexBuffer.h>
#include <core/VertexBufferLayout.h>
#include <core/VertexArray.h>
#include <core/IndexBuffer.h>
#include <core/Renderer.h>
#include <utils/Logger.h>
#include <GL/glew.h>

class OpenGLBasic {
private:
    Window m_Window;
public:
    OpenGLBasic(int width, int height, const char* title);
    void run();
};