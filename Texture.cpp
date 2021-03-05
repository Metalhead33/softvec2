#include "Texture.hpp"

void Texture::sampleNearestNeighbour(const glm::vec2 &uv, glm::vec4 &col) const
{
	getPixel(glm::ivec2( int(std::round(uv.x * float(getW()-1))), int(std::round(uv.y * float(getH()-1))) ),col);
}

static const glm::vec2 LOOKUP[2][2] = {
{  glm::vec2( 0.25f, 0.00f ), glm::vec2( 0.50f, 0.75f ) },
{  glm::vec2( 0.75f, 0.50f ), glm::vec2( 0.00f, 0.25f ) }
};

void Texture::sampleDithered(const glm::vec2 &uv, const glm::ivec2 &screencoords, glm::vec4 &col) const
{
	glm::vec2 texelCoords = glm::vec2(uv.x * float(getW()-1),uv.y * float(getH()-1));
	texelCoords += LOOKUP[screencoords[1]&1][screencoords[0]&1];
	getPixel(glm::ivec2( int(std::round(texelCoords.x)),int(std::round(texelCoords.y)) ),col);
}

void Texture::sampleBilinear(const glm::vec2 &uv, glm::vec4 &col) const
{
	const glm::vec2 tmp = glm::vec2(uv.x * float(getW()-1),uv.y * float(getH()-1));
	const glm::vec2 coordEdgeTopLeft( std::floor(tmp[0]), std::floor(tmp[1]) );
	const glm::vec2 coordEdgeTopRight( std::ceil(tmp[0]), std::floor(tmp[1]) );
	const glm::vec2 coordEdgeBottomLeft( std::floor(tmp[0]), std::ceil(tmp[1]) );
	const glm::vec2 coordEdgeBottomRight( std::ceil(tmp[0]), std::ceil(tmp[1]) );
	const glm::vec2 weight = tmp - coordEdgeTopLeft;
	glm::vec4 colourTopLeft, colourTopRight, colourBottomLeft, colourBottomRight;
	getPixel(glm::ivec2( int(coordEdgeTopLeft[0]),int(coordEdgeTopLeft[1]) ),colourTopLeft );
	getPixel(glm::ivec2( int(coordEdgeTopRight[0]),int(coordEdgeTopRight[1]) ),colourTopRight );
	getPixel(glm::ivec2( int(coordEdgeBottomLeft[0]),int(coordEdgeBottomLeft[1]) ),colourBottomLeft );
	getPixel(glm::ivec2( int(coordEdgeBottomRight[0]),int(coordEdgeBottomRight[1]) ),colourBottomRight );
	colourTopLeft *= (weight[0] * weight[1]);
	colourTopRight *= ((1.0f-weight[0]) * weight[1]);
	colourBottomLeft *= (weight[0] * (1.0f-weight[1]));
	colourBottomRight *= ((1.0f-weight[0]) * (1.0f-weight[1]));
	col = colourTopLeft + colourTopRight + colourBottomLeft + colourBottomRight;
}

glm::vec4 Texture::getPixel(const glm::ivec2 &pos)
{
	glm::vec4 tmp;
	getPixel(pos,tmp);
	return tmp;
}

glm::vec4 Texture::sampleNearestNeighbour(const glm::vec2 &uv) const
{
	glm::vec4 tmp;
	sampleNearestNeighbour(uv,tmp);
	return tmp;
}

glm::vec4 Texture::sampleDithered(const glm::vec2 &uv, const glm::ivec2 &screencoords) const
{
	glm::vec4 tmp;
	sampleDithered(uv,screencoords,tmp);
	return tmp;
}

glm::vec4 Texture::sampleBilinear(const glm::vec2 &uv) const
{
	glm::vec4 tmp;
	sampleBilinear(uv,tmp);
	return tmp;
}
