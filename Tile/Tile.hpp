#ifndef TILE_HPP
#define TILE_HPP
#include "Terrain.hpp"
#include <vector>
#include <glm/glm.hpp>

struct Tile {
	Terrain terrainType;
};

struct Grid {
	std::vector<Tile> tiles;
	unsigned w,h;
	Grid(unsigned w, unsigned h);
	Grid(const Grid& cpy);
	Grid& operator=(const Grid& cpy);
	Grid(Grid&& mov);
	Grid& operator=(Grid&& mov);

	Tile& get(const glm::ivec2& coord);
	const Tile& get(const glm::ivec2& coord) const;
	Tile& operator[](const glm::ivec2& coord);
	const Tile& operator[](const glm::ivec2& coord) const;
};

#endif // TILE_HPP
