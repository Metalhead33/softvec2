#ifndef STANDARDTEXTURE_HPP
#define STANDARDTEXTURE_HPP
#include <glm/glm.hpp>
#include "Texture.hpp"
#include "StandardPixelType.hpp"
#include "PixelRgb16bit.hpp"
#include "PixelRgb8bit.hpp"
#include <vector>
#include <cstring>

template <typename PixelType> class StandardTexture : public Texture {
private:
	std::vector<PixelType> pixels;
	unsigned w,h;
public:
	StandardTexture(const StandardTexture& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	StandardTexture(StandardTexture&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	StandardTexture& operator=(const StandardTexture& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	StandardTexture& operator=(StandardTexture&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	StandardTexture() : w(0), h(0) {

	}
	StandardTexture(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelType));
	}
	StandardTexture(unsigned w, unsigned h, const PixelType* pixels) : pixels(w*h), w(w), h(h)
	{
		memcpy(this->pixels.data(),pixels,this->pixels.size() * sizeof(PixelType));
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelType));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelType); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelType); }
	unsigned getStride() const { return w*sizeof(PixelType); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelType& pixel = pixels[(w*(pos.y%h))+(pos.x%w)];
		pixel.fromVec4(col);
	}
	virtual void setPixelDithered(const glm::ivec2& pos, const glm::vec4& col, float ditherAmount = 0.5f) {
		PixelType& pixel = pixels[(w*(pos.y%h))+(pos.x%w)];
		pixel.fromVec4Dithered(col,pos,ditherAmount);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelType& pixel = pixels[(w*(pos.y%h))+(pos.x%w)];
		pixel.toVec4(col);
	}
	void iterateOverPixels(const PixelModifier& modifier, bool requiresOriginalPixel) {
		if(requiresOriginalPixel) {
			glm::vec4 kernel;
			for(auto& it : pixels) {
				it.toVec4(kernel);
				modifier(kernel);
				it.fromVec4(kernel);
			}
		} else {
			glm::vec4 kernel;
			modifier(kernel);
			for(auto& it : pixels) {
				it.fromVec4(kernel);
			}
		}
	}
};

typedef StandardTexture<PixelRgb332> TextureRgb332;
typedef StandardTexture<PixelRgb444> TextureRgb444;
typedef StandardTexture<PixelArgb4444> TextureArgb4444;
typedef StandardTexture<PixelRgba4444> TextureRgba4444;
typedef StandardTexture<PixelRgba5551> TextureRgba5551;
typedef StandardTexture<PixelArgb1555> TextureArgb1555;
typedef StandardTexture<PixelRgb555> TextureRgb555;
typedef StandardTexture<PixelRgb565> TextureRgb565;
// 8-bit Unsigned integer
typedef StandardTexture<PixelGreyscaleU8> TextureGreyscaleU8;
typedef StandardTexture<PixelRgbU8> TextureRgbU8;
typedef StandardTexture<PixelRgbaU8> TextureRgbaU8;
typedef StandardTexture<PixelArgbU8> TextureArgbU8;
typedef StandardTexture<PixelBgrU8> TextureBgrU8;
typedef StandardTexture<PixelBgraU8> TextureBgraU8;
typedef StandardTexture<PixelAbgrU8> TextureAbgrU8;
typedef StandardTexture<PixelRgbaU8> TextureRgbxU8;
typedef StandardTexture<PixelXrgbU8> TextureXrgbU8;
typedef StandardTexture<PixelBgrxU8> TextureBgrxU8;
typedef StandardTexture<PixelXbgrU8> TextureXbgrU8;
// 8-bit Signed integer
typedef StandardTexture<PixelGreyscaleS8> TextureGreyscaleS8;
typedef StandardTexture<PixelRgbS8> TextureRgbS8;
typedef StandardTexture<PixelRgbaS8> TextureRgbaS8;
typedef StandardTexture<PixelArgbS8> TextureArgbS8;
typedef StandardTexture<PixelBgrS8> TextureBgrS8;
typedef StandardTexture<PixelBgraS8> TextureBgraS8;
typedef StandardTexture<PixelAbgrS8> TextureAbgrS8;
// 16-bit Unsigned integer
typedef StandardTexture<PixelGreyscaleU16> TextureGreyscaleU16;
typedef StandardTexture<PixelRgbU16> TextureRgbU16;
typedef StandardTexture<PixelRgbaU16> TextureRgbaU16;
typedef StandardTexture<PixelArgbU16> TextureArgbU16;
typedef StandardTexture<PixelBgrU16> TextureBgrU16;
typedef StandardTexture<PixelBgraU16> TextureBgraU16;
typedef StandardTexture<PixelAbgrU16> TextureAbgrU16;
// 16-bit Signed integer
typedef StandardTexture<PixelGreyscaleS16> TextureGreyscaleS16;
typedef StandardTexture<PixelRgbS16> TextureRgbS16;
typedef StandardTexture<PixelRgbaS16> TextureRgbaS16;
typedef StandardTexture<PixelArgbS16> TextureArgbS16;
typedef StandardTexture<PixelBgrS16> TextureBgrS16;
typedef StandardTexture<PixelBgraS16> TextureBgraS16;
typedef StandardTexture<PixelAbgrS16> TextureAbgrS16;
// 32-bit Unsigned integer
typedef StandardTexture<PixelGreyscaleU32> TextureGreyscaleU32;
typedef StandardTexture<PixelRgbU32> TextureRgbU32;
typedef StandardTexture<PixelRgbaU32> TextureRgbaU32;
typedef StandardTexture<PixelArgbU32> TextureArgbU32;
typedef StandardTexture<PixelBgrU32> TextureBgrU32;
typedef StandardTexture<PixelBgraU32> TextureBgraU32;
typedef StandardTexture<PixelAbgrU32> TextureAbgrU32;
// 32-bit Signed integer
typedef StandardTexture<PixelGreyscaleS32> TextureGreyscaleS32;
typedef StandardTexture<PixelRgbS32> TextureRgbS32;
typedef StandardTexture<PixelRgbaS32> TextureRgbaS32;
typedef StandardTexture<PixelArgbS32> TextureArgbS32;
typedef StandardTexture<PixelBgrS32> TextureBgrS32;
typedef StandardTexture<PixelBgraS32> TextureBgraS32;
typedef StandardTexture<PixelAbgrS32> TextureAbgrS32;
// 16-bit float
typedef StandardTexture<PixelGreyscaleF16> TextureGreyscaleF16;
typedef StandardTexture<PixelRgbF16> TextureRgbF16;
typedef StandardTexture<PixelRgbaF16> TextureRgbaF16;
typedef StandardTexture<PixelArgbF16> TextureArgbF16;
typedef StandardTexture<PixelBgrF16> TextureBgrF16;
typedef StandardTexture<PixelBgraF16> TextureBgraF16;
typedef StandardTexture<PixelAbgrF16> TextureAbgrF16;
// 32-bit float
typedef StandardTexture<PixelGreyscaleF32> TextureGreyscaleF32;
typedef StandardTexture<PixelRgbF32> TextureRgbF32;
typedef StandardTexture<PixelRgbaF32> TextureRgbaF32;
typedef StandardTexture<PixelArgbF32> TextureArgbF32;
typedef StandardTexture<PixelBgrF32> TextureBgrF32;
typedef StandardTexture<PixelBgraF32> TextureBgraF32;
typedef StandardTexture<PixelAbgrF32> TextureAbgrF32;

#endif // STANDARDTEXTURE_HPP
