#include "tools\lsCRT.h"
#include "tools\FunctionTables\FunctionTables.h"
#include <immintrin.h>

////////////////////////////////////////////////////
//	MATH FUNCTIONS
////////////////////////////////////////////////////

s32 ls_abs(s32 x)
{
	return (x < 0) ? x*(-1) : x;
}

f32 ls_abs(f32 x)
{
	return (x < 0.0f) ? x*(-1.0f) : x;
}

f32 rad(f32 x)
{
	return ((x*PI_32) / 180.0f);
}

f64 ls_sine(f64 x)
{
	b32 isNegative = (x > 0) ? FALSE : TRUE;
	f64 mappedX = x;

	if (isNegative)
	{
		while (mappedX < -(2.0f*PI_32))
		{
			mappedX += (2.0f*PI_32);
		}

		mappedX += 2.0f*PI_32;
	}
	else
	{
		while (mappedX > 2.0f*PI_32)
		{
			mappedX -= (2.0f*PI_32);
		}
	}

	f64 z = (mappedX - 3.1416f) / 1.8413f;

	f64 cube = z*z*z;
	f64 fifth = cube*z*z;
	f64 seventh = fifth*z*z;
	f64 ninth = seventh*z*z;

	f64 square = z*z;
	f64 fourth = square*square;
	f64 sixth = fourth*square;
	f64 eigth = fourth*fourth;
	f64 tenth = eigth*square;

	return (1.9252e-16*tenth) - (0.00052653*ninth) - (1.3721e-15*eigth) + (0.013847*seventh) + (3.344e-15*sixth)
		- (0.17589*fifth) - (3.0365e-15*fourth) + (1.0402*cube) + (1.6822e-16*square) - (1.8412*z) + (5.4606e-16);
}

f64 ls_asin(f64 x)
{
	if ((x < -1.0f) || (x > 1.0f))
		return 0;

	f64 z = (x + 7.2164e-17f) / 0.5817f;

	f64 cube = z*z*z;
	f64 fifth = cube*z*z;
	f64 seventh = fifth*z*z;
	f64 ninth = seventh*z*z;

	f64 square = z*z;
	f64 fourth = square*square;
	f64 sixth = fourth*square;
	f64 eigth = fourth*fourth;
	f64 tenth = eigth*square;

	return (1.6544e-15*tenth) + (0.024044*ninth) - (1.1741e-14*eigth) - (0.12358*seventh) + (2.9093e-14*sixth)
		+ (0.22158*fifth) - (2.938e-14*fourth) - (0.10393*cube) + (1.0267e-14*square) + (0.60425*z) - 6.3772e-16;
}

f64 ls_cos(f64 x)
{
	b32 isNegative = (x > 0) ? FALSE : TRUE;
	f64 mappedX = x;

	if (isNegative)
	{
		while (mappedX < -(2.0f*PI_32))
		{
			mappedX += (2.0f*PI_32);
		}
		mappedX += 2.0f*PI_32;
	}
	else
	{
		while (mappedX > 2.0f*PI_32)
		{
			mappedX -= (2.0f*PI_32);
		}
	}

	f64 z = (mappedX - 3.1416f) / 1.8413f;

	f64 cube = z*z*z;
	f64 fifth = cube*z*z;
	f64 seventh = fifth*z*z;
	f64 ninth = seventh*z*z;

	f64 square = z*z;
	f64 fourth = square*square;
	f64 sixth = fourth*square;
	f64 eigth = fourth*fourth;
	f64 tenth = eigth*square;

	return (9.9058e-05*tenth) - (2.4826e-16*ninth) - (0.0032018*eigth) + (1.475e-15*seventh) + (0.054013*sixth) 
		- (3.0717e-15*fifth) - (0.47883*fourth) + (2.9256e-15*cube) + (1.6951*square) - (1.5395e-15*z) - 1;
}

f64 ls_acos(f64 x)
{
	if ((x < -1.0f) || (x > 1.0f))
		return 0;

	f64 z = (x + 7.2164e-17f) / 0.5817f;

	f64 cube = z*z*z;
	f64 fifth = cube*z*z;
	f64 seventh = fifth*z*z;
	f64 ninth = seventh*z*z;

	f64 square = z*z;
	f64 fourth = square*square;
	f64 sixth = fourth*square;
	f64 eigth = fourth*fourth;
	f64 tenth = eigth*square;

	return -(2.3277e-15*tenth) - (0.024044*ninth) + (1.7628e-14*eigth) + (0.12358*seventh) - (4.6935e-14*sixth)
		- (0.22158*fifth) + (5.1126e-14*fourth) + (0.10393*cube) - (1.9655e-14*square) - (0.60425*z) + 1.5708;
}


f64 ls_tan(f64 x)
{
	return (ls_sine(x) / ls_cos(x));
}

//f64 ls_atan(f64 x)
//{
//	if (x > 4.0f) { return (f64)(PI_32 / 2.0f); }
//	if (x < -4.0f) { return (f64)(-PI_32 / 2.0f); }
//	
//	//[-4;4]
//	f64 z = (x + 2.8866e-16f) / 2.3268f;
//
//	//[-pi/2, pi/2]
//	//f64 z = (x - 1.0658e-16f) / 0.91373f;
//
//	//[-6, 6]
//	//f64 z = (x + 2.4869e-16) / 4.0719;
//
//	f64 cube = z*z*z;
//	f64 fifth = cube*z*z;
//	f64 seventh = fifth*z*z;
//	f64 ninth = seventh*z*z;
//
//	f64 square = z*z;
//	f64 fourth = square*square;
//	f64 sixth = fourth*square;
//	f64 eigth = fourth*fourth;
//	f64 tenth = eigth*square;
//
//	//[-pi/2; pi/2]
//	//return -(4.9113e-17*tenth) + (0.0021578*ninth) + (3.3292e-16*eigth) - (0.020435*seventh) - (8.1985e-16*sixth)
//	//	+ (0.084557*fifth) + (7.7802e-16*fourth) - (0.23796*cube) - (2.0129e-16*square) + (0.91182*z) + (1.209e-16);
//
//	//[-4;4]
//	return -(8.1227e-16*tenth) + (0.055954*ninth) + (6.0735e-15*eigth) - (0.44061*seventh) - (1.5317e-14*sixth)
//		+ (1.3053*fifth) + (1.489e-14*fourth) - (1.915*cube) - (4.731e-15*square) + (2.1475*z) + (7.9715e-18);
//
//	//[-6;6]
//	//return -(8.9202e-17*tenth) + (0.14909*ninth) - (1.4026e-16*eigth) - (1.13*seventh) + (2.155e-15*sixth)
//	//	+ (3.1309*fifth) - (4.1577e-15*fourth) - (4.0012*cube) + (2.4222e-15*square) + (3.1433*z) - (3.6934e-16);
//}

//This feels even worse
f64 ls_atan(f64 x)
{
	b32 isNegative = x < 0.0f ? TRUE : FALSE;
	if ((x > 10.00f) || (x < -10.00f))
	{
		if (isNegative) { return -arctan[1001]; }
		else { return arctan[1001]; }
	}

	f32 xValue = ls_abs((f32)x)*100.0f;
	if (isNegative) { return -arctan[(int)xValue]; }
	else { return arctan[(int)xValue]; }
}

f32 ls_sqrt(f32 x)
{
	__m128 Result = _mm_set_ps1(x);
	Result = _mm_rsqrt_ps(Result);

	return (1 / Result.m128_f32[0]);
}

////////////////////////////////////////////////////
//	STRING FUNCTIONS
////////////////////////////////////////////////////


s32 ls_len(char * string)
{
	int Result = 0;
	char *At = string;
	while (*At != 0)
	{
		Result++;
		At++;
	}

	return Result;
}

char * ls_itoa(s32 x)
{
	HANDLE HeapHandle = GetProcessHeap(); //@TODO: How to not do this?

	char *Result = 0;
	bool isNegative = false;
	u32 size = 0;
	int units = 0, e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0, e6 = 0;
	if (x < 0)
	{
		isNegative = true;
		x = ls_abs(x);
	}

	if ((x >= 1000000) && (x < 10000000)) { size = 8;  Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }
	else if ((x >= 100000) && (x < 1000000)) { size = 7;  Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }
	else if ((x >= 10000) && (x < 100000)) { size = 6; Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }
	else if ((x >= 1000) && (x < 10000)) { size = 5; Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }
	else if ((x >= 100) && (x < 1000)) { size = 4; Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }
	else if ((x >= 10) && (x < 100)) { size = 3; Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }
	else if (x < 10) { size = 2; Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size); }

	switch (size-1)
	{
		case 7:
			e6 = (int)(x / 1000000); x -= e6 * 1000000;
			e5 = (int)(x / 100000); x -= e5 * 100000;
			e4 = (int)(x / 10000); x -= e4 * 10000;
			e3 = (int)(x / 1000); x -= e3 * 1000;
			e2 = (int)(x / 100); x -= e2 * 100;
			e1 = (int)(x / 10); x -= e1 * 10;
			units = x;

			Result[0] = e6 + 48;
			Result[1] = e5 + 48;
			Result[2] = e4 + 48;
			Result[3] = e3 + 48;
			Result[4] = e2 + 48;
			Result[5] = e1 + 48;
			Result[6] = units + 48;
			Result[7] = 0;

			return Result;

		case 6:
			e5 = (int)(x / 100000); x -= e5 * 100000;
			e4 = (int)(x / 10000); x -= e4 * 10000;
			e3 = (int)(x / 1000); x -= e3 * 1000;
			e2 = (int)(x / 100); x -= e2 * 100;
			e1 = (int)(x / 10); x -= e1 * 10;
			units = x;

			Result[0] = e5 + 48;
			Result[1] = e4 + 48;
			Result[2] = e3 + 48;
			Result[3] = e2 + 48;
			Result[4] = e1 + 48;
			Result[5] = units + 48;
			Result[6] = 0;

			return Result;

		case 5:
			e4 = (int)(x / 10000); x -= e4 * 10000;
			e3 = (int)(x / 1000); x -= e3 * 1000;
			e2 = (int)(x / 100); x -= e2 * 100;
			e1 = (int)(x / 10); x -= e1 * 10;
			units = x;

			Result[0] = e4 + 48;
			Result[1] = e3 + 48;
			Result[2] = e2 + 48;
			Result[3] = e1 + 48;
			Result[4] = units + 48;
			Result[5] = 0;

			return Result;

		case 4:
			e3 = (int)(x / 1000); x -= e3 * 1000;
			e2 = (int)(x / 100); x -= e2 * 100;
			e1 = (int)(x / 10); x -= e1 * 10;
			units = x;

			Result[0] = e3 + 48;
			Result[1] = e2 + 48;
			Result[2] = e1 + 48;
			Result[3] = units + 48;
			Result[4] = 0;

			return Result;

		case 3:
			e2 = (int)(x / 100); x -= e2 * 100;
			e1 = (int)(x / 10); x -= e1 * 10;
			units = x;

			Result[0] = e2 + 48;
			Result[1] = e1 + 48;
			Result[2] = units + 48;
			Result[3] = 0;

			return Result;

		case 2:
			e1 = (int)(x / 10); x -= e1 * 10;
			units = x;

			Result[0] = e1 + 48;
			Result[1] = units + 48;
			Result[2] = 0;

			return Result;

		case 1:
			units = x;

			Result[0] = units + 48;
			Result[1] = 0;

			return Result;
	}

	return nullptr;
}

char * ls_ftoa(f32 x)
{
	HANDLE HeapHandle = GetProcessHeap();
	char *Result = 0;

	char *IntegerPart = ls_itoa((int)x);
	char *FractPart = 0;
	if (x < 1.0f)
	{
		s32 fractValue = s32((x + 1.0f) * 1000000);
		FractPart = ls_itoa(fractValue);
	}
	else if (x >= 10.0f)
	{
		f32 fixedX = (x - (int)x) + 1.0f;
		s32 fractValue = s32(fixedX * 1000000);
		FractPart = ls_itoa(fractValue);
	}
	else
	{
		s32 fractValue = s32(x * 1000000);
		FractPart = ls_itoa(fractValue);
	}

	BOOL hasSucceded = 0;

	if (x < 0)
	{
		char *Negative = ls_concat("-", IntegerPart, 0);
		char *Part1 = ls_concat(Negative, ".", 0);
		Result = ls_concat(Part1, FractPart + 1, 0);

		hasSucceded = HeapFree(HeapHandle, 0, Negative);
		Assert(hasSucceded);
		hasSucceded = HeapFree(HeapHandle, 0, Part1);
		Assert(hasSucceded);
	}
	else
	{
		char *Part1 = ls_concat(IntegerPart, ".", 0);
		Result = ls_concat(Part1, FractPart + 1, 0);

		hasSucceded = HeapFree(HeapHandle, 0, Part1);
		Assert(hasSucceded);
	}

	hasSucceded = HeapFree(HeapHandle, 0, IntegerPart);
	Assert(hasSucceded);
	hasSucceded = HeapFree(HeapHandle, 0, FractPart);
	Assert(hasSucceded);

	return Result;
}

char * ls_concat(char *string1, char *string2, b32 hasToFree)
{
	HANDLE HeapHandle = GetProcessHeap();

	char *Result = 0;
	int string1Len = ls_len(string1);
	int string2Len = ls_len(string2);

	int size = string1Len + string2Len;
	Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size+1);

	char *At = string1;
	int i = 0;
	while (i < string1Len)
	{
		Result[i] = *At;
		At++;
		i++;
	}
	int y = 0;
	At = string2;
	while (y <= string2Len)
	{
		Result[i] = *At;
		At++;
		y++;
		i++;
	}

	if (hasToFree)
	{
		BOOL hasSucceded = HeapFree(HeapHandle, 0, string1);
		Assert(hasSucceded);
		hasSucceded = HeapFree(HeapHandle, 0, string2);
		Assert(hasSucceded);
	}

	return Result;
}

s32 ls_strcmp(char *string1, char *string2)
{
	s32 string1Len = ls_len(string1);
	s32 string2Len = ls_len(string2);

	if (string1Len < string2Len)
	{
		return -1;
	}
	else if (string2Len < string1Len)
	{
		return 1;
	}
	else if (string1Len == string2Len)
	{
		char *At1 = string1;
		char *At2 = string2;

		b32 areSame = TRUE;
		while (string1Len && areSame)
		{
			if (*At1 != *At2)
			{
				areSame = FALSE;
			}
			
			At1++;
			At2++;
			string1Len--;
		}

		if (areSame == TRUE)
		{
			return 0;
		}
		else
		{
			//@TODO: Keep this like this? I don't know :(
			return 2;
		}
	}

	return 2;
}

s32 ls_strcpy(char *dest, char *src, bool nullTerminate)
{
	char *At = src;
	char *To = dest;

	s32 srcLen = ls_len(src);
	s32 c = 0;

	s32 it = srcLen;
	if (nullTerminate) { it += 1; }
	while (it--)
	{
		*To = *At;
		At++;
		To++;
		c++;
	}

	return c;
}

s32 ls_sprintf(char *dest, const char *format, ...)
{
	HANDLE HeapHandle = GetProcessHeap();

	char buff[1024] = {};
	const char *p = format;
	char *s = 0;

	s32 nInt = 0;
	f32 nFloat = 0.0f;

	va_list argList;
	va_start(argList, format);

	s32 i = 0;
	for (p = format; *p != 0; p++)
	{
		if (*p != '%')
		{
			buff[i] = *p;
			i++;
			continue;
		}

		switch (*++p)
		{
			case 'd':
				nInt = va_arg(argList, s32);
				s = ls_itoa(nInt);
				i += ls_strcpy(buff + i, s, 0);
				HeapFree(HeapHandle, 0, s);
				break;

			case 'f':
				nFloat = (f32)va_arg(argList, f64);
				s = ls_ftoa(nFloat);
				i += ls_strcpy(buff + i, s, 0);
				HeapFree(HeapHandle, 0, s);
				break;
			
			case '%':
				buff[i] = '%';
				i++;
				break;
		}
	}
	va_end(argList);

	buff[i] = 0;
	i++;
	ls_memcpy(buff, dest, i);

	return i;
}

////////////////////////////////////////////////////
//	MEMORY FUNCTIONS
////////////////////////////////////////////////////


void ls_memcpy(void *src, void *dest, size_t size)
{
	char *At = (char *)src;
	char *To = (char *)dest;
	
	size_t it = size;
	while (it--)
	{
		*To = *At;
		At++;
		To++;
	}
}

//@TODO: Move to proper files for logging system
void LogErrori_(char* Message, s32 Error)
{
	HANDLE HeapHandle = GetProcessHeap();

	char *toString = ls_itoa(Error);
	char *ErrorString = ls_concat(Message, toString, 0);
	HeapFree(HeapHandle, 0, toString);
	OutputDebugStringA(ErrorString);
	HeapFree(HeapHandle, 0, ErrorString);
}

void LogErrorf_(char* Message, f32 Error)
{
	HANDLE HeapHandle = GetProcessHeap();

	char *toString = ls_ftoa(Error);
	char *ErrorString = ls_concat(Message, toString, 0);
	HeapFree(HeapHandle, 0, toString);
	OutputDebugStringA(ErrorString);
	HeapFree(HeapHandle, 0, ErrorString);
}