#include <core/Window.h>
#include <iostream>

Window::Window(int width, int height, const char* title) : m_width(width), m_height(height), m_title(title) {
    // Initialize the GLFW Library
    if(!glfwInit()) {
        std::cerr << "GLFW Init Failed!" << std::endl;
    }

    // Create the Window
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    // Terminate if the window is null
    if(!m_window) {
        glfwTerminate();
        return;
    }

    // Expose the window
    glfwMakeContextCurrent(m_window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    
    // Error in the initializing
    if(err != GLEW_OK) {
        std::cerr << "GLEW Init Failed: " << glewGetErrorString(err) << std::endl;
        return;
    }

    // Log Data
    std::cout << "OpenGL Loaded!" << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
    // check if window exist
    if(m_window) {
        // destroy the window
        glfwDestroyWindow(m_window);
        // terminate
        glfwTerminate();
    }
}

// Wrapper Functions
bool Window::shouldClose() const { return glfwWindowShouldClose(m_window); }
void Window::swapBuffers() const { glfwSwapBuffers(m_window); }
void Window::pollEvents() const { glfwPollEvents(); }