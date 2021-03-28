#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include "Texture.hpp"
#include "ZBuffer.hpp"

class Framebuffer
{
public:
	virtual ~Framebuffer() = default;
	virtual Texture* getTexture() = 0;
	virtual const Texture* getTexture() const = 0;
	virtual ZBuffer* getZbuffer() = 0;
	virtual const ZBuffer* getZbuffer() const = 0;
	virtual void swapBuffers() = 0;
};

#endif // FRAMEBUFFER_HPP
