#include "ClipspacePipeline.hpp"

ClipspaceVertexOut clipspaceVertexShader(const ClipspaceUniform &uniform, const ClipspaceVertexIn &input)
{
	ClipspaceVertexOut out{glm::vec3( (input.COORDS[0] + 1.0f) / 2.0f * uniform.viewport.x,
				((input.COORDS[1]-1.0f) / -2.0f) * uniform.viewport.y,
				(input.COORDS[2] * -1.0f) ), input.TEXCOORD};
	if(uniform.perspectiveCorrection) out.TEXCOORD /= out.COORDS.z;
	return out;
}

void clipspaceFragmentShader(Framebuffer& framebuffer,const ClipspaceUniform &uniform, const ClipspaceVertexOut &v0, const ClipspaceVertexOut &v1, const ClipspaceVertexOut &v2, float w0, float w1, float w2, const glm::ivec2 &screenCoord)
{
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	const float z = 1.0f / (w0 * v0.COORDS.z + w1 * v1.COORDS.z + w2 * v2.COORDS.z);
	float& zbuffpoint = framebuffer.getZbuffer()->get(screenCoord.x,screenCoord.y);
	if(z <= 0.0f && z <= zbuffpoint) {
	glm::vec2 texCoord = {
					(w0 * v0.TEXCOORD.r) + (w1 * v1.TEXCOORD.r) + (w2 * v2.TEXCOORD.r),
					(w0 * v0.TEXCOORD.g) + (w1 * v1.TEXCOORD.g) + (w2 * v2.TEXCOORD.g)
					};
	if(uniform.perspectiveCorrection) texCoord *= z;
	glm::vec4 pixelOut = uniform.tex->sample(texCoord,screenCoord,uniform.sampling);
	if ( framebuffer.getTexture()->setPixelWithBlending(screenCoord,pixelOut,uniform.blendingMode) ) zbuffpoint = z;
	}
}
