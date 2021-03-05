#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <glm/glm.hpp>

class Texture
{
public:
	virtual ~Texture() = default;
	virtual void* getPixels() = 0;
	virtual void clear() = 0;
	virtual const void* getPixels() const = 0;
	virtual unsigned getW() const = 0;
	virtual unsigned getH() const = 0;
	virtual unsigned getPictureSize() const = 0;
	virtual unsigned getPixelSize() const = 0;
	virtual unsigned getSizeInBytes() const = 0;
	virtual unsigned getStride() const = 0;
	virtual void setPixel(const glm::ivec2& pos, const glm::vec4& col) = 0;
	virtual void getPixel(const glm::ivec2& pos, glm::vec4& col) const = 0;

	// Non-return variants
	void sampleNearestNeighbour(const glm::vec2& uv, glm::vec4& col) const;
	void sampleDithered(const glm::vec2& uv, const glm::ivec2& screencoords, glm::vec4& col) const;
	void sampleBilinear(const glm::vec2& uv, glm::vec4& col) const;

	// Returning variants
	glm::vec4 getPixel(const glm::ivec2& pos);
	glm::vec4 sampleNearestNeighbour(const glm::vec2& uv) const;
	glm::vec4 sampleDithered(const glm::vec2& uv, const glm::ivec2& screencoords) const;
	glm::vec4 sampleBilinear(const glm::vec2& uv) const;

};

#endif // TEXTURE_HPP
