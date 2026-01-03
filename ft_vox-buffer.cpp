#include "ft_vox.hpp"

using namespace ft;

Buffer::Buffer(void) : m_id(0), m_size(0) { }

Buffer::Buffer(const void *data, GLsizei size) : m_id(0), m_size(size) {
    this->create(data, size);
}

Buffer::Buffer(const Buffer &other) : m_id(other.m_id), m_size(other.m_size) { } 

Buffer::~Buffer(void) {
    this->destroy();
}

const Buffer &Buffer::operator = (const Buffer &other) {
    if (this == &other) { return (*this); }
    
    this->m_id = other.m_id;
    this->m_size = other.m_size;
    return (*this);
}
 
Buffer &Buffer::create(const void *data, GLsizei size) {
    if (this->ready()) { this->destroy(); }

    glCreateBuffers(1, &this->m_id);
    if (!this->m_id) {
        FT_LOGE("buffer: failed to create\n");
        return (*this);
    }

    glNamedBufferData(this->m_id, size, data, GL_DYNAMIC_DRAW);
    this->m_size = size;

    FT_LOG("buffer: created successfully | ID: %d | SIZE: %d\n", this->m_id, this->m_size);
    return (*this);
}

Buffer &Buffer::destroy(void) {
    if (!this->ready()) { return (*this); }
    
    glDeleteBuffers(1, &this->m_id), this->m_id = 0;
    FT_LOG("buffer: deleted successfully\n");
    return (*this);
}

Buffer &Buffer::setData(const void *data, GLsizei size, GLsizei offset) {
    if (!this->ready()) { return (this->create(data, size)); }

    if (offset == 0) {
        if (size != this->m_size) {
            glNamedBufferSubData(this->m_id, offset, size, data);
        }

        else {
            glNamedBufferData(this->m_id, size, data, GL_DYNAMIC_DRAW);
        }
    }
    
    else {
        glNamedBufferSubData(this->m_id, offset, size, data);
    }
    
    return (*this);
}

GLuint Buffer::getID(void) const {
    return (this->m_id);
}

GLsizei Buffer::getSize(void) const {
    return (this->m_size);
}

bool Buffer::ready(void) {
    return (this->m_id != 0);
}
