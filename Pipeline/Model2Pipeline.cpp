#include "Model2Pipeline.hpp"

void model2FragmentShader(const Model2Uniform &uniform, const Model2VertexOut &v0, const Model2VertexOut &v1, const Model2VertexOut &v2, float w0, float w1, float w2, const glm::ivec2 &screenCoord)
{
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	const float z = ((w0 * v0.COORDS.z) + (w1 * v1.COORDS.z) + (w2 * v2.COORDS.z));
	float& zbuffpoint = uniform.zbuffer->get(screenCoord.x,screenCoord.y);
	if(z >= 0.0f &&  z <= zbuffpoint) {
	glm::vec2 texCoord = {
					(w0 * v0.TEXCOORD.r) + (w1 * v1.TEXCOORD.r) + (w2 * v2.TEXCOORD.r),
					(w0 * v0.TEXCOORD.g) + (w1 * v1.TEXCOORD.g) + (w2 * v2.TEXCOORD.g)
					};
	if(uniform.perspectiveCorrection) texCoord *= z;
	glm::vec4 pixelOut = uniform.tex->sample(texCoord,screenCoord,uniform.sampling);
	if ( uniform.framebuffer->setPixelWithBlending(screenCoord,pixelOut,uniform.blendingMode) ) zbuffpoint = z;
	}
}

Model2VertexOut model2VertexShader(const Model2Uniform &uniform, const Model2VertexIn &input)
{
	glm::vec4 v4 = uniform.mvp * glm::vec4(input.COORDS,1.0f);
	v4.x /= v4.w;
	v4.y /= v4.w;
	v4.z /= v4.w;
	v4.x = ((v4.x + 1.0f) / 2.0f) * uniform.viewport.x;
	v4.y = ((1.0f - v4.y) / 2.0f) * uniform.viewport.y;
	//v4.z *= -1.0f;
	Model2VertexOut out{ glm::vec3(v4.x,v4.y,v4.z) ,input.TEXCOORD };
	//out.COORDS.z *= -1.0f;
	if(uniform.perspectiveCorrection) out.TEXCOORD /= out.COORDS.z;
	return out;
}
