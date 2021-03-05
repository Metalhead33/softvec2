#include "ClipspacePipeline.hpp"

ClipspaceVertexOut clipspaceVertexShader(const ClipspaceUniform &uniform, const ClipspaceVertexIn &input)
{
	ClipspaceVertexOut out{glm::vec3( (input.COORDS[0] + 1.0f) / 2.0f * uniform.framebuffer->getW(),
				((input.COORDS[1]-1.0f) / -2.0f) * uniform.framebuffer->getH(),
				(input.COORDS[2] * -1.0f) ), input.TEXCOORD};
	if(uniform.perspectiveCorrection) out.TEXCOORD /= out.COORDS.z;
	return out;
}

void clipspaceFragmentShader(const ClipspaceUniform &uniform, const ClipspaceVertexOut &v0, const ClipspaceVertexOut &v1, const ClipspaceVertexOut &v2, float w0, float w1, float w2, const glm::ivec2 &screenCoord)
{
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	const float z = 1.0f / (w0 * v0.COORDS.z + w1 * v1.COORDS.z + w2 * v2.COORDS.z);
	float& zbuffpoint = uniform.zbuffer->get(screenCoord.x,screenCoord.y);
	if(z <= 0.0f && z <= zbuffpoint) {
	zbuffpoint = z;
	glm::vec2 texCoord = {
					(w0 * v0.TEXCOORD.r) + (w1 * v1.TEXCOORD.r) + (w2 * v2.TEXCOORD.r),
					(w0 * v0.TEXCOORD.g) + (w1 * v1.TEXCOORD.g) + (w2 * v2.TEXCOORD.g)
					};
	if(uniform.perspectiveCorrection) texCoord *= z;
	switch (uniform.sampling) {
	case TextureFiltering::NEAREST_NEIGHBOUR:
		uniform.framebuffer->setPixel(screenCoord,uniform.tex->sampleNearestNeighbour(texCoord));
		break;
	case TextureFiltering::DITHERED:
		uniform.framebuffer->setPixel(screenCoord,uniform.tex->sampleDithered(texCoord,screenCoord));
		break;
	case TextureFiltering::BILINEAR:
		uniform.framebuffer->setPixel(screenCoord,uniform.tex->sampleBilinear(texCoord));
		break;
	default:
		break;
	}
	}
}
ClipspaceVertexOut clipspaceVertexShader2(const ClipspaceUniformMoving &uniform, const ClipspaceVertexIn &input)
{
	ClipspaceVertexOut out{glm::vec3( (input.COORDS[0]+uniform.offset+ 1.0f) / 2.0f * uniform.framebuffer->getW(),
				((input.COORDS[1]+uniform.offset-1.0f) / -2.0f) * uniform.framebuffer->getH(),
				(input.COORDS[2] * -1.0f) ), input.TEXCOORD};
	if(uniform.perspectiveCorrection) out.TEXCOORD /= out.COORDS.z;
	return out;
}

void clipspaceFragmentShader2(const ClipspaceUniformMoving &uniform, const ClipspaceVertexOut &v0, const ClipspaceVertexOut &v1, const ClipspaceVertexOut &v2, float w0, float w1, float w2, const glm::ivec2 &screenCoord)
{
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	const float z = 1.0f / (w0 * v0.COORDS.z + w1 * v1.COORDS.z + w2 * v2.COORDS.z);
	float& zbuffpoint = uniform.zbuffer->get(screenCoord.x,screenCoord.y);
	if(z <= 0.0f && z <= zbuffpoint) {
	zbuffpoint = z;
	glm::vec2 texCoord = {
					(w0 * v0.TEXCOORD.r) + (w1 * v1.TEXCOORD.r) + (w2 * v2.TEXCOORD.r),
					(w0 * v0.TEXCOORD.g) + (w1 * v1.TEXCOORD.g) + (w2 * v2.TEXCOORD.g)
					};
	if(uniform.perspectiveCorrection) texCoord *= z;
	glm::vec4 colourKernel;
	switch (uniform.sampling) {
	case TextureFiltering::NEAREST_NEIGHBOUR:
		uniform.tex->sampleNearestNeighbour(texCoord,colourKernel);
		break;
	case TextureFiltering::DITHERED:
		uniform.tex->sampleDithered(texCoord,screenCoord,colourKernel);
		break;
	case TextureFiltering::BILINEAR:
		uniform.tex->sampleBilinear(texCoord,colourKernel);
		break;
	default:
		break;
	}
	colourKernel.r *= uniform.offset;
	colourKernel.g *= (1-0.f - uniform.offset);
	uniform.framebuffer->setPixel(screenCoord,colourKernel);
	}
}
