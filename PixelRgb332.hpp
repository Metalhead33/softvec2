#ifndef PIXELRGB332_HPP
#define PIXELRGB332_HPP
#include <glm/glm.hpp>
#include <cstdint>

struct PixelRgb332 {
	uint8_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
#endif // PIXELRGB332_HPP
