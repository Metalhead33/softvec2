#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include "StandardTexture.hpp"
#include "Pipeline/BasicPipeline.hpp"
#include "Pipeline/ClipspacePipeline.hpp"
#include "CreateTexture.hpp"
#include <MhLib/Io/MhFile.hpp>
#include <cmath>

using namespace std;

static const unsigned W = 640, H = 480;
static const glm::ivec2 viewport(W,H);

typedef TextureABGR<uint8_t> Framebuffer;
Framebuffer framebuffer(W,H);
ZBuffer zbuff(W,H);
std::shared_ptr<Texture> tex = nullptr;

ClipspaceVertexIn clipspaceVertices[] = {
	{ glm::vec3(-1.0f,1.0f,0.0f), glm::vec2(0.0f, 0.0f) }, // Upper left
	{ glm::vec3(1.0f,1.0f,0.0f), glm::vec2(1.0f, 0.0f) }, // Upper right
	{ glm::vec3(-1.0f,-1.0f,0.0f), glm::vec2(0.0f, 1.0f) }, // Lower left
	{ glm::vec3(1.0f,-1.0f,0.0f), glm::vec2(1.0f, 1.0f) } // Lower right
};
unsigned clipspaceIndices[] = { 0, 1, 2, 1, 2, 3 };

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
	MH33::Io::File pngText("/home/metalhead33/printr/cubemap1.png",MH33::Io::Mode::READ);
	tex = textureFromPNG(pngText);
	ClipspaceUniformMoving uniform = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR, 0.0f };

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
		ClipspacePipeline2::renderTriangles(viewport,uniform,clipspaceVertices,clipspaceIndices,6);

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
		if(uniform.offset >= 1.0f) uniform.offset = 0.0f;
		else uniform.offset += 0.016666666666667;
	} while(!isInterrupted);
	return 0;
}
