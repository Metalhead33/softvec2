#ifndef OPTIMIZEDTEXTURE_HPP
#define OPTIMIZEDTEXTURE_HPP
#include <cstdint>
#include "Texture.hpp"
#include "Palette.hpp"
#include "../NormDenorm.hpp"
#include <vector>
#include <cstring>
#include <memory>

enum class TexRes : uint8_t {
	T_1_X_1=0,
	T_2_X_2=1,
	T_4_X_4=2,
	T_8_X_8=3,
	T_16_X_16=4,
	T_32_X_32=5,
	T_64_X_64=6,
	T_128_X_128=7,
	T_256_X_256=8,
	T_512_X_512=9,
	T_1024_X_1024=10,
	T_2048_X_2048=11,
	T_4096_X_4096=12,
	T_8192_X_8192=13,
	T_16384_X_16384=15
};

template <TexRes po2> struct OptimizedTextureDimensions {
	static constexpr const uint32_t DIM = 1 << uint32_t(po2);
	static constexpr const uint32_t PIXCOUNT = DIM * DIM;
	static constexpr const float FDIM = float(DIM-1);
	static constexpr uint32_t getIndex(uint32_t x, uint32_t y)
	{
		return (y << uint32_t(po2)) | x;
	}
};

template <typename ColourDepth, TexRes po2> class OptimizedTextureGreyscale : public Texture {
public:
	typedef std::vector<ColourDepth> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	static constexpr const unsigned pitch = OptimizedTextureDimensions<po2>::DIM *sizeof(ColourDepth);
	static constexpr const unsigned bpp = sizeof(ColourDepth) * 8;
public:
	OptimizedTextureGreyscale()
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{

	}
	OptimizedTextureGreyscale(const ColourDepth* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{
		std::memcpy(buffer.data(),pixels,sizeof(ColourDepth)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureGreyscale(const OptimizedTextureGreyscale& cpy) // Copy constructor
		: buffer(cpy.buffer)
	{

	}
	OptimizedTextureGreyscale(OptimizedTextureGreyscale&& mov) // Move constructor
		: buffer(std::move(mov.buffer))
	{

	}
	void operator=(const OptimizedTextureGreyscale& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
	}
	void operator=(OptimizedTextureGreyscale&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
	}
	// Regular buffer compatibility
	ColourDepth* data() { return buffer.data(); }
	const ColourDepth* data() const { return buffer.data(); }
	ColourDepth& at(unsigned i) { return buffer[i]; }
	ColourDepth& operator[](unsigned i) { return buffer[i]; }
	const ColourDepth& at(unsigned i) const { return buffer[i]; }
	const ColourDepth& operator[](unsigned i) const { return buffer[i]; }
	iterator begin() { return buffer.begin(); }
	const_iterator begin() const { return buffer.begin(); }
	iterator end() { return buffer.end(); }
	const_iterator end() const { return buffer.end(); }
	reverse_iterator rbegin() { return buffer.rbegin(); }
	const_reverse_iterator rbegin() const { return buffer.rbegin(); }
	reverse_iterator rend() { return buffer.rend(); }
	const_reverse_iterator rend() const { return buffer.rend(); }
	// Texture implementations
	unsigned getWidth() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getHeight() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return OptimizedTextureDimensions<po2>::PIXCOUNT; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return OptimizedTextureDimensions<po2>::FDIM; }
	float getFHeight() const { return OptimizedTextureDimensions<po2>::FDIM; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		SimdFvec4 tmp = src * SimdFvec4(0.2989f,0.5871f,0.1140f,0.0f);
		tmpRef = denormalize<ColourDepth>(tmp.sum());
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		dst = normalize(tmpRef);
		dst[3] = 1.0f;
	}
};
template <typename ColourDepth, TexRes po2> class OptimizedTextureRGB : public Texture {
public:
	struct PixelRGB {
		ColourDepth r;
		ColourDepth g;
		ColourDepth b;
	};
	typedef std::vector<PixelRGB> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	static constexpr const unsigned pitch = OptimizedTextureDimensions<po2>::DIM *sizeof(PixelRGB);
	static constexpr const unsigned bpp = sizeof(PixelRGB) * 8;
public:
	OptimizedTextureRGB()
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{

	}
	OptimizedTextureRGB(const PixelRGB* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelRGB)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureRGB(const OptimizedTextureRGB& cpy) // Copy constructor
		: buffer(cpy.buffer)
	{

	}
	OptimizedTextureRGB(OptimizedTextureRGB&& mov) // Move constructor
		: buffer(std::move(mov.buffer))
	{

	}
	void operator=(const OptimizedTextureRGB& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
	}
	void operator=(OptimizedTextureRGB&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
	}
	// Regular buffer compatibility
	PixelRGB* data() { return buffer.data(); }
	const PixelRGB* data() const { return buffer.data(); }
	PixelRGB& at(unsigned i) { return buffer[i]; }
	PixelRGB& operator[](unsigned i) { return buffer[i]; }
	const PixelRGB& at(unsigned i) const { return buffer[i]; }
	const PixelRGB& operator[](unsigned i) const { return buffer[i]; }
	iterator begin() { return buffer.begin(); }
	const_iterator begin() const { return buffer.begin(); }
	iterator end() { return buffer.end(); }
	const_iterator end() const { return buffer.end(); }
	reverse_iterator rbegin() { return buffer.rbegin(); }
	const_reverse_iterator rbegin() const { return buffer.rbegin(); }
	reverse_iterator rend() { return buffer.rend(); }
	const_reverse_iterator rend() const { return buffer.rend(); }
	// Texture implementations
	unsigned getWidth() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getHeight() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return OptimizedTextureDimensions<po2>::PIXCOUNT; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return OptimizedTextureDimensions<po2>::FDIM; }
	float getFHeight() const { return OptimizedTextureDimensions<po2>::FDIM; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), 1.0f);
	}
};
template <typename ColourDepth, TexRes po2> class OptimizedTextureBGR : public Texture {
public:
	struct PixelBGR {
		ColourDepth b;
		ColourDepth g;
		ColourDepth r;
	};
	typedef std::vector<PixelBGR> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	static constexpr const unsigned pitch = OptimizedTextureDimensions<po2>::DIM *sizeof(PixelBGR);
	static constexpr const unsigned bpp = sizeof(PixelBGR) * 8;
public:
	OptimizedTextureBGR()
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{

	}
	OptimizedTextureBGR(const PixelBGR* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelBGR)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureBGR(const OptimizedTextureBGR& cpy) // Copy constructor
		: buffer(cpy.buffer)
	{

	}
	OptimizedTextureBGR(OptimizedTextureBGR&& mov) // Move constructor
		: buffer(std::move(mov.buffer))
	{

	}
	void operator=(const OptimizedTextureBGR& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
	}
	void operator=(OptimizedTextureBGR&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
	}
	// Regular buffer compatibility
	PixelBGR* data() { return buffer.data(); }
	const PixelBGR* data() const { return buffer.data(); }
	PixelBGR& at(unsigned i) { return buffer[i]; }
	PixelBGR& operator[](unsigned i) { return buffer[i]; }
	const PixelBGR& at(unsigned i) const { return buffer[i]; }
	const PixelBGR& operator[](unsigned i) const { return buffer[i]; }
	iterator begin() { return buffer.begin(); }
	const_iterator begin() const { return buffer.begin(); }
	iterator end() { return buffer.end(); }
	const_iterator end() const { return buffer.end(); }
	reverse_iterator rbegin() { return buffer.rbegin(); }
	const_reverse_iterator rbegin() const { return buffer.rbegin(); }
	reverse_iterator rend() { return buffer.rend(); }
	const_reverse_iterator rend() const { return buffer.rend(); }
	// Texture implementations
	unsigned getWidth() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getHeight() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return OptimizedTextureDimensions<po2>::PIXCOUNT; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return OptimizedTextureDimensions<po2>::FDIM; }
	float getFHeight() const { return OptimizedTextureDimensions<po2>::FDIM; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), 1.0f);
	}
};
template <typename ColourDepth, TexRes po2> class OptimizedTextureRGBA : public Texture {
public:
	struct PixelRGBA {
		ColourDepth r;
		ColourDepth g;
		ColourDepth b;
		ColourDepth a;
	};
	typedef std::vector<PixelRGBA> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	static constexpr const unsigned pitch = OptimizedTextureDimensions<po2>::DIM *sizeof(PixelRGBA);
	static constexpr const unsigned bpp = sizeof(PixelRGBA) * 8;
public:
	OptimizedTextureRGBA()
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{

	}
	OptimizedTextureRGBA(const PixelRGBA* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelRGBA)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureRGBA(const OptimizedTextureRGBA& cpy) // Copy constructor
		: buffer(cpy.buffer)
	{

	}
	OptimizedTextureRGBA(OptimizedTextureRGBA&& mov) // Move constructor
		: buffer(std::move(mov.buffer))
	{

	}
	void operator=(const OptimizedTextureRGBA& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
	}
	void operator=(OptimizedTextureRGBA&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
	}
	// Regular buffer compatibility
	PixelRGBA* data() { return buffer.data(); }
	const PixelRGBA* data() const { return buffer.data(); }
	PixelRGBA& at(unsigned i) { return buffer[i]; }
	PixelRGBA& operator[](unsigned i) { return buffer[i]; }
	const PixelRGBA& at(unsigned i) const { return buffer[i]; }
	const PixelRGBA& operator[](unsigned i) const { return buffer[i]; }
	iterator begin() { return buffer.begin(); }
	const_iterator begin() const { return buffer.begin(); }
	iterator end() { return buffer.end(); }
	const_iterator end() const { return buffer.end(); }
	reverse_iterator rbegin() { return buffer.rbegin(); }
	const_reverse_iterator rbegin() const { return buffer.rbegin(); }
	reverse_iterator rend() { return buffer.rend(); }
	const_reverse_iterator rend() const { return buffer.rend(); }
	// Texture implementations
	unsigned getWidth() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getHeight() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return OptimizedTextureDimensions<po2>::PIXCOUNT; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return OptimizedTextureDimensions<po2>::FDIM; }
	float getFHeight() const { return OptimizedTextureDimensions<po2>::FDIM; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
		tmpRef.a = denormalize<ColourDepth>(src[3]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), normalize(tmpRef.a));
	}
};
template <typename ColourDepth, TexRes po2> class OptimizedTextureBGRA : public Texture {
public:
	struct PixelBGRA {
		ColourDepth b;
		ColourDepth g;
		ColourDepth r;
		ColourDepth a;
	};
	typedef std::vector<PixelBGRA> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	static constexpr const unsigned pitch = OptimizedTextureDimensions<po2>::DIM *sizeof(PixelBGRA);
	static constexpr const unsigned bpp = sizeof(PixelBGRA) * 8;
public:
	OptimizedTextureBGRA()
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{

	}
	OptimizedTextureBGRA(const PixelBGRA* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT)
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelBGRA)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureBGRA(const OptimizedTextureBGRA& cpy) // Copy constructor
		: buffer(cpy.buffer)
	{

	}
	OptimizedTextureBGRA(OptimizedTextureBGRA&& mov) // Move constructor
		: buffer(std::move(mov.buffer))
	{

	}
	void operator=(const OptimizedTextureBGRA& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
	}
	void operator=(OptimizedTextureBGRA&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
	}
	// Regular buffer compatibility
	PixelBGRA* data() { return buffer.data(); }
	const PixelBGRA* data() const { return buffer.data(); }
	PixelBGRA& at(unsigned i) { return buffer[i]; }
	PixelBGRA& operator[](unsigned i) { return buffer[i]; }
	const PixelBGRA& at(unsigned i) const { return buffer[i]; }
	const PixelBGRA& operator[](unsigned i) const { return buffer[i]; }
	iterator begin() { return buffer.begin(); }
	const_iterator begin() const { return buffer.begin(); }
	iterator end() { return buffer.end(); }
	const_iterator end() const { return buffer.end(); }
	reverse_iterator rbegin() { return buffer.rbegin(); }
	const_reverse_iterator rbegin() const { return buffer.rbegin(); }
	reverse_iterator rend() { return buffer.rend(); }
	const_reverse_iterator rend() const { return buffer.rend(); }
	// Texture implementations
	unsigned getWidth() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getHeight() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return OptimizedTextureDimensions<po2>::PIXCOUNT; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return OptimizedTextureDimensions<po2>::FDIM; }
	float getFHeight() const { return OptimizedTextureDimensions<po2>::FDIM; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
		tmpRef.a = denormalize<ColourDepth>(src[3]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		auto& tmpRef = at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1]) );
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), normalize(tmpRef.a));
	}
};
template <typename ColourDepth, TexRes po2> class OptimizedTextureIndexed : public Texture {
public:
	typedef std::shared_ptr<Palette<ColourDepth>> sPalette;
	typedef std::vector<uint8_t> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	sPalette palette;
	static constexpr const unsigned pitch = OptimizedTextureDimensions<po2>::DIM *sizeof(uint8_t);
	static constexpr const unsigned bpp = sizeof(uint8_t) * 8;
public:
	OptimizedTextureIndexed(const sPalette& npalette)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT), palette(npalette)
	{

	}
	OptimizedTextureIndexed(sPalette&& npalette)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT), palette(std::move(npalette))
	{

	}
	OptimizedTextureIndexed(const sPalette& npalette,const uint8_t* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT),palette(npalette)
	{
		std::memcpy(buffer.data(),pixels,sizeof(uint8_t)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureIndexed(sPalette&& npalette,const uint8_t* pixels)
		: buffer(OptimizedTextureDimensions<po2>::PIXCOUNT),palette(std::move(npalette))
	{
		std::memcpy(buffer.data(),pixels,sizeof(uint8_t)*OptimizedTextureDimensions<po2>::PIXCOUNT);
	}
	OptimizedTextureIndexed(const OptimizedTextureIndexed& cpy) // Copy constructor
		: buffer(cpy.buffer), palette(cpy.palette)
	{

	}
	OptimizedTextureIndexed(OptimizedTextureIndexed&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), palette(std::move(mov.palette))
	{

	}
	void operator=(const OptimizedTextureIndexed& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->palette = cpy.palette;
	}
	void operator=(OptimizedTextureIndexed&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->palette = std::move(mov.palette);
	}
	// Regular buffer compatibility
	uint8_t* data() { return buffer.data(); }
	const uint8_t* data() const { return buffer.data(); }
	uint8_t& at(unsigned i) { return buffer[i]; }
	uint8_t& operator[](unsigned i) { return buffer[i]; }
	const uint8_t& at(unsigned i) const { return buffer[i]; }
	const uint8_t& operator[](unsigned i) const { return buffer[i]; }
	iterator begin() { return buffer.begin(); }
	const_iterator begin() const { return buffer.begin(); }
	iterator end() { return buffer.end(); }
	const_iterator end() const { return buffer.end(); }
	reverse_iterator rbegin() { return buffer.rbegin(); }
	const_reverse_iterator rbegin() const { return buffer.rbegin(); }
	reverse_iterator rend() { return buffer.rend(); }
	const_reverse_iterator rend() const { return buffer.rend(); }
	// Texture implementations
	unsigned getWidth() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getHeight() const { return OptimizedTextureDimensions<po2>::DIM; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return OptimizedTextureDimensions<po2>::PIXCOUNT; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return OptimizedTextureDimensions<po2>::FDIM; }
	float getFHeight() const { return OptimizedTextureDimensions<po2>::FDIM; }
	const sPalette& getPalette() const { return palette; }
	void setPalette(const sPalette& npalette) { palette = npalette; }
	void setPalette(sPalette&& npalette) { palette = std::move(npalette); }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		(void)src;(void)coords;
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		palette->storePixelTo(dst,at(OptimizedTextureDimensions<po2>::getIndex(coords[0],coords[1])));
	}
};

#endif // OPTIMIZEDTEXTURE_HPP
