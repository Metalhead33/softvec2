#ifndef MODELPIPELINE_HPP
#define MODELPIPELINE_HPP
#include "Pipeline/ClipspacePipeline.hpp"
#include "../Texture.hpp"
#include "../ZBuffer.hpp"

struct ModelUniform {
	Texture* framebuffer;
	ZBuffer* zbuffer;
	bool perspectiveCorrection;
	Texture* tex;
	TextureFiltering sampling;
	AlphaBlending blendingMode;
	//glm::mat4 mvp;
	glm::mat4 model,proj;
	glm::vec4 viewport;
};
typedef ClipspaceVertexIn ModelVertexIn;
struct ModelVertexOut {
	glm::vec3 COORDS;
	glm::vec2 TEXCOORD;
	inline static ModelVertexOut split(const ModelVertexOut& t, const ModelVertexOut& m, const ModelVertexOut& b, float dy, float iy) {
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

ModelVertexOut modelVertexShader(const ModelUniform& uniform, const ModelVertexIn& input);
void modelFragmentShader(const ModelUniform& uniform, const ModelVertexOut& v0,const ModelVertexOut& v1,const ModelVertexOut& v2, float w0,float w1,float w2,const glm::ivec2& screenCoord);
typedef Pipeline<ModelVertexIn,ModelVertexOut,ModelUniform,modelVertexShader,modelFragmentShader> ModelPipeline;

#endif // MODELPIPELINE_HPP
