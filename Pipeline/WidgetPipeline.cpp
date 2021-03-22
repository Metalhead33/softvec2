#include "WidgetPipeline.hpp"

WidgetVertexOut widgetVertexShader(const WidgetUniform &uniform, const WidgetVertexIn &input)
{
	return {glm::vec2(
				(((input.COORDS[0] + 1.0f) / 2.0f) * float(uniform.size.x)) + float(uniform.offset.x),
				(((input.COORDS[1]-1.0f) / -2.0f) * float(uniform.size.y)) + float(uniform.offset.y)
				), input.TEXCOORD};
}

void widgetFragmentShader(const WidgetUniform &uniform, const WidgetVertexOut &v0, const WidgetVertexOut &v1, const WidgetVertexOut &v2, float w0, float w1, float w2, const glm::ivec2 &screenCoord)
{
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	glm::vec2 texCoord = {
					(w0 * v0.TEXCOORD.r) + (w1 * v1.TEXCOORD.r) + (w2 * v2.TEXCOORD.r),
					(w0 * v0.TEXCOORD.g) + (w1 * v1.TEXCOORD.g) + (w2 * v2.TEXCOORD.g)
					};
	uniform.framebuffer->setPixelWithBlending(screenCoord,uniform.tex->sample(texCoord,screenCoord,uniform.sampling),uniform.blendingMode);
}
