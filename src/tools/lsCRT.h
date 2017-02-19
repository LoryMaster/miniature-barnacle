#pragma once

#include "lsWindows.h"
#include <stdarg.h>

#define fil(value) for(int i = 0; i < value; i++)
#define fjl(value) for(int j = 0; j < value; j++)

////////////////////////////////////////////////////
//	MATH FUNCTIONS
////////////////////////////////////////////////////

#define PI_32 3.1415926f

s32 ls_abs(s32 x);
f32 ls_abs(f32 x);

f32 rad(f32 x);
f64 ls_sine(f64 x);
f64 ls_asin(f64 x);
f64 ls_cos(f64 x);
f64 ls_acos(f64 x);
f64 ls_tan(f64 x);
f64 ls_atan(f64 x);

f32 ls_sqrt(f32 x);

////////////////////////////////////////////////////
//	STRING FUNCTIONS
////////////////////////////////////////////////////

s32 ls_len(char * string);
char * ls_itoa(s32 x);
char * ls_ftoa(f32 x);
char * ls_concat(char *string1, char *string2, b32 hasToFree);
s32 ls_strcmp(char *string1, char *string2);
s32 ls_strcpy(char *dest, char *src, bool nullTerminate);

s32 ls_sprintf(char *dest, const char *format, ...);

////////////////////////////////////////////////////
//	MEMORY FUNCTIONS
////////////////////////////////////////////////////

void ls_memcpy(void *src, void *dest, size_t size);

//@TODO: Move in its own logging system
void LogErrori_(char *Message, s32 Error);
void LogErrorf_(char *Message, f32 Error);

#ifdef _DEBUG
#define LogErrori(name, value) LogErrori_(name, value)
#define LogErrorf(name, value) LogErrorf_(name, value)
#else
#define LogErrori(name, value)
#define LogErrorf(name, value)
#endif