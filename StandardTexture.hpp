#ifndef STANDARDTEXTURE_HPP
#define STANDARDTEXTURE_HPP
#include <glm/glm.hpp>
#include "MhNormDenorm.hpp"
#include "Texture.hpp"
#include <vector>
#include <cstring>

template <typename Precision> class TextureGreyscale : public Texture {
private:
	std::vector<Precision> pixels;
	unsigned w,h;
public:
	TextureGreyscale() : w(0), h(0) {

	}
	TextureGreyscale(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(Precision));
	}
	TextureGreyscale(const TextureGreyscale& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureGreyscale(TextureGreyscale&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureGreyscale& operator=(const TextureGreyscale& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureGreyscale& operator=(TextureGreyscale&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(Precision));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(Precision); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(Precision); }
	unsigned getStride() const { return w*sizeof(Precision); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		Precision& pixel = pixels[(w*pos.y)+pos.x];
		pixel = fdenormalize<Precision>(col.r);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const float pixel = fnormalize(pixels[(w*pos.y)+pos.x]);
		col.r = pixel;
		col.g = pixel;
		col.b = pixel;
		col.a = 1.0f;
	}
};

template <typename Precision> class TextureRGB : public Texture {
public:
	struct PixelRGB {
		Precision r,g,b;
	};
private:
	std::vector<PixelRGB> pixels;
	unsigned w,h;
public:
	TextureRGB() : w(0), h(0) {

	}
	TextureRGB(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelRGB));
	}
	TextureRGB(const TextureRGB& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureRGB(TextureRGB&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureRGB& operator=(const TextureRGB& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureRGB& operator=(TextureRGB&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelRGB));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelRGB); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelRGB); }
	unsigned getStride() const { return w*sizeof(PixelRGB); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelRGB& pixel = pixels[(w*pos.y)+pos.x];
		pixel.r = fdenormalize<Precision>(col.r);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.b = fdenormalize<Precision>(col.b);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelRGB& pixel = pixels[(w*pos.y)+pos.x];
		col.r = fnormalize(pixel.r);
		col.g = fnormalize(pixel.g);
		col.b = fnormalize(pixel.b);
		col.a = 1.0f;
	}
};
template <typename Precision> class TextureRGBA : public Texture {
public:
	struct PixelRGBA {
		Precision r,g,b,a;
	};
private:
	std::vector<PixelRGBA> pixels;
	unsigned w,h;
public:
	TextureRGBA() : w(0), h(0) {

	}
	TextureRGBA(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelRGBA));
	}
	TextureRGBA(const TextureRGBA& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureRGBA(TextureRGBA&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureRGBA& operator=(const TextureRGBA& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureRGBA& operator=(TextureRGBA&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelRGBA));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelRGBA); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelRGBA); }
	unsigned getStride() const { return w*sizeof(PixelRGBA); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelRGBA& pixel = pixels[(w*pos.y)+pos.x];
		pixel.r = fdenormalize<Precision>(col.r);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.b = fdenormalize<Precision>(col.b);
		pixel.a = fdenormalize<Precision>(col.a);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelRGBA& pixel = pixels[(w*pos.y)+pos.x];
		col.r = fnormalize(pixel.r);
		col.g = fnormalize(pixel.g);
		col.b = fnormalize(pixel.b);
		col.a = fnormalize(pixel.a);
	}
};
template <typename Precision> class TextureBGR : public Texture {
public:
	struct PixelBGR {
		Precision b,g,r;
	};
private:
	std::vector<PixelBGR> pixels;
	unsigned w,h;
public:
	TextureBGR() : w(0), h(0) {

	}
	TextureBGR(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelBGR));
	}
	TextureBGR(const TextureBGR& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureBGR(TextureBGR&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureBGR& operator=(const TextureBGR& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureBGR& operator=(TextureBGR&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelBGR));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelBGR); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelBGR); }
	unsigned getStride() const { return w*sizeof(PixelBGR); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelBGR& pixel = pixels[(w*pos.y)+pos.x];
		pixel.b = fdenormalize<Precision>(col.b);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.r = fdenormalize<Precision>(col.r);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelBGR& pixel = pixels[(w*pos.y)+pos.x];
		col.b = fnormalize(pixel.b);
		col.g = fnormalize(pixel.g);
		col.r = fnormalize(pixel.r);
		col.a = 1.0f;
	}
};
template <typename Precision> class TextureBGRA : public Texture {
public:
	struct PixelBGRA {
		Precision b,g,r,a;
	};
private:
	std::vector<PixelBGRA> pixels;
	unsigned w,h;
public:
	TextureBGRA() : w(0), h(0) {

	}
	TextureBGRA(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelBGRA));
	}
	TextureBGRA(const TextureBGRA& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureBGRA(TextureBGRA&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureBGRA& operator=(const TextureBGRA& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureBGRA& operator=(TextureBGRA&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelBGRA));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelBGRA); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelBGRA); }
	unsigned getStride() const { return w*sizeof(PixelBGRA); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelBGRA& pixel = pixels[(w*pos.y)+pos.x];
		pixel.r = fdenormalize<Precision>(col.r);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.b = fdenormalize<Precision>(col.b);
		pixel.a = fdenormalize<Precision>(col.a);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelBGRA& pixel = pixels[(w*pos.y)+pos.x];
		col.b = fnormalize(pixel.b);
		col.g = fnormalize(pixel.g);
		col.r = fnormalize(pixel.r);
		col.a = fnormalize(pixel.a);
	}
};
template <typename Precision> class TextureARGB : public Texture {
public:
	struct PixelARGB {
		Precision a,r,g,b;
	};
private:
	std::vector<PixelARGB> pixels;
	unsigned w,h;
public:
	TextureARGB() : w(0), h(0) {

	}
	TextureARGB(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelARGB));
	}
	TextureARGB(const TextureARGB& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureARGB(TextureARGB&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureARGB& operator=(const TextureARGB& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureARGB& operator=(TextureARGB&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelARGB));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelARGB); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelARGB); }
	unsigned getStride() const { return w*sizeof(PixelARGB); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelARGB& pixel = pixels[(w*pos.y)+pos.x];
		pixel.a = fdenormalize<Precision>(col.a);
		pixel.r = fdenormalize<Precision>(col.r);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.b = fdenormalize<Precision>(col.b);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelARGB& pixel = pixels[(w*pos.y)+pos.x];
		col.a = fnormalize(pixel.a);
		col.r = fnormalize(pixel.r);
		col.g = fnormalize(pixel.g);
		col.b = fnormalize(pixel.b);
	}
};
template <typename Precision> class TextureABGR : public Texture {
public:
	struct PixelABGR {
		Precision a,b,g,r;
	};
private:
	std::vector<PixelABGR> pixels;
	unsigned w,h;
public:
	TextureABGR() : w(0), h(0) {

	}
	TextureABGR(unsigned w, unsigned h) : pixels(w*h), w(w), h(h)
	{
		memset(pixels.data(),0,pixels.size() * sizeof(PixelABGR));
	}
	TextureABGR(const TextureABGR& cpy) : pixels(cpy.pixels), w(cpy.w), h(cpy.h)
	{

	}
	TextureABGR(TextureABGR&& mov) : pixels(std::move(mov.pixels)), w(mov.w), h(mov.h)
	{
		mov.w = 0;
		mov.h = 0;
	}
	TextureABGR& operator=(const TextureABGR& cpy)
	{
		this->pixels = cpy.pixels;
		this->w = cpy.w;
		this->h = cpy.h;
		return *this;
	}
	TextureABGR& operator=(TextureABGR&& mov)
	{
		this->pixels = std::move(mov.pixels);
		this->w = mov.w;
		this->h = mov.h;
		mov.w = 0;
		mov.h = 0;
		return *this;
	}
	void* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelABGR));
	}
	const void* getPixels() const { return pixels.data(); }
	unsigned getW() const { return w; }
	unsigned getH() const { return h; }
	unsigned getPictureSize() const { return pixels.size(); }
	unsigned getPixelSize() const { return sizeof(PixelABGR); }
	unsigned getSizeInBytes() const { return pixels.size() * sizeof(PixelABGR); }
	unsigned getStride() const { return w*sizeof(PixelABGR); }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelABGR& pixel = pixels[(w*pos.y)+pos.x];
		pixel.a = fdenormalize<Precision>(col.a);
		pixel.r = fdenormalize<Precision>(col.r);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.b = fdenormalize<Precision>(col.b);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelABGR& pixel = pixels[(w*pos.y)+pos.x];
		col.a = fnormalize(pixel.a);
		col.r = fnormalize(pixel.r);
		col.g = fnormalize(pixel.g);
		col.b = fnormalize(pixel.b);
	}
};


#endif // STANDARDTEXTURE_HPP
