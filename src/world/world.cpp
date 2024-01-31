//
// Created by Matej on 18/01/2024.
//

#include "world/world.h"
#include "graphics/renderer.h"

using namespace minecraft;

World::World()
{
    this->randomize_seed();
}

World::~World()
{
    this->clear();
}

void World::update(f32 delta)
{
}

void World::render(const Ref<Shader>& shader) const
{
    // TODO: Only render chunks that are visible
    // TODO: Only render chunks that are within a certain distance
    // TODO: Only render chunks that are within the view frustum
    for (auto& [position, chunk] : m_chunks)
    {
        if (!chunk->m_vertex_array && !chunk->m_vertex_buffer && !chunk->m_index_buffer)
            continue;

        auto model = mat4(1.0f);
        model = translate(model, vec3(
            position.x * CHUNK_WIDTH,
            position.y * CHUNK_HEIGHT,
            position.z * CHUNK_DEPTH
        ));

        Renderer::submit(shader, chunk->m_vertex_array, model);
    }
}

void World::set_block(i32 x, i32 y, i32 z, BlockType type)
{
    vec3 chunk_offset = world_to_chunk(x, y, z);

    // Chunk doesn't exist
    if (m_chunks.find(chunk_offset) == m_chunks.end())
        // m_chunks[chunk_offset] = new Chunk(this, chunk_offset);
        return;

    m_chunks[chunk_offset]->set_block(x % CHUNK_WIDTH, y % CHUNK_HEIGHT, z % CHUNK_DEPTH, type);
    // spdlog::info("world::set_block directly in chunk");
    // m_chunks[chunk_offset]->m_blocks[CHUNK_INDEX(x % CHUNK_WIDTH, y % CHUNK_HEIGHT, z % CHUNK_DEPTH)].set_type(type);
}

Block* World::get_block(i32 x, i32 y, i32 z)
{
    vec3 chunk_offset = world_to_chunk(x, y, z);

    if (m_chunks.find(chunk_offset) == m_chunks.end())
        return nullptr;

    return m_chunks[chunk_offset]->get_block(x % CHUNK_WIDTH, y % CHUNK_HEIGHT, z % CHUNK_DEPTH);
    // return &m_chunks[chunk_offset]->m_blocks[CHUNK_INDEX(x, y, z)];
}

i32 World::seed() const
{
    return m_seed;
}

void World::randomize_seed()
{
    srand(time(nullptr));
    m_seed = rand() % INT_MAX;
}

void World::clear()
{
    for (auto& [offset, chunk] : m_chunks)
        delete chunk;
    m_chunks.clear();
    m_generated = false;
}

void World::generate()
{
    APP_ASSERT(!m_generated, "World already generated! Call clear() first!");

    spdlog::info("Generating world...");

    for (i32 x = 0; x < WORLD_WIDTH; x++)
        for (i32 y = 0; y < WORLD_HEIGHT; y++)
            for (i32 z = 0; z < WORLD_DEPTH; z++)
            {
                auto offset = ivec3(x, y, z);
                m_chunks[offset] = new Chunk(this, offset);
            }

    for (auto& [offset, chunk] : m_chunks)
    {
        chunk->generate_mesh();
    }

    m_generated = true;
    spdlog::info("Done!");
}

ivec3 World::world_to_chunk(i32 x, i32 y, i32 z)
{
    i32 chunk_x = x / CHUNK_WIDTH;
    i32 chunk_y = y / CHUNK_HEIGHT;
    i32 chunk_z = z / CHUNK_DEPTH;
    return {chunk_x, chunk_y, chunk_z};
}
