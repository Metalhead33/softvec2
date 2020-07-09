#ifndef PIPELINE_HPP
#define PIPELINE_HPP
#include "SortTriangle.hpp"
#include "../Texture/Texture.hpp"
#include <functional>
#include <vector>

typedef std::vector<float> ZBuffer;

template <typename VertexInput, typename VertexOutput, typename FragmentInput, typename Uniform> struct Pipeline {
	typedef std::function<VertexOutput(const VertexInput&, const Uniform&, const fvec4&)> VertexShader;
	typedef std::function<void(Texture&,const FragmentInput&,const Uniform&)> FragmentShader;
	typedef std::function<void(Texture&,ZBuffer&, const FragmentShader&, const Uniform&, const VertexOutput*, const VertexOutput*, const VertexOutput*)> Interpollator;

	static void drawTriangles(Texture& framebuffer, ZBuffer& zbuffer, const fvec4& viewport, VertexShader VS, Interpollator IP, FragmentShader FS,
							  const Uniform& uniforms, const VertexInput& v0, const VertexInput& v1, const VertexInput& v2)
	{
		const VertexOutput pv0 = VS(v0,uniforms,viewport);
		const VertexOutput pv1 = VS(v1,uniforms,viewport);
		const VertexOutput pv2 = VS(v2,uniforms,viewport);
		IP(framebuffer,zbuffer,FS,&pv0,&pv1,&pv2);
	}
	static void drawTriangles(Texture& framebuffer, ZBuffer& zbuffer, const fvec4& viewport, VertexShader VS, Interpollator IP, FragmentShader FS,
							  const Uniform& uniforms, const VertexInput* vertices, size_t vertexCount)
	{
		for(size_t i = 0; i < vertexCount; i += 3)
		{
			const VertexInput& v0 = vertices[i];
			const VertexInput& v1 = vertices[i+1];
			const VertexInput& v2 = vertices[i+2];
			drawTriangles(framebuffer,zbuffer,viewport,VS,IP,FS,uniforms,v0,v1,v2);
		}
	}
	static void drawTriangles(Texture& framebuffer, ZBuffer& zbuffer, const fvec4& viewport, VertexShader VS, Interpollator IP, FragmentShader FS,
							  const Uniform& uniforms, const VertexInput* vertices, const int* indices, size_t indexCount)
	{
		for(size_t i = 0; i < indexCount; i += 3)
		{
			const VertexInput& v0 = vertices[indices[i]];
			const VertexInput& v1 = vertices[indices[i+1]];
			const VertexInput& v2 = vertices[indices[i+2]];
			drawTriangles(framebuffer,zbuffer,viewport,VS,IP,FS,uniforms,v0,v1,v2);
		}
	}
};

#endif // PIPELINE_HPP
