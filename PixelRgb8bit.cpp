#include "PixelRgb8bit.hpp"

static constexpr const float COEF3 = 0.0090909090909091f;
float rg3[4][4] = {
	{-16.0f * COEF3, 4.0f * COEF3, 13.0f * COEF3, -1.0f * COEF3},
	{8.0f * COEF3, -12.0f * COEF3, -5.0f * COEF3, 9.0f * COEF3},
	{-14.0f * COEF3, 2.0f * COEF3, 15.0f * COEF3, -3.0f * COEF3},
	{6.0f * COEF3, -10.0f * COEF3, -7.0f * COEF3, 11.0f * COEF3}
};
static constexpr const float COEF2 = 0.02f;
float b2[4][4] = {
	{16.0f * COEF2, -4.0f * COEF2, -13.0f * COEF2, 1.0f * COEF2},
	{-8.0f * COEF2, 12.0f * COEF2, 5.0f * COEF2, -9.0f * COEF2},
	{14.0f * COEF2, -2.0f * COEF2, -15.0f * COEF2, 3.0f * COEF2},
	{-6.0f * COEF2, 10.0f * COEF2, 7.0f * COEF2, -11.0f * COEF2}
};

static float dither3(float val, const glm::ivec2 &coords, float ditherAmount = 0.5f) {
	return val - (rg3[coords.y%4][coords.x%4] * ditherAmount);
}
static float dither2(float val, const glm::ivec2 &coords, float ditherAmount = 0.5f) {
	return val - (b2[coords.y%4][coords.x%4] * ditherAmount);
}

void PixelRgb332::fromVec4(const glm::vec4 &col)
{
	const uint8_t r = uint8_t(col.r * 7.0f);
	const uint8_t g = uint8_t(col.g * 7.0f);
	const uint8_t b = uint8_t(col.b * 3.0f);
	data = ((r << 5) | (g << 2) | b);
}

void PixelRgb332::fromVec4Dithered(const glm::vec4 &col, const glm::ivec2 &coords, float ditherAmount)
{
	fromVec4(glm::vec4( dither3(col.r,coords,ditherAmount),
						dither3(col.g,coords,ditherAmount),
						dither2(col.b,coords,ditherAmount), col.a ));
}

static constexpr const float rg7 = 1.0f / 7.0f;
static constexpr const float b3 = 1.0f / 3.0f;
void PixelRgb332::toVec4(glm::vec4 &col) const
{
	const uint8_t r = (data & 0xE0) >> 5;
	const uint8_t g = (data & 0x1C) >> 2;
	const uint8_t b = (data & 0x03);
	col.r = float(r) * rg7;
	col.g = float(g) * rg7;
	col.b = float(b) * b3;
}
