#ifndef CSCIx239
#define CSCIx239

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

    
void         CreateShader(int prog,const GLenum type,const char* file);
void         PrintProgramLog(int obj);
int          CreateShaderProg(const char* VertFile,const char* FragFile);

#ifdef __cplusplus
}
#endif

#endif

