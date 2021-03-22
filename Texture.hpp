#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <glm/glm.hpp>
#include <functional>
#include <memory>

enum class TextureFiltering {
	NEAREST_NEIGHBOUR,
	DITHERED,
	BILINEAR
};
enum class AlphaBlending {
	INTERPOLATED,
	DITHERED
};
class Texture;
typedef std::shared_ptr<Texture> sTexture;
class Texture
{
public:
	typedef std::function<void(glm::vec4&)> PixelModifier;
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
	virtual void iterateOverPixels(const PixelModifier& modifier, bool requiresOriginalPixel) = 0;

	// Non-return variants
	void sample(const glm::vec2& uv, const glm::ivec2& screencoords, glm::vec4& col, TextureFiltering filteringType) const;
	void sampleNearestNeighbour(const glm::vec2& uv, glm::vec4& col) const;
	void sampleDithered(const glm::vec2& uv, const glm::ivec2& screencoords, glm::vec4& col) const;
	void sampleBilinear(const glm::vec2& uv, glm::vec4& col) const;

	// Returning variants
	glm::vec4 getPixel(const glm::ivec2& pos);
	glm::vec4 sample(const glm::vec2& uv, const glm::ivec2& screencoords, TextureFiltering filteringType) const;
	glm::vec4 sampleNearestNeighbour(const glm::vec2& uv) const;
	glm::vec4 sampleDithered(const glm::vec2& uv, const glm::ivec2& screencoords) const;
	glm::vec4 sampleBilinear(const glm::vec2& uv) const;

	// Some other convenience functions
	void clearToColour(const glm::vec4& colour);
	bool setPixelWithBlending(const glm::ivec2& pos, const glm::vec4& col, AlphaBlending blendingMode);
};

#endif // TEXTURE_HPP
