#include "ClipspaceRenderer.hpp"
#include <algorithm>


void renderClipspace(ZBuffer &zbuffer, Texture &framebuffer, const fvec4 &viewport, const Texture &texture, const ClipspaceVertex *A, const ClipspaceVertex *B, const ClipspaceVertex *C)
{
	CloickwiseOrderVERT<ClipspaceVertex>::sortTriangle(&A,&B,&C);
	auto v0 = NDCspace2rasterspace(A->coords,viewport);
	auto v1 = NDCspace2rasterspace(B->coords,viewport);
	auto v2 = NDCspace2rasterspace(C->coords,viewport);
	const float weighter = 1.0f / TriangleUtilities<float>::edgeFunction(v0,v1,v2);
	fvec4 colour;
	v0[2] = 1.0f / v0[2];
	v1[2] = 1.0f / v1[2];
	v2[2] = 1.0f / v2[2];

	auto boundingBox = TriangleUtilities<float>::createBoundingBox(*reinterpret_cast<const TriangleUtilities<float>::Vector4D*>(viewport.data()),v0,v1,v2);
	const unsigned minX = std::max(unsigned(boundingBox[0][0]),unsigned(0));
	const unsigned maxX = std::min(unsigned(boundingBox[1][0]),framebuffer.getWidth());
	const unsigned minY = std::max(unsigned(boundingBox[0][1]),unsigned(0));
	const unsigned maxY = std::min(unsigned(boundingBox[1][1]),framebuffer.getHeight());

	if(minY > framebuffer.getHeight() || maxY < 0 || minX > framebuffer.getWidth() || maxX < 0)
		return;
	for (unsigned j = minY; j < maxY; ++j) {
		for (unsigned i = minX; i < maxX; ++i) {
			fvec2 p = {i + 0.5f, j + 0.5f};
			const float w0 = TriangleUtilities<float>::edgeFunction(v1, v2, p) / weighter;
			const float w1 = TriangleUtilities<float>::edgeFunction(v2, v0, p) / weighter;
			const float w2 = TriangleUtilities<float>::edgeFunction(v0, v1, p) / weighter;
			const float z = 1.0f / (w0 * v0[2] + w1 * v1[2] + w2 * v2[2]);
			auto& zbuffpoint = zbuffer[(framebuffer.getWidth() * j)+i];
			if (w0 >= 0 && w1 >= 0 && w2 >= 0 && z < 0.0f && z < zbuffpoint)
			{
				zbuffpoint = z;
				const fvec2 textCoordKernel = {
					((w0 * A->texcoords[0] + w1 * B->texcoords[0] + w2 * C->texcoords[0])),
					(1.0f-(w0 * A->texcoords[1] + w1 * B->texcoords[1] + w2 * C->texcoords[1]))};
				texture.getPixelNearestNeighbour(colour,textCoordKernel);
				framebuffer.blendPixels(colour,{int(i),int(j)});
			}
		}
	}
}

void renderClipspace(ZBuffer &zbuffer, Texture &framebuffer, const fvec4 &viewport, const Texture &texture, const ClipspaceVertex *vertices, size_t vertexCount)
{
	for(size_t i = 0; i < vertexCount; i += 3)
	{
		const ClipspaceVertex& v0 = vertices[i];
		const ClipspaceVertex& v1 = vertices[i+1];
		const ClipspaceVertex& v2 = vertices[i+2];
		renderClipspace(zbuffer,framebuffer,viewport,texture,&v0,&v1,&v2);
	}
}

void renderClipspace(ZBuffer &zbuffer, Texture &framebuffer, const fvec4 &viewport, const Texture &texture, const ClipspaceVertex *vertices, int *indices, size_t indexCount)
{
	for(size_t i = 0; i < indexCount; i += 3)
	{
		const ClipspaceVertex& v0 = vertices[indices[i]];
		const ClipspaceVertex& v1 = vertices[indices[i+1]];
		const ClipspaceVertex& v2 = vertices[indices[i+2]];
		renderClipspace(zbuffer,framebuffer,viewport,texture,&v0,&v1,&v2);
	}
}
