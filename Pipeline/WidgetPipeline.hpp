#ifndef WIDGETPIPELINE_HPP
#define WIDGETPIPELINE_HPP
#include "Pipeline/ClipspacePipeline.hpp"
#include "../Texture.hpp"

struct WidgetUniform {
	Texture* tex;
	TextureFiltering sampling;
	AlphaBlending blendingMode;
	glm::ivec2 size;
	glm::ivec2 offset;
};
struct WidgetVertexIn {
	glm::vec2 COORDS;
	glm::vec2 TEXCOORD;
};
struct WidgetVertexOut {
	glm::vec2 COORDS;
	glm::vec2 TEXCOORD;
	inline static WidgetVertexOut split(const WidgetVertexOut& t, const WidgetVertexOut& m, const WidgetVertexOut& b, float dy, float iy) {
		return { glm::vec2(
						t.COORDS.x + ((b.COORDS.x - t.COORDS.x) / dy) * iy,
						m.COORDS.y
						),
					glm::vec2(
						t.TEXCOORD.r + ((b.TEXCOORD.r - t.TEXCOORD.r) / dy) * iy,
						t.TEXCOORD.g + ((b.TEXCOORD.g - t.TEXCOORD.g) / dy) * iy
						) };
	}
};

WidgetVertexOut widgetVertexShader(const WidgetUniform& uniform, const WidgetVertexIn& input);
void widgetFragmentShader(Framebuffer& framebuffer,const WidgetUniform& uniform, const WidgetVertexOut& v0,const WidgetVertexOut& v1,const WidgetVertexOut& v2, float w0,float w1,float w2,const glm::ivec2& screenCoord);
typedef Pipeline<WidgetVertexIn,WidgetVertexOut,WidgetUniform,widgetVertexShader,widgetFragmentShader> WidgetPipeline;

#endif // WIDGETPIPELINE_HPP
