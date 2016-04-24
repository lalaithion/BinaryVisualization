HEADERS = gradient.h image.h interpolate.h \
    BV_OpenGL.h \
    BV_Viewer.h \
    colors.h
SOURCES = gradient.cpp image.cpp interpolate.cpp \
    BinaryVisualization.cpp \
    BV_OpenGL.cpp \
    BV_Viewer.cpp
QT += opengl
RESOURCES = BinaryVisualization.qrc
