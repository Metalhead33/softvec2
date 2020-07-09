#ifndef MAT_HPP
#define MAT_HPP
#include "vec.hpp"

template <typename T, size_t X, size_t Y, typename VecForm = vec<T,Y>> struct mat
{
	typedef T individual_type;
	typedef VecForm element_type;
	typedef VecForm* iterator;
	typedef const VecForm* const_iterator;
	static const size_t length = X;
	static constexpr const T lengthCast = T(X);
	static const size_t elementSize = sizeof(VecForm);
	static const size_t sizeInBytes = length * elementSize;
	VecForm elements[length];

	// Iterators
	iterator begin() { return &elements[0]; }
	const_iterator begin() const { return &elements[0]; }
	iterator end() { return &elements[length]; }
	const_iterator end() const { return &elements[length]; }
	// Accessors
	element_type& operator[](size_t i) { return elements[i]; }
	const element_type& operator[](size_t i) const { return elements[i]; }
	element_type& get(size_t i) { return elements[i]; }
	const element_type& get(size_t i) const { return elements[i]; }
	// Assignment operators
	void operator+=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] += b.elements[i];
	}
	void operator+=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] += b;
	}
	void operator+=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] += b;
	}
	void operator-=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] -= b.elements[i];
	}
	void operator-=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] -= b;
	}
	void operator-=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] -= b;
	}
	void operator*=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] *= b.elements[i];
	}
	void operator*=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] *= b;
	}
	void operator*=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] *= b;
	}
	void operator/=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] /= b.elements[i];
	}
	void operator/=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] /= b;
	}
	void operator/=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] /= b;
	}
	void operator%=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] %= b.elements[i];
	}
	void operator%=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] %= b;
	}
	void operator%=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] %= b;
	}
	void operator&=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] &= b.elements[i];
	}
	void operator&=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] &= b;
	}
	void operator&=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] &= b;
	}
	void operator|=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] |= b.elements[i];
	}
	void operator|=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] |= b;
	}
	void operator|=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] |= b;
	}
	void operator^=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] ^= b.elements[i];
	}
	void operator^=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] ^= b;
	}
	void operator^=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] ^= b;
	}
	void operator<<=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] <<= b.elements[i];
	}
	void operator<<=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] <<= b;
	}
	void operator<<=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] <<= b;
	}
	void operator>>=(const mat& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] >>= b.elements[i];
	}
	void operator>>=(const element_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] >>= b;
	}
	void operator>>=(const individual_type& b)
	{
		for(size_t i=0; i < length; ++i)
			elements[i] >>= b;
	}

	// Copier operators
	mat operator+(const mat& b) const
	{
		mat tmp=*this;
		tmp+=b;
		return tmp;
	}
	mat operator+(const element_type& b) const
	{
		mat tmp=*this;
		tmp+=b;
		return tmp;
	}
	mat operator+(const individual_type& b) const
	{
		mat tmp=*this;
		tmp+=b;
		return tmp;
	}
	mat operator-(const mat& b) const
	{
		mat tmp=*this;
		tmp-=b;
		return tmp;
	}
	mat operator-(const element_type& b) const
	{
		mat tmp=*this;
		tmp-=b;
		return tmp;
	}
	mat operator-(const individual_type& b) const
	{
		mat tmp=*this;
		tmp-=b;
		return tmp;
	}
	mat operator*(const mat& b) const
	{
		mat tmp=*this;
		tmp*=b;
		return tmp;
	}
	mat operator*(const element_type& b) const
	{
		mat tmp=*this;
		tmp*=b;
		return tmp;
	}
	mat operator*(const individual_type& b) const
	{
		mat tmp=*this;
		tmp*=b;
		return tmp;
	}
	mat operator/(const mat& b) const
	{
		mat tmp=*this;
		tmp/=b;
		return tmp;
	}
	mat operator/(const element_type& b) const
	{
		mat tmp=*this;
		tmp/=b;
		return tmp;
	}
	mat operator/(const individual_type& b) const
	{
		mat tmp=*this;
		tmp/=b;
		return tmp;
	}
	mat operator%(const mat& b) const
	{
		mat tmp=*this;
		tmp%=b;
		return tmp;
	}
	mat operator%(const element_type& b) const
	{
		mat tmp=*this;
		tmp%=b;
		return tmp;
	}
	mat operator%(const individual_type& b) const
	{
		mat tmp=*this;
		tmp%=b;
		return tmp;
	}
	mat operator&(const mat& b) const
	{
		mat tmp=*this;
		tmp&=b;
		return tmp;
	}
	mat operator&(const element_type& b) const
	{
		mat tmp=*this;
		tmp&=b;
		return tmp;
	}
	mat operator&(const individual_type& b) const
	{
		mat tmp=*this;
		tmp&=b;
		return tmp;
	}
	mat operator|(const mat& b) const
	{
		mat tmp=*this;
		tmp|=b;
		return tmp;
	}
	mat operator|(const element_type& b) const
	{
		mat tmp=*this;
		tmp|=b;
		return tmp;
	}
	mat operator|(const individual_type& b) const
	{
		mat tmp=*this;
		tmp|=b;
		return tmp;
	}
	mat operator^(const mat& b) const
	{
		mat tmp=*this;
		tmp^=b;
		return tmp;
	}
	mat operator^(const element_type& b) const
	{
		mat tmp=*this;
		tmp^=b;
		return tmp;
	}
	mat operator^(const individual_type& b) const
	{
		mat tmp=*this;
		tmp^=b;
		return tmp;
	}
	mat operator<<(const mat& b) const
	{
		mat tmp=*this;
		tmp<<=b;
		return tmp;
	}
	mat operator<<(const element_type& b) const
	{
		mat tmp=*this;
		tmp<<=b;
		return tmp;
	}
	mat operator<<(const individual_type& b) const
	{
		mat tmp=*this;
		tmp<<=b;
		return tmp;
	}
	mat operator>>(const mat& b) const
	{
		mat tmp=*this;
		tmp>>=b;
		return tmp;
	}
	mat operator>>(const element_type& b) const
	{
		mat tmp=*this;
		tmp>>=b;
		return tmp;
	}
	mat operator>>(const individual_type& b) const
	{
		mat tmp=*this;
		tmp>>=b;
		return tmp;
	}
	// Sum
	individual_type sum() const
	{
		individual_type tmp = 0;
		for(size_t i = 0; i < length; ++i) tmp += elements[i].sum();
		return tmp;
	}
	element_type sumNorm() const
	{
		element_type tmp = 0;
		for(size_t i = 0; i < length; ++i) tmp += elements[i].sumNorm();
		return tmp/lengthCast;
	}
	individual_type sumRow(size_t row) const
	{
		return elements[row].sum();
	}
	individual_type sumColumn(size_t column) const
	{
		individual_type tmp = 0;
		for(size_t i = 0; i < length; ++i) tmp += elements[i][column];
		return tmp;
	}
	individual_type vectorialSum(const mat& b)
	{
		const mat tmp = *this * b;
		return tmp.sum();
	}
	individual_type vectorialSumNorm(const mat& b)
	{
		const mat tmp = *this * b;
		return tmp.sumRow();
	}
	mat normalize() const
	{
		mat tmp=*this;
		T largest = std::numeric_limits<T>::min();
		for(const auto& y : *this)
		{
			for(const auto& x : *this) largest = std::max(largest,x);
		}
		for(auto& y : *this)
		{
			y /= largest;
		}
		return tmp;
	}
	element_type vectorialMultiplication(const element_type& b)
	{
		mat matTmp=*this;
		matTmp *= b;
		element_type vecTmp;
		for(size_t i = 0; i < element_type::length; ++i)
		{
			vecTmp[i] = matTmp.sumRow(i);
		}
		return vecTmp;
	}
};

#endif // MAT_HPP
