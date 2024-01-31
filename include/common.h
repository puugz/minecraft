//
// Created by Matej on 29/12/2023.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/hash.hpp>
#include <memory>
#include "spdlog/spdlog.h"

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#endif

#define APP_ASSERT(x, ...) { if(!(x)) { spdlog::error(__VA_ARGS__); DEBUG_BREAK(); } }

namespace minecraft
{
    using i8     = int8_t;
    using i16    = int16_t;
    using i32    = int32_t;
    using i64    = int64_t;
    using u8     = uint8_t;
    using u16    = uint16_t;
    using u32    = uint32_t;
    using u64    = uint64_t;
    using f32    = float;
    using f64    = double;
    using size_t = std::size_t;

    template<typename ReturnType, typename... Args>
    using Fn = const std::function<ReturnType(Args...)>;

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    using WeakRef = std::weak_ptr<T>;

    // this is so i can use glm types without using it's namespace
    // glm also has the int types defined above so it sort of clashes with them
    using ivec2 = glm::ivec2;
    using ivec3 = glm::ivec3;
    using ivec4 = glm::ivec4;
    using vec2  = glm::vec2;
    using vec3  = glm::vec3;
    using vec4  = glm::vec4;
    using mat2  = glm::mat2;
    using mat3  = glm::mat3;
    using mat4  = glm::mat4;

    inline i32 rand_int(const i32 min, const i32 max)
    {
        return min + (rand() % (max - min + 1));
    }
}
