#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "StandardTexture.hpp"
#include "Pipeline/BasicPipeline.hpp"
#include "Pipeline/WidgetPipeline.hpp"
#include "CreateTexture.hpp"
#include "Tile/Tile.hpp"
#include <MhLib/Io/MhFile.hpp>
#include <cmath>

#include <stdexcept>

using namespace std;

static const unsigned W = 640, H = 480;
static const unsigned CX = W/2, CY = H/2;
static const glm::ivec2 viewport(W,H);
static const char* MODEL_PATH = "/home/metalhead33/printr/cube.dae";
int mouseX=0, mouseY=0;

typedef TextureRgba5551 Framebuffer;
Framebuffer framebuffer(W,H);
std::shared_ptr<Texture> tex = nullptr;


std::vector<WidgetVertexIn> vertices = {
	{ glm::vec2(0.0f, 1.0f), glm::vec2(0.50f, 0.0f) },	// Index 0
	{ glm::vec2(-1.0f, 0.5f), glm::vec2(0.00f, 0.25f) },	// Index 1
	{ glm::vec2(1.0f, 0.5f), glm::vec2(1.00f, 0.25f) },	// Index 2
	{ glm::vec2(-1.0f, -0.5f), glm::vec2(0.00f, 0.75f) },	// Index 3
	{ glm::vec2(1.0f, -0.5f), glm::vec2(1.00f, 0.75f) },	// Index 4
	{ glm::vec2(0.0f, -1.0f), glm::vec2(0.50f, 1.0f) }	// Index 5
};
std::vector<unsigned> indices = {
	0, 1, 2, // Triangle 1
	1, 2, 4, // Triangle 2
	1, 3, 4, // Triangle 3
	3, 4, 5 // Triangle 4
};

void renderHexagonGrid(const glm::ivec2& hexagonSize, const glm::ivec2& initialOffset, int rows, int columns) {
	WidgetUniform uniform = { &framebuffer, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR, AlphaBlending::DITHERED, hexagonSize, glm::ivec2(0,0) };
	const int xoff1 = hexagonSize.x / 2;
	const int yoff2 = int(float(hexagonSize.y) * 0.75f);
	uniform.offset.y = initialOffset.y;
	for(int row = 0; row < rows; ++row) {
		uniform.offset.x = (row&1) ? initialOffset.x - xoff1 :initialOffset.x;
		for(int column = 0; column < columns; ++column) {
			//uniform.offset.y = (column&1) ? rowStartY + yoff2 : rowStartY;
			WidgetPipeline::renderTriangles(viewport,uniform,vertices.data(),indices.data(),indices.size() );
			uniform.offset.x += hexagonSize.x;
		}
		uniform.offset.y += yoff2;
	}
}
void rennderTileGrid(const Grid& grid, const glm::ivec2& hexagonSize, const glm::ivec2& gridOffset, const glm::ivec2& framebufferOffset, int rows, int columns)  {
	WidgetUniform uniform = { &framebuffer, nullptr, TextureFiltering::NEAREST_NEIGHBOUR, AlphaBlending::DITHERED, hexagonSize, glm::ivec2(0,0) };
	const int xoff1 = hexagonSize.x / 2;
	const int yoff2 = int(float(hexagonSize.y) * 0.75f);
	uniform.offset.y = framebufferOffset.y;
	for(int row = 0; row < rows; ++row) {
		uniform.offset.x = (row&1) ? framebufferOffset.x - xoff1 :framebufferOffset.x;
		const int gridRow = gridOffset.y + row;
		if(gridRow < grid.h) {
			for(int column = 0; column < columns; ++column) {
				const int gridColumn = gridOffset.x + column;
				if(gridColumn < grid.w) {
					uniform.tex = TerrainTextures[grid[glm::ivec2(gridRow, gridColumn)].terrainType].get();
					WidgetPipeline::renderTriangles(viewport,uniform,vertices.data(),indices.data(),indices.size() );
					uniform.offset.x += hexagonSize.x;
				} else break;
			}
		} else break;
		uniform.offset.y += yoff2;
	}
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBA5551, SDL_TEXTUREACCESS_STREAMING, W,H);
	MH33::Io::File pngText("/home/metalhead33/printr/uvtemplate.png",MH33::Io::Mode::READ);
	BasicUniform basicUniform = {&framebuffer, AlphaBlending::DITHERED};
	tex = textureFromPNG(pngText);
	/*
struct WidgetUniform {
	Texture* framebuffer;
	Texture* tex;
	TextureFiltering sampling;
	AlphaBlending blendingMode;
	glm::ivec2 size;
	glm::ivec2 offset;
};
*/
	bool isInterrupted=false;
	SDL_WarpMouseInWindow(NULL,CX,CY);
	do {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
			case SDL_QUIT: isInterrupted = true; break;
			default: break;
			}
		}
		framebuffer.clearToColour(glm::vec4(0.0f,0.0f,0.0f,1.0f));
		// Draw a triangle
		//renderHexagonGrid(glm::ivec2(128,128),glm::ivec2(-128,-128),(W/128)+128,(H/128)+128);
		renderHexagonGrid(glm::ivec2(128,128),glm::ivec2(128,128),4,4);
		/*BasicPipeline::renderTriangle(viewport,basicUniform, BasicVertexIn{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0, 0.0f, 1.0f) },
										  BasicVertexIn{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(0.0f, 1.0, 0.0f, 1.0f) },
										BasicVertexIn{ glm::vec3(1.0f, -1.0f, 0.0f), glm::vec4(0.0f, 0.0, 1.0f, 1.0f) }
									  );*/
		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), W*2);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
