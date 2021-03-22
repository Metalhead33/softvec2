#ifndef BASICPIPELINE_HPP
#define BASICPIPELINE_HPP
#include "Pipeline/RenderingPipeline.hpp"
#include "../Texture.hpp"

struct BasicUniform {
	Texture* framebuffer;
	AlphaBlending blendingMode;
};
struct BasicVertexIn {
	glm::vec3 COORDS;
	glm::vec4 COLOUR;
};
struct BasicVertexOut {
	glm::vec2 COORDS;
	glm::vec4 COLOUR;
	inline static BasicVertexOut split(const BasicVertexOut& t, const BasicVertexOut& m, const BasicVertexOut& b, float dy, float iy) {
		return { glm::vec2(
						t.COORDS.x + ((b.COORDS.x - t.COORDS.x) / dy) * iy,
						m.COORDS.y
						),
					glm::vec4(
						t.COLOUR.r + ((b.COLOUR.r - t.COLOUR.r) / dy) * iy,
						t.COLOUR.g + ((b.COLOUR.g - t.COLOUR.g) / dy) * iy,
						t.COLOUR.b + ((b.COLOUR.b - t.COLOUR.b) / dy) * iy,
						t.COLOUR.a + ((b.COLOUR.a - t.COLOUR.a) / dy) * iy
						) };
	}
};
BasicVertexOut basicVertexShader(const BasicUniform& uniform, const BasicVertexIn& input);
void basicFragmentShader(const BasicUniform& uniform, const BasicVertexOut& v0,const BasicVertexOut& v1,const BasicVertexOut& v2, float w0,float w1,float w2,const glm::ivec2& screenCoord);
typedef Pipeline<BasicVertexIn,BasicVertexOut,BasicUniform,basicVertexShader,basicFragmentShader> BasicPipeline;


#endif // BASICPIPELINE_HPP
