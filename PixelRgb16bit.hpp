#ifndef PIXELRGB16BIT_HPP
#define PIXELRGB16BIT_HPP
#include <glm/glm.hpp>
#include <cstdint>

struct PixelRgb444 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
struct PixelArgb4444 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
struct PixelRgba4444 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
struct PixelArgb1555 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
struct PixelRgba5551 {
	uint16_t data;
	void fromVec4(const glm::vec4& col);
	void fromVec4Dithered(const glm::vec4& col, const glm::ivec2& coords, float ditherAmount = 0.5f);
	void toVec4(glm::vec4& col) const;
};
struct PixelRgb555 {
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

#endif // PIXELRGB16BIT_HPP
