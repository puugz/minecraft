//
// Created by Matej on 16/01/2024.
//

#pragma once

#include "block.h"
#include "common.h"
#include "graphics/shader.h"
#include "graphics/vertex_array.h"

#define CHUNK_WIDTH  32
#define CHUNK_HEIGHT 32
#define CHUNK_DEPTH  32
#define CHUNK_SIZE CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH
#define CHUNK_INDEX(x, y, z) (x + y * CHUNK_WIDTH + z * CHUNK_HEIGHT * CHUNK_DEPTH)

#define WORLD_WIDTH  (256 / CHUNK_WIDTH)
#define WORLD_HEIGHT 1
#define WORLD_DEPTH  (256 / CHUNK_DEPTH)
#define WORLD_VOLUME WORLD_WIDTH * WORLD_HEIGHT * WORLD_DEPTH

namespace minecraft
{
    class Chunk;

    struct Vec3Hash
    {
        size_t operator()(const ivec3& offset) const
        {
            return std::hash<int>()(offset.x) ^ std::hash<int>()(offset.y) ^ std::hash<int>()(offset.z);
        }
    };

    struct Vec3Equal
    {
        bool operator()(const ivec3& a, const ivec3& b) const
        {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }
    };

    class World
    {
    public:
        World();
        ~World();

        void update(f32 delta);

        void render(const Ref<Shader>& shader) const;

        // Set the block at the given position in world space
        void set_block(i32 x, i32 y, i32 z, BlockType type);

        // Get the block at the given position in world space
        Block* get_block(i32 x, i32 y, i32 z);

        i32 seed() const;

        void clear();
        void generate();

    private:
        i32 m_seed;
        std::unordered_map<ivec3, Chunk*, Vec3Hash, Vec3Equal> m_chunks;

        bool m_generated = false;

        // Convert world space to chunk space
        static ivec3 world_to_chunk(i32 x, i32 y, i32 z);

        friend class Chunk;
        friend class App;
    };

    /*
     * +=============================================+
     * |=================== CHUNK ===================|
     * +=============================================+
     */

    class Chunk
    {
    public:
        Chunk() = default;
        Chunk(World* world, vec3 local_offset);
        ~Chunk();

        // Set the block at the given position in chunk space
        void set_block(i32 x, i32 y, i32 z, BlockType type);

        // Get the block at the given position in chunk space
        Block* get_block(i32 x, i32 y, i32 z) const;

        ivec3 chunk_offset() const
        {
            return {
                m_local_offset.x * CHUNK_WIDTH,
                m_local_offset.y * CHUNK_HEIGHT,
                m_local_offset.z * CHUNK_DEPTH
            };
        }

    private:
        Block* m_blocks;
        World* m_world;

        ivec3 m_local_offset;

        Ref<VertexArray> m_vertex_array;
        Ref<VertexBuffer> m_vertex_buffer;
        Ref<IndexBuffer> m_index_buffer;

        // Generates the mesh for the chunk
        void generate_mesh();

        // Sets the block at chunk position + chunk offset
        void set_block_world(i32 x, i32 y, i32 z, BlockType type);

        void plant_tree(i32 x, i32 y, i32 z);

        friend class World;
        friend class App;
    };
}
