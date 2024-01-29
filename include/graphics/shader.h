//
// Created by Matej on 29/12/2023.
//

#pragma once

#include "common.h"

namespace minecraft
{
    enum class ShaderType
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };

    class Shader
    {
    public:
        ~Shader();

        void bind() const;
        void unbind() const;

        static Ref<Shader> create(const char* vertex_path, const char* fragment_path);
        static Ref<Shader> create(const char* shader_path);

        void set(const std::string& name, bool value) const;
        void set(const std::string& name, i32 value) const;
        void set(const std::string& name, f32 value) const;
        void set(const std::string& name, mat4 value) const;
        void set(const std::string& name, vec3 value) const;
        void set(const std::string& name, f32 x, f32 y, f32 z) const;

    private:
        u32 m_id;
        mutable std::unordered_map<std::string, i32> m_uniform_map;

        i32 uniform_location(const std::string& name) const;

        static std::string read_file(const char* path);
        static bool parse_shader(const std::string& source, std::string& vertex_source, std::string& fragment_source);
        static std::string remove_directive_lines(const std::string& source);

        void compile(const char* source, ShaderType type) const;
        void link() const;
    };
}