#ifndef PIXELRGB565_HPP
#define PIXELRGB565_HPP
#include <glm/glm.hpp>
#include <cstdint>

struct PixelRgba5551 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
struct PixelRgb565 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};

#endif // PIXELRGB565_HPP
