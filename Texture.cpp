#include "Texture.hpp"

void Texture::sample(const glm::vec2 &uv, const glm::ivec2 &screencoords, glm::vec4 &col, TextureFiltering filteringType) const
{
	switch (filteringType) {
	case TextureFiltering::NEAREST_NEIGHBOUR:
		sampleNearestNeighbour(uv,col);
		break;
	case TextureFiltering::DITHERED:
		sampleDithered(uv,screencoords,col);
		break;
	case TextureFiltering::BILINEAR:
		sampleBilinear(uv,col);
		break;
	default:
		break;
	}
}

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

glm::vec4 Texture::sample(const glm::vec2 &uv, const glm::ivec2 &screencoords, TextureFiltering filteringType) const
{
	glm::vec4 tmp;
	sample(uv,screencoords,tmp,filteringType);
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

void Texture::clearToColour(const glm::vec4 &colour)
{
	iterateOverPixels([&colour](glm::vec4& dst) { dst = colour; }, false );
}

const glm::vec4 thresholdMatrix[4] = {
glm::vec4(1.0 / 17.0,  9.0 / 17.0,  3.0 / 17.0, 11.0 / 17.0),
glm::vec4(13.0 / 17.0,  5.0 / 17.0, 15.0 / 17.0,  7.0 / 17.0),
glm::vec4(4.0 / 17.0, 12.0 / 17.0,  2.0 / 17.0, 10.0 / 17.0),
glm::vec4(16.0 / 17.0,  8.0 / 17.0, 14.0 / 17.0,  6.0 / 17.0)
};

bool Texture::setPixelWithBlending(const glm::ivec2 &pos, const glm::vec4 &col, AlphaBlending blendingMode)
{
	float a = col.a;
	if(blendingMode == AlphaBlending::DITHERED) a = (a >= thresholdMatrix[pos.x % 4][pos.y % 4]) ? 1.0f : 0.0f;
	if(a >= 0.99607843137255f) {
		setPixelDithered(pos,col,0.5f);
		//setPixel(pos,col);
		return true;
	} else if(a <= 0.003921568627451f) {
		return false;
	} else {
		glm::vec4 kernel = getPixel(pos);
		const float rem = 1.0f - a;
		kernel.r = (kernel.r * rem) + (col.r * a);
		kernel.g = (kernel.g * rem) + (col.g * a);
		kernel.b = (kernel.b * rem) + (col.b * a);
		kernel.a = std::min(1.0f,kernel.a + a);
		setPixelDithered(pos,kernel,0.5f);
		return true;
	}
}
