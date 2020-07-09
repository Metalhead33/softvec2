#ifndef STANDARDTEXTURE_HPP
#define STANDARDTEXTURE_HPP
#include "Texture.hpp"
#include "Palette.hpp"
#include <cstdint>
#include <cstring>
#include <memory>

template <typename ColourDepth> class TextureGreyscale : public Texture {
public:
	typedef std::vector<ColourDepth> PixelBuffer;
	typedef typename PixelBuffer::iterator iterator;
	typedef typename PixelBuffer::const_iterator const_iterator;
	typedef typename PixelBuffer::reverse_iterator reverse_iterator;
	typedef typename PixelBuffer::const_reverse_iterator const_reverse_iterator;
private:
	PixelBuffer buffer;
	unsigned width, height, pitch, pixcount;
	float fwidth, fheight;
	static constexpr const unsigned bpp = sizeof(ColourDepth) * 8;
public:
	TextureGreyscale(unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureGreyscale(const ColourDepth* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(ColourDepth)*nwidth*nheight);
	}
	TextureGreyscale(const TextureGreyscale& cpy) // Copy constructor
		: buffer(cpy.buffer), width(cpy.width), height(cpy.height),
		  pitch(cpy.pitch), pixcount(cpy.pixcount), fwidth(cpy.fwidth),
		  fheight(cpy.fheight)
	{

	}
	TextureGreyscale(TextureGreyscale&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), width(mov.width), height(mov.height),
		  pitch(mov.pitch), pixcount(mov.pixcount), fwidth(mov.fwidth),
		  fheight(mov.fheight)
	{

	}
	void operator=(const TextureGreyscale& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->width = cpy.width;
		this->height = cpy.height;
		this->pitch = cpy.pitch;
		this->pixcount = cpy.pixcount;
		this->fwidth = cpy.fwidth;
		this->fheight= cpy.fheight;
	}
	void operator=(TextureGreyscale&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->width = mov.width;
		this->height = mov.height;
		this->pitch = mov.pitch;
		this->pixcount = mov.pixcount;
		this->fwidth = mov.fwidth;
		this->fheight= mov.fheight;
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
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return pixcount; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return fwidth; }
	float getFHeight() const { return fheight; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(coords[1] * width + coords[0]);
		SimdFvec4 tmp = src * SimdFvec4(0.2989f,0.5871f,0.1140f,0.0f);
		tmpRef = denormalize<ColourDepth>(tmp.sum());
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		const auto& tmpRef = at(coords[1] * width + coords[0]);
		dst = normalize(tmpRef);
		dst[3] = 1.0f;
	}
};

template <typename ColourDepth> class TextureRGB : public Texture {
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
	unsigned width, height, pitch, pixcount;
	float fwidth, fheight;
	static constexpr const unsigned bpp = sizeof(PixelRGB) * 8;
public:
	TextureRGB(unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureRGB(const PixelRGB* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelRGB)*nwidth*nheight);
	}
	TextureRGB(const TextureRGB& cpy) // Copy constructor
		: buffer(cpy.buffer), width(cpy.width), height(cpy.height),
		  pitch(cpy.pitch), pixcount(cpy.pixcount), fwidth(cpy.fwidth),
		  fheight(cpy.fheight)
	{

	}
	TextureRGB(TextureRGB&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), width(mov.width), height(mov.height),
		  pitch(mov.pitch), pixcount(mov.pixcount), fwidth(mov.fwidth),
		  fheight(mov.fheight)
	{

	}
	void operator=(const TextureRGB& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->width = cpy.width;
		this->height = cpy.height;
		this->pitch = cpy.pitch;
		this->pixcount = cpy.pixcount;
		this->fwidth = cpy.fwidth;
		this->fheight= cpy.fheight;
	}
	void operator=(TextureRGB&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->width = mov.width;
		this->height = mov.height;
		this->pitch = mov.pitch;
		this->pixcount = mov.pixcount;
		this->fwidth = mov.fwidth;
		this->fheight= mov.fheight;
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
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return pixcount; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return fwidth; }
	float getFHeight() const { return fheight; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(coords[1] * width + coords[0]);
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		const auto& tmpRef = at(coords[1] * width + coords[0]);
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), 1.0f);
	}
};
template <typename ColourDepth> class TextureBGR : public Texture {
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
	unsigned width, height, pitch, pixcount;
	float fwidth, fheight;
	static constexpr const unsigned bpp = sizeof(PixelBGR) * 8;
public:
	TextureBGR(unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureBGR(const PixelBGR* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelBGR)*nwidth*nheight);
	}
	TextureBGR(const TextureBGR& cpy) // Copy constructor
		: buffer(cpy.buffer), width(cpy.width), height(cpy.height),
		  pitch(cpy.pitch), pixcount(cpy.pixcount), fwidth(cpy.fwidth),
		  fheight(cpy.fheight)
	{

	}
	TextureBGR(TextureBGR&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), width(mov.width), height(mov.height),
		  pitch(mov.pitch), pixcount(mov.pixcount), fwidth(mov.fwidth),
		  fheight(mov.fheight)
	{

	}
	void operator=(const TextureBGR& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->width = cpy.width;
		this->height = cpy.height;
		this->pitch = cpy.pitch;
		this->pixcount = cpy.pixcount;
		this->fwidth = cpy.fwidth;
		this->fheight= cpy.fheight;
	}
	void operator=(TextureBGR&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->width = mov.width;
		this->height = mov.height;
		this->pitch = mov.pitch;
		this->pixcount = mov.pixcount;
		this->fwidth = mov.fwidth;
		this->fheight= mov.fheight;
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
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return pixcount; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return fwidth; }
	float getFHeight() const { return fheight; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(coords[1] * width + coords[0]);
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		const auto& tmpRef = at(coords[1] * width + coords[0]);
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), 1.0f);
	}
};

template <typename ColourDepth> class TextureRGBA : public Texture {
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
	unsigned width, height, pitch, pixcount;
	float fwidth, fheight;
	static constexpr const unsigned bpp = sizeof(PixelRGBA) * 8;
public:
	TextureRGBA(unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureRGBA(const PixelRGBA* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelRGBA)*nwidth*nheight);
	}
	TextureRGBA(const TextureRGBA& cpy) // Copy constructor
		: buffer(cpy.buffer), width(cpy.width), height(cpy.height),
		  pitch(cpy.pitch), pixcount(cpy.pixcount), fwidth(cpy.fwidth),
		  fheight(cpy.fheight)
	{

	}
	TextureRGBA(TextureRGBA&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), width(mov.width), height(mov.height),
		  pitch(mov.pitch), pixcount(mov.pixcount), fwidth(mov.fwidth),
		  fheight(mov.fheight)
	{

	}
	void operator=(const TextureRGBA& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->width = cpy.width;
		this->height = cpy.height;
		this->pitch = cpy.pitch;
		this->pixcount = cpy.pixcount;
		this->fwidth = cpy.fwidth;
		this->fheight= cpy.fheight;
	}
	void operator=(TextureRGBA&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->width = mov.width;
		this->height = mov.height;
		this->pitch = mov.pitch;
		this->pixcount = mov.pixcount;
		this->fwidth = mov.fwidth;
		this->fheight= mov.fheight;
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
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return pixcount; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return fwidth; }
	float getFHeight() const { return fheight; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(coords[1] * width + coords[0]);
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
		tmpRef.a = denormalize<ColourDepth>(src[3]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		const auto& tmpRef = at(coords[1] * width + coords[0]);
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), normalize(tmpRef.a));
	}
};
template <typename ColourDepth> class TextureBGRA : public Texture {
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
	unsigned width, height, pitch, pixcount;
	float fwidth, fheight;
	static constexpr const unsigned bpp = sizeof(PixelBGRA) * 8;
public:
	TextureBGRA(unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureBGRA(const PixelBGRA* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(PixelBGRA)*nwidth*nheight);
	}
	TextureBGRA(const TextureBGRA& cpy) // Copy constructor
		: buffer(cpy.buffer), width(cpy.width), height(cpy.height),
		  pitch(cpy.pitch), pixcount(cpy.pixcount), fwidth(cpy.fwidth),
		  fheight(cpy.fheight)
	{

	}
	TextureBGRA(TextureBGRA&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), width(mov.width), height(mov.height),
		  pitch(mov.pitch), pixcount(mov.pixcount), fwidth(mov.fwidth),
		  fheight(mov.fheight)
	{

	}
	void operator=(const TextureBGRA& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->width = cpy.width;
		this->height = cpy.height;
		this->pitch = cpy.pitch;
		this->pixcount = cpy.pixcount;
		this->fwidth = cpy.fwidth;
		this->fheight= cpy.fheight;
	}
	void operator=(TextureBGRA&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->width = mov.width;
		this->height = mov.height;
		this->pitch = mov.pitch;
		this->pixcount = mov.pixcount;
		this->fwidth = mov.fwidth;
		this->fheight= mov.fheight;
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
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return pixcount; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return fwidth; }
	float getFHeight() const { return fheight; }
	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		auto& tmpRef = at(coords[1] * width + coords[0]);
		tmpRef.r = denormalize<ColourDepth>(src[0]);
		tmpRef.g = denormalize<ColourDepth>(src[1]);
		tmpRef.b = denormalize<ColourDepth>(src[2]);
		tmpRef.a = denormalize<ColourDepth>(src[3]);
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		const auto& tmpRef = at(coords[1] * width + coords[0]);
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), normalize(tmpRef.a));
	}
};
template <typename ColourDepth> class TextureIndexed : public Texture {
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
	unsigned width, height, pitch, pixcount;
	float fwidth, fheight;
	static constexpr const unsigned bpp = sizeof(uint8_t) * 8;
public:
	TextureIndexed(const sPalette& npalette, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), palette(npalette), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureIndexed(sPalette&& npalette, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight), palette(std::move(npalette)), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(ColourDepth)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{

	}
	TextureIndexed(const sPalette& npalette,const uint8_t* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight),palette(npalette), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(uint8_t)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(uint8_t)*nwidth*nheight);
	}
	TextureIndexed(sPalette&& npalette,const uint8_t* pixels, unsigned nwidth, unsigned nheight)
		: buffer(nwidth * nheight),palette(std::move(npalette)), width(nwidth), height(nheight),
		  pitch(nwidth*sizeof(uint8_t)), pixcount(nwidth*nheight),
		  fwidth(float(nwidth-1)), fheight(float(nheight-1))
	{
		std::memcpy(buffer.data(),pixels,sizeof(uint8_t)*nwidth*nheight);
	}
	TextureIndexed(const TextureIndexed& cpy) // Copy constructor
		: buffer(cpy.buffer), palette(cpy.palette), width(cpy.width), height(cpy.height),
		  pitch(cpy.pitch), pixcount(cpy.pixcount), fwidth(cpy.fwidth),
		  fheight(cpy.fheight)
	{

	}
	TextureIndexed(TextureIndexed&& mov) // Move constructor
		: buffer(std::move(mov.buffer)), palette(std::move(mov.palette)),width(mov.width), height(mov.height),
		  pitch(mov.pitch), pixcount(mov.pixcount), fwidth(mov.fwidth),
		  fheight(mov.fheight)
	{

	}
	void operator=(const TextureIndexed& cpy) // Copy assignment
	{
		this->buffer = cpy.buffer;
		this->palette = cpy.palette;
		this->width = cpy.width;
		this->height = cpy.height;
		this->pitch = cpy.pitch;
		this->pixcount = cpy.pixcount;
		this->fwidth = cpy.fwidth;
		this->fheight= cpy.fheight;
	}
	void operator=(TextureIndexed&& mov) // Move assignment
	{
		this->buffer = std::move(mov.buffer);
		this->palette = std::move(mov.palette);
		this->width = mov.width;
		this->height = mov.height;
		this->pitch = mov.pitch;
		this->pixcount = mov.pixcount;
		this->fwidth = mov.fwidth;
		this->fheight= mov.fheight;
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
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }
	unsigned getPitch() const { return pitch; }
	unsigned getPixelCount() const { return pixcount; }
	unsigned getBPP() const { return bpp; }
	float getFWidth() const { return fwidth; }
	float getFHeight() const { return fheight; }
	const sPalette& getPalette() const { return palette; }
	void setPalette(const sPalette& npalette) { palette = npalette; }
	void setPalette(sPalette&& npalette) { palette = std::move(npalette); }

	void loadPixelFrom(const fvec4& src, const ivec2& coords)
	{
		(void)src;(void)coords;
	}
	void storePixelTo(fvec4& dst, const ivec2& coords) const
	{
		palette->storePixelTo(dst,at(coords[1] * width + coords[0]));
	}
};

// Greyscale
typedef TextureGreyscale<uint8_t> TexRu8;
typedef TextureGreyscale<uint16_t> TexRu16;
typedef TextureGreyscale<uint32_t> TexRu32;
typedef TextureGreyscale<int8_t> TexRi8;
typedef TextureGreyscale<int16_t> TexRi16;
typedef TextureGreyscale<int32_t> TexRi32;
typedef TextureGreyscale<half_float::half> TexRf16;
typedef TextureGreyscale<float> TexRf32;
typedef TextureGreyscale<double> TexRf64;
// RGB
typedef TextureRGB<uint8_t> TexRGBu8;
typedef TextureRGB<uint16_t> TexRGBu16;
typedef TextureRGB<uint32_t> TexRGBu32;
typedef TextureRGB<int8_t> TexRGBi8;
typedef TextureRGB<int16_t> TexRGBi16;
typedef TextureRGB<int32_t> TexRGBi32;
typedef TextureRGB<half_float::half> TexRGBf16;
typedef TextureRGB<float> TexRGBf32;
typedef TextureRGB<double> TexRGBf64;
// BGR
typedef TextureBGR<uint8_t> TexBGRu8;
typedef TextureBGR<uint16_t> TexBGRu16;
typedef TextureBGR<uint32_t> TexBGRu32;
typedef TextureBGR<int8_t> TexBGRi8;
typedef TextureBGR<int16_t> TexBGRi16;
typedef TextureBGR<int32_t> TexBGRi32;
typedef TextureBGR<half_float::half> TexBGRf16;
typedef TextureBGR<float> TexBGRf32;
typedef TextureBGR<double> TexBGRf64;
// RGBA
typedef TextureRGBA<uint8_t> TexRGBAu8;
typedef TextureRGBA<uint16_t> TexRGBAu16;
typedef TextureRGBA<uint32_t> TexRGBAu32;
typedef TextureRGBA<int8_t> TexRGBAi8;
typedef TextureRGBA<int16_t> TexRGBAi16;
typedef TextureRGBA<int32_t> TexRGBAi32;
typedef TextureRGBA<half_float::half> TexRGBAf16;
typedef TextureRGBA<float> TexRGBAf32;
typedef TextureRGBA<double> TexRGBAf64;
// BGRA
typedef TextureBGRA<uint8_t> TexBGRAu8;
typedef TextureBGRA<uint16_t> TexBGRAu16;
typedef TextureBGRA<uint32_t> TexBGRAu32;
typedef TextureBGRA<int8_t> TexBGRAi8;
typedef TextureBGRA<int16_t> TexBGRAi16;
typedef TextureBGRA<int32_t> TexBGRAi32;
typedef TextureBGRA<half_float::half> TexBGRAf16;
typedef TextureBGRA<float> TexBGRAf32;
typedef TextureBGRA<double> TexBGRAf64;
// Indexed
typedef TextureIndexed<uint8_t> TexIndexedU8;
typedef TextureIndexed<uint16_t> TexIndexedU16;
typedef TextureIndexed<uint32_t> TexIndexedU32;
typedef TextureIndexed<int8_t> TexIndexedI8;
typedef TextureIndexed<int16_t> TexIndexedI16;
typedef TextureIndexed<int32_t> TexIndexedI32;
typedef TextureIndexed<half_float::half> TexIndexedF16;
typedef TextureIndexed<float> TexIndexedF32;
typedef TextureIndexed<double> TexIndexedF64;

#endif // STANDARDTEXTURE_HPP
