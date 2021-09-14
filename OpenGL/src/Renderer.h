#pragma once

#include<GL/glew.h>

/*STARTOF: Error Checking for gl functions: We can now put gl functions inside GLCall(x)*/
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
                    x;\
                    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);