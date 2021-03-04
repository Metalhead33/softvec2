#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include "Texture.hpp"
#include "RenderingPipeline.hpp"
using namespace std;

static const int W = 640, H = 480;
static const glm::ivec2 viewport(W,H);

typedef TextureABGR<uint8_t> Framebuffer;
Framebuffer framebuffer(W,H);

struct Uniform {
	Framebuffer* framebuffer;
};
struct BasicVertexIn {
	glm::vec3 COORDS;
	glm::vec4 COLOUR;
};
struct BasicVertexOut {
	glm::vec2 COORDS;
	glm::vec4 COLOUR;
	/*
			VertexOutput v4 = VertexOutput::split(*t,*m,*b,dy,iy);
			/*v4.COORDS.y = m->COORDS.y;
			v4.COORDS.x = t->COORDS.x + ((b->COORDS.x - t->COORDS.x) / dy) * iy;
			if (PixelShader::InterpolateZ) v4.z = t->z + ((b->z - t->z) / dy) * iy;
			if (PixelShader::InterpolateW) v4.w = t->w + ((b->w - t->w) / dy) * iy;
			v4.COLOUR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			for (int i = 0; i < PixelShader::VarCount; ++i)
			  v4.var[i] = t->var[i] + ((b->var[i] - t->var[i]) / dy) * iy;*/
	static BasicVertexOut split(const BasicVertexOut& t, const BasicVertexOut& m, const BasicVertexOut& b, float dy, float iy) {
		return { glm::vec2(
						m.COORDS.y,
						t.COORDS.x + ((b.COORDS.x - t.COORDS.x) / dy) * iy
						),
					glm::vec4(
						t.COLOUR.r + ((b.COLOUR.r - t.COLOUR.r) / dy) * iy,
						t.COLOUR.g + ((b.COLOUR.g - t.COLOUR.g) / dy) * iy,
						t.COLOUR.b + ((b.COLOUR.b - t.COLOUR.b) / dy) * iy,
						t.COLOUR.a + ((b.COLOUR.a - t.COLOUR.a) / dy) * iy
						) };
	}
};
/*
	typedef std::function<VertexOutput(const Uniform&, const VertexInput&)> VertexShader;
	typedef std::function<void(const Uniform&, const VertexOutput&,const VertexOutput&,const VertexOutput&,float,float,float,const glm::ivec2&)> FragmentShader;
*/
BasicVertexOut vertexShader(const Uniform& uniform, const BasicVertexIn& input) {
	return { glm::vec2(
					(input.COORDS[0] + 1.0f) / 2.0f * uniform.framebuffer->getW(),
					((input.COORDS[1]-1.0f) / -2.0f) * uniform.framebuffer->getH()
					), input.COLOUR };
}
void fragmentShader(const Uniform& uniform, const BasicVertexOut& v0,const BasicVertexOut& v1,const BasicVertexOut& v2,
							float w0,float w1,float w2,const glm::ivec2& screenCoord) {
	if(screenCoord.x < 0 || screenCoord.y < 0) return;
	glm::vec4 colourKernel = {
					(w0 * v0.COLOUR.r) + (w1 * v1.COLOUR.r) + (w2 * v2.COLOUR.r),
					(w0 * v0.COLOUR.g) + (w1 * v1.COLOUR.g) + (w2 * v2.COLOUR.g),
					(w0 * v0.COLOUR.b) + (w1 * v1.COLOUR.b) + (w2 * v2.COLOUR.b),
					(w0 * v0.COLOUR.a) + (w1 * v1.COLOUR.a) + (w2 * v2.COLOUR.a)
					};
	uniform.framebuffer->setPixel(screenCoord,colourKernel);
}


int main()
{
	BasicVertexIn vertices[] = {
		{ glm::vec3(0.0f,1.0f,0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) }, // RED
		{ glm::vec3(-2.0f,-1.0f,0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) }, // GREEN
		{ glm::vec3(1.0f,-1.0f,0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) } // BLUE
	};
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
	Uniform uniform = { &framebuffer };
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
		Pipeline<BasicVertexIn,BasicVertexOut,Uniform>::renderTriangles(vertexShader,fragmentShader,viewport,uniform,vertices,3);

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
