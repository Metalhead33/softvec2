#ifndef CLIPSPACEPIPELINE_HPP
#define CLIPSPACEPIPELINE_HPP
#include "Pipeline/RenderingPipeline.hpp"
#include "../Texture.hpp"
#include "../ZBuffer.hpp"

struct ClipspaceUniform {
	bool perspectiveCorrection;
	Texture* tex;
	TextureFiltering sampling;
	AlphaBlending blendingMode;
	glm::ivec2 viewport;
};
struct ClipspaceVertexIn {
	glm::vec3 COORDS;
	glm::vec2 TEXCOORD;
};
struct ClipspaceVertexOut {
	glm::vec3 COORDS;
	glm::vec2 TEXCOORD;
	inline static ClipspaceVertexOut split(const ClipspaceVertexOut& t, const ClipspaceVertexOut& m, const ClipspaceVertexOut& b, float dy, float iy) {
		return { glm::vec3(
						t.COORDS.x + ((b.COORDS.x - t.COORDS.x) / dy) * iy,
						m.COORDS.y,
						t.COORDS.z + ((b.COORDS.z - t.COORDS.z) / dy) * iy
						),
					glm::vec2(
						t.TEXCOORD.r + ((b.TEXCOORD.r - t.TEXCOORD.r) / dy) * iy,
						t.TEXCOORD.g + ((b.TEXCOORD.g - t.TEXCOORD.g) / dy) * iy
						) };
	}
};

ClipspaceVertexOut clipspaceVertexShader(const ClipspaceUniform& uniform, const ClipspaceVertexIn& input);
void clipspaceFragmentShader(Framebuffer& framebuffer,const ClipspaceUniform& uniform, const ClipspaceVertexOut& v0,const ClipspaceVertexOut& v1,const ClipspaceVertexOut& v2, float w0,float w1,float w2,const glm::ivec2& screenCoord);
typedef Pipeline<ClipspaceVertexIn,ClipspaceVertexOut,ClipspaceUniform,clipspaceVertexShader,clipspaceFragmentShader> ClipspacePipeline;

#endif // CLIPSPACEPIPELINE_HPP
