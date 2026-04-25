#include <core/Window.h>
#include <core/Shader.h>
#include <core/VertexBuffer.h>
#include <core/VertexBufferLayout.h>
#include <core/VertexArray.h>
#include <core/IndexBuffer.h>
#include <core/Renderer.h>
#include <GL/glew.h>

int main(void)
{
    // Create Window
    Window window(640, 800, "Hello World");

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

    // 2. Create a Vertex Buffer (The Raw Data)
    VertexBuffer vbo(positions, 8 * sizeof(float));

    // 3. Create a Layout (The Blueprint)
    VertexBufferLayout layout;
    layout.push<float>(2); // We are pushing 2 floats for (x, y)

    // 4. Link the Buffer and Layout to the VAO
    vao.addBuffer(vbo, layout);

    // 5. Index Buffer (The Draw Instructions)
    IndexBuffer ibo(indices, 6);

    // Compile The Shaders
    Shader shader("src/shaders/Basic.vert", "src/shaders/Basic.frag");

    // Clean up state before the loop
    vao.unbind();
    vbo.unbind();
    ibo.unbind();
    shader.unbind();

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

    return 0;
}