#include <engine/OpenGLBasic.h>

OpenGLBasic::OpenGLBasic(int width, int height, const char* title)
    : m_Window(width, height, title) {}

void OpenGLBasic::run() {
    LOG_INFO("Application Starting...");

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
    float positions[] = {
        topLeft.x,     topLeft.y, 0.0f, 1.0f,     // 0
        topRight.x,    topRight.y, 1.0f, 1.0f,    // 1
        bottomRight.x, bottomRight.y, 1.0f, 0.0f, // 2
        bottomLeft.x,  bottomLeft.y, 0.0f, 0.0f  // 3
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
    VertexBuffer vbo(positions, 4 * 4 * sizeof(float));
    LOG_INFO("Vertex Buffer Object (VBO) created and initialized with data.");

    // 3. Create a Layout (The Blueprint)
    VertexBufferLayout layout;
    layout.push<float>(2); // We are pushing 2 floats for (x, y)
    layout.push<float>(2); // We are pushing 2 floats for (u, v)
    LOG_INFO("Buffer Layout defined: 2 Floats per vertex.");

    // 4. Link the Buffer and Layout to the VAO
    vao.addBuffer(vbo, layout);
    LOG_INFO("VBO and Layout linked to VAO.");

    // 5. Index Buffer (The Draw Instructions)
    IndexBuffer ibo(indices, 6);
    LOG_INFO("Index Buffer (IBO) created: 6 indices total.");

    // Compile The Shaders
    LOG_INFO("Compiling Shaders...");
    Shader shader("assets/shaders/Basic.vert", "assets/shaders/Basic.frag");
    LOG_INFO("Shaders linked successfully.");

    // Create the Renderer conductor
    Renderer renderer;

    // Timer Setup for Animations
    Timer timer;
    float blueChannel = 0.0f;
    float increment = 0.5f;

    // Texture
    Texture texture("assets/textures/test.jpeg");
    texture.bind();
    shader.setUniform1i("u_Texture", 0);

    // Main Loop
    while(!m_Window.shouldClose()) {
        // Clear Screen
        renderer.clear();

        // Update Current time frame
        timer.update();

        // Use the shader for setting uniform
        shader.bind();

        // Use Delta Time to animate the color smoothly
        blueChannel += increment * timer.getDeltaTime();
        if (blueChannel > 1.0f) {
            blueChannel = 1.0f;
            increment *= -1.0f;
        } 
        else if (blueChannel < 0.0f) {
            blueChannel = 0.0f;
            increment *= -1.0f;
        }

        // Setting the uniform
        shader.setUniform4f("u_Color", 0.2f, 0.3f, blueChannel, 1.0f);
        // Draw to the hidden buffer
        renderer.draw(vao, ibo, shader);

        // Show to the Screen
        m_Window.swapBuffers();

        // Pull Events
        m_Window.pollEvents();
    }

    LOG_INFO("Window closing. Cleaning up...");
}