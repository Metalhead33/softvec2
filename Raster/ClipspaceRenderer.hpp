#ifndef CLIPSPACERENDERER_HPP
#define CLIPSPACERENDERER_HPP
#include "../vecdefs.hpp"
#include "../Texture/Texture.hpp"
#include "SortTriangle.hpp"
#include <vector>
typedef std::vector<float> ZBuffer;

struct ClipspaceVertex {
	fvec3 coords;
	fvec2 texcoords;
};

void renderClipspace(ZBuffer& zbuffer, Texture& framebuffer, const fvec4& viewport, const Texture& texture,
					 const ClipspaceVertex* A, const ClipspaceVertex* B, const ClipspaceVertex* C);
void renderClipspace(ZBuffer& zbuffer, Texture& framebuffer, const fvec4& viewport, const Texture& texture,
					 const ClipspaceVertex* vertices, size_t vertexCount);
void renderClipspace(ZBuffer& zbuffer, Texture& framebuffer, const fvec4& viewport, const Texture& texture,
					 const ClipspaceVertex* vertices, int* indices, size_t indexCount);

#endif // CLIPSPACERENDERER_HPP
