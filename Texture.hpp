#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <glm/glm.hpp>
#include "MhNormDenorm.hpp"
#include <vector>
#include <cstring>

template <typename Precision> class TextureRGB {
public:
	struct PixelRGB {
		Precision r,g,b;
	};
private:
	std::vector<PixelRGB> pixels;
	int w,h;
public:
	TextureRGB() : w(0), h(0) {

	}
	TextureRGB(int w, int h) : pixels(w*h), w(w), h(h)
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
	PixelRGB* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelRGB));
	}
	const PixelRGB* getPixels() const { return pixels.data(); }
	int getW() const { return w; }
	int getH() const { return h; }
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

template <typename Precision> class TextureARGB {
public:
	struct PixelARGB {
		Precision a,r,g,b;
	};
private:
	std::vector<PixelARGB> pixels;
	int w,h;
public:
	TextureARGB() : w(0), h(0) {

	}
	TextureARGB(int w, int h) : pixels(w*h), w(w), h(h)
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
	PixelARGB* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelARGB));
	}
	const PixelARGB* getPixels() const { return pixels.data(); }
	int getW() const { return w; }
	int getH() const { return h; }
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
template <typename Precision> class TextureRGBA {
public:
	struct PixelRGBA {
		Precision a,r,g,b;
	};
private:
	std::vector<PixelRGBA> pixels;
	int w,h;
public:
	TextureRGBA() : w(0), h(0) {

	}
	TextureRGBA(int w, int h) : pixels(w*h), w(w), h(h)
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
	PixelRGBA* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelRGBA));
	}
	const PixelRGBA* getPixels() const { return pixels.data(); }
	int getW() const { return w; }
	int getH() const { return h; }
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
template <typename Precision> class TextureBGRA {
public:
	struct PixelBGRA {
		Precision b,g,r,a;
	};
private:
	std::vector<PixelBGRA> pixels;
	int w,h;
public:
	TextureBGRA() : w(0), h(0) {

	}
	TextureBGRA(int w, int h) : pixels(w*h), w(w), h(h)
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
	PixelBGRA* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelBGRA));
	}
	const PixelBGRA* getPixels() const { return pixels.data(); }
	int getW() const { return w; }
	int getH() const { return h; }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelBGRA& pixel = pixels[(w*pos.y)+pos.x];
		pixel.b = fdenormalize<Precision>(col.b);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.r = fdenormalize<Precision>(col.r);
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
template <typename Precision> class TextureABGR {
public:
	struct PixelABGR {
		Precision a,b,g,r;
	};
private:
	std::vector<PixelABGR> pixels;
	int w,h;
public:
	TextureABGR() : w(0), h(0) {

	}
	TextureABGR(int w, int h) : pixels(w*h), w(w), h(h)
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
	PixelABGR* getPixels() { return pixels.data(); }
	void clear() {
		memset(pixels.data(),0,pixels.size() * sizeof(PixelABGR));
	}
	const PixelABGR* getPixels() const { return pixels.data(); }
	int getW() const { return w; }
	int getH() const { return h; }
	void setPixel(const glm::ivec2& pos, const glm::vec4& col) {
		PixelABGR& pixel = pixels[(w*pos.y)+pos.x];
		pixel.a = fdenormalize<Precision>(col.a);
		pixel.b = fdenormalize<Precision>(col.b);
		pixel.g = fdenormalize<Precision>(col.g);
		pixel.r = fdenormalize<Precision>(col.r);
	}
	void getPixel(const glm::ivec2& pos, glm::vec4& col) const {
		const PixelABGR& pixel = pixels[(w*pos.y)+pos.x];
		col.a = fnormalize(pixel.a);
		col.b = fnormalize(pixel.b);
		col.g = fnormalize(pixel.g);
		col.r = fnormalize(pixel.r);
	}
};


#endif // TEXTURE_HPP
