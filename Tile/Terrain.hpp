#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include "../Texture.hpp"
#include <cstdint>
#include <array>

enum Terrain {
	WATER = 0,
	DIRT,
	GRASS,
	SWAMP,
	SNOW,
	ICE,
	SAND,
	ROCK,
	LAVA,
	TERRAIN_MAX
};

extern std::array<sTexture,Terrain::TERRAIN_MAX> TerrainTextures;
void initializeTerrainTextures();

#endif // TERRAIN_HPP
