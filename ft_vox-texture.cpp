#include "ft_vox.hpp"

using namespace ft;

Texture::Texture(void) : m_id(0), m_width(0), m_height(0), m_channels(0) { }

Texture::Texture(const size_t width, const size_t height, void *data) : m_id(0), m_width(0), m_height(0), m_channels(0) {
    this->create(width, height, data);
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
    FT_UNUSED(filepath);
    return (*this);
}

Texture &Texture::create(const size_t width, const size_t height, void *data) {
    FT_UNUSED(width);
    FT_UNUSED(height);
    FT_UNUSED(data);
    return (*this);
}

Texture &Texture::destroy(void) {
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
