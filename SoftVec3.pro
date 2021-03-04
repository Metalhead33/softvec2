TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2

SOURCES += \
        TriangleSort.cpp \
        main.cpp

HEADERS += \
	MhNormDenorm.hpp \
	RenderingPipeline.hpp \
	Texture.hpp \
	TriangleSort.hpp
