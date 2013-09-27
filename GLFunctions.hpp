#ifndef GLFUNCTIONS_HPP
#define GLFUNCTIONS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Log.hpp"
#include "BnD.hpp"
#undef near
#undef far

/*extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;*/
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

int LoadGLFunctions();
GLuint NewGLProgram(const char*, const char*, const char* _default_ = nullptr);
void GLOrtho(BnD::Mat<GLfloat, 4>&, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void GLIdentity(BnD::Mat<GLfloat, 4>&);
void GLScale(BnD::Mat<GLfloat, 4>&);

#endif // GLFUNCTIONS_HPP
