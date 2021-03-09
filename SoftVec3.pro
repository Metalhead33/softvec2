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
        Texture.cpp \
        ZBuffer.cpp \
        main.cpp

HEADERS += \
	Camera.hpp \
	CreateTexture.hpp \
	MhNormDenorm.hpp \
	Pipeline/BasicPipeline.hpp \
	Pipeline/ClipspacePipeline.hpp \
	Pipeline/Model2Pipeline.hpp \
	Pipeline/ModelPipeline.hpp \
	Pipeline/RenderingPipeline.hpp \
	Pipeline/TriangleSort.hpp \
	StandardTexture.hpp \
	Texture.hpp \
	ZBuffer.hpp
