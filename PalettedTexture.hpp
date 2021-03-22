#ifndef PALETTEDTEXTURE_HPP
#define PALETTEDTEXTURE_HPP
#include <glm/glm.hpp>
#include "StandardPixelType.hpp"
#include "PixelRgb565.hpp"
#include "Texture.hpp"
#include <array>
#include <cstring>
#include <memory>

template <typename ColourType> class Palette {
private:
	std::array<ColourType,256> pal;
public:
	constexpr static size_t paletteSize() { return 256*sizeof(ColourType); }
	Palette(const Palette& cpy) {
		memcpy(this->pal.data(),cpy.pal.data(),paletteSize()) ;
	}
	Palette& operator=(const Palette& cpy) {
		memcpy(this->pal.data(),cpy.pal.data(),paletteSize());
		return *this;
	}
	Palette() {
		memset(pal.data(),0,256*sizeof(ColourType));
	}
	Palette(const ColourType* cpy, size_t maxNum) {
		maxNum = std::min(maxNum,256);
		for(size_t i = 0; i < maxNum; ++i) {
			pal[i] = cpy[i];
		}
	}
	ColourType& getColour(uint8_t index) {
		return pal[index];
	}
	const ColourType& getColour(uint8_t index) const {
		return pal[index];
	}
	ColourType& operator[](uint8_t index) {
		return pal[index];
	}
	const ColourType& operator[](uint8_t index) const {
		return pal[index];
	}
};

template <typename PixelType> class PalettedTexture : public Texture {
public:
	typedef Palette<PixelType> ColourLookupTable;
	typedef std::shared_ptr<ColourLookupTable> sColourLookupTable;
private:
	std::vector<uint8_t> pixels;
	sColourLookupTable clut;
	unsigned w,h;
public:
	PalettedTexture() : w(0), h(0) {

	}
	PalettedTexture(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size());
	}
	PalettedTexture(unsigned w, unsigned h, const uint8_t* pixels, const sColourLookupTable& clut) : clut(clut), pixels(w*h), w(w), h(h)
	{
		memcpy(this->pixels.data(),pixels,this->pixels.size());
	}
	PalettedTexture(unsigned w, unsigned h, const uint8_t* pixels, sColourLookupTable&& clut) : clut(std::move(clut)), pixels(w*h), w(w), h(h)
	{
		memcpy(this->pixels.data(),pixels,this->pixels.size());
	}
	PalettedTexture(const PalettedTexture& cpy) : pixels(cpy.pixels), clut(cpy.clut),  w(cpy.w), h(cpy.h)
	{

	}
	PalettedTexture(PalettedTexture&& mov) : pixels(std::move(mov.pixels)), clut(std::move(mov.clut)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	PalettedTexture& operator=(const PalettedTexture& cpy)
	{
		this->pixels = cpy.pixels;
		this->clut = cpy.clut;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	PalettedTexture& operator=(PalettedTexture&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->clut = std::move(mov.clut);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	const sColourLookupTable& getClut() const { return clut; }
	void setClut(const sColourLookupTable& clut) { this->clut = clut; }
	void setClut(sColourLookupTable&& clut) { this->clut = std::move(clut); }
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size());
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(uint8_t); }
	unsigned getSizeInBytes() const { return pixels.size(); }
	unsigned getStride() const { return w*sizeof(uint8_t); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		(void)pos;
		(void)col;
	}
	virtual void setPixelDithered(const glm::ivec2& pos, const glm::vec4& col, float ditherAmount = 0.5f) {
		(void)pos;
		(void)col;
		(void)ditherAmount;
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelType& pixel = clut->getColour(pixels[(w*(pos.y%h))+(pos.x%w)]);
		pixel.toVec4(col);
	}
	void iterateOverPixels(const PixelModifier& modifier, bool requiresOriginalPixel) {
		(void)modifier;
		(void)requiresOriginalPixel;
	}
};

// PixelRgb565
typedef PalettedTexture<PixelRgba5551> PalettedTextureRgb555;
typedef PalettedTexture<PixelRgb565> PalettedTextureRgb565;
// 8-bit Unsigned integer
typedef PalettedTexture<PixelRgbU8> PalettedTextureRgbU8;
typedef PalettedTexture<PixelRgbaU8> PalettedTextureRgbaU8;
typedef PalettedTexture<PixelArgbU8> PalettedTextureArgbU8;
typedef PalettedTexture<PixelBgrU8> PalettedTextureBgrU8;
typedef PalettedTexture<PixelBgraU8> PalettedTextureBgraU8;
typedef PalettedTexture<PixelAbgrU8> PalettedTextureAbgrU8;
// 8-bit Signed integer
typedef PalettedTexture<PixelRgbS8> PalettedTextureRgbS8;
typedef PalettedTexture<PixelRgbaS8> PalettedTextureRgbaS8;
typedef PalettedTexture<PixelArgbS8> PalettedTextureArgbS8;
typedef PalettedTexture<PixelBgrS8> PalettedTextureBgrS8;
typedef PalettedTexture<PixelBgraS8> PalettedTextureBgraS8;
typedef PalettedTexture<PixelAbgrS8> PalettedTextureAbgrS8;
// 16-bit Unsigned integer
typedef PalettedTexture<PixelRgbU16> PalettedTextureRgbU16;
typedef PalettedTexture<PixelRgbaU16> PalettedTextureRgbaU16;
typedef PalettedTexture<PixelArgbU16> PalettedTextureArgbU16;
typedef PalettedTexture<PixelBgrU16> PalettedTextureBgrU16;
typedef PalettedTexture<PixelBgraU16> PalettedTextureBgraU16;
typedef PalettedTexture<PixelAbgrU16> PalettedTextureAbgrU16;
// 16-bit Signed integer
typedef PalettedTexture<PixelRgbS16> PalettedTextureRgbS16;
typedef PalettedTexture<PixelRgbaS16> PalettedTextureRgbaS16;
typedef PalettedTexture<PixelArgbS16> PalettedTextureArgbS16;
typedef PalettedTexture<PixelBgrS16> PalettedTextureBgrS16;
typedef PalettedTexture<PixelBgraS16> PalettedTextureBgraS16;
typedef PalettedTexture<PixelAbgrS16> PalettedTextureAbgrS16;
// 32-bit Unsigned integer
typedef PalettedTexture<PixelRgbU32> PalettedTextureRgbU32;
typedef PalettedTexture<PixelRgbaU32> PalettedTextureRgbaU32;
typedef PalettedTexture<PixelArgbU32> PalettedTextureArgbU32;
typedef PalettedTexture<PixelBgrU32> PalettedTextureBgrU32;
typedef PalettedTexture<PixelBgraU32> PalettedTextureBgraU32;
typedef PalettedTexture<PixelAbgrU32> PalettedTextureAbgrU32;
// 32-bit Signed integer
typedef PalettedTexture<PixelRgbS32> PalettedTextureRgbS32;
typedef PalettedTexture<PixelRgbaS32> PalettedTextureRgbaS32;
typedef PalettedTexture<PixelArgbS32> PalettedTextureArgbS32;
typedef PalettedTexture<PixelBgrS32> PalettedTextureBgrS32;
typedef PalettedTexture<PixelBgraS32> PalettedTextureBgraS32;
typedef PalettedTexture<PixelAbgrS32> PalettedTextureAbgrS32;
// 16-bit float
typedef PalettedTexture<PixelRgbF16> PalettedTextureRgbF16;
typedef PalettedTexture<PixelRgbaF16> PalettedTextureRgbaF16;
typedef PalettedTexture<PixelArgbF16> PalettedTextureArgbF16;
typedef PalettedTexture<PixelBgrF16> PalettedTextureBgrF16;
typedef PalettedTexture<PixelBgraF16> PalettedTextureBgraF16;
typedef PalettedTexture<PixelAbgrF16> PalettedTextureAbgrF16;
// 32-bit float
typedef PalettedTexture<PixelRgbF32> PalettedTextureRgbF32;
typedef PalettedTexture<PixelRgbaF32> PalettedTextureRgbaF32;
typedef PalettedTexture<PixelArgbF32> PalettedTextureArgbF32;
typedef PalettedTexture<PixelBgrF32> PalettedTextureBgrF32;
typedef PalettedTexture<PixelBgraF32> PalettedTextureBgraF32;
typedef PalettedTexture<PixelAbgrF32> PalettedTextureAbgrF32;

#endif // PALETTEDTEXTURE_HPP
