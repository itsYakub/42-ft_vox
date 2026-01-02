#include "ft_vox.hpp"

using namespace ft;

Texture::Texture(void) : m_id(0), m_width(0), m_height(0), m_channels(0) { }

Texture::Texture(const size_t width, const size_t height, void *data) : ft::Texture(width, height, 4, data) { }

Texture::Texture(const size_t width, const size_t height, const size_t channels, void *data) : m_id(0), m_width(0), m_height(0), m_channels(0) {
    this->create(width, height, channels, data);
}

Texture::Texture(const std::string &filepath) : m_id(0), m_width(0), m_height(0), m_channels(0) {
    this->load(filepath);
}

Texture::Texture(const Texture &other) : m_id(other.m_id), m_width(other.m_width), m_height(other.m_height), m_channels(other.m_channels) { }

Texture::~Texture(void) {
    this->destroy();
}

const Texture &Texture::operator = (const Texture &other) {
    if (this == &other) { return (*this); }
    
    this->m_id = other.m_id;
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_channels = other.m_channels;
    return (*this);
}

Texture &Texture::load(const std::string &filepath) {
    if (this->ready()) { this->destroy(); }
    
    GLsizei width    = 0,
            height   = 0,
            channels = 0;
    
    stbi_uc *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        FT_LOGE("texture: loading failure | PATH: %s\n", filepath.c_str());
        return (*this);
    }

    this->create(width, height, channels, data);
    free(data);
    
    FT_LOG("texture: created successfully | ID: %d | PATH: %s\n", this->m_id, filepath.c_str());
    return (*this);
}

Texture &Texture::create(const size_t width, const size_t height, void *data) {
    return (this->create(width, height, 4, data));
}

Texture &Texture::create(const size_t width, const size_t height, const size_t channels, void *data) {
    if (this->ready()) { this->destroy(); }

    GLenum format = GL_NONE;
    switch (channels) {
        case (1): { format = GL_RED; } break;
        case (3): { format = GL_RGB; } break;
        case (4): { format = GL_RGBA; } break;

        default: { return (*this); }
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &this->m_id);
    if (!this->m_id) {
        FT_LOGE("texture: create failure\n");
        return (*this);
    }

    glTextureParameteri(this->m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(this->m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(this->m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTextureParameteri(this->m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTextureStorage2D(this->m_id, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(this->m_id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(this->m_id);
   
    this->m_width = width;
    this->m_height = height;
    this->m_channels = channels; 
    FT_LOG("texture: created successfully | ID: %d | WIDH: %d | HEIGHT: %d | CHANNELS: %d\n", this->m_id, this->m_width, this->m_height, this->m_channels);
    return (*this);
}

Texture &Texture::destroy(void) {
    glDeleteTextures(1, &this->m_id);
    this->m_id = 0;
    this->m_width = 0;
    this->m_height = 0;
    this->m_channels = 0;
    
    FT_LOG("texture: deleted successefully\n"); 
    return (*this);
}

GLuint Texture::getID(void) const {
    return (this->m_id);
}

GLsizei Texture::getWidth(void) const {
    return (this->m_width);
}

GLsizei Texture::getHeight(void) const {
    return (this->m_height);
}

GLsizei Texture::getChannels(void) const {
    return (this->m_channels);
}

bool Texture::ready(void) const {
    return (this->m_id != 0);
}
