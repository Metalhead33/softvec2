#ifndef SSE_HPP
#define SSE_HPP
extern "C" {
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
}
class SimdFvec4 {
public:
	typedef float* iterator;
	typedef const float* const_iterator;
private:
	__m128 _data;
public:
	SimdFvec4();
	SimdFvec4(const __m128& a);
	SimdFvec4(float a);
	SimdFvec4(const float* arr);
	SimdFvec4(float e0, float e1, float e2, float e3);
	SimdFvec4(const SimdFvec4& cpy); // Copy constructor;
	void operator=(const SimdFvec4& cpy); // Copy assignment
	void operator=(float a);
	void operator=(const float* arr);
	void store(float* arr) const;
	SimdFvec4 reciprocal() const;
	void set_to_reciprocal();

	// Compatibility with STL containers
	float* data();
	const float* data() const;
	size_t size() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	float& at(size_t i);
	const float& at(size_t i) const;
	float& operator[](size_t i);
	const float& operator[](size_t i) const;
	// Arithemetics and comparisons with other vectors
	void operator+=(const SimdFvec4& b);
	void operator-=(const SimdFvec4& b);
	void operator*=(const SimdFvec4& b);
	void operator/=(const SimdFvec4& b);
	void operator<<=(const SimdFvec4& b); // Minimum
	void operator>>=(const SimdFvec4& b); // Maximum
	SimdFvec4 operator+(const SimdFvec4& b) const;
	SimdFvec4 operator-(const SimdFvec4& b) const;
	SimdFvec4 operator*(const SimdFvec4& b) const;
	SimdFvec4 operator/(const SimdFvec4& b) const;
	bool operator==(const SimdFvec4& b) const;
	bool operator!=(const SimdFvec4& b) const;
	bool operator>(const SimdFvec4& b) const;
	bool operator>=(const SimdFvec4& b) const;
	bool operator<(const SimdFvec4& b) const;
	bool operator<=(const SimdFvec4& b) const;
	SimdFvec4 operator<<(const SimdFvec4& b); // Minimum
	SimdFvec4 operator>>(const SimdFvec4& b); // Maximum
	static SimdFvec4 min(const SimdFvec4& a, const SimdFvec4& b); // Minimum
	static SimdFvec4 max(const SimdFvec4& a, const SimdFvec4& b); // Maximum
	static SimdFvec4 clamp(const SimdFvec4& a, const SimdFvec4& _min, const SimdFvec4& _max); // Clamp
	float vectorialMul(const SimdFvec4& b) const;
	// Arithemetics with scalars
	void operator+=(float b);
	void operator-=(float b);
	void operator*=(float b);
	void operator/=(float b);
	void operator<<=(float b); // Minimum
	void operator>>=(float b); // Maximum
	SimdFvec4 operator+(float b) const;
	SimdFvec4 operator-(float b) const;
	SimdFvec4 operator*(float b) const;
	SimdFvec4 operator/(float b) const;
	SimdFvec4 operator<<(float b); // Minimum
	SimdFvec4 operator>>(float b); // Maximum
	bool operator==(float b) const;
	bool operator!=(float b) const;
	bool operator>(float b) const;
	bool operator>=(float b) const;
	bool operator<(float b) const;
	bool operator<=(float b) const;
	float vectorialMul(float b) const;
	// Other mathematical goodies
	SimdFvec4 sqrt() const;
	void set_to_sqrt();
	SimdFvec4 rsqrt() const;
	void set_to_rsqrt();
	SimdFvec4 normalize() const;
	void set_to_norm();
	float sum() const;
};
class SimdIvec4 {
public:
	typedef int* iterator;
	typedef const int* const_iterator;
private:
	__m128i _data;
public:
	SimdIvec4();
	SimdIvec4(const __m128i& a);
	SimdIvec4(int a);
	SimdIvec4(const int* arr);
	SimdIvec4(int e0, int e1, int e2, int e3);
	SimdIvec4(const SimdIvec4& cpy); // Copy constructor;
	void operator=(const SimdIvec4& cpy); // Copy assignment
	void operator=(int a);
	void store(int* arr) const;
	// Compatibility with STL containers
	int* data();
	const int* data() const;
	size_t size() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	int& at(size_t i);
	const int& at(size_t i) const;
	int& operator[](size_t i);
	const int& operator[](size_t i) const;
	// Arithemetics and comparisons with other vectors
	void operator+=(const SimdIvec4& b);
	void operator-=(const SimdIvec4& b);
	void operator*=(const SimdIvec4& b);
	void operator/=(const SimdIvec4& b);
	void operator<<=(const SimdIvec4& b); // Minimum
	void operator>>=(const SimdIvec4& b); // Maximum
	SimdIvec4 operator+(const SimdIvec4& b) const;
	SimdIvec4 operator-(const SimdIvec4& b) const;
	SimdIvec4 operator*(const SimdIvec4& b) const;
	SimdIvec4 operator/(const SimdIvec4& b) const;
	bool operator==(const SimdIvec4& b) const;
	bool operator!=(const SimdIvec4& b) const;
	bool operator>(const SimdIvec4& b) const;
	bool operator>=(const SimdIvec4& b) const;
	bool operator<(const SimdIvec4& b) const;
	bool operator<=(const SimdIvec4& b) const;
	SimdIvec4 operator<<(const SimdIvec4& b); // Minimum
	SimdIvec4 operator>>(const SimdIvec4& b); // Maximum
	static SimdIvec4 min(const SimdIvec4& a, const SimdIvec4& b); // Minimum
	static SimdIvec4 max(const SimdIvec4& a, const SimdIvec4& b); // Maximum
	static SimdIvec4 clamp(const SimdIvec4& a, const SimdIvec4& _min, const SimdIvec4& _max); // Clamp
	// Arithemetics with scalars
	void operator+=(int b);
	void operator-=(int b);
	void operator*=(int b);
	void operator/=(int b);
	void operator<<=(int b); // Minimum
	void operator>>=(int b); // Maximum
	SimdIvec4 operator+(int b) const;
	SimdIvec4 operator-(int b) const;
	SimdIvec4 operator*(int b) const;
	SimdIvec4 operator/(int b) const;
	SimdIvec4 operator<<(int b); // Minimum
	SimdIvec4 operator>>(int b); // Maximum
	bool operator==(int b) const;
	bool operator!=(int b) const;
	bool operator>(int b) const;
	bool operator>=(int b) const;
	bool operator<(int b) const;
	bool operator<=(int b) const;
	// Other mathematical goodies
	int sum() const;
};

#endif // SSE_HPP
