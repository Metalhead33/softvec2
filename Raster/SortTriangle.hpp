#ifndef SORTTRIANGLE_HPP
#define SORTTRIANGLE_HPP
#include "../vecdefs.hpp"
#include <functional>

fvec3 NDCspace2rasterspace(const fvec3& ndcspace, const fvec2& screendimensions);
fvec3 NDCspace2rasterspace(const fvec3& ndcspace, const fvec4& viewport);

template <typename T >
struct CloickwiseOrderCRD {
	typedef vec<T,2> VectorType;
	typedef std::function<void(const VectorType&, const VectorType&, const VectorType&)> RasterizerFunction;
	static const VectorType& clockwiseCompare(const VectorType& a, const VectorType& b) // Return reference to the first one
	{
		if(a[1] == b[1]) // If they are equal we will order by X instead of Y
			return (a[0] > b[0]) ? a : b;
		else
			return (a[1] > b[1]) ? a : b;
	}
	static bool isPrecedingClockwise(const VectorType& a, const VectorType& b) // Is A above B?
	{
		if(a[1] == b[1]) // If they are equal we will order by X instead of Y
			return (a[0] > b[0]);
		else
			return (a[1] > b[1]);
	}
	static void sortTriangle(RasterizerFunction func, const VectorType* v0, const VectorType* v1, const VectorType* v2)
	{
		if(isPrecedingClockwise(*v1,*v0)) std::swap(v0,v1);
		if(isPrecedingClockwise(*v2,*v0)) std::swap(v0,v2);
		if(isPrecedingClockwise(*v2,*v1)) std::swap(v1,v2);
		func(*v0,*v1,*v2);
	}
	static void sortTriangle(const VectorType** v0, const VectorType** v1, const VectorType** v2)
	{
		if(isPrecedingClockwise(**v1,**v0)) std::swap(*v0,*v1);
		if(isPrecedingClockwise(**v2,**v0)) std::swap(*v0,*v2);
		if(isPrecedingClockwise(**v2,**v1)) std::swap(*v1,*v2);
	}
};

template <typename VertexFormat >
struct CloickwiseOrderVERT {
	typedef std::function<void(const VertexFormat&, const VertexFormat&, const VertexFormat&)> RasterizerFunction;
	static const VertexFormat& clockwiseCompare(const VertexFormat& a, const VertexFormat& b) // Return reference to the first one
	{
		if(a.coords[1] == b.coords[1]) // If they are equal we will order by X instead of Y
			return (a.coords[0] > b.coords[0]) ? a : b;
		else
			return (a.coords[1] > b.coords[1]) ? a : b;
	}
	static bool isPrecedingClockwise(const VertexFormat& a, const VertexFormat& b) // Is A above B?
	{
		if(a.coords[1] == b.coords[1]) // If they are equal we will order by X instead of Y
			return (a.coords[0] > b.coords[0]);
		else
			return (a.coords[1] > b.coords[1]);
	}
	static void sortTriangle(RasterizerFunction func, const VertexFormat* v0, const VertexFormat* v1, const VertexFormat* v2)
	{
		if(isPrecedingClockwise(*v1,*v0)) std::swap(v0,v1);
		if(isPrecedingClockwise(*v2,*v0)) std::swap(v0,v2);
		if(isPrecedingClockwise(*v2,*v1)) std::swap(v1,v2);
		func(*v0,*v1,*v2);
	}
	static void sortTriangle(const VertexFormat** v0, const VertexFormat** v1, const VertexFormat** v2)
	{
		if(isPrecedingClockwise(**v1,**v0)) std::swap(*v0,*v1);
		if(isPrecedingClockwise(**v2,**v0)) std::swap(*v0,*v2);
		if(isPrecedingClockwise(**v2,**v1)) std::swap(*v1,*v2);
	}
};

template <typename VectorFormat> struct TriangleUtilities {
	typedef vec<VectorFormat,2> Vector2D;
	typedef vec<VectorFormat,3> Vector3D;
	typedef vec<VectorFormat,4> Vector4D;
	typedef std::array<Vector2D,3> Triangle2D;
	typedef std::array<Vector3D,3> Triangle3D;
	typedef std::array<Vector4D,3> Triangle4D;
	typedef std::array<Vector2D,4> Rectangle2D;

	static VectorFormat edgeFunction(const Vector2D& a, const Vector2D& b, const Vector2D& c)
	{
		return ((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]));
	}
	static VectorFormat edgeFunction(const Vector3D& a, const Vector3D& b, const Vector3D& c)
	{
		return ((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]));
	}
	static VectorFormat edgeFunction(const Vector3D& a, const Vector3D& b, const Vector2D& c)
	{
		return ((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]));
	}
	static VectorFormat edgeFunction(const Vector4D& a, const Vector4D& b, const Vector4D& c)
	{
		return ((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]));
	}
	static VectorFormat triangleArea(const Triangle2D& triang)
	{
		return edgeFunction(triang[0],triang[1],triang[2]) / 2;
	}
	static bool isPointPartOfTriangle(const Vector2D& point, const Triangle2D& triangle)
	{
		bool inside = true;
		inside &= edgeFunction(triangle[0], triangle[1], point) >= 0;
		inside &= edgeFunction(triangle[1], triangle[2], point) >= 0;
		inside &= edgeFunction(triangle[2], triangle[0], point) >= 0;
		return inside;
	}
	static Rectangle2D createBoundingBox(const Vector4D& viewport, const Vector2D& v0, const Vector2D& v1, const Vector2D& v2)
	{
		Rectangle2D box = {{ { std::numeric_limits<VectorFormat>::max(), std::numeric_limits<VectorFormat>::infinity() },
							  { std::numeric_limits<VectorFormat>::lowest(), std::numeric_limits<VectorFormat>::lowest() },
							  }};
		// Calculations - V0
		box[0][0] = std::min(box[0][0],v0[0]);
		box[0][1] = std::min(box[0][1],v0[1]);
		box[1][0] = std::max(box[1][0],v0[0]);
		box[1][1] = std::max(box[1][1],v0[1]);
		// Calculations - V1
		box[0][0] = std::min(box[0][0],v1[0]);
		box[0][1] = std::min(box[0][1],v1[1]);
		box[1][0] = std::max(box[1][0],v1[0]);
		box[1][1] = std::max(box[1][1],v1[1]);
		// Calculations - V2
		box[0][0] = std::min(box[0][0],v2[0]);
		box[0][1] = std::min(box[0][1],v2[1]);
		box[1][0] = std::max(box[1][0],v2[0]);
		box[1][1] = std::max(box[1][1],v2[1]);
		// Final calculations to prevent overdraw
		box[0][0] = std::max(box[0][0],viewport[0]);
		box[0][1] = std::max(box[0][1],viewport[1]);
		box[1][0] = std::min(box[1][0],viewport[2]);
		box[1][1] = std::min(box[1][1],viewport[3]);
		return box;
	}
	static Rectangle2D createBoundingBox(const Vector4D& viewport, const Vector3D& v0, const Vector3D& v1, const Vector3D& v2)
	{
		Rectangle2D box = {{ { std::numeric_limits<VectorFormat>::max(), std::numeric_limits<VectorFormat>::infinity() },
							{ std::numeric_limits<VectorFormat>::lowest(), std::numeric_limits<VectorFormat>::lowest() },
							}};
		// Calculations - V0
		box[0][0] = std::min(box[0][0],v0[0]);
		box[0][1] = std::min(box[0][1],v0[1]);
		box[1][0] = std::max(box[1][0],v0[0]);
		box[1][1] = std::max(box[1][1],v0[1]);
		// Calculations - V1
		box[0][0] = std::min(box[0][0],v1[0]);
		box[0][1] = std::min(box[0][1],v1[1]);
		box[1][0] = std::max(box[1][0],v1[0]);
		box[1][1] = std::max(box[1][1],v1[1]);
		// Calculations - V2
		box[0][0] = std::min(box[0][0],v2[0]);
		box[0][1] = std::min(box[0][1],v2[1]);
		box[1][0] = std::max(box[1][0],v2[0]);
		box[1][1] = std::max(box[1][1],v2[1]);
		// Final calculations to prevent overdraw
		box[0][0] = std::max(box[0][0],viewport[0]);
		box[0][1] = std::max(box[0][1],viewport[1]);
		box[1][0] = std::min(box[1][0],viewport[2]);
		box[1][1] = std::min(box[1][1],viewport[3]);
		return box;
	}
	static Rectangle2D createBoundingBox(const Vector4D& viewport, const Vector4D& v0, const Vector4D& v1, const Vector4D& v2)
	{
		Rectangle2D box = {{ { std::numeric_limits<VectorFormat>::max(), std::numeric_limits<VectorFormat>::infinity() },
							{ std::numeric_limits<VectorFormat>::lowest(), std::numeric_limits<VectorFormat>::lowest() },
							}};
		// Calculations - V0
		box[0][0] = std::min(box[0][0],v0[0]);
		box[0][1] = std::min(box[0][1],v0[1]);
		box[1][0] = std::max(box[1][0],v0[0]);
		box[1][1] = std::max(box[1][1],v0[1]);
		// Calculations - V1
		box[0][0] = std::min(box[0][0],v1[0]);
		box[0][1] = std::min(box[0][1],v1[1]);
		box[1][0] = std::max(box[1][0],v1[0]);
		box[1][1] = std::max(box[1][1],v1[1]);
		// Calculations - V2
		box[0][0] = std::min(box[0][0],v2[0]);
		box[0][1] = std::min(box[0][1],v2[1]);
		box[1][0] = std::max(box[1][0],v2[0]);
		box[1][1] = std::max(box[1][1],v2[1]);
		// Final calculations to prevent overdraw
		box[0][0] = std::max(box[0][0],viewport[0]);
		box[0][1] = std::max(box[0][1],viewport[1]);
		box[1][0] = std::min(box[1][0],viewport[2]);
		box[1][1] = std::min(box[1][1],viewport[3]);
		return box;
	}
	static Rectangle2D createBoundingBox(const Vector4D& viewport, const Triangle2D& triang) { return createBoundingBox(viewport,triang[0],triang[1],triang[2]); }
	static Rectangle2D createBoundingBox(const Vector4D& viewport, const Triangle3D& triang) { return createBoundingBox(viewport,triang[0],triang[1],triang[2]); }
	static Rectangle2D createBoundingBox(const Vector4D& viewport, const Triangle4D& triang) { return createBoundingBox(viewport,triang[0],triang[1],triang[2]); }

};

#endif // SORTTRIANGLE_HPP
