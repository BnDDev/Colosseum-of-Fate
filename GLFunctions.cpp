#include "GLFunctions.hpp"

/*PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;*/
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;

int LoadGLFunctions() {
    /*if(!(glCreateShader = (PFNGLCREATESHADERPROC) SDL_GL_GetProcAddress("glCreateShader"))) return 10;
    if(!(glShaderSource = (PFNGLSHADERSOURCEPROC) SDL_GL_GetProcAddress("glShaderSource"))) return 20;
    if(!(glCompileShader = (PFNGLCOMPILESHADERPROC) SDL_GL_GetProcAddress("glCompileShader"))) return 30;
    if(!(glGetShaderiv = (PFNGLGETSHADERIVPROC) SDL_GL_GetProcAddress("glGetShaderiv"))) return 40;
    if(!(glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) SDL_GL_GetProcAddress("glGetShaderInfoLog"))) return 50;
    if(!(glCreateProgram = (PFNGLCREATEPROGRAMPROC) SDL_GL_GetProcAddress("glCreateProgram"))) return 60;
    if(!(glAttachShader = (PFNGLATTACHSHADERPROC) SDL_GL_GetProcAddress("glAttachShader"))) return 70;
    if(!(glLinkProgram = (PFNGLLINKPROGRAMPROC) SDL_GL_GetProcAddress("glLinkProgram"))) return 80;
    if(!(glGetProgramiv = (PFNGLGETPROGRAMIVPROC) SDL_GL_GetProcAddress("glGetProgramiv"))) return 90;
    if(!(glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) SDL_GL_GetProcAddress("glGetProgramInfoLog"))) return 100;
    if(!(glDetachShader = (PFNGLDETACHSHADERPROC) SDL_GL_GetProcAddress("glDetachShader"))) return 108;
    if(!(glDeleteShader = (PFNGLDELETESHADERPROC) SDL_GL_GetProcAddress("glDeleteShader"))) return 110;
    if(!(glGenBuffers = (PFNGLGENBUFFERSPROC) SDL_GL_GetProcAddress("glGenBuffers"))) return 120;
    if(!(glBindBuffer = (PFNGLBINDBUFFERPROC) SDL_GL_GetProcAddress("glBindBuffer"))) return 130;
    if(!(glBufferData = (PFNGLBUFFERDATAPROC) SDL_GL_GetProcAddress("glBufferData"))) return 140;
    if(!(glBufferSubData = (PFNGLBUFFERSUBDATAPROC) SDL_GL_GetProcAddress("glBufferSubData"))) return 141;
    if(!(glUseProgram = (PFNGLUSEPROGRAMPROC) SDL_GL_GetProcAddress("glUseProgram"))) return 150;
    if(!(glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) SDL_GL_GetProcAddress("glEnableVertexAttribArray"))) return 160;
    if(!(glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) SDL_GL_GetProcAddress("glVertexAttribPointer"))) return 170;
    if(!(glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) SDL_GL_GetProcAddress("glDisableVertexAttribArray"))) return 180;
    if(!(glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) SDL_GL_GetProcAddress("glGetUniformLocation"))) return 190;
    if(!(glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) SDL_GL_GetProcAddress("glGetAttribLocation"))) return 192;
    if(!(glActiveTexture = (PFNGLACTIVETEXTUREPROC) SDL_GL_GetProcAddress("glActiveTexture"))) return 200;
    if(!(glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) SDL_GL_GetProcAddress("glUniformMatrix4fv"))) return 210;
    if(!(glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) SDL_GL_GetProcAddress("glDeleteBuffers"))) return 220;
    if(!(glDeleteProgram = (PFNGLDELETEPROGRAMPROC) SDL_GL_GetProcAddress("glDeleteProgram"))) return 230;*/
    if(!(glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) SDL_GL_GetProcAddress("glGenVertexArrays"))) return 240;
    if(!(glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) SDL_GL_GetProcAddress("glBindVertexArray"))) return 241;
    if(!(glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) SDL_GL_GetProcAddress("glDeleteVertexArrays"))) return 242;
    return 0;
}

GLuint NewGLProgram(const char* vs, const char* fs, const char* gs) {
    constexpr size_t MAX_LEN = 4096;
    GLchar str[MAX_LEN];
    GLint ret;
    GLuint glv, glf, glg;

    glv = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(glv, 1, &vs, nullptr);
    glCompileShader(glv);
    glGetShaderiv(glv, GL_COMPILE_STATUS, &ret);
    if(ret != GL_TRUE) {
        glGetShaderInfoLog(glv, MAX_LEN, nullptr, str);
        Log::Error("GLVertex Shader error:\n%s", str);
    }

    glf = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(glf, 1, &fs, nullptr);
    glCompileShader(glf);
    glGetShaderiv(glf, GL_COMPILE_STATUS, &ret);
    if(ret != GL_TRUE) {
        glGetShaderInfoLog(glf, MAX_LEN, nullptr, str);
        Log::Error("GLFragment Shader error:\n%s", str);
    }

    if(gs) {
        glg = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(glg, 1, &gs, nullptr);
        glCompileShader(glg);
        glGetShaderiv(glg, GL_COMPILE_STATUS, &ret);
        if(ret != GL_TRUE) {
            glGetShaderInfoLog(glg, MAX_LEN, nullptr, str);
            Log::Error("GLGeometry Shader error:\n%s", str);
        }
    }

    GLuint glp = glCreateProgram();
    glAttachShader(glp, glv);
    glAttachShader(glp, glf);
    if(gs) glAttachShader(glp, glg);
    glLinkProgram(glp);
    glGetProgramiv(glp, GL_LINK_STATUS, &ret);
    if(ret != GL_TRUE) {
        glGetProgramInfoLog(glp, MAX_LEN, nullptr, str);
        Log::Error("GLProgram error:\n%s", str);
    } else Log::Info("GLProgram created!");

    if(gs) {
        glDetachShader(glp, glg);
        glDeleteShader(glg);
    }
    glDetachShader(glp, glv);
    glDetachShader(glp, glf);
    glDeleteShader(glv);
    glDeleteShader(glf);

    return glp;
}

void GLOrtho(BnD::Mat<GLfloat, 4>& mat, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
    mat.v[0][0] = 2.0f / (right - left);
    mat.v[0][1] = 0.0f;
    mat.v[0][2] = 0.0f;
    mat.v[0][3] = 0.0f;

    mat.v[1][0] = 0.0f;
    mat.v[1][1] = 2.0f / (top - bottom);
    mat.v[1][2] = 0.0f;
    mat.v[1][3] = 0.0f;

    mat.v[2][0] = 0.0f;
    mat.v[2][1] = 0.0f;
    mat.v[2][2] = -2.0f / (far - near);
    mat.v[2][3] = 0.0f;

    mat.v[3][0] = -(right + left) / (right - left);
    mat.v[3][1] = -(top + bottom) / (top - bottom);
    mat.v[3][2] = -(far + near) / (far - near);
    mat.v[3][3] = 1.0f;
}

void GLIdentity(BnD::Mat<GLfloat, 4>& mat)
{
    mat.v[0][0] = 1.0f;
    mat.v[0][1] = 0.0f;
    mat.v[0][2] = 0.0f;
    mat.v[0][3] = 0.0f;

    mat.v[1][0] = 0.0f;
    mat.v[1][1] = 1.0f;
    mat.v[1][2] = 0.0f;
    mat.v[1][3] = 0.0f;

    mat.v[2][0] = 0.0f;
    mat.v[2][1] = 0.0f;
    mat.v[2][2] = 1.0f;
    mat.v[2][3] = 0.0f;

    mat.v[3][0] = 0.0f;
    mat.v[3][1] = 0.0f;
    mat.v[3][2] = 0.0f;
    mat.v[3][3] = 1.0f;
}
