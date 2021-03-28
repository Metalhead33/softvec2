#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "StandardTexture.hpp"
#include "Pipeline/BasicPipeline.hpp"
#include "Pipeline/WidgetPipeline.hpp"
#include "Tile/Tile.hpp"
#include <MhLib/Io/MhFile.hpp>
#include <cmath>
#include "SdlFramebuffer.hpp"

#include <stdexcept>

using namespace std;

static const unsigned W = 640, H = 480;
static const unsigned CX = W/2, CY = H/2;
static const glm::ivec2 viewport(W,H);
int mouseX=0, mouseY=0;

#define FRAMEBUFFER_16_BIT
#ifdef FRAMEBUFFER_8_BIT
typedef SdlFramebuffer<PixelRgb332,SDL_PIXELFORMAT_RGB332> FrameBuff;
#elif defined(FRAMEBUFFER_12_BIT)
typedef SdlFramebuffer<PixelRgb444,SDL_PIXELFORMAT_RGB444> FrameBuff;
#elif defined(FRAMEBUFFER_555)
typedef SdlFramebuffer<PixelRgb555,SDL_PIXELFORMAT_RGB555> FrameBuff;
#elif defined(FRAMEBUFFER_16_BIT)
typedef SdlFramebuffer<PixelRgb565,SDL_PIXELFORMAT_RGB565> FrameBuff;
#else
typedef SdlFramebuffer<PixelXrgbU8,SDL_PIXELFORMAT_BGRX8888> FrameBuff;
#endif
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

void rennderTileGrid(FrameBuff& framebuffer, const Grid& grid, const glm::ivec2& hexagonSize, const glm::ivec2& gridOffset, const glm::ivec2& framebufferOffset, int rows, int columns)  {
	WidgetUniform uniform = { nullptr, TextureFiltering::NEAREST_NEIGHBOUR, AlphaBlending::DITHERED, hexagonSize, glm::ivec2(0,0) };
	rows = std::min(rows,int(grid.h)-gridOffset.y);
	columns = std::min(columns,int(grid.w)-gridOffset.x);
	const int xoff1 = hexagonSize.x / 2;
	const int yoff2 = int(float(hexagonSize.y) * 0.75f);
	uniform.offset.y = framebufferOffset.y;
	for(int row = gridOffset.y; row < rows; ++row) {
		uniform.offset.x = (row&1) ? framebufferOffset.x - xoff1 : framebufferOffset.x;
			for(int column = gridOffset.x; column < columns; ++column) {
				uniform.tex = TerrainTextures[grid[glm::ivec2(row, column)].terrainType].get();
				WidgetPipeline::renderTriangles(framebuffer,viewport,uniform,vertices.data(),indices.data(),indices.size() );
				uniform.offset.x += hexagonSize.x;
			}
		uniform.offset.y += yoff2;
	}
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	sSdlWindow window = sSdlWindow(SDL_CreateWindow("Chip8",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0),SDL_DestroyWindow);
	FrameBuff framebuffer(window,-1,0,W,H);
	initializeTerrainTextures();
	Grid grid(120,120);
	for(int i = 10; i < 20; ++i) {
		for(int j = 10; j < 20; ++j) {
			grid[glm::ivec2(i,j)].terrainType = Terrain::SWAMP;
		}
	}
	grid[glm::ivec2(5,5)].terrainType = Terrain::ICE;

	const unsigned hexagonDim = 32;
	const int hexagonDimMin = int(hexagonDim) * -1;

	glm::ivec2 offset(0,0);
	glm::ivec2 fieldSize((W/hexagonDim)+(2*hexagonDim),
						 (H/hexagonDim)+(2*hexagonDim));

	bool isInterrupted=false;
	SDL_WarpMouseInWindow(NULL,CX,CY);
	do {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
			case SDL_QUIT: isInterrupted = true; break;
			case SDL_KEYDOWN:
			{
				switch(ev.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isInterrupted = true; break;
					break;
				case SDLK_w:
					offset.y -= 3;
					offset.y = std::clamp(offset.y,0,int(grid.h*hexagonDim));
					break;
				case SDLK_s:
					offset.y += 3;
					offset.y = std::clamp(offset.y,0,int(grid.h*hexagonDim));
					break;
				case SDLK_a:
					offset.x -= 3;
					offset.x = std::clamp(offset.x,0,int(grid.w*hexagonDim));
					break;
				case SDLK_d:
					offset.x += 3;
					offset.x = std::clamp(offset.x,0,int(grid.w*hexagonDim));
					break;
				case SDLK_SPACE:
					std::cout << "Offset: { " << offset.x << " " << offset.y << "} " << std::endl; break;
				default: break;
				}
				break;
			}
			default: break;
			}
		}
		framebuffer.getTexture()->clearToColour(glm::vec4(0.0f,0.0f,0.0f,1.0f));
		// Draw a triangle
		rennderTileGrid(framebuffer, grid, glm::ivec2(hexagonDim,hexagonDim),glm::ivec2(offset.x/hexagonDim,offset.y/hexagonDim),
						glm::ivec2( ((offset.x%hexagonDim)*-1) + hexagonDimMin, ((offset.y%hexagonDim)*-1) + hexagonDimMin),
						fieldSize.y,fieldSize.x);
		/*rennderTileGrid(framebuffer, grid, glm::ivec2(hexagonDim,hexagonDim),glm::ivec2(offset.x/hexagonDim,offset.y/hexagonDim),
						glm::ivec2((offset.x%hexagonDimMin),(offset.y%hexagonDimMin)),
						fieldSize.y,fieldSize.x);*/
		framebuffer.swapBuffers();
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
