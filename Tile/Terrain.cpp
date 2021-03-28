#include "Terrain.hpp"
#include "../CreateTexture.hpp"
#include <MhLib/Io/MhFile.hpp>

std::array<sTexture,Terrain::TERRAIN_MAX> TerrainTextures;

/*
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
*/

const char* TerrainTexturePaths[] = {
	"tiles/water.png",
	"tiles/dirt.png",
	"tiles/grass.png",
	"tiles/swamp.png",
	"tiles/snow.png",
	"tiles/ice.png",
	"tiles/sand.png",
	"tiles/rock.png",
	"tiles/lava.png"
};

bool initialized = false;
void initializeTerrainTextures()
{
	if(!initialized) {
		for(int i = Terrain::WATER; i < Terrain::TERRAIN_MAX; ++i ) {
			MH33::Io::File importedTex(TerrainTexturePaths[i],MH33::Io::Mode::READ);
			TerrainTextures[i] = textureFromPNG(importedTex);
		}
		initialized = true;
	}
}
