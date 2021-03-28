#ifndef DITHER_HPP
#define DITHER_HPP
#include <glm/glm.hpp>
#include <limits>

template <typename NumberType> struct OrderedDither {
	static constexpr const float MAX = float(std::numeric_limits<NumberType>::max()) * 8.0f;
	static constexpr const float MAX_RECIPROCAL = 1.0f/float(MAX);

	static constexpr const float LookupTable[4][4] = {
		{0.0f * MAX_RECIPROCAL,  8.0f * MAX_RECIPROCAL,  -2.0f * MAX_RECIPROCAL, 10.0f * MAX_RECIPROCAL},
	   {12.0f * MAX_RECIPROCAL,  -4.0f * MAX_RECIPROCAL, 14.0f * MAX_RECIPROCAL,  -6.0f * MAX_RECIPROCAL},
		{-3.0f * MAX_RECIPROCAL, 11.0f * MAX_RECIPROCAL,  -1.0f * MAX_RECIPROCAL,  9.0f * MAX_RECIPROCAL},
	   {15.0f * MAX_RECIPROCAL,  -7.0f * MAX_RECIPROCAL, 13.0f * MAX_RECIPROCAL,  -5.0f * MAX_RECIPROCAL}
	};
	static constexpr float ditherUp(float value, const glm::ivec2& coords, float ditherAmount = 0.5f) {
		return value + LookupTable[coords.y%4][coords.x%4];
	}
	static constexpr float ditherDown(float value, const glm::ivec2& coords, float ditherAmount = 0.5f) {
		return value - LookupTable[coords.y%4][coords.x%4];
	}
};

#endif // DITHER_HPP
