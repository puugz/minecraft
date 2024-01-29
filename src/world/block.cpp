//
// Created by Matej on 18/01/2024.
//

#include "world/block.h"

using namespace minecraft;

Block::Block(ivec3 position, BlockType type)
{
	m_position = position;
	m_type = type;
}

vec2 Block::get_uv_offset(BlockFace face) const
{
	if (m_type == BlockType::Grass)
	{
		if (face == BlockFace::Top)
			return GRASS_TOP_UV_OFFSET;
		if (face == BlockFace::Bottom)
			return DIRT_UV_OFFSET;
		return GRASS_SIDE_UV_OFFSET;
	}
	if (m_type == BlockType::Dirt)
		return DIRT_UV_OFFSET;
	if (m_type == BlockType::Stone)
		return STONE_UV_OFFSET;
	if (m_type == BlockType::Log)
	{
		if (face == BlockFace::Top
			|| face == BlockFace::Bottom)
			return LOG_TOP_UV_OFFSET;
		return LOG_SIDE_UV_OFFSET;
	}
	if (m_type == BlockType::Plank)
		return PLANK_UV_OFFSET;
	if (m_type == BlockType::Leaf)
		return LEAF_UV_OFFSET;
	if (m_type == BlockType::Glowstone)
		return GLOWSTONE_UV_OFFSET;
	if (m_type == BlockType::Glass)
		return GLASS_UV_OFFSET;
	if (m_type == BlockType::Bedrock)
		return BEDROCK_UV_OFFSET;
	if (m_type == BlockType::Sand)
		return SAND_UV_OFFSET;
	if (m_type == BlockType::Water)
		return WATER_UV_OFFSET;
	if (m_type == BlockType::Lava)
		return LAVA_UV_OFFSET;
	if (m_type == BlockType::Bricks)
		return BRICKS_UV_OFFSET;
	if (m_type == BlockType::Cobblestone)
		return COBBLESTONE_UV_OFFSET;

	return STONE_UV_OFFSET;
}
