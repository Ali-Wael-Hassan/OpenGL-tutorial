#pragma once

#include <utils/GLDebug.h>
#include <stb_image.h>
#include <GL/glew.h>
#include <string>


class Texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    int m_Width;
    int m_Height;
    int m_BPP;

    unsigned char* loadImageFromDisk(const std::string& path);
    void initOpenGLTexture(unsigned char* data);
    void setTextureParameters();

public:
    Texture(const std::string& path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const;
    inline int getHeight() const;
};