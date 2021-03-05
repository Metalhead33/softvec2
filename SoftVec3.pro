TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2 -lMhLib

SOURCES += \
        Pipeline/BasicPipeline.cpp \
        Pipeline/TriangleSort.cpp \
        Texture.cpp \
        main.cpp

HEADERS += \
	MhNormDenorm.hpp \
	Pipeline/BasicPipeline.hpp \
	Pipeline/RenderingPipeline.hpp \
	Pipeline/TriangleSort.hpp \
	StandardTexture.hpp \
	Texture.hpp
