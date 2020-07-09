#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>
#include "Texture/OptimizedTexture.hpp"

/*
static SDL_Window* WIN = nullptr;
static SDL_Renderer* RENDER = nullptr;
static SDL_Texture* FRAMEBUFFER = nullptr;
static PixelRGBA* FRAMEBUFFER_BUFF = nullptr;

static const int WIDTH = 640;
static const int HEIGHT= 480;
static const int PITCH = WIDTH*4;
*/

int main()
{
	/*SDL_Init(SDL_INIT_VIDEO);
	WIN = SDL_CreateWindow("Softvec2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
	SDL_SetWindowMinimumSize(WIN,WIDTH,HEIGHT);
	RENDER = SDL_CreateRenderer(WIN,-1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(RENDER,WIDTH,HEIGHT);
	SDL_RenderSetIntegerScale(RENDER,SDL_bool::SDL_TRUE);
	FRAMEBUFFER = SDL_CreateTexture(RENDER,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);
	FRAMEBUFFER_BUFF = reinterpret_cast<PixelRGBA*>(SDL_malloc(sizeof(PixelRGBA)*WIDTH*HEIGHT));
	paintPixelAt(FRAMEBUFFER_BUFF,300,300,WIDTH,255,255,255);
	paintPixelAt(FRAMEBUFFER_BUFF,300,301,WIDTH,255,255,255);
	paintPixelAt(FRAMEBUFFER_BUFF,301,301,WIDTH,255,255,255);
	paintPixelAt(FRAMEBUFFER_BUFF,301,300,WIDTH,255,255,255);
	printf("Hello World!\n");
	while(1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) goto EXIT;
		}
		SDL_RenderClear(RENDER);
		SDL_UpdateTexture(FRAMEBUFFER, NULL, FRAMEBUFFER_BUFF, PITCH);
		SDL_RenderCopy(RENDER, FRAMEBUFFER, NULL, NULL);
		SDL_RenderPresent(RENDER);
	}

	EXIT:
	SDL_DestroyRenderer(RENDER);
	SDL_DestroyWindow(WIN);
	SDL_Quit();*/
	std::cout << OptimizedTextureDimensions<TexRes::T256X256>::PIXCOUNT << std::endl;
	return 0;
}
