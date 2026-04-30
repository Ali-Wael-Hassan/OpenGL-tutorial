#pragma once

#include <GLFW/glfw3.h>

class Timer {
private:
    float m_LastFrameTime;
    float m_DeletaTime;
public:
    Timer() : m_LastFrameTime(0.0f), m_DeletaTime(0.0f) {}
    void update() {
        float currentFrame = (float)glfwGetTime();
        m_DeletaTime = currentFrame - m_LastFrameTime;
        m_LastFrameTime = currentFrame;
    }

    float getDeltaTime() const { return m_DeletaTime; }
};