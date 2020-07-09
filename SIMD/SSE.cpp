#include "SSE.hpp"
#include <cstdint>
#include <algorithm>
#include <smmintrin.h>
#define FAST_DIVISION

float storeVectorialSumAs( const __m128& valueA, const __m128& valueB)
{
	__m128 result;
	result = _mm_mul_ps(valueA,valueB);
	result = _mm_hadd_ps(result,result);
	result = _mm_hadd_ps(result,result);
	return *reinterpret_cast<float*>(&result);
}

SimdFvec4::SimdFvec4()
	: _data(_mm_setzero_ps())
{

}

SimdFvec4::SimdFvec4(const __m128 &a)
	: _data(a)
{

}

SimdFvec4::SimdFvec4(float a)
	: _data(_mm_set1_ps(a))
{

}

SimdFvec4::SimdFvec4(const float *arr)
	: _data(_mm_load_ps(arr))
{

}

SimdFvec4::SimdFvec4(float e0, float e1, float e2, float e3)
	: _data(_mm_set_ps(e3,e2,e1,e0))
{

}

SimdFvec4::SimdFvec4(const SimdFvec4 &cpy)
	: _data(cpy._data)
{

}

void SimdFvec4::operator=(const SimdFvec4 &cpy)
{
	_data = cpy._data;
}

void SimdFvec4::operator=(float a)
{
	_data = _mm_set1_ps(a);
}

void SimdFvec4::operator=(const float *arr)
{
	_data = _mm_load_ps(arr);
}

void SimdFvec4::store(float *arr) const
{
	_mm_store_ps(arr,_data);
}

SimdFvec4 SimdFvec4::reciprocal() const
{
	return SimdFvec4(_mm_rcp_ps(_data));
}

void SimdFvec4::set_to_reciprocal()
{
	_data = _mm_rcp_ps(_data);
}

float *SimdFvec4::data()
{
	return reinterpret_cast<float*>(&_data);
}

const float *SimdFvec4::data() const
{
	return reinterpret_cast<const float*>(&_data);
}

size_t SimdFvec4::size() const
{
	return 4;
}
SimdFvec4::iterator SimdFvec4::begin()
{
	return reinterpret_cast<float*>(&_data);
}
SimdFvec4::iterator SimdFvec4::end()
{
	return &reinterpret_cast<float*>(&_data)[4];
}
SimdFvec4::const_iterator SimdFvec4::begin() const
{
	return reinterpret_cast<const float*>(&_data);
}
SimdFvec4::const_iterator SimdFvec4::end() const
{
	return &reinterpret_cast<const float*>(&_data)[4];
}
float& SimdFvec4::at(size_t i)
{
	return reinterpret_cast<float*>(&_data)[i];
}
const float& SimdFvec4::at(size_t i) const
{
	return reinterpret_cast<const float*>(&_data)[i];
}
float& SimdFvec4::operator[](size_t i)
{
	return reinterpret_cast<float*>(&_data)[i];
}
const float& SimdFvec4::operator[](size_t i) const
{
	return reinterpret_cast<const float*>(&_data)[i];
}

void SimdFvec4::operator+=(const SimdFvec4& b)
{
	_data = _mm_add_ps(_data,b._data);
}
void SimdFvec4::operator-=(const SimdFvec4& b)
{
	_data = _mm_sub_ps(_data,b._data);
}
void SimdFvec4::operator*=(const SimdFvec4& b)
{
	_data = _mm_mul_ps(_data,b._data);
}
void SimdFvec4::operator/=(const SimdFvec4& b)
{
#ifdef FAST_DIVISION
	_data = _mm_mul_ps(_data,_mm_rcp_ps(b._data));
#else
	_data = _mm_div_ps(_data,b._data);
#endif
}

SimdFvec4 SimdFvec4::operator+(const SimdFvec4& b) const
{
	return SimdFvec4(_mm_add_ps(_data,b._data));
}
SimdFvec4 SimdFvec4::operator-(const SimdFvec4& b) const
{
	return SimdFvec4(_mm_sub_ps(_data,b._data));
}
SimdFvec4 SimdFvec4::operator*(const SimdFvec4& b) const
{
	return SimdFvec4(_mm_mul_ps(_data,b._data));
}
SimdFvec4 SimdFvec4::operator/(const SimdFvec4& b) const
{
#ifdef FAST_DIVISION
	return SimdFvec4(_mm_mul_ps(_data,_mm_rcp_ps(b._data)));
#else
	return SimdFvec4(_mm_div_ps(_data,b._data));
#endif
}
void SimdFvec4::operator<<=(const SimdFvec4& b) // Minimum
{
	_data = _mm_min_ps(_data,b._data);
}
void SimdFvec4::operator>>=(const SimdFvec4& b) // Maximum
{
	_data = _mm_max_ss(_data,b._data);
}
SimdFvec4 SimdFvec4::operator<<(const SimdFvec4& b) // Minimum
{
	return SimdFvec4(_mm_min_ps(_data,b._data));
}
SimdFvec4 SimdFvec4::operator>>(const SimdFvec4& b) // Maximum
{
	return SimdFvec4(_mm_max_ps(_data,b._data));
}
SimdFvec4 SimdFvec4::min(const SimdFvec4& a, const SimdFvec4& b)
{
	return SimdFvec4(_mm_min_ps(a._data,b._data));
}
SimdFvec4 SimdFvec4::max(const SimdFvec4& a, const SimdFvec4& b)
{
	return SimdFvec4(_mm_max_ps(a._data,b._data));
}
SimdFvec4 SimdFvec4::clamp(const SimdFvec4& a, const SimdFvec4& _min, const SimdFvec4& _max)
{
	return SimdFvec4(_mm_min_ps(_mm_max_ps(a._data,_min._data),_max._data));
}

float SimdFvec4::vectorialMul(const SimdFvec4& b) const
{
	return storeVectorialSumAs(_data,b._data);
}
float SimdFvec4::vectorialMul(float b) const
{
	return storeVectorialSumAs(_data,_mm_set1_ps(b));
}

void SimdFvec4::operator+=(float b)
{
	_data = _mm_add_ps(_data,_mm_set1_ps(b));
}
void SimdFvec4::operator-=(float b)
{
	_data = _mm_sub_ps(_data,_mm_set1_ps(b));
}
void SimdFvec4::operator*=(float b)
{
	_data = _mm_mul_ps(_data,_mm_set1_ps(b));
}
void SimdFvec4::operator/=(float b)
{
#ifdef FAST_DIVISION
	_data = _mm_mul_ps(_data,_mm_rcp_ps(_mm_set1_ps(b)));
#else
	_data = _mm_div_ps(_data,_mm_set1_ps(b));
#endif
}

SimdFvec4 SimdFvec4::operator+(float b) const
{
	return SimdFvec4(_mm_add_ps(_data,_mm_set1_ps(b)));
}
SimdFvec4 SimdFvec4::operator-(float b) const
{
	return SimdFvec4(_mm_sub_ps(_data,_mm_set1_ps(b)));
}
SimdFvec4 SimdFvec4::operator*(float b) const
{
	return SimdFvec4(_mm_mul_ps(_data,_mm_set1_ps(b)));
}
SimdFvec4 SimdFvec4::operator/(float b) const
{
#ifdef FAST_DIVISION
	return SimdFvec4(_mm_mul_ps(_data,_mm_rcp_ps(_mm_set1_ps(b))));
#else
	return SimdFvec4(_mm_div_ps(_data,_mm_set1_ps(b)));
#endif
}
void SimdFvec4::operator<<=(float b) // Minimum
{
	_data = _mm_min_ps(_data,_mm_set1_ps(b));
}
void SimdFvec4::operator>>=(float b) // Maximum
{
	_data = _mm_max_ps(_data,_mm_set1_ps(b));
}
SimdFvec4 SimdFvec4::operator<<(float b) // Minimum
{
	return SimdFvec4(_mm_min_ps(_data,_mm_set1_ps(b)));
}
SimdFvec4 SimdFvec4::operator>>(float b) // Maximum
{
	return SimdFvec4(_mm_max_ps(_data,_mm_set1_ps(b)));
}

bool SimdFvec4::operator==(const SimdFvec4& b) const
{
	__m128 tmp = _mm_cmpeq_ps(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator!=(const SimdFvec4& b) const
{
	__m128 tmp = _mm_cmpneq_ps(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator>(const SimdFvec4& b) const
{
	__m128 tmp = _mm_cmpgt_ps(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator>=(const SimdFvec4& b) const
{
	__m128 tmp = _mm_cmpge_ps(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator<(const SimdFvec4& b) const
{
	__m128 tmp = _mm_cmplt_ps(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator<=(const SimdFvec4& b) const
{
	__m128 tmp = _mm_cmple_ps(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator==(float b) const
{
	__m128 tmp = _mm_cmpeq_ps(_data,_mm_set1_ps(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator!=(float b) const
{
	__m128 tmp = _mm_cmpneq_ps(_data,_mm_set1_ps(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator>(float b) const
{
	__m128 tmp = _mm_cmpgt_ps(_data,_mm_set1_ps(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator>=(float b) const
{
	__m128 tmp = _mm_cmpge_ps(_data,_mm_set1_ps(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator<(float b) const
{
	__m128 tmp = _mm_cmplt_ps(_data,_mm_set1_ps(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdFvec4::operator<=(float b) const
{
	__m128 tmp = _mm_cmple_ps(_data,_mm_set1_ps(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}

SimdFvec4 SimdFvec4::sqrt() const
{
	return SimdFvec4(_mm_sqrt_ps(_data));
}
void SimdFvec4::set_to_sqrt()
{
	_data = _mm_sqrt_ps(_data);
}
SimdFvec4 SimdFvec4::rsqrt() const
{
	return SimdFvec4(_mm_rsqrt_ps(_data));
}
void SimdFvec4::set_to_rsqrt()
{
	_data = _mm_rsqrt_ps(_data);
}
SimdFvec4 SimdFvec4::normalize() const
{
	float maximum = std::min(at(0),std::min(at(1),std::min(at(2),at(3))));
	return *this / maximum;
}
void SimdFvec4::set_to_norm()
{
	float maximum = std::min(at(0),std::min(at(1),std::min(at(2),at(3))));
	*this /= maximum;
}

float SimdFvec4::sum() const
{
	__m128 tmp = _mm_hadd_ps(_data,_data);
	tmp = _mm_hadd_ps(tmp,tmp);
	return reinterpret_cast<float*>(&tmp)[0];
}

SimdIvec4::SimdIvec4()
	: _data(_mm_setzero_si128())
{

}

SimdIvec4::SimdIvec4(const __m128i &a)
	: _data(a)
{

}

SimdIvec4::SimdIvec4(int a)
	: _data(_mm_set1_epi32(a))
{

}

SimdIvec4::SimdIvec4(const int *arr)
	: _data(_mm_load_si128(reinterpret_cast<const __m128i*>(arr)))
{

}

SimdIvec4::SimdIvec4(int e0, int e1, int e2, int e3)
	: _data(_mm_set_epi32(e3,e2,e1,e0))
{

}

SimdIvec4::SimdIvec4(const SimdIvec4 &cpy)
	: _data(cpy._data)
{

}

void SimdIvec4::operator=(const SimdIvec4 &cpy)
{
	_data = cpy._data;
}

void SimdIvec4::operator=(int a)
{
	_data = _mm_set1_epi32(a);
}

void SimdIvec4::store(int *arr) const
{
	_mm_store_si128(reinterpret_cast<__m128i*>(arr),_data);
}
int* SimdIvec4::data() { return reinterpret_cast<int*>(&_data); }
const int* SimdIvec4::data() const { return reinterpret_cast<const int*>(&_data); }
size_t SimdIvec4::size() const { return 4; }
SimdIvec4::iterator SimdIvec4::begin() { return reinterpret_cast<int*>(&_data); }
SimdIvec4::iterator SimdIvec4::end() { return &reinterpret_cast<int*>(&_data)[4]; }
SimdIvec4::const_iterator SimdIvec4::begin() const { return reinterpret_cast<const int*>(&_data); }
SimdIvec4::const_iterator SimdIvec4::end() const { return &reinterpret_cast<const int*>(&_data)[4]; }
int& SimdIvec4::at(size_t i) { return *reinterpret_cast<int*>(&_data); }
const int& SimdIvec4::at(size_t i) const { return *reinterpret_cast<const int*>(&_data); }
int& SimdIvec4::operator[](size_t i) { return *reinterpret_cast<int*>(&_data); }
const int& SimdIvec4::operator[](size_t i) const { return *reinterpret_cast<const int*>(&_data); }

void SimdIvec4::operator+=(const SimdIvec4& b)
{
	_data = _mm_add_epi32(_data,b._data);
}
void SimdIvec4::operator-=(const SimdIvec4& b)
{
	_data = _mm_sub_epi32(_data,b._data);
}
void SimdIvec4::operator*=(const SimdIvec4& b)
{
	// Multiplication is not supported on SIMD!
	at(0) *= b[0];
	at(1) *= b[1];
	at(2) *= b[2];
	at(3) *= b[3];
}
void SimdIvec4::operator/=(const SimdIvec4& b)
{
	// Division is not supported on SIMD!
	at(0) /= b[0];
	at(1) /= b[1];
	at(2) /= b[2];
	at(3) /= b[3];
}
void SimdIvec4::operator<<=(const SimdIvec4& b)
{
	_data = _mm_min_epi32(_data,b._data);
} // Minimum
void SimdIvec4::operator>>=(const SimdIvec4& b)
{
	_data = _mm_max_epi32(_data,b._data);
} // Maximum
SimdIvec4 SimdIvec4::operator+(const SimdIvec4& b) const
{
	return SimdIvec4(_mm_add_epi32(_data,b._data));
}
SimdIvec4 SimdIvec4::operator-(const SimdIvec4& b) const
{
	return SimdIvec4(_mm_sub_epi32(_data,b._data));
}
SimdIvec4 SimdIvec4::operator*(const SimdIvec4& b) const
{
	SimdIvec4 tmp(*this);
	tmp *= b;
	return tmp;
}
SimdIvec4 SimdIvec4::operator/(const SimdIvec4& b) const
{
	SimdIvec4 tmp(*this);
	tmp /= b;
	return tmp;
}
bool SimdIvec4::operator==(const SimdIvec4& b) const
{
	__m128i tmp = _mm_cmpeq_epi32(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdIvec4::operator!=(const SimdIvec4& b) const
{
	return !(*this == b);
}
bool SimdIvec4::operator>(const SimdIvec4& b) const
{
	__m128i tmp = _mm_cmpgt_epi32(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdIvec4::operator>=(const SimdIvec4& b) const
{
	return (*this == b) || (*this > b);
}
bool SimdIvec4::operator<(const SimdIvec4& b) const
{
	__m128i tmp = _mm_cmplt_epi32(_data,b._data);
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdIvec4::operator<=(const SimdIvec4& b) const
{
	return (*this == b) || (*this < b);
}
SimdIvec4 SimdIvec4::operator<<(const SimdIvec4& b)
{
	return SimdIvec4(_mm_min_epi32(_data,b._data));
} // Minimum
SimdIvec4 SimdIvec4::operator>>(const SimdIvec4& b)
{
	return SimdIvec4(_mm_max_epi32(_data,b._data));
} // Maximum
SimdIvec4 SimdIvec4::min(const SimdIvec4& a, const SimdIvec4& b)
{
	return SimdIvec4(_mm_min_epi32(a._data,b._data));
} // Minimum
SimdIvec4 SimdIvec4::max(const SimdIvec4& a, const SimdIvec4& b)
{
	return SimdIvec4(_mm_max_epi32(a._data,b._data));
} // Maximum
SimdIvec4 SimdIvec4::clamp(const SimdIvec4& a, const SimdIvec4& _min, const SimdIvec4& _max)
{
	return SimdIvec4(_mm_min_epi32(_mm_max_epi32(a._data,_min._data),_max._data));
} // Clamp
// Arithemetics with scalars
void SimdIvec4::operator+=(int b)
{
	_data = _mm_add_epi32(_data,_mm_set1_epi32(b));
}
void SimdIvec4::operator-=(int b)
{
	_data = _mm_sub_epi32(_data,_mm_set1_epi32(b));
}
void SimdIvec4::operator*=(int b)
{
	// Intrinsics don't support multiplication
	at(0) *= b;
	at(1) *= b;
	at(2) *= b;
	at(3) *= b;
}
void SimdIvec4::operator/=(int b)
{
	// Intrinsics don't support division
	at(0) /= b;
	at(1) /= b;
	at(2) /= b;
	at(3) /= b;
}
void SimdIvec4::operator<<=(int b)
{
	_data = _mm_min_epi32(_data,_mm_set1_epi32(b));
} // Minimum
void SimdIvec4::operator>>=(int b)
{
	_data = _mm_max_epi32(_data,_mm_set1_epi32(b));
} // Maximum
SimdIvec4 SimdIvec4::operator+(int b) const
{
	return SimdIvec4(_mm_add_epi32(_data,_mm_set1_epi32(b)));
}
SimdIvec4 SimdIvec4::operator-(int b) const
{
	return SimdIvec4(_mm_sub_epi32(_data,_mm_set1_epi32(b)));
}
SimdIvec4 SimdIvec4::operator*(int b) const
{
	SimdIvec4 tmp(*this);
	tmp *= b;
	return tmp;
}
SimdIvec4 SimdIvec4::operator/(int b) const
{
	SimdIvec4 tmp(*this);
	tmp /= b;
	return tmp;
}
SimdIvec4 SimdIvec4::operator<<(int b)
{
	return SimdIvec4(_mm_min_epi32(_data,_mm_set1_epi32(b)));
} // Minimum
SimdIvec4 SimdIvec4::operator>>(int b)
{
	return SimdIvec4(_mm_max_epi32(_data,_mm_set1_epi32(b)));
} // Maximum
bool SimdIvec4::operator==(int b) const
{
	__m128i tmp = _mm_cmpeq_epi32(_data,_mm_set1_epi32(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdIvec4::operator!=(int b) const
{
	return !(*this == b);
}
bool SimdIvec4::operator>(int b) const
{
	__m128i tmp = _mm_cmpgt_epi32(_data,_mm_set1_epi32(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdIvec4::operator>=(int b) const
{
	return (*this == b) || (*this > b);
}
bool SimdIvec4::operator<(int b) const
{
	__m128i tmp = _mm_cmplt_epi32(_data,_mm_set1_epi32(b));
	return reinterpret_cast<uint32_t*>(&tmp)[0] && reinterpret_cast<uint32_t*>(&tmp)[1] &&
		   reinterpret_cast<uint32_t*>(&tmp)[2] && reinterpret_cast<uint32_t*>(&tmp)[3];
}
bool SimdIvec4::operator<=(int b) const
{
	return (*this == b) || (*this < b);
}
// Other mathematical goodies
int SimdIvec4::sum() const
{
	__m128i result = _mm_hadd_epi32(_data, _data);
	result = _mm_hadd_epi32(result, result);
	return _mm_cvtsi128_si32(result);
}
