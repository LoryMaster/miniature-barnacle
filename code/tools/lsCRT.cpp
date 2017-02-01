#include "tools\lsCRT.h"
#include <immintrin.h>

////////////////////////////////////////////////////
//	MATH FUNCTIONS
////////////////////////////////////////////////////

s32 ls_abs(s32 x)
{
	return (x < 0) ? x*(-1) : x;
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

f64 ls_tan(f64 x)
{
	return (ls_sine(x) / ls_cos(x));
}

f32 ls_sqrt(f32 x)
{
	__m128 Result = _mm_set_ps(x, x, x, x);
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
	int units = 0, tens = 0, hundreds = 0, thousands = 0, tensOfThousands = 0;
	if (x < 0)
	{
		isNegative = true;
		x = ls_abs(x);
	}
	if ((x >= 10000) && (x < 100000))
	{
		tensOfThousands = x;
		while ((tensOfThousands % 10000) != 0)
		{
			tensOfThousands--;
		}
		thousands = x - tensOfThousands;
		while ((thousands % 1000) != 0)
		{
			thousands--;
		}
		hundreds = x - tensOfThousands - thousands;
		while ((hundreds % 100) != 0)
		{
			hundreds--;
		}
		tens = x - tensOfThousands - thousands - hundreds;

		while ((tens % 10) != 0)
		{
			tens--;
		}
		units = x - tensOfThousands - thousands - hundreds - tens;
		tensOfThousands /= 10000;
		thousands /= 1000;
		hundreds /= 100;
		tens /= 10;



		Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 5);
		Assert(Result != NULL);
		Result[0] = tensOfThousands + 48;
		Result[1] = thousands + 48;
		Result[2] = hundreds + 48;
		Result[3] = tens + 48;
		Result[4] = units + 48;

		return Result;
	}
	if ((x >= 1000) && (x < 10000))
	{
		thousands = x;
		while ((thousands % 1000) != 0)
		{
			thousands--;
		}
		hundreds = x - thousands;
		while ((hundreds % 100) != 0)
		{
			hundreds--;
		}
		tens = x - thousands - hundreds;

		while ((tens % 10) != 0)
		{
			tens--;
		}
		units = x - thousands - hundreds - tens;
		thousands /= 1000;
		hundreds /= 100;
		tens /= 10;



		Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 4);
		Assert(Result != NULL);
		Result[0] = thousands + 48;
		Result[1] = hundreds + 48;
		Result[2] = tens + 48;
		Result[3] = units + 48;

		return Result;
	}
	if ((x >= 100) && (x < 1000))
	{
		hundreds = x;
		while ((hundreds % 100) != 0)
		{
			hundreds--;
		}
		tens = x - hundreds;

		while ((tens % 10) != 0)
		{
			tens--;
		}
		units = x - hundreds - tens;
		hundreds /= 100;
		tens /= 10;
		
		

		Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 3);
		Assert(Result != NULL);
		Result[0] = hundreds + 48;
		Result[1] = tens + 48;
		Result[2] = units + 48;

		return Result;
	}

	if ((x >= 10) && (x < 100))
	{
		tens = x;
		while ((tens % 10) != 0)
		{
			tens--;
		}
		units = x - tens;
		tens /= 10;
		

		Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 2);
		Assert(Result != NULL);
		Result[0] = tens + 48;
		Result[1] = units + 48;

		return Result;
	}
	else if(x < 10)
	{
		units = x;
		Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 1);
		Assert(Result != NULL);
		Result[0] = units + 48;

		return Result;
	}

	return nullptr;
}

char * ls_concat(char *string1, char *string2, b32 hasToFree)
{
	HANDLE HeapHandle = GetProcessHeap();

	char *Result = 0;
	int string1Len = ls_len(string1);
	int string2Len = ls_len(string2);

	int size = string1Len + string2Len;
	Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, size);

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
void LogError_(char* Message, s32 Error)
{
	HANDLE HeapHandle = GetProcessHeap();

	char *toString = ls_itoa(Error);
	char* ErrorString = ls_concat(Message, toString, 0);
	HeapFree(HeapHandle, 0, toString);
	OutputDebugStringA(ErrorString);
	HeapFree(HeapHandle, 0, ErrorString);
}