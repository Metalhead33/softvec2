#ifndef PALETTE_HPP
#define PALETTE_HPP
#include "../NormDenorm.hpp"
#include <cstdint>
#include <vector>
#include "../vecdefs.hpp"

template <typename ColourDepth> struct Palette {
	struct PixelRGBA {
		ColourDepth r,b,g,a;
	};
	std::vector<PixelRGBA> colours;
	void storePixelTo(fvec4& dst, uint8_t index) const
	{
		const auto& tmpRef = colours.at(index);
		dst = SimdFvec4(normalize(tmpRef.r), normalize(tmpRef.g), normalize(tmpRef.b), normalize(tmpRef.a));
	}
};

#endif // PALETTE_HPP
