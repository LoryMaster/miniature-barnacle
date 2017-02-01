#pragma once

#include "lsWindows.h"

////////////////////////////////////////////////////
//	MATH FUNCTIONS
////////////////////////////////////////////////////

#define PI_32 3.1415926f

s32 ls_abs(s32 x);
f64 ls_sine(f64 x);
f64 ls_cos(f64 x);
f64 ls_tan(f64 x);
f32 ls_sqrt(f32 x);

////////////////////////////////////////////////////
//	STRING FUNCTIONS
////////////////////////////////////////////////////

s32 ls_len(char * string);
char * ls_itoa(s32 x);
char * ls_concat(char *string1, char *string2, b32 hasToFree);
s32 ls_strcmp(char *string1, char *string2);

////////////////////////////////////////////////////
//	MEMORY FUNCTIONS
////////////////////////////////////////////////////

void ls_memcpy(void *src, void *dest, size_t size);

//@TODO: Move in its own logging system
void LogError_(char *Message, s32 Error);

#ifdef _DEBUG
#define LogError(name, value) LogError_(name, value)
#else
#define LogError(value)
#endif