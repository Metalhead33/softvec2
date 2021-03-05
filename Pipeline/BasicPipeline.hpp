#ifndef BASICPIPELINE_HPP
#define BASICPIPELINE_HPP
#include "Pipeline/RenderingPipeline.hpp"
#include "../Texture.hpp"

struct BasicUniform {
	Texture* framebuffer;
};
struct BasicVertexIn {
	glm::vec3 COORDS;
	glm::vec4 COLOUR;
};
struct BasicVertexOut {
	glm::vec2 COORDS;
	glm::vec4 COLOUR;
	/*
			VertexOutput v4 = VertexOutput::split(*t,*m,*b,dy,iy);
			/*v4.COORDS.y = m->COORDS.y;
			v4.COORDS.x = t->COORDS.x + ((b->COORDS.x - t->COORDS.x) / dy) * iy;
			if (PixelShader::InterpolateZ) v4.z = t->z + ((b->z - t->z) / dy) * iy;
			if (PixelShader::InterpolateW) v4.w = t->w + ((b->w - t->w) / dy) * iy;
			v4.COLOUR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			for (int i = 0; i < PixelShader::VarCount; ++i)
			  v4.var[i] = t->var[i] + ((b->var[i] - t->var[i]) / dy) * iy;*/
	inline static BasicVertexOut split(const BasicVertexOut& t, const BasicVertexOut& m, const BasicVertexOut& b, float dy, float iy) {
		return { glm::vec2(
						m.COORDS.y,
						t.COORDS.x + ((b.COORDS.x - t.COORDS.x) / dy) * iy
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
typedef Pipeline<BasicVertexIn,BasicVertexOut,BasicUniform> BasicPipeline;


#endif // BASICPIPELINE_HPP
