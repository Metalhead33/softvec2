#ifndef MODEL2PIPELINE_HPP
#define MODEL2PIPELINE_HPP
#include "Pipeline/ClipspacePipeline.hpp"
#include "../Texture.hpp"
#include "../ZBuffer.hpp"

struct Model2Uniform {
	bool perspectiveCorrection;
	Texture* tex;
	TextureFiltering sampling;
	AlphaBlending blendingMode;
	//glm::mat4 mvp;
	glm::mat4 mvp;
	glm::vec2 viewport;
};
typedef ClipspaceVertexIn Model2VertexIn;
struct Model2VertexOut {
	glm::vec3 COORDS;
	glm::vec2 TEXCOORD;
	inline static Model2VertexOut split(const Model2VertexOut& t, const Model2VertexOut& m, const Model2VertexOut& b, float dy, float iy) {
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

Model2VertexOut model2VertexShader(const Model2Uniform& uniform, const Model2VertexIn& input);
void model2FragmentShader(Framebuffer& framebuffer,const Model2Uniform& uniform, const Model2VertexOut& v0,const Model2VertexOut& v1,const Model2VertexOut& v2, float w0,float w1,float w2,const glm::ivec2& screenCoord);
typedef Pipeline<Model2VertexIn,Model2VertexOut,Model2Uniform,model2VertexShader,model2FragmentShader> Model2Pipeline;
#endif // MODEL2PIPELINE_HPP
