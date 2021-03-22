#include "PixelRgb565.hpp"

static constexpr const float COEF5 = 0.003921568627451f;
float rb5[4][4] = {
	{16.0f * COEF5, 4.0f * COEF5, 13.0f * COEF5, 1.0f * COEF5},
	{8.0f * COEF5, 12.0f * COEF5, 5.0f * COEF5, 9.0f * COEF5},
	{14.0f * COEF5, 2.0f * COEF5, 15.0f * COEF5, 3.0f * COEF5},
	{6.0f * COEF5, 10.0f * COEF5, 7.0f * COEF5, 11.0f * COEF5}
};
static constexpr const float COEF6 = 0.0019569471624266f;
float g6[4][4] = {
	{16.0f * COEF6, 4.0f * COEF6, 13.0f * COEF6, 1.0f * COEF6},
	{8.0f * COEF6, 12.0f * COEF6, 5.0f * COEF6, 9.0f * COEF6},
	{14.0f * COEF6, 2.0f * COEF6, 15.0f * COEF6, 3.0f * COEF6},
	{6.0f * COEF6, 10.0f * COEF6, 7.0f * COEF6, 11.0f * COEF6}
};

static float dither5(float val, const glm::ivec2 &coords, float ditherAmount = 0.5f) {
	return val - (rb5[coords.y%4][coords.x%4] * ditherAmount);
}
static float dither6(float val, const glm::ivec2 &coords, float ditherAmount = 0.5f) {
	return val - (g6[coords.y%4][coords.x%4] * ditherAmount);
}

void PixelRgb565::fromVec4(const glm::vec4 &col)
{
	const uint16_t r = uint16_t(col.r * 31.0f);
	const uint16_t g = uint16_t(col.g * 63.0f);
	const uint16_t b = uint16_t(col.b * 31.0f);
	data = ((r << 11) | (g << 5) | b);
}

void PixelRgb565::fromVec4Dithered(const glm::vec4 &col, const glm::ivec2 &coords, float ditherAmount)
{
	fromVec4(glm::vec4( dither5(col.r,coords,ditherAmount),
						dither6(col.g,coords,ditherAmount),
						dither5(col.b,coords,ditherAmount), col.a ));
}

static constexpr const float i5r = 1.0f / 31.0f;
static constexpr const float i6r = 1.0f / 63.0f;

void PixelRgb565::toVec4(glm::vec4 &col) const
{
	const uint16_t r = (data & 0xF800) >> 11;
	const uint16_t g = (data & 0x07E0) >> 5;
	const uint16_t b = (data & 0x001F);
	col.r = float(r) * i5r;
	col.g = float(g) * i6r;
	col.b = float(b) * i5r;
}
void PixelRgba5551::fromVec4(const glm::vec4 &col)
{
	const uint16_t r = uint16_t(col.r * 31.0f);
	const uint16_t g = uint16_t(col.g * 31.0f);
	const uint16_t b = uint16_t(col.b * 31.0f);
	const uint16_t a = uint16_t(col.a >= 0.5f);
	data = ( (r << 11) | (g << 6) | (b << 1) | a);
}
void PixelRgba5551::fromVec4Dithered(const glm::vec4 &col, const glm::ivec2 &coords, float ditherAmount)
{
	fromVec4(glm::vec4( dither5(col.r,coords,ditherAmount),
						dither5(col.g,coords,ditherAmount),
						dither5(col.b,coords,ditherAmount), col.a ));
}
void PixelRgba5551::toVec4(glm::vec4 &col) const
{
	const uint16_t r = (data & 0xF800) >> 11;
	const uint16_t g = (data & 0x07C0) >> 6;
	const uint16_t b = (data & 0x003E) >> 1;
	const uint16_t a = (data & 0x0001);
	col.r = float(r) * i5r;
	col.g = float(g) * i6r;
	col.b = float(b) * i5r;
	col.a = float(a);
}
