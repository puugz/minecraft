//
// Created by Matej on 16/01/2024.
//

#pragma once

#include "common.h"

#define BLOCK_LEFT_TOPLEFT(x, y, z)       -0.5f + x,  0.5f + y, -0.5f + z
#define BLOCK_LEFT_BOTTOMLEFT(x, y, z)    -0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_LEFT_BOTTOMRIGHT(x, y, z)   -0.5f + x, -0.5f + y,  0.5f + z
#define BLOCK_LEFT_TOPRIGHT(x, y, z)      -0.5f + x,  0.5f + y,  0.5f + z

#define BLOCK_RIGHT_TOPLEFT(x, y, z)       0.5f + x,  0.5f + y,  0.5f + z
#define BLOCK_RIGHT_BOTTOMLEFT(x, y, z)    0.5f + x, -0.5f + y,  0.5f + z
#define BLOCK_RIGHT_BOTTOMRIGHT(x, y, z)   0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_RIGHT_TOPRIGHT(x, y, z)      0.5f + x,  0.5f + y, -0.5f + z

#define BLOCK_TOP_TOPLEFT(x, y, z)         0.5f + x,  0.5f + y,  0.5f + z
#define BLOCK_TOP_BOTTOMLEFT(x, y, z)      0.5f + x,  0.5f + y, -0.5f + z
#define BLOCK_TOP_BOTTOMRIGHT(x, y, z)    -0.5f + x,  0.5f + y, -0.5f + z
#define BLOCK_TOP_TOPRIGHT(x, y, z)       -0.5f + x,  0.5f + y,  0.5f + z

#define BLOCK_BOTTOM_TOPLEFT(x, y, z)     -0.5f + x, -0.5f + y,  0.5f + z
#define BLOCK_BOTTOM_BOTTOMLEFT(x, y, z)  -0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z)  0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_BOTTOM_TOPRIGHT(x, y, z)     0.5f + x, -0.5f + y,  0.5f + z

#define BLOCK_FRONT_TOPLEFT(x, y, z)      -0.5f + x,  0.5f + y,  0.5f + z
#define BLOCK_FRONT_BOTTOMLEFT(x, y, z)   -0.5f + x, -0.5f + y,  0.5f + z
#define BLOCK_FRONT_BOTTOMRIGHT(x, y, z)   0.5f + x, -0.5f + y,  0.5f + z
#define BLOCK_FRONT_TOPRIGHT(x, y, z)      0.5f + x,  0.5f + y,  0.5f + z

#define BLOCK_BACK_TOPLEFT(x, y, z)        0.5f + x,  0.5f + y, -0.5f + z
#define BLOCK_BACK_BOTTOMLEFT(x, y, z)     0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_BACK_BOTTOMRIGHT(x, y, z)   -0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_BACK_TOPRIGHT(x, y, z)      -0.5f + x,  0.5f + y, -0.5f + z

#define BLOCK_ATLAS_WIDTH   64
#define BLOCK_ATLAS_HEIGHT  64
#define BLOCK_TILE_SIZE     16

#define BLOCK_UV_TOPLEFT(x, y)       x * BLOCK_TILE_SIZE / BLOCK_ATLAS_WIDTH      , (y + 1) * BLOCK_TILE_SIZE / BLOCK_ATLAS_HEIGHT
#define BLOCK_UV_BOTTOMLEFT(x, y)    x * BLOCK_TILE_SIZE / BLOCK_ATLAS_WIDTH      , y * BLOCK_TILE_SIZE / BLOCK_ATLAS_HEIGHT
#define BLOCK_UV_BOTTOMRIGHT(x, y)   (x + 1) * BLOCK_TILE_SIZE / BLOCK_ATLAS_WIDTH, y * BLOCK_TILE_SIZE / BLOCK_ATLAS_HEIGHT
#define BLOCK_UV_TOPRIGHT(x, y)      (x + 1) * BLOCK_TILE_SIZE / BLOCK_ATLAS_WIDTH, (y + 1) * BLOCK_TILE_SIZE / BLOCK_ATLAS_HEIGHT

#define GRASS_SIDE_UV_OFFSET  vec2(0, 3)
#define GRASS_TOP_UV_OFFSET   vec2(1, 3)
#define DIRT_UV_OFFSET        vec2(2, 3)
#define STONE_UV_OFFSET       vec2(3, 3)
#define LOG_SIDE_UV_OFFSET    vec2(0, 2)
#define LOG_TOP_UV_OFFSET     vec2(1, 2)
#define PLANK_UV_OFFSET       vec2(2, 2)
#define LEAF_UV_OFFSET        vec2(3, 2)
#define GLOWSTONE_UV_OFFSET   vec2(0, 1)
#define GLASS_UV_OFFSET       vec2(1, 1)
#define BEDROCK_UV_OFFSET     vec2(2, 1)
#define SAND_UV_OFFSET        vec2(3, 1)
#define WATER_UV_OFFSET       vec2(0, 0)
#define LAVA_UV_OFFSET        vec2(1, 0)
#define BRICKS_UV_OFFSET      vec2(2, 0)
#define COBBLESTONE_UV_OFFSET vec2(3, 0)

namespace minecraft
{
    enum class BlockFace
    {
        Left,
        Right,
        Top,
        Bottom,
        Front,
        Back,
    };

    enum class BlockType
    {
        Air,
        Grass,
        Dirt,
        Stone,
        Log,
        Plank,
        Leaf,
        Glowstone,
        Glass,
        Bedrock,
        Sand,
        Water,
        Lava,
        Bricks,
        Cobblestone,
    };

    class Block
    {
    public:
        Block() = default;
        Block(ivec3 position, BlockType type);

        bool is_transparent() const
        {
            return m_type == BlockType::Air
                || m_type == BlockType::Leaf
                || m_type == BlockType::Glass
                || m_type == BlockType::Water
                || m_type == BlockType::Lava;
        }

        bool is_solid() const
        {
            return m_type != BlockType::Air
                && m_type != BlockType::Water
                && m_type != BlockType::Lava;
        }

        vec2 get_uv_offset(BlockFace face) const;

        void set_type(BlockType type) { m_type = type; }

        ivec3 position() const { return m_position; }
        BlockType type() const { return m_type; }

    private:
        ivec3 m_position = ivec3(-1, -1, -1); // position in chunk space
        BlockType m_type = BlockType::Air;
    };
}
