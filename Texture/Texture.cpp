#include "Texture.hpp"
#include <cmath>

typedef mat<fvec2,2,2> OrderedDitherLookupTable;
const OrderedDitherLookupTable LOOKUP = {{
	{{  { 0.25f, 0.00f }, { 0.50f, 0.75f } }},
	{{  { 0.75f, 0.50f }, { 0.00f, 0.25f } }}
}};

void Texture::getPixelNearestNeighbour(fvec4 &dst, const fvec2 &coords) const
{
	const fvec2 tmp = coords * fvec2{ getFWidth(), getFHeight() };
	storePixelTo(dst,ivec2{ int(std::round(tmp[0])),int(std::round(tmp[1])) } );
}

void Texture::getPixelOrderedDithering(fvec4 &dst, const fvec2 &coords, const ivec2 &screenCoords) const
{
	const fvec2 tmp = coords * fvec2{ getFWidth(), getFHeight() }  + LOOKUP[screenCoords[1]&1][screenCoords[0]&1];
	storePixelTo(dst,ivec2{ int(std::round(tmp[0])),int(std::round(tmp[1])) } );
}

void Texture::getPixelBilinear(fvec4 &dst, const fvec2 &coords) const
{
	const fvec2 tmp = coords * fvec2{ getFWidth(), getFHeight() };
	const fvec2 coordEdgeTopLeft{ std::floor(coords[0]), std::floor(coords[1]) };
	const fvec2 coordEdgeTopRight{ std::ceil(coords[0]), std::floor(coords[1]) };
	const fvec2 coordEdgeBottomLeft{ std::floor(coords[0]), std::ceil(coords[1]) };
	const fvec2 coordEdgeBottomRight{ std::ceil(coords[0]), std::ceil(coords[1]) };
	const fvec2 weight = tmp - coordEdgeTopLeft;
	fvec4 colourTopLeft, colourTopRight, colourBottomLeft, colourBottomRight;
	storePixelTo(colourTopLeft,ivec2{ int(coordEdgeTopLeft[0]),int(coordEdgeTopLeft[1]) } );
	storePixelTo(colourTopRight,ivec2{ int(coordEdgeTopRight[0]),int(coordEdgeTopRight[1]) } );
	storePixelTo(colourBottomLeft,ivec2{ int(coordEdgeBottomLeft[0]),int(coordEdgeBottomLeft[1]) } );
	storePixelTo(colourBottomRight,ivec2{ int(coordEdgeBottomRight[0]),int(coordEdgeBottomRight[1]) } );
	colourTopLeft *= (weight[0] * weight[1]);
	colourTopRight *= ((1.0f-weight[0]) * weight[1]);
	colourBottomLeft *= (weight[0] * (1.0f-weight[1]));
	colourBottomRight *= ((1.0f-weight[0]) * (1.0f-weight[1]));
	dst = colourTopLeft + colourTopRight + colourBottomLeft + colourBottomRight;
}

void Texture::blendPixels(const fvec4 &src, const ivec2 &coords)
{
	if(src[3] >= 1.0f)
	{
		loadPixelFrom(src,coords);
	} else if(src[3] >= 0.003921568627451f) {
		fvec4 kernel;
		storePixelTo(kernel,coords);
		kernel *= (1.0f - src[3]);
		kernel += (src * src[3]);
		kernel[3] = 1.0f;
		loadPixelFrom(kernel,coords);
	}
}
