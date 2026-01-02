#include "ft_vox.hpp"

static const GLchar *g_glsl_vertex = R"(
#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texcoord;

out vec4 v_color;
out vec2 v_texcoord;

uniform mat4 u_proj;
uniform mat4 u_view;

void main() {
    gl_Position = u_proj * u_view * vec4(a_position.xyz, 1.0);
    v_color = a_color;
    v_texcoord = a_texcoord;
})";

static const GLchar *g_glsl_fragment = R"(
#version 460 core

in vec4 v_color;
in vec2 v_texcoord;

out vec4 f_color;

void main() {
    f_color = v_color;
})";

using namespace ft;

Shader::Shader(void) : ft::Shader(g_glsl_vertex, g_glsl_fragment) { }

Shader::Shader(const GLchar *vertex, const GLchar *fragment) : m_id(0), m_uniforms( { } ) {
    this->setVertexShader(vertex);
    this->setFragmentShader(fragment);
}

Shader::Shader(const Shader &other) : m_id(other.m_id), m_uniforms(other.m_uniforms) { }

Shader::~Shader(void) {
    glDeleteProgram(this->m_id), this->m_id = 0;
    
    FT_LOG("shader: deleted sccessfully\n");
}

const Shader &Shader::operator = (const Shader &other) {
    if (this == &other) { return (*this); }
    
    this->m_id = other.m_id;
    this->m_uniforms = other.m_uniforms;
    return (*this);
}

Shader &Shader::setVertexShader(const GLchar *raw) {
    if (!this->ready()) { this->createProgram(); }

    /* shader compilation */
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &raw, 0);
    glCompileShader(shader);
   
    /* compile error */
    GLint compile = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile);
    if (compile != GL_TRUE) {
        GLsizei length = 0;
        GLchar message[1024] = { };
        glGetShaderInfoLog(shader, 1024, &length, message);

        FT_LOGE("vertex: %s\n", message);
        return (*this);
    }

    /* shader linking */
    glAttachShader(this->m_id, shader);
    glLinkProgram(this->m_id);
    glDeleteShader(shader), shader = 0;
    
    /* linking error */
    GLint link = 0;
    glGetProgramiv(this->m_id, GL_LINK_STATUS, &link);
    if (link != GL_TRUE) {
        GLsizei length = 0;
        GLchar message[1024] = { };
        glGetProgramInfoLog(shader, 1024, &length, message);

        FT_LOGE("shader: %s\n", message);
        return (*this);
    }
  
    FT_LOG("shader: new vertex shader set\n");
    return (*this);
}

Shader &Shader::setVertexShader(const std::string &filepath) {
    if (!this->ready()) { this->createProgram(); }

    std::ifstream infile(filepath);
    if (!infile.is_open()) { return (*this); }

    std::string content;
    std::string line;
    while (std::getline(infile, line)) {
        content += line;
    }    

    return (this->setVertexShader(content.c_str()));
}

Shader &Shader::setFragmentShader(const GLchar *raw) {
    if (!this->ready()) { this->createProgram(); }

    /* shader compilation */
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &raw, 0);
    glCompileShader(shader);
   
    /* compile error */
    GLint compile = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile);
    if (compile != GL_TRUE) {
        GLsizei length = 0;
        GLchar message[1024] = { };
        glGetShaderInfoLog(shader, 1024, &length, message);

        FT_LOGE("fragment: %s\n", message);
        return (*this);
    }
    
    /* shader linking */
    glAttachShader(this->m_id, shader);
    glLinkProgram(this->m_id);
    glDeleteShader(shader), shader = 0;
    
    /* linking error */
    GLint link = 0;
    glGetProgramiv(this->m_id, GL_LINK_STATUS, &link);
    if (link != GL_TRUE) {
        GLsizei length = 0;
        GLchar message[1024] = { };
        glGetProgramInfoLog(shader, 1024, &length, message);

        FT_LOGE("shader: %s\n", message);
        return (*this);
    }
   
    FT_LOG("shader: new fragment shader set\n");
    return (*this);
}

Shader &Shader::setFragmentShader(const std::string &filepath) {
    if (!this->ready()) { this->createProgram(); }

    std::ifstream infile(filepath);
    if (!infile.is_open()) { return (*this); }

    std::string content;
    std::string line;
    while (std::getline(infile, line)) {
        content += line;
    }    

    return (this->setFragmentShader(content.c_str()));
}

GLuint Shader::getID(void) const {
    return (this->m_id);
}

GLint Shader::getUniform(const std::string &name) {
    if (!this->ready()) { this->createProgram(); }

    /* check if uniform IDalready in map... */
    for (auto i : this->m_uniforms) {
        if (i.first == name) {
            GLint id = i.second;
            if (id == -1) {
                FT_LOGE("shader: invalid uniform | NAME: %s\n", name.c_str());
            }
            return (id);
        }
    }

    /* ...otherwise, retrieve it from the shader, insert it to the map and return the ID*/
    GLint id = glGetUniformLocation(this->m_id, name.c_str());
    if (id == -1) {
        FT_LOGE("shader: invalid uniform | NAME: %s\n", name.c_str());
    }
    this->m_uniforms.insert( { name, id } );
    return (id);
    
}

bool Shader::ready(void) const {
    return (this->m_id != 0);
}

Shader &Shader::createProgram(void) {
    if (this->ready()) { glDeleteProgram(this->m_id), this->m_id = 0; }

    this->m_id = glCreateProgram();
    FT_LOG("shader: created successfully | ID: %d\n", this->m_id);
    return (*this);
}
