#include "SortTriangle.hpp"

fvec3 NDCspace2rasterspace(const fvec3& ndcspace, const fvec2& screendimensions)
{
	return fvec3{ (ndcspace[0] + 1.0f) * 0.5f * screendimensions[0],
				   ((ndcspace[1]-1.0f) * -0.5f) * screendimensions[1],
				   -ndcspace[2]
	};
}
fvec3 NDCspace2rasterspace(const fvec3& ndcspace, const fvec4 &viewport)
{
	return fvec3{ (ndcspace[0] + 1.0f) * 0.5f * viewport[2],
				   ((ndcspace[1]-1.0f) * -0.5f) * viewport[3],
				   ndcspace[2]
	};
}
