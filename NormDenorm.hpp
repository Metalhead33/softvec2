#ifndef NORMDENORM_HPP
#define NORMDENORM_HPP
#include <limits>
#include "half.hpp"

template <typename T> struct norm_denorm {
	static constexpr const float minimal_reciprocal = 1.0f / static_cast<float>(std::numeric_limits<T>::min());
	static constexpr const float maximal_reciprocal = 1.0f / static_cast<float>(std::numeric_limits<T>::max());
	inline static constexpr float normalize(const T& org)
	{
		return org < 0
			? -static_cast<float>(org) * minimal_reciprocal
			:  static_cast<float>(org) * maximal_reciprocal;
	}
	inline static constexpr T denormalize(const float& org)
	{
		return org < 0.0f
			? static_cast<T>(-static_cast<float>(org) * static_cast<float>(std::numeric_limits<T>::min()))
			: static_cast<T>(static_cast<float>(org) * static_cast<float>(std::numeric_limits<T>::max()));
	}
};

template <> struct norm_denorm<float> {
	inline static constexpr float normalize(const float& org)
	{
		return org;
	}
	inline static constexpr float denormalize(const float& org)
	{
		return org;
	}
};
template <> struct norm_denorm<double> {
	inline static constexpr float normalize(const double& org)
	{
		return static_cast<float>(org);
	}
	inline static constexpr double denormalize(const float& org)
	{
		return static_cast<double>(org);
	}
};
typedef half_float::half half;
template <> struct norm_denorm<half> {
	inline static float normalize(const half& org)
	{
		return static_cast<float>(org);
	}
	inline static half denormalize(const float& org)
	{
		return static_cast<half>(org);
	}
};

template <typename T> float normalize(const T& org)
{
	return norm_denorm<T>::normalize(org);
}
template <typename T> T denormalize(const float& org)
{
	return norm_denorm<T>::denormalize(org);
}
template <typename INPUT, typename OUTPUT> OUTPUT scale(const INPUT& in)
{
	return denormalize<OUTPUT>(normalize(in));
}


#endif // NORMDENORM_HPP
