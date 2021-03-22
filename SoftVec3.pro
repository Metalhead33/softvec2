TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2 -lMhLib -lassimp

SOURCES += \
        Camera.cpp \
        CreateTexture.cpp \
        Pipeline/BasicPipeline.cpp \
        Pipeline/ClipspacePipeline.cpp \
        Pipeline/Model2Pipeline.cpp \
        Pipeline/ModelPipeline.cpp \
        Pipeline/TriangleSort.cpp \
        Pipeline/WidgetPipeline.cpp \
        Texture.cpp \
        Tile/Terrain.cpp \
        Tile/Tile.cpp \
        ZBuffer.cpp \
        main.cpp

HEADERS += \
	Camera.hpp \
	CreateTexture.hpp \
	PalettedTexture.hpp \
	Pipeline/BasicPipeline.hpp \
	Pipeline/ClipspacePipeline.hpp \
	Pipeline/Model2Pipeline.hpp \
	Pipeline/ModelPipeline.hpp \
	Pipeline/RenderingPipeline.hpp \
	Pipeline/TriangleSort.hpp \
	Pipeline/WidgetPipeline.hpp \
	StandardPixelType.hpp \
	StandardTexture.hpp \
	Texture.hpp \
	Tile/Terrain.hpp \
	Tile/Tile.hpp \
	ZBuffer.hpp
