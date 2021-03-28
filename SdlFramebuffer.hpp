#ifndef SDLFRAMEBUFFER_HPP
#define SDLFRAMEBUFFER_HPP
#include "Framebuffer.hpp"
#include "StandardTexture.hpp"
#include <SDL2/SDL.h>
#include <memory>

typedef std::shared_ptr<SDL_Window> sSdlWindow;
template <typename PixelType, SDL_PixelFormatEnum SdlPixelId> class SdlFramebuffer : public Framebuffer {
public:
	typedef StandardTexture<PixelType> TextureType;
	typedef std::unique_ptr<SDL_Texture,decltype(&SDL_DestroyTexture)> uSdlTexture;
	typedef std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> uSdlRenderer;
private:
	sSdlWindow window;
	uSdlRenderer sdlRenderer;
	uSdlTexture sdlTex;
	TextureType tex;
	ZBuffer zbuff;
	SdlFramebuffer(const SdlFramebuffer& cpy) = delete;
	SdlFramebuffer& operator=(const SdlFramebuffer& cpy) = delete;
public:
	SdlFramebuffer(SdlFramebuffer&& mov) : window(std::move(mov.window)), sdlRenderer(std::move(mov.sdlRenderer)),
		sdlTex(std::move(mov.sdlTex)), tex(std::move(mov.tex)), zbuff( std::move(mov.zbuff)) {

	}
	SdlFramebuffer& operator=(SdlFramebuffer&& mov) {
		this->window = std::move(mov.window);
		this->sdlRenderer = std::move(mov.sdlRenderer);
		this->sdlTex = std::move(mov.sdlTex);
		this->tex = std::move(mov.tex);
		this->zbuff = std::move(mov.zbuff);
		return *this;
	}
	SdlFramebuffer(const sSdlWindow& window, int index, uint32_t flags, unsigned W, unsigned H)
		: window(window),
		  sdlRenderer(SDL_CreateRenderer(this->window.get(),index,flags),SDL_DestroyRenderer),
		  sdlTex(SDL_CreateTexture(this->sdlRenderer.get(), SdlPixelId, SDL_TEXTUREACCESS_STREAMING, W,H),SDL_DestroyTexture),
		  tex(W,H), zbuff(W,H)
	{

	}
	SdlFramebuffer(sSdlWindow&& window, int index, uint32_t flags, unsigned W, unsigned H)
		: window(std::move(window)),
		  sdlRenderer(SDL_CreateRenderer(this->window.get(),index,flags),SDL_DestroyRenderer),
		  sdlTex(SDL_CreateTexture(this->sdlRenderer.get(), SdlPixelId, SDL_TEXTUREACCESS_STREAMING, W,H),SDL_DestroyTexture),
		  tex(W,H), zbuff(W,H)
	{

	}

	Texture* getTexture() { return &tex; }
	const Texture* getTexture() const { return &tex; }
	ZBuffer* getZbuffer() { return &zbuff; }
	const ZBuffer* getZbuffer() const { return &zbuff; }
	void swapBuffers() {
		SDL_UpdateTexture(sdlTex.get(), nullptr, tex.getPixels(), tex.getStride() );
		SDL_RenderCopy(sdlRenderer.get(), sdlTex.get(), nullptr, nullptr);
		SDL_RenderPresent(sdlRenderer.get());
	}
};

#endif // SDLFRAMEBUFFER_HPP
