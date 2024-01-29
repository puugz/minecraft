//
// Created by Matej on 29/12/2023.
//

#include "graphics/shader.h"

#include <fstream>
#include <sstream>

using namespace minecraft;

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::bind() const
{
    glUseProgram(m_id);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

Ref<Shader> Shader::create(const char* vertex_path, const char* fragment_path)
{
    const auto shader = std::make_shared<Shader>();
    shader->m_id = glCreateProgram();

    shader->compile(read_file(vertex_path).c_str(), ShaderType::Vertex);
    shader->compile(read_file(fragment_path).c_str(), ShaderType::Fragment);
    shader->link();

    return shader;
}

Ref<Shader> Shader::create(const char* shader_path)
{
    const auto shader = std::make_shared<Shader>();
    shader->m_id = glCreateProgram();

    spdlog::debug("Parsing {}", shader_path);

    std::string source = read_file(shader_path);
    std::string vertex_source, fragment_source;

    if (parse_shader(source, vertex_source, fragment_source))
    {
        shader->compile(vertex_source.c_str(), ShaderType::Vertex);
        shader->compile(fragment_source.c_str(), ShaderType::Fragment);
        shader->link();
    }
    else
    {
        APP_ASSERT(false, "Failed to parse shader file: {}", shader_path);
    }

    return shader;
}

void Shader::set(const std::string& name, const bool value) const
{
    glUniform1i(uniform_location(name), value);
}

void Shader::set(const std::string& name, i32 value) const
{
    glUniform1i(uniform_location(name), value);
}

void Shader::set(const std::string& name, f32 value) const
{
    glUniform1f(uniform_location(name), value);
}

void Shader::set(const std::string& name, mat4 value) const
{
    glUniformMatrix4fv(uniform_location(name), 1, GL_FALSE, value_ptr(value));
}

void Shader::set(const std::string& name, vec3 value) const
{
    glUniform3fv(uniform_location(name), 1, value_ptr(value));
}

void Shader::set(const std::string& name, f32 x, f32 y, f32 z) const
{
    glUniform3f(uniform_location(name), x, y, z);
}

i32 Shader::uniform_location(const std::string& name) const
{
    if (m_uniform_map.find(name) != m_uniform_map.end())
        return m_uniform_map[name];

    const i32 location = glGetUniformLocation(m_id, name.c_str());
    m_uniform_map[name] = location;

    return location;
}

std::string Shader::read_file(const char* path)
{
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);

        std::stringstream stream;
        stream << file.rdbuf();
        code = stream.str();

        file.close();
    }
    catch (std::ifstream::failure& e)
    {
        APP_ASSERT(false, "{}: {}", e.what(), path);
    }

    return code;
}

bool Shader::parse_shader(const std::string& source, std::string& vertex_source, std::string& fragment_source)
{
    size_t vertex_start = source.find("#type vertex");
    if (vertex_start != std::string::npos)
    {
        size_t vertex_end = source.find("#type", vertex_start + 1);
        if (vertex_end != std::string::npos)
            vertex_source = "#version 330 core\n" + remove_directive_lines(source.substr(vertex_start, vertex_end - vertex_start));
    }

    size_t fragment_start = source.find("#type fragment");
    if (fragment_start != std::string::npos)
        fragment_source = "#version 330 core\n" + remove_directive_lines(source.substr(fragment_start));

    return !vertex_source.empty() && !fragment_source.empty();
}

std::string Shader::remove_directive_lines(const std::string& source)
{
    // Remove lines containing "#type"
    std::istringstream iss(source);
    std::ostringstream oss;

    std::string line;
    while (std::getline(iss, line))
    {
        if (line.find("#type") == std::string::npos)
            oss << line << '\n';
    }

    return oss.str();
}

void Shader::compile(const char* source, ShaderType type) const
{
    i32 success;
    char info_log[512];

    u8 shader_id = glCreateShader(static_cast<int>(type));
    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, nullptr, info_log);
        APP_ASSERT(false, "Failed to compile shader: {}", info_log);
    }

    glAttachShader(m_id, shader_id);
}

void Shader::link() const
{
    i32 success;
    char info_log[512];

    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, info_log);
        APP_ASSERT(false, "Failed to link shader: {}", info_log);
    }

    i32 count;
    u32 shaders[2];
    glGetAttachedShaders(m_id, 2, &count, shaders);

    for (i32 i = 0; i < count; i++)
    {
        glDeleteShader(shaders[i]);
    }
}
