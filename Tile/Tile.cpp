#include "Tile.hpp"

Grid::Grid(unsigned w, unsigned h): tiles(w*h), w(w), h(h)
{

}

Grid::Grid(const Grid &cpy) : tiles(cpy.tiles), w(cpy.w), h(cpy.h)
{

}

Grid &Grid::operator=(const Grid &cpy)
{
	this->tiles = cpy.tiles;
	this->w = cpy.w;
	this->h = cpy.h;
	return *this;
}

Grid::Grid(Grid &&mov) : tiles(std::move(mov.tiles)), w(mov.w), h(mov.h)
{

}

Grid &Grid::operator=(Grid &&mov)
{
	this->tiles = std::move(mov.tiles);
	this->w = mov.w;
	this->h = mov.h;
	return *this;
}

Tile &Grid::get(const glm::ivec2 &coord)
{
	return tiles[(coord.y*w)+coord.x];
}

const Tile &Grid::get(const glm::ivec2 &coord) const
{
	return tiles[(coord.y*w)+coord.x];
}

Tile &Grid::operator[](const glm::ivec2 &coord)
{
	return tiles[(coord.y*w)+coord.x];
}

const Tile &Grid::operator[](const glm::ivec2 &coord) const
{
	return tiles[(coord.y*w)+coord.x];
}
