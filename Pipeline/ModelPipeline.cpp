#include "ModelPipeline.hpp"
#include <glm/gtc/matrix_transform.hpp>

ModelVertexOut modelVertexShader(const ModelUniform &uniform, const ModelVertexIn &input)
{
	//glm::vec4 tempVec = glm::vec4(input.COORDS,1.0f) * uniform.mvp;
	/*tempVec.x /= tempVec.w;
	tempVec.y /= tempVec.w;
	tempVec.z /= tempVec.w;*/
	/*ModelVertexOut out{glm::vec3( (tempVec.x + 1.0f) / 2.0f * uniform.framebuffer->getW(),
				((tempVec.y-1.0f) / -2.0f) * uniform.framebuffer->getH(),
				(tempVec.z * -1.0f) ), input.TEXCOORD};*/
	/*ModelVertexOut out{glm::vec3( (tempVec.x / tempVec.w),
				(tempVec.y / tempVec.w),
				(tempVec.z / tempVec.w) ), input.TEXCOORD};*/
	ModelVertexOut out{ glm::projectZO(input.COORDS,uniform.model,uniform.proj,uniform.viewport),input.TEXCOORD };
	out.COORDS.z *= -1.0f;
	if(uniform.perspectiveCorrection) out.TEXCOORD /= out.COORDS.z;
	return out;
}

void modelFragmentShader(const ModelUniform &uniform, const ModelVertexOut &v0, const ModelVertexOut &v1, const ModelVertexOut &v2, float w0, float w1, float w2, const glm::ivec2 &screenCoord)
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
