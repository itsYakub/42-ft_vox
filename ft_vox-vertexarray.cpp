#include "ft_vox.hpp"

using namespace ft;

VertexArray::VertexArray(void) : m_id(0) {
    this->create();
}

VertexArray::VertexArray(const VertexArray &other) : m_id(other.m_id) { } 

VertexArray::~VertexArray(void) {
    this->destroy();
}

const VertexArray &VertexArray::operator = (const VertexArray &other) {
    if (this == &other) { return (*this); }
    
    this->m_id = other.m_id;
    return (*this);
}
 
VertexArray &VertexArray::create(void) {
    if (this->ready()) { this->destroy(); }

    glCreateVertexArrays(1, &this->m_id);
    if (!this->m_id) {
        FT_LOGE("vertex array: failed to create\n");
        return (*this);
    }

    FT_LOG("vertex array: created successfully | ID: %d\n", this->m_id);
    return (*this);
}

VertexArray &VertexArray::destroy(void) {
    if (!this->ready()) { return (*this); }
    
    glDeleteVertexArrays(1, &this->m_id), this->m_id = 0;
    FT_LOG("vertex array: deleted successfully\n");
    return (*this);
}

VertexArray &VertexArray::bind(void) {
    if (this->ready()) { this->destroy(); }

    glBindVertexArray(this->m_id);
    return (*this);
}

VertexArray &VertexArray::unbind(void) {
    if (this->ready()) { this->destroy(); }

    glBindVertexArray(0);
    return (*this);
}

VertexArray &VertexArray::setLayout(GLuint layout, GLuint index, GLsizei size, GLsizei offset) {
    if (!this->ready()) { return (*this); }

    glEnableVertexArrayAttrib(this->m_id, layout);
    glVertexArrayAttribBinding(this->m_id, layout, index);
    glVertexArrayAttribFormat(this->m_id, layout, size, GL_FLOAT, GL_FALSE, offset);
    return (*this);
}

VertexArray &VertexArray::setVertexBuffer(ft::Buffer &buffer, GLuint index, GLsizei offset, GLsizei stride) {
    if (!this->ready())  { return (*this); }
    if (!buffer.ready()) { return (*this); }

    glVertexArrayVertexBuffer(this->m_id, index, buffer.getID(), offset, stride);
    return (*this);
}

VertexArray &VertexArray::setIndexBuffer(ft::Buffer &buffer) {
    if (!this->ready())  { return (*this); }
    if (!buffer.ready()) { return (*this); }

    glVertexArrayElementBuffer(this->m_id, buffer.getID());
    return (*this);
}

GLuint VertexArray::getID(void) const {
    return (this->m_id);
}

bool VertexArray::ready(void) {
    return (this->m_id != 0);
}
