#include "TriangleSort.hpp"

bool isPrecedingClockwise(const glm::ivec2 &a, const glm::ivec2 &b)
{
	if(a.y == b.y) // If they are equal we will order by X instead of Y
		return (a.x > b.x);
	else
		return (a.y > b.y);
}

bool isPrecedingClockwise(const glm::vec2 &a, const glm::vec2 &b)
{
	if(a.y == b.y) // If they are equal we will order by X instead of Y
		return (a.x > b.x);
	else
		return (a.y > b.y);
}

bool isPrecedingClockwise(const glm::vec3 &a, const glm::vec3 &b)
{
	if(a.y == b.y) // If they are equal we will order by X instead of Y
		return (a.x > b.x);
	else
		return (a.y > b.y);
}

float edgeFunction(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c)
{
	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
}

int edgeFunction(const glm::ivec2 &a, const glm::ivec2 &b, const glm::ivec2 &c)
{
	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
}
