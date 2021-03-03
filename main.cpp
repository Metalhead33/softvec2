#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include "Texture.hpp"
#include "TriangleSort.hpp"
using namespace std;

typedef std::function<void(int,int,int)> ScalineResolver;

static const int W = 640, H = 480;

TextureABGR<uint8_t> framebuffer(W,H);

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
	glm::vec2 coords;
	glm::vec4 colour;
};


int main()
{
	BasicVertex vertices[] = {
		{ glm::vec2(W/2,0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) }, // RED
		{ glm::vec2(0.0f,H), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) }, // GREEN
		{ glm::vec2(W,H), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) } // BLUE
	};
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
		int area = edgeFunction(vertices[0].coords,vertices[1].coords,vertices[2].coords);
		auto scanlineResolver = [vertices,area](int scanline, int minX, int maxX) {
			glm::ivec2 p(minX,scanline);
			const float farea = float(area);
			for(; p.x < maxX; ++p.x) {
				glm::vec2 pf = glm::vec2(float(p.x)+0.5f,float(p.y)+0.5f);
				const float w0 = float(edgeFunction(vertices[1].coords, vertices[2].coords, pf)) / farea;
				const float w1 = float(edgeFunction(vertices[2].coords, vertices[0].coords, pf)) / farea;
				const float w2 = float(edgeFunction(vertices[0].coords, vertices[1].coords, pf)) / farea;
				glm::vec4 colourKernel = {
								(w0 * vertices[0].colour.r) + (w1 * vertices[1].colour.r) + (w2 * vertices[2].colour.r),
								(w0 * vertices[0].colour.g) + (w1 * vertices[1].colour.g) + (w2 * vertices[2].colour.g),
								(w0 * vertices[0].colour.b) + (w1 * vertices[1].colour.b) + (w2 * vertices[2].colour.b),
								(w0 * vertices[0].colour.a) + (w1 * vertices[1].colour.a) + (w2 * vertices[2].colour.a)
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
		fillBottomFlatTriangle(scanlineResolver,vertices[0].coords,vertices[1].coords,vertices[2].coords);

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
