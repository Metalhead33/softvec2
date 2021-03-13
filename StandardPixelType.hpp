#ifndef STANDARDPIXELTYPE_HPP
#define STANDARDPIXELTYPE_HPP
#include <glm/glm.hpp>
#include <cstdint>
#include <MhLib/Util/MhNormDenorm.hpp>
template <typename Precision> struct PixelGreyscale {
	Precision brightness;
	void fromVec4(const glm::vec4& col) {
		brightness = MH33::Util::fdenormalize<Precision>(col.r);
	}
	void toVec4(glm::vec4& col) const {
		const float pixel = MH33::Util::fnormalize(brightness);
		col.r = pixel;
		col.g = pixel;
		col.b = pixel;
		col.a = 1.0f;
	}
};

template <typename Precision> struct PixelRGB {
	Precision r,g,b;
	void fromVec4(const glm::vec4& col) {
		r = MH33::Util::fdenormalize<Precision>(col.r);
		g = MH33::Util::fdenormalize<Precision>(col.g);
		b = MH33::Util::fdenormalize<Precision>(col.b);
	}
	void toVec4(glm::vec4& col) const {
		col.r = MH33::Util::fnormalize(r);
		col.g = MH33::Util::fnormalize(g);
		col.b = MH33::Util::fnormalize(b);
		col.a = 1.0f;
	}
};
template <typename Precision> struct PixelRGBA {
	Precision r,g,b,a;
	void fromVec4(const glm::vec4& col) {
		r = MH33::Util::fdenormalize<Precision>(col.r);
		g = MH33::Util::fdenormalize<Precision>(col.g);
		b = MH33::Util::fdenormalize<Precision>(col.b);
		a = MH33::Util::fdenormalize<Precision>(col.a);
	}
	void toVec4(glm::vec4& col) const {
		col.r = MH33::Util::fnormalize(r);
		col.g = MH33::Util::fnormalize(g);
		col.b = MH33::Util::fnormalize(b);
		col.a = MH33::Util::fnormalize(a);
	}
};
template <typename Precision> struct PixelARGB {
	Precision a,r,g,b;
	void fromVec4(const glm::vec4& col) {
		a = MH33::Util::fdenormalize<Precision>(col.a);
		r = MH33::Util::fdenormalize<Precision>(col.r);
		g = MH33::Util::fdenormalize<Precision>(col.g);
		b = MH33::Util::fdenormalize<Precision>(col.b);
	}
	void toVec4(glm::vec4& col) const {
		col.a = MH33::Util::fnormalize(a);
		col.r = MH33::Util::fnormalize(r);
		col.g = MH33::Util::fnormalize(g);
		col.b = MH33::Util::fnormalize(b);
	}
};

template <typename Precision> struct PixelBGR {
	Precision r,g,b;
	void fromVec4(const glm::vec4& col) {
		b = MH33::Util::fdenormalize<Precision>(col.b);
		g = MH33::Util::fdenormalize<Precision>(col.g);
		r = MH33::Util::fdenormalize<Precision>(col.r);
	}
	void toVec4(glm::vec4& col) const {
		col.b = MH33::Util::fnormalize(b);
		col.g = MH33::Util::fnormalize(g);
		col.r = MH33::Util::fnormalize(r);
		col.a = 1.0f;
	}
};
template <typename Precision> struct PixelBGRA {
	Precision r,g,b,a;
	void fromVec4(const glm::vec4& col) {
		b = MH33::Util::fdenormalize<Precision>(col.b);
		g = MH33::Util::fdenormalize<Precision>(col.g);
		r = MH33::Util::fdenormalize<Precision>(col.r);
		a = MH33::Util::fdenormalize<Precision>(col.a);
	}
	void toVec4(glm::vec4& col) const {
		col.b = MH33::Util::fnormalize(b);
		col.g = MH33::Util::fnormalize(g);
		col.r = MH33::Util::fnormalize(r);
		col.a = MH33::Util::fnormalize(a);
	}
};
template <typename Precision> struct PixelABGR {
	Precision a,r,g,b;
	void fromVec4(const glm::vec4& col) {
		a = MH33::Util::fdenormalize<Precision>(col.a);
		b = MH33::Util::fdenormalize<Precision>(col.b);
		g = MH33::Util::fdenormalize<Precision>(col.g);
		r = MH33::Util::fdenormalize<Precision>(col.r);
	}
	void toVec4(glm::vec4& col) const {
		col.a = MH33::Util::fnormalize(a);
		col.b = MH33::Util::fnormalize(b);
		col.g = MH33::Util::fnormalize(g);
		col.r = MH33::Util::fnormalize(r);
	}
};

// 8-bit Unsigned integer
typedef PixelGreyscale<uint8_t> PixelGreyscaleU8;
typedef PixelRGB<uint8_t> PixelRgbU8;
typedef PixelRGBA<uint8_t> PixelRgbaU8;
typedef PixelARGB<uint8_t> PixelArgbU8;
typedef PixelBGR<uint8_t> PixelBgrU8;
typedef PixelBGRA<uint8_t> PixelBgraU8;
typedef PixelABGR<uint8_t> PixelAbgrU8;
// 8-bit Signed integer
typedef PixelGreyscale<int8_t> PixelGreyscaleS8;
typedef PixelRGB<int8_t> PixelRgbS8;
typedef PixelRGBA<int8_t> PixelRgbaS8;
typedef PixelARGB<int8_t> PixelArgbS8;
typedef PixelBGR<int8_t> PixelBgrS8;
typedef PixelBGRA<int8_t> PixelBgraS8;
typedef PixelABGR<int8_t> PixelAbgrS8;
// 16-bit Unsigned integer
typedef PixelGreyscale<uint16_t> PixelGreyscaleU16;
typedef PixelRGB<uint16_t> PixelRgbU16;
typedef PixelRGBA<uint16_t> PixelRgbaU16;
typedef PixelARGB<uint16_t> PixelArgbU16;
typedef PixelBGR<uint16_t> PixelBgrU16;
typedef PixelBGRA<uint16_t> PixelBgraU16;
typedef PixelABGR<uint16_t> PixelAbgrU16;
// 16-bit Signed integer
typedef PixelGreyscale<int16_t> PixelGreyscaleS16;
typedef PixelRGB<int16_t> PixelRgbS16;
typedef PixelRGBA<int16_t> PixelRgbaS16;
typedef PixelARGB<int16_t> PixelArgbS16;
typedef PixelBGR<int16_t> PixelBgrS16;
typedef PixelBGRA<int16_t> PixelBgraS16;
typedef PixelABGR<int16_t> PixelAbgrS16;
// 32-bit Unsigned integer
typedef PixelGreyscale<uint32_t> PixelGreyscaleU32;
typedef PixelRGB<uint32_t> PixelRgbU32;
typedef PixelRGBA<uint32_t> PixelRgbaU32;
typedef PixelARGB<uint32_t> PixelArgbU32;
typedef PixelBGR<uint32_t> PixelBgrU32;
typedef PixelBGRA<uint32_t> PixelBgraU32;
typedef PixelABGR<uint32_t> PixelAbgrU32;
// 32-bit Signed integer
typedef PixelGreyscale<int32_t> PixelGreyscaleS32;
typedef PixelRGB<int32_t> PixelRgbS32;
typedef PixelRGBA<int32_t> PixelRgbaS32;
typedef PixelARGB<int32_t> PixelArgbS32;
typedef PixelBGR<int32_t> PixelBgrS32;
typedef PixelBGRA<int32_t> PixelBgraS32;
typedef PixelABGR<int32_t> PixelAbgrS32;
// 16-bit float
typedef PixelGreyscale<half_float::half> PixelGreyscaleF16;
typedef PixelRGB<half_float::half> PixelRgbF16;
typedef PixelRGBA<half_float::half> PixelRgbaF16;
typedef PixelARGB<half_float::half> PixelArgbF16;
typedef PixelBGR<half_float::half> PixelBgrF16;
typedef PixelBGRA<half_float::half> PixelBgraF16;
typedef PixelABGR<half_float::half> PixelAbgrF16;
// 32-bit float
typedef PixelGreyscale<float> PixelGreyscaleF32;
typedef PixelRGB<float> PixelRgbF32;
typedef PixelRGBA<float> PixelRgbaF32;
typedef PixelARGB<float> PixelArgbF32;
typedef PixelBGR<float> PixelBgrF32;
typedef PixelBGRA<float> PixelBgraF32;
typedef PixelABGR<float> PixelAbgrF32;

#endif // STANDARDPIXELTYPE_HPP
