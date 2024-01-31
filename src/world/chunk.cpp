//
// Created by Matej on 18/01/2024.
//

#include "world/world.h"
#include <fstream>
#include "fastnoiselite/fastnoiselite.h"

using namespace minecraft;

#define SHOULD_ADD_FACE(block, adjacent_block) \
    (!adjacent_block || (block->type() != adjacent_block->type() && adjacent_block->is_transparent()))

#define FLOATS_PER_VERTEX 5
#define CHUNK_ADD_FACE(side)                                                        \
    u32 base_idx = static_cast<u32>(vertices.size() / 5);                           \
    \
    vertices.insert(vertices.end(), {                                               \
        BLOCK_##side##_TOPLEFT(x, y, z),     BLOCK_UV_TOPLEFT(uv.x, uv.y),          \
        BLOCK_##side##_BOTTOMLEFT(x, y, z),  BLOCK_UV_BOTTOMLEFT(uv.x, uv.y),       \
        BLOCK_##side##_BOTTOMRIGHT(x, y, z), BLOCK_UV_BOTTOMRIGHT(uv.x, uv.y),      \
        BLOCK_##side##_TOPRIGHT(x, y, z),    BLOCK_UV_TOPRIGHT(uv.x, uv.y),         \
    });                                                                             \
    \
    indices.insert(indices.end(), {                                                 \
        0 + base_idx, 1 + base_idx, 2 + base_idx,                                   \
        2 + base_idx, 3 + base_idx, 0 + base_idx,                                   \
    });

namespace
{
    VertexLayout layout = {
        {VertexType::Float3}, // position
        {VertexType::Float2}, // texcoord
    };
}

#define BEDROCK_LEVEL 0
#define WATER_LEVEL 2
#define SAND_LEVEL 3

Chunk::Chunk(World* world, vec3 local_offset)
    :
    m_world(world),
    m_local_offset(local_offset)
{
    m_blocks = new Block[CHUNK_SIZE];

    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(m_world->seed());
    noise.SetFractalType(FastNoiseLite::FractalType_Ridged);
    noise.SetFractalOctaves(2);

    // fill blocks
    for (i32 i = 0; i < CHUNK_SIZE; i++)
    {
        const i32 x = i % CHUNK_WIDTH;
        // const i32 y = i / CHUNK_WIDTH % CHUNK_HEIGHT;
        const i32 z = i / CHUNK_WIDTH / CHUNK_HEIGHT % CHUNK_DEPTH;

        auto offset = chunk_offset();

        f32 noise3d = noise.GetNoise(
            static_cast<f32>(x + offset.x),
            static_cast<f32>(z + offset.z)
        );

        i32 block_height = glm::round(CHUNK_HEIGHT * noise3d);
        // i32 block_height = noise3d * CHUNK_HEIGHT / 2.0f + CHUNK_HEIGHT / 2.0f;

        set_block(x, BEDROCK_LEVEL, z, BlockType::Bedrock);

        if (block_height <= SAND_LEVEL)
        {
            for (i32 y = block_height; y > BEDROCK_LEVEL; y--)
                set_block(x, y, z, BlockType::Sand);
        }

        for (i32 y = WATER_LEVEL; y > BEDROCK_LEVEL; y--)
        {
            Block* b = get_block(x, y, z);

            if (!b || b->type() == BlockType::Air)
                set_block(x, y, z, BlockType::Water);
        }

        if (block_height > SAND_LEVEL)
        {
            set_block(x, block_height, z, BlockType::Grass);
            i32 y_dirt_offset = rand_int(3, 5);

            for (i32 y = block_height - 1; y > glm::max(block_height - 1 - y_dirt_offset, BEDROCK_LEVEL); y--)
                set_block(x, y, z, BlockType::Dirt);

            for (i32 y = block_height - y_dirt_offset; y > BEDROCK_LEVEL; y--)
                set_block(x, y, z, BlockType::Stone);

            // plant trees
            if (rand() % 32000 == 1)
                plant_tree(x, block_height, z);
        }
    }
}

Chunk::~Chunk()
{
    delete[] m_blocks;
}

void Chunk::generate_mesh()
{
    std::vector<f32> vertices;
    std::vector<u32> indices;

    for (i32 i = 0; i < CHUNK_SIZE; i++)
    {
        const i32 x = i % CHUNK_WIDTH;
        const i32 y = i / CHUNK_WIDTH % CHUNK_HEIGHT;
        const i32 z = i / CHUNK_WIDTH / CHUNK_HEIGHT % CHUNK_DEPTH;

        const Block* block = get_block(x, y, z);

        if (!block || block->type() == BlockType::Air)
            continue;

        ivec3 offset = chunk_offset();

        const Block* block_top    = m_world->get_block(x     + offset.x, y + 1 + offset.y, z     + offset.z);
        const Block* block_bottom = m_world->get_block(x     + offset.x, y - 1 + offset.y, z     + offset.z);
        const Block* block_left   = m_world->get_block(x - 1 + offset.x, y     + offset.y, z     + offset.z);
        const Block* block_right  = m_world->get_block(x + 1 + offset.x, y     + offset.y, z     + offset.z);
        const Block* block_front  = m_world->get_block(x     + offset.x, y     + offset.y, z + 1 + offset.z);
        const Block* block_back   = m_world->get_block(x     + offset.x, y     + offset.y, z - 1 + offset.z);

        // TOP BLOCK
        if (SHOULD_ADD_FACE(block, block_top))
        {
            vec2 uv = block->get_uv_offset(BlockFace::Top);
            CHUNK_ADD_FACE(TOP);
        }

        // BOTTOM BLOCK
        if (SHOULD_ADD_FACE(block, block_bottom))
        {
            vec2 uv = block->get_uv_offset(BlockFace::Bottom);
            CHUNK_ADD_FACE(BOTTOM);
        }

        // LEFT BLOCK
        if (SHOULD_ADD_FACE(block, block_left))
        {
            vec2 uv = block->get_uv_offset(BlockFace::Left);
            CHUNK_ADD_FACE(LEFT);
        }

        // RIGHT BLOCK
        if (SHOULD_ADD_FACE(block, block_right))
        {
            vec2 uv = block->get_uv_offset(BlockFace::Right);
            CHUNK_ADD_FACE(RIGHT);
        }

        // FRONT BLOCK
        if (SHOULD_ADD_FACE(block, block_front))
        {
            vec2 uv = block->get_uv_offset(BlockFace::Front);
            CHUNK_ADD_FACE(FRONT);
        }

        // BACK BLOCK
        if (SHOULD_ADD_FACE(block, block_back))
        {
            vec2 uv = block->get_uv_offset(BlockFace::Back);
            CHUNK_ADD_FACE(BACK);
        }
    }

    m_vertex_array = VertexArray::create();
    m_index_buffer = IndexBuffer::create(indices.data(), indices.size());
    m_vertex_buffer = VertexBuffer::create(vertices.data(), vertices.size() * sizeof(f32));
    m_vertex_buffer->set_layout(layout);

    m_vertex_array->add_vertex_buffer(m_vertex_buffer);
    m_vertex_array->set_index_buffer(m_index_buffer);
}

void Chunk::set_block_world(i32 x, i32 y, i32 z, BlockType type)
{
    // ?
    const ivec3 offset = chunk_offset();
    m_world->set_block(x + offset.x, y + offset.y, z + offset.z, type);
}

void Chunk::plant_tree(i32 x, i32 y, i32 z)
{
    // TODO: Clean up
    for (i32 yy = y; yy < y + 6; yy++)
    {
        set_block(x, yy, z, BlockType::Log);
    }

    for (i32 yy = y + 3; yy < y + 5; yy++)
    {
        for (i32 xx = -2; xx <= 2; xx++)
            for (i32 zz = -2; zz <= 2; zz++)
            {
                Block* block = get_block(x + xx, yy, z + zz);

                if (!block || !block->is_solid())
                    set_block(x + xx, yy, z + zz, BlockType::Leaf);
            }
    }

    {
        i32 yy = y + 5;
        for (i32 xx = -1; xx <= 1; xx++)
            for (i32 zz = -1; zz <= 1; zz++)
            {
                Block* block = get_block(x + xx, yy, z + zz);

                if (!block || !block->is_solid())
                    set_block(x + xx, yy, z + zz, BlockType::Leaf);
            }

        yy++;
        // todo: place only on non solid blocks like above
        set_block(x, yy, z - 1, BlockType::Leaf);
        set_block(x, yy, z, BlockType::Leaf);
        set_block(x, yy, z + 1, BlockType::Leaf);
        set_block(x + 1, yy, z, BlockType::Leaf);
        set_block(x - 1, yy, z, BlockType::Leaf);
    }
}

void Chunk::set_block(i32 x, i32 y, i32 z, BlockType type)
{
    // check if position is in chunk
    if (x < 0 || x >= CHUNK_WIDTH ||
        y < 0 || y >= CHUNK_HEIGHT ||
        z < 0 || z >= CHUNK_DEPTH)
    {
        // spdlog::info("Chunk::set_block out of chunk range. Setting with world.");
        // m_world->set_block(x + m_offset.x, y + m_offset.y, z + m_offset.z, type);
        // set_block_world(x, y, z, type);
        return;
    }

    if (Block* b = get_block(x, y, z))
        b->set_type(type);
    else
        m_blocks[CHUNK_INDEX(x, y, z)] = Block(ivec3(x, y, z), type);
}

Block* Chunk::get_block(i32 x, i32 y, i32 z) const
{
    if (x < 0 || x >= CHUNK_WIDTH ||
        y < 0 || y >= CHUNK_HEIGHT ||
        z < 0 || z >= CHUNK_DEPTH)
        // return m_world->get_block(x + m_offset.x, y + m_offset.y, z + m_offset.z);
        return nullptr;

    return &m_blocks[CHUNK_INDEX(x, y, z)];
}
