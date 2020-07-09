#ifndef VEC_HPP
#define VEC_HPP
#include <cstddef>
#include <algorithm>

template <typename T, size_t x> struct vec
{
	typedef T element_type;
	typedef T* iterator;
	typedef const T* const_iterator;
	static const size_t length = x;
	static constexpr const T lengthCast = T(x);
	static const size_t elementSize = sizeof(T);
	static const size_t sizeInBytes = length * elementSize;
	T elements[length];

	// Iterators
	iterator begin() { return &elements[0]; }
	const_iterator begin() const { return &elements[0]; }
	iterator end() { return &elements[length]; }
	const_iterator end() const { return &elements[length]; }

	element_type* data() { return elements; }
	const element_type* data() const { return elements; }
	// Accessors
	element_type& operator[](size_t i) { return elements[i]; }
	const element_type& operator[](size_t i) const { return elements[i]; }
	element_type& get(size_t i) { return elements[i]; }
	const element_type& get(size_t i) const { return elements[i]; }
	// Assignment operations
	void operator+=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] += b.elements[i];
	}
	void operator+=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] += b;
	}
	void operator-=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] -= b.elements[i];
	}
	void operator-=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] -= b;
	}
	void operator*=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] *= b.elements[i];
	}
	void operator*=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] *= b;
	}
	void operator/=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] /= b.elements[i];
	}
	void operator/=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] *= b;
	}
	void operator%=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] /= b.elements[i];
	}
	void operator%=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] %= b;
	}
	void operator&=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] &= b.elements[i];
	}
	void operator&=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] &= b;
	}
	void operator|=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] |= b.elements[i];
	}
	void operator|=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] |= b;
	}
	void operator^=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] ^= b.elements[i];
	}
	void operator^=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] ^= b;
	}
	void operator<<=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] <<= b.elements[i];
	}
	void operator<<=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] <<= b;
	}
	void operator>>=(const vec& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] >>= b.elements[i];
	}
	void operator>>=(const element_type& b)
	{
		for(size_t i = 0; i < length; ++i)
			elements[i] >>= b;
	}
	// Copier operations
	vec operator+(const vec& b) const
	{
		vec tmp=*this;
		tmp += b;
		return tmp;
	}
	vec operator+(const element_type& b) const
	{
		vec tmp=*this;
		tmp += b;
		return tmp;
	}
	vec operator-(const vec& b) const
	{
		vec tmp=*this;
		tmp -= b;
		return tmp;
	}
	vec operator-(const element_type& b) const
	{
		vec tmp=*this;
		tmp -= b;
		return tmp;
	}
	vec operator*(const vec& b) const
	{
		vec tmp=*this;
		tmp *= b;
		return tmp;
	}
	vec operator*(const element_type& b) const
	{
		vec tmp=*this;
		tmp *= b;
		return tmp;
	}
	vec operator/(const vec& b) const
	{
		vec tmp=*this;
		tmp /= b;
		return tmp;
	}
	vec operator/(const element_type& b) const
	{
		vec tmp=*this;
		tmp /= b;
		return tmp;
	}
	vec operator%(const vec& b) const
	{
		vec tmp=*this;
		tmp %= b;
		return tmp;
	}
	vec operator%(const element_type& b) const
	{
		vec tmp=*this;
		tmp %= b;
		return tmp;
	}
	vec operator&(const vec& b) const
	{
		vec tmp=*this;
		tmp &= b;
		return tmp;
	}
	vec operator&(const element_type& b) const
	{
		vec tmp=*this;
		tmp &= b;
		return tmp;
	}
	vec operator|(const vec& b) const
	{
		vec tmp=*this;
		tmp |= b;
		return tmp;
	}
	vec operator|(const element_type& b) const
	{
		vec tmp=*this;
		tmp |= b;
		return tmp;
	}
	vec operator^(const vec& b) const
	{
		vec tmp=*this;
		tmp ^= b;
		return tmp;
	}
	vec operator^(const element_type& b) const
	{
		vec tmp=*this;
		tmp ^= b;
		return tmp;
	}
	vec operator<<(const vec& b) const
	{
		vec tmp=*this;
		tmp <<= b;
		return tmp;
	}
	vec operator<<(const element_type& b) const
	{
		vec tmp=*this;
		tmp <<= b;
		return tmp;
	}
	vec operator>>(const vec& b) const
	{
		vec tmp=*this;
		tmp >>= b;
		return tmp;
	}
	vec operator>>(const element_type& b) const
	{
		vec tmp=*this;
		tmp >>= b;
		return tmp;
	}
	// Sum
	element_type sum() const
	{
		element_type tmp = 0;
		for(size_t i = 0; i < length; ++i) tmp += elements[i];
		return tmp;
	}
	element_type sumNorm() const
	{
		element_type tmp = 0;
		for(size_t i = 0; i < length; ++i) tmp += elements[i];
		return tmp/lengthCast;
	}
	element_type vectorialSum(const vec& b) const
	{
		const vec tmp = *this * b;
		return tmp.sum();
	}
	element_type vectorialSumNorm(const vec& b) const
	{
		const vec tmp = *this * b;
		return tmp.sumRow();
	}

	vec& max(const vec& b) const
	{
		for(size_t i = 0; i < length;++i)
			elements[i] = std::max(elements[i],b.elements[i]);
		return *this;
	}
	vec& max(const element_type& b) const
	{
		for(size_t i = 0; i < length;++i)
			elements[i] = std::max(elements[i],b);
		return *this;
	}
	vec& min(const vec& b) const
	{
		for(size_t i = 0; i < length;++i)
			elements[i] = std::min(elements[i],b.elements[i]);
		return *this;
	}
	vec& min(const element_type& b) const
	{
		for(size_t i = 0; i < length;++i)
			elements[i] = std::min(elements[i],b);
		return *this;
	}
	vec& clamp(const vec& minimal, const vec& maximal)
	{
		return max(minimal).min(maximal);
	}
	vec& clamp(const element_type& minimal, const element_type& maximal)
	{
		return max(minimal).min(maximal);
	}

	vec normalize() const
	{
		vec tmp=*this;
		T largest = std::numeric_limits<T>::min();
		for(const auto& it : *this)
			largest = std::max(largest,it);
		tmp /= largest;
		return tmp;
	}
};

template <size_t dimensions> struct vec_cross_product
{
	typedef vec<float,dimensions> vectype;
	static vectype cross(const vectype& a, const vectype& b)
	{
		static_assert (dimensions == 2 || dimensions == 3,"Only vectors with 2 or 3 dimensions can have cross products!");
		void(a,b);
	}
};

template <> struct vec_cross_product<3>
{
	typedef vec<float,3> vectype;
	static vectype cross(const vectype& a, const vectype& b)
	{
		return {{a[1] * b[2] - a[2] * b[1],
		a[0] * b[2] - a[2] * b[0],
		a[0] * b[1] - a[1] * b[0]}};
	}
};
template <> struct vec_cross_product<2>
{
	typedef vec<float,2> vectype;
	static vec<float,3> cross(const vectype& a, const vectype& b)
	{
		const vec<float,3> a0 = {{ a[0], a[1], 0.0f }};
		const vec<float,3> b0 = {{ b[0], b[1], 0.0f }};
		return vec_cross_product<3>::cross(a0,b0);
	}
};
template <size_t dimensions> vec<float,3> cross(const vec<float,dimensions>& a, const vec<float,dimensions>& b)
{
	return vec_cross_product<dimensions>::cross(a,b);
}

#endif // VEC_HPP
