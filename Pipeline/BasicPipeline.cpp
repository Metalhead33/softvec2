#include "BasicPipeline.hpp"

BasicVertexOut basicVertexShader(const BasicUniform& uniform, const BasicVertexIn& input) {
	return { glm::vec2(
					(input.COORDS[0] + 1.0f) / 2.0f * uniform.framebuffer->getW(),
					((input.COORDS[1]-1.0f) / -2.0f) * uniform.framebuffer->getH()
					), input.COLOUR };
}
void basicFragmentShader(const BasicUniform& uniform, const BasicVertexOut& v0,const BasicVertexOut& v1,const BasicVertexOut& v2,
							float w0,float w1,float w2,const glm::ivec2& screenCoord) {
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	glm::vec4 colourKernel = {
					(w0 * v0.COLOUR.r) + (w1 * v1.COLOUR.r) + (w2 * v2.COLOUR.r),
					(w0 * v0.COLOUR.g) + (w1 * v1.COLOUR.g) + (w2 * v2.COLOUR.g),
					(w0 * v0.COLOUR.b) + (w1 * v1.COLOUR.b) + (w2 * v2.COLOUR.b),
					(w0 * v0.COLOUR.a) + (w1 * v1.COLOUR.a) + (w2 * v2.COLOUR.a)
					};
	uniform.framebuffer->setPixelWithBlending(screenCoord,colourKernel,uniform.blendingMode);
}
