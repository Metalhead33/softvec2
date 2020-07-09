TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2
QMAKE_CXXFLAGS +=-msse4

SOURCES += \
	Raster/ClipspaceRenderer.cpp \
	Raster/SortTriangle.cpp \
	SIMD/SSE.cpp \
	Texture/Texture.cpp \
	main.cpp

HEADERS += \
	NormDenorm.hpp \
	Raster/ClipspaceRenderer.hpp \
	Raster/Pipeline.hpp \
	Raster/SortTriangle.hpp \
	SIMD/SSE.hpp \
	Texture/OptimizedTexture.hpp \
	Texture/Palette.hpp \
	Texture/StandardTexture.hpp \
	Texture/Texture.hpp \
	half.hpp \
	mat.hpp \
	vec.hpp \
	vecdefs.hpp

DISTFILES += \
	.gitignore \
	README.md
