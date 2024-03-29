#ifndef RENDERINGPIPELINE_HPP
#define RENDERINGPIPELINE_HPP
#include <functional>
#include <glm/glm.hpp>
#include "TriangleSort.hpp"
#include <algorithm>
#include "../Framebuffer.hpp"

template <typename VertexInput,
		  typename VertexOutput,
		  typename Uniform,
		  auto VertexShader,
		  auto FragmentShader> struct Pipeline {
	//typedef std::function<VertexOutput(const Uniform&, const VertexInput&)> VertexShader;
	//typedef std::function<void(Framebuffer&, const Uniform&, const VertexOutput&,const VertexOutput&,const VertexOutput&,float,float,float,const glm::ivec2&)> FragmentShader;
	static void resolveScanline(Framebuffer& framebuffer, const Uniform& uniform, const glm::ivec2& viewport, int scanline, int minX, int maxX, float rArea,
								const VertexOutput& v0, const VertexOutput& v1, const VertexOutput& v2) {
		const int max_x = std::min(maxX,viewport.x);
		for(int x = std::max(minX,0); x < max_x; ++x) {
			glm::ivec2 p = glm::ivec2(x,scanline);
			glm::vec2 pf = glm::vec2(float(p.x)+0.5f,float(p.y)+0.5f);
			const float w0 = float(Fixed::edgeFunction(v1.COORDS, v2.COORDS, pf)) * rArea;
			const float w1 = float(Fixed::edgeFunction(v2.COORDS, v0.COORDS, pf)) * rArea;
			const float w2 = float(Fixed::edgeFunction(v0.COORDS, v1.COORDS, pf)) * rArea;
			FragmentShader(framebuffer,uniform,v0,v1,v2,w0,w1,w2,p);
		}
	}
	static void fillBottomFlatTriangle(Framebuffer& framebuffer, const Uniform& uniform, const glm::ivec2& viewport, float rArea, const VertexOutput& v0, const VertexOutput& v1, const VertexOutput& v2) {
		const float invslope1 = float(v1.COORDS.x - v0.COORDS.x) / float(v1.COORDS.y - v0.COORDS.y);
		const float invslope2 = float(v2.COORDS.x - v0.COORDS.x) / float(v2.COORDS.y - v0.COORDS.y);
		const int minY = std::clamp(int(std::trunc(v0.COORDS.y)),0,viewport.y);
		const int minX = std::clamp(int(std::trunc(v1.COORDS.y)),0,viewport.y);
		for(int i = minY; i < minX;++i) {
			const float dy = float(i) - v0.COORDS.y + 0.5f;
			const float curx1 = v0.COORDS.x + (invslope1 * dy) +0.5f;
			const float curx2 = v0.COORDS.x + (invslope2 * dy) + 0.5f;
			resolveScanline(framebuffer,uniform,viewport,i,int(std::trunc(curx1)),int(std::trunc(curx2)),rArea,v0,v1,v2);
		}
	}
	static void fillTopFlatTriangle(Framebuffer& framebuffer, const Uniform& uniform, const glm::ivec2& viewport, float rArea, const VertexOutput& v0, const VertexOutput& v1, const VertexOutput& v2) {
		const float invslope1 = float(v2.COORDS.x - v0.COORDS.x) / float(v2.COORDS.y - v0.COORDS.y);
		const float invslope2 = float(v2.COORDS.x - v1.COORDS.x) / float(v2.COORDS.y - v1.COORDS.y);
		const int minY = std::clamp(int(std::trunc(v0.COORDS.y)),0,viewport.y);
		const int minX = std::clamp(int(std::trunc(v2.COORDS.y)),0,viewport.y);
		for(int i = minY; i < minX;++i) {
			const float dy = float(i) - v2.COORDS.y;
			const float curx1 = v2.COORDS.x + (invslope1 * dy);
			const float curx2 = v2.COORDS.x + (invslope2 * dy);
			resolveScanline(framebuffer,uniform,viewport,i,int(std::trunc(curx1)),int(std::trunc(curx2)),rArea,v0,v1,v2);
		}
	}
	static void renderVertexOutput(Framebuffer& framebuffer, const Uniform& uniform, const glm::ivec2& viewport, const VertexOutput& v0, const VertexOutput& v1, const VertexOutput& v2) {
		const VertexOutput *t = &v0;
		const VertexOutput *m = &v1;
		const VertexOutput *b = &v2;
		// Sort by Y
		if (t->COORDS.y > m->COORDS.y) std::swap(t, m);
		if (m->COORDS.y > b->COORDS.y) std::swap(m, b);
		if (t->COORDS.y > m->COORDS.y) std::swap(t, m);
		const float dy = (b->COORDS.y - t->COORDS.y);
		const float iy = (m->COORDS.y - t->COORDS.y);
		if (m->COORDS.y == t->COORDS.y)
		{
			const VertexOutput *l = m, *r = t;
			if (l->COORDS.x > r->COORDS.x) std::swap(l, r);
			const float area = Generic::edgeFunction(*t,*r,*b);
			const float rArea = 1.0f / area;
			fillTopFlatTriangle(framebuffer,uniform, viewport, rArea, *l, *r, *b);
		}
		else if (m->COORDS.y == b->COORDS.y)
		{
		const VertexOutput *l = m, *r = b;
			if (l->COORDS.x > r->COORDS.x) std::swap(l, r);
			const float area = Generic::edgeFunction(*t,*l,*r);
			const float rArea = 1.0f / area;
			fillBottomFlatTriangle(framebuffer,uniform, viewport, rArea, *t, *l, *r);
		}
		else
		  {
			// Split the triangle
			VertexOutput v4 = VertexOutput::split(*t,*m,*b,dy,iy);
			/*v4.COORDS.y = m->COORDS.y;
			v4.COORDS.x = t->COORDS.x + ((b->COORDS.x - t->COORDS.x) / dy) * iy;
			if (PixelShader::InterpolateZ) v4.z = t->z + ((b->z - t->z) / dy) * iy;
			if (PixelShader::InterpolateW) v4.w = t->w + ((b->w - t->w) / dy) * iy;
			v4.COLOUR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			for (int i = 0; i < PixelShader::VarCount; ++i)
			  v4.var[i] = t->var[i] + ((b->var[i] - t->var[i]) / dy) * iy;*/

			const VertexOutput *l = m, *r = &v4;
			if (l->COORDS.x > r->COORDS.x) std::swap(l, r);
			const float area1 = Generic::edgeFunction(*t,*l,*r);
			const float area2 = Generic::edgeFunction(*l,*r,*b);
			const float rArea1 = 1.0f / area1;
			const float rArea2 = 1.0f / area2;
			fillBottomFlatTriangle(framebuffer,uniform, viewport, rArea1, *t, *l, *r);
			fillTopFlatTriangle(framebuffer,uniform, viewport, rArea2, *l, *r, *b);
		  }
	}
	static void renderTriangle(Framebuffer& framebuffer, const glm::ivec2& viewport, const Uniform& uniform, const VertexInput& v0, const VertexInput& v1, const VertexInput& v2) {
		const VertexOutput o0 = VertexShader(uniform,v0);
		const VertexOutput o1 = VertexShader(uniform,v1);
		const VertexOutput o2 = VertexShader(uniform,v2);
		renderVertexOutput(framebuffer,uniform,viewport,o0,o1,o2);
	}
	static void renderTriangles(Framebuffer& framebuffer, const glm::ivec2& viewport, const Uniform& uniform, const VertexInput* vertices, size_t vertexCount) {
		for(size_t i = 0; i < vertexCount; i += 3) {
			renderTriangle(framebuffer,viewport,uniform,vertices[i],vertices[i+1],vertices[i+2]);
		}
	}
	static void renderTriangles(Framebuffer& framebuffer, const glm::ivec2& viewport, const Uniform& uniform, const VertexInput* vertices, unsigned* indices, size_t indexCount) {
		for(size_t i = 0; i < indexCount; i += 3) {
			renderTriangle(framebuffer,viewport,uniform,vertices[indices[i]],vertices[indices[i+1]],vertices[indices[i+2]]);
		}
	}
};

#endif // RENDERINGPIPELINE_HPP
