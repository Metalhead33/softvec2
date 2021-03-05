TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2 -lMhLib

SOURCES += \
        CreateTexture.cpp \
        Pipeline/BasicPipeline.cpp \
        Pipeline/ClipspacePipeline.cpp \
        Pipeline/TriangleSort.cpp \
        Texture.cpp \
        ZBuffer.cpp \
        main.cpp

HEADERS += \
	CreateTexture.hpp \
	MhNormDenorm.hpp \
	Pipeline/BasicPipeline.hpp \
	Pipeline/ClipspacePipeline.hpp \
	Pipeline/RenderingPipeline.hpp \
	Pipeline/TriangleSort.hpp \
	StandardTexture.hpp \
	Texture.hpp \
	ZBuffer.hpp
