#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include "StandardTexture.hpp"
#include "Pipeline/BasicPipeline.hpp"
using namespace std;

static const int W = 640, H = 480;
static const glm::ivec2 viewport(W,H);

typedef TextureABGR<uint8_t> Framebuffer;
Framebuffer framebuffer(W,H);

int main()
{
	BasicVertexIn vertices[] = {
		{ glm::vec3(0.0f,1.0f,0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) }, // RED
		{ glm::vec3(-1.0f,-1.0f,0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) }, // GREEN
		{ glm::vec3(1.0f,-1.0f,0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) } // BLUE
	};
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
	BasicUniform uniform = { &framebuffer };
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
		BasicPipeline::renderTriangles(viewport,uniform,vertices,3);

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
