#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include "Texture.hpp"
#include "TriangleSort.hpp"
using namespace std;

static const int W = 640, H = 480;

TextureABGR<uint8_t> framebuffer(W,H);

typedef std::function<void(int,int,int)> ScalineResolver;
void fillBottomFlatTriangle(const ScalineResolver& resolver, const glm::ivec2& v0, const glm::ivec2& v1, const glm::ivec2& v2) {
	const float invslope1 = float(v1.x - v0.x) / float(v1.y - v0.y);
	const float invslope2 = float(v2.x - v0.x) / float(v2.y - v0.y);
	for(int i = v0.y; i < v2.y;++i) {
		const int dy = i - v0.y;
		const int curx1 = int(float(v0.x + invslope1 * dy));
		const int curx2 = int(float(v0.x + invslope2 * dy));
		resolver(i,curx1,curx2);
	}
}
void fillBottomFlatTriangle(const ScalineResolver& resolver, const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2) {
	const float invslope1 = float(v1.x - v0.x) / float(v1.y - v0.y);
	const float invslope2 = float(v2.x - v0.x) / float(v2.y - v0.y);
	const int minY = int(std::trunc(v0.y));
	const int minX = int(std::trunc(v2.y));
	for(int i = minY; i < minX;++i) {
		const float dy = float(i) - v0.y;
		const float curx1 = v0.x + invslope1 * dy + 0.5f;
		const float curx2 = v0.x + invslope2 * dy + 0.5f;
		resolver(i,int(std::trunc(curx1)),int(std::trunc(curx2)));
	}
}
void fillTopFlatTriangle(const ScalineResolver& resolver, const glm::ivec2& v0, const glm::ivec2& v1, const glm::ivec2& v2) {
	const float invslope1 = (v2.x - v0.x) / (v2.y - v0.y);
	const float invslope2 = (v2.x - v1.x) / (v2.y - v1.y);
	for(int i = v0.y; i < v2.y;++i) {
		const int dy = i - v2.y;
		const int curx1 = int(float(v2.x + invslope1 * dy));
		const int curx2 = int(float(v2.x + invslope2 * dy));
		resolver(i,curx1,curx2);
	}
}
void fillTopFlatTriangle(const ScalineResolver& resolver, const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2) {
	const float invslope1 = (v2.x - v0.x) / (v2.y - v0.y);
	const float invslope2 = (v2.x - v1.x) / (v2.y - v1.y);
	const int minY = int(std::trunc(v0.y));
	const int minX = int(std::trunc(v2.y));
	for(int i = minY; i < minX;++i) {
		const float dy = float(i) - v2.y;
		const float curx1 = v2.x + invslope1 * dy + 0.5f;
		const float curx2 = v2.x + invslope2 * dy + 0.5f;
		resolver(i,int(std::trunc(curx1)),int(std::trunc(curx2)));
	}
}

struct BasicVertex {
	glm::vec2 COORDS;
	glm::vec4 COLOUR;
	static BasicVertex split(const BasicVertex& v0, const BasicVertex& v1, const BasicVertex& v2) {
		return { .COORDS = glm::vec2((v0.COORDS.x + ((v1.COORDS.y - v0.COORDS.y) / (v2.COORDS.y - v0.COORDS.y)) * (v2.COORDS.x - v0.COORDS.x)), v1.COORDS.y),
					.COLOUR = glm::vec4() };
	}
};

void renderTriangle(const ScalineResolver& resolver, const BasicVertex& v0, const BasicVertex& v1, const BasicVertex& v2) {
	int area = Generic::edgeFunction(v0,v1,v2);
	const BasicVertex *t = &v0;
	const BasicVertex *m = &v1;
	const BasicVertex *b = &v2;
	// Sort by Y
	if (t->COORDS.y > m->COORDS.y) std::swap(t, m);
	if (m->COORDS.y > b->COORDS.y) std::swap(m, b);
	if (t->COORDS.y > m->COORDS.y) std::swap(t, m);
	const float dy = (b->COORDS.y - t->COORDS.y);
	const float iy = (m->COORDS.y - t->COORDS.y);
	if (m->COORDS.y == t->COORDS.y)
	{
		const BasicVertex *l = m, *r = t;
		if (l->COORDS.x > r->COORDS.x) std::swap(l, r);
		fillTopFlatTriangle(resolver, l->COORDS, r->COORDS, b->COORDS);
	}
	else if (m->COORDS.y == b->COORDS.y)
	{
	const BasicVertex *l = m, *r = b;
		if (l->COORDS.x > r->COORDS.x) std::swap(l, r);
		fillBottomFlatTriangle(resolver, t->COORDS, l->COORDS, r->COORDS);
	}
	else
	  {
		// Split the triangle
		BasicVertex v4;
		v4.COORDS.y = m->COORDS.y;
		v4.COORDS.x = t->COORDS.x + ((b->COORDS.x - t->COORDS.x) / dy) * iy;
		//if (PixelShader::InterpolateZ) v4.z = t->z + ((b->z - t->z) / dy) * iy;
		//if (PixelShader::InterpolateW) v4.w = t->w + ((b->w - t->w) / dy) * iy;
		v4.COLOUR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		/*for (int i = 0; i < PixelShader::VarCount; ++i)
		  v4.var[i] = t->var[i] + ((b->var[i] - t->var[i]) / dy) * iy;*/

		const BasicVertex *l = m, *r = &v4;
		if (l->COORDS.x > r->COORDS.x) std::swap(l, r);

		fillBottomFlatTriangle(resolver, t->COORDS, l->COORDS, r->COORDS);
		fillTopFlatTriangle(resolver, l->COORDS, r->COORDS, b->COORDS);
	  }
}


int main()
{
	BasicVertex vertices[] = {
		{ glm::vec2(0.0f,H-20.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) }, // GREEN
		{ glm::vec2(W,H/2.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, // BLUE
		{ glm::vec2(W/2,0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) } // RED
	};
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
		int area = Generic::edgeFunction(vertices[0],vertices[1],vertices[2]);
		auto scanlineResolver = [vertices,area](int scanline, int minX, int maxX) {
			glm::ivec2 p(minX,scanline);
			const float farea = 1.0f / float(area);
			for(; p.x < maxX; ++p.x) {
				glm::vec2 pf = glm::vec2(float(p.x)+0.5f,float(p.y)+0.5f);
				const float w0 = float(Fixed::edgeFunction(vertices[1].COORDS, vertices[2].COORDS, pf)) * farea;
				const float w1 = float(Fixed::edgeFunction(vertices[2].COORDS, vertices[0].COORDS, pf)) * farea;
				const float w2 = float(Fixed::edgeFunction(vertices[0].COORDS, vertices[1].COORDS, pf)) * farea;
				glm::vec4 colourKernel = {
								(w0 * vertices[0].COLOUR.r) + (w1 * vertices[1].COLOUR.r) + (w2 * vertices[2].COLOUR.r),
								(w0 * vertices[0].COLOUR.g) + (w1 * vertices[1].COLOUR.g) + (w2 * vertices[2].COLOUR.g),
								(w0 * vertices[0].COLOUR.b) + (w1 * vertices[1].COLOUR.b) + (w2 * vertices[2].COLOUR.b),
								(w0 * vertices[0].COLOUR.a) + (w1 * vertices[1].COLOUR.a) + (w2 * vertices[2].COLOUR.a)
								};
				framebuffer.setPixel(p,colourKernel);
			}
		};
	bool isInterrupted=false;
	do {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
			case SDL_QUIT: isInterrupted = true; break;
			default: break;
			}
		}
		framebuffer.clear();
		// Draw a triangle
		renderTriangle(scanlineResolver,vertices[0],vertices[1],vertices[2]);

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
