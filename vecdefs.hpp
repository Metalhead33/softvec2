#ifndef VECDEFS_HPP
#define VECDEFS_HPP
#include "SIMD/SSE.hpp"
#include "vec.hpp"
#include "mat.hpp"
#include <array>

typedef vec<float,2> fvec2;
typedef vec<float,3> fvec3;
typedef SimdFvec4 fvec4;

typedef vec<int,2> ivec2;
typedef vec<int,3> ivec3;
typedef SimdIvec4 ivec4;

#endif // VECDEFS_HPP
