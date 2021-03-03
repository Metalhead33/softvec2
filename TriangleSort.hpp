#ifndef TRIANGLESORT_HPP
#define TRIANGLESORT_HPP
#include <glm/glm.hpp>

int edgeFunction(const glm::ivec2 &a, const glm::ivec2 &b, const glm::ivec2 &c);
float edgeFunction(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c);
bool isPrecedingClockwise(const glm::ivec2& a, const glm::ivec2& b); // Is A above B?
bool isPrecedingClockwise(const glm::vec2& a, const glm::vec2& b); // Is A above B?
bool isPrecedingClockwise(const glm::vec3& a, const glm::vec3& b); // Is A above B?
template <class VertexType> bool windingTest(const VertexType& a, const VertexType& b) {
	return isPrecedingClockwise(a.COORDS,b.COORDS);
}
template <class VertexType> void sortTriangle(const VertexType** v0, const VertexType** v1, const VertexType** v2) {
	if(windingTest(**v1,**v0)) std::swap(*v0,*v1);
	if(windingTest(**v2,**v0)) std::swap(*v0,*v2);
	if(windingTest(**v2,**v1)) std::swap(*v1,*v2);
}

#endif // TRIANGLESORT_HPP
