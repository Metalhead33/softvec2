#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "../vecdefs.hpp"

class Texture {
public:
	virtual ~Texture() = default;
	// Texture info
	virtual unsigned getWidth() const = 0;
	virtual unsigned getHeight() const = 0;
	virtual unsigned getPitch() const = 0;
	virtual unsigned getPixelCount() const = 0;
	virtual unsigned getBPP() const = 0;
	virtual float getFWidth() const = 0;
	virtual float getFHeight() const = 0;
	// Load from and to
	virtual void loadPixelFrom(const fvec4& src, const ivec2& coords) = 0;
	virtual void storePixelTo(fvec4& dst, const ivec2& coords) const = 0;
	// Helpers
	void getPixelNearestNeighbour(fvec4& dst, const fvec2& coords) const;
	void getPixelOrderedDithering(fvec4& dst, const fvec2& coords, const ivec2& screenCoords) const;
	void getPixelBilinear(fvec4& dst, const fvec2& coords) const;
	void blendPixels(const fvec4& src, const ivec2& coords);
};

#endif // TEXTURE_HPP
