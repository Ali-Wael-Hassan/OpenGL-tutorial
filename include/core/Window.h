#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* m_window;
    char *m_title;
    int m_width;
    int m_height;

public:
    // Initialize the Window
    Window(int width, int height, char* title);

    // Destroy the Window
    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

    // Prevent Multiple Calls
    Window(const Window&) = delete;
    Window(Window&&) = delete;
};