#include <core/Texture.h>

Texture::Texture(const std::string& path)
    : m_RendererID(0), m_FilePath(path), m_Width(0), m_Height(0), m_BPP(0)
{
    // Load the pixel data from the disk
    unsigned char* data = loadImageFromDisk(path);
    
    // Check if the data was loaded successfully
    if (data) {
        // Create the OpenGL texture and upload the data
        initOpenGLTexture(data);
        // Free the CPU memory after uploading to GPU
        stbi_image_free(data);
        // Log the successful creation
        LOG_INFO("Texture Created: " + path + " (ID: " + std::to_string(m_RendererID) + ")");
    }
    else {
        // Log an error if the texture failed to load
        LOG_ERROR("Texture Constructor: Failed to initialize texture from " + path);
    }
}

unsigned char* Texture::loadImageFromDisk(const std::string& path) {
    // Flip the texture to match OpenGL coordinate system
    stbi_set_flip_vertically_on_load(1);
    // Load the image data using 4 channels (RGBA)
    unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // Check for loading errors
    if (!data) {
        LOG_ERROR("Texture Loader: Could not find or read file at " + path);
    }

    // Return the raw pixel data
    return data;
}

void Texture::initOpenGLTexture(unsigned char* data) {
    // Generate the texture ID
    GLCall(glGenTextures(1, &m_RendererID));
    // Select the texture
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    // Configure the scaling and wrapping settings
    setTextureParameters();

    // Upload the pixels to the GPU
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    
    // Unselect the texture
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::setTextureParameters() {
    // Set the filtering for scaling down
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    // Set the filtering for scaling up
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    // Set the wrapping for the S (X) axis
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    // Set the wrapping for the T (Y) axis
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

Texture::~Texture() {
    LOG_INFO("Deleting Texture ID: " + std::to_string(m_RendererID));
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

inline int Texture::getWidth() const {
    return m_Width;
}

inline int Texture::getHeight() const {
    return m_Height;
}