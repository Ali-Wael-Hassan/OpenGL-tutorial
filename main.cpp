#include <core/Window.h>
#include <core/Shader.h>
#include <core/VertexBuffer.h>
#include <core/VertexBufferLayout.h>
#include <core/VertexArray.h>
#include <core/IndexBuffer.h>
#include <core/Renderer.h>
#include <utils/Logger.h>
#include <GL/glew.h>

int main(void)
{
    LOG_INFO("Application Starting...");

    // Create Window
    Window window(640, 800, "Hello World");
    LOG_INFO("Window created: 640x800");

    // Positions
    struct Range {
        float x;
        float y;
    };

    // Constant Values
    const Range topLeft     = {-0.5f,  0.5f};
    const Range topRight    = { 0.5f,  0.5f};
    const Range bottomLeft  = {-0.5f, -0.5f};
    const Range bottomRight = { 0.5f, -0.5f};

    // Verticies
    float positions[8] = {
        topLeft.x,     topLeft.y,     // 0
        topRight.x,    topRight.y,    // 1
        bottomRight.x, bottomRight.y, // 2
        bottomLeft.x,  bottomLeft.y   // 3
    };

    // Triangles
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    // 1. Create a Vertex Array (The State Manager)
    VertexArray vao;
    LOG_INFO("Vertex Array Object (VAO) created.");

    // 2. Create a Vertex Buffer (The Raw Data)
    VertexBuffer vbo(positions, 8 * sizeof(float));
    LOG_INFO("Vertex Buffer Object (VBO) created and initialized with data.");

    // 3. Create a Layout (The Blueprint)
    VertexBufferLayout layout;
    layout.push<float>(2); // We are pushing 2 floats for (x, y)
    LOG_INFO("Buffer Layout defined: 2 Floats per vertex.");

    // 4. Link the Buffer and Layout to the VAO
    vao.addBuffer(vbo, layout);
    LOG_INFO("VBO and Layout linked to VAO.");

    // 5. Index Buffer (The Draw Instructions)
    IndexBuffer ibo(indices, 6);
    LOG_INFO("Index Buffer (IBO) created: 6 indices total.");

    // Compile The Shaders
    LOG_INFO("Compiling Shaders...");
    Shader shader("src/shaders/Basic.vert", "src/shaders/Basic.frag");
    LOG_INFO("Shaders linked successfully.");

    // Clean up state before the loop
    vao.unbind();
    vbo.unbind();
    ibo.unbind();
    shader.unbind();
    LOG_INFO("Initial state unbound. Entering Main Loop.");

    // Create the Renderer conductor
    Renderer renderer;

    // Main Loop
    while(!window.shouldClose()) {
        // Clear Screen
        renderer.clear();

        // Draw to the hidden buffer
        renderer.draw(vao, ibo, shader);

        // Show to the Screen
        window.swapBuffers();

        // Pull Events
        window.pollEvents();
    }

    LOG_INFO("Window closing. Cleaning up...");
    return 0;
}