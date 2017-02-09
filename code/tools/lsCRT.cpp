#include "tools\lsCRT.h"
#include <immintrin.h>

////////////////////////////////////////////////////
//	MATH FUNCTIONS
////////////////////////////////////////////////////

s32 ls_abs(s32 x)
{
	return (x < 0) ? x*(-1) : x;
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

f64 ls_atan(f64 x)
{
	b32 isNegative = (x > 0) ? FALSE : TRUE;
	f64 mappedX = x;

	if (isNegative)
	{
		while (mappedX < -(PI_32/2))
		{
			mappedX += PI_32;
		}
	}
	else
	{
		while (mappedX > PI_32/2)
		{
			mappedX -= PI_32;
		}
	}

	f64 z = (mappedX - 1.0658e-16f) / 0.91373f;

	f64 cube = z*z*z;
	f64 fifth = cube*z*z;
	f64 seventh = fifth*z*z;
	f64 ninth = seventh*z*z;

	f64 square = z*z;
	f64 fourth = square*square;
	f64 sixth = fourth*square;
	f64 eigth = fourth*fourth;
	f64 tenth = eigth*square;

	return -(4.9113e-17*tenth) + (0.0021578*ninth) + (3.3292e-16*eigth) - (0.020435*seventh) - (8.1985e-16*sixth)
		+ (0.084557*fifth) + (7.7802e-16*fourth) - (0.23796*cube) - (2.0129e-16*square) + (0.91182*z) + (1.209e-16);
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

//@NOTE: Figured this is waaay too overcomplicated for a proper float conversion to string. let's just integer divide a couple of times.
// But it was fun to understand and solve these problems. Anyway, I solved it, so I'm happy about that :D
//char * ls_ftoa(f32 x)
//{
//	HANDLE HeapHandle = GetProcessHeap();
//
//	// Probably can even remove this memcpy. Gonna keep it for now!
//	u32 floatMemory = 0;
//	ls_memcpy((void *)(&x), (void *)&floatMemory, 4);
//	
//	char *Result = 0;
//	u8 *At = (u8 *)(&floatMemory) + 3;
//	u8 Sign = (*At >> 7) & 1u;
//
//	At = (u8 *)(&floatMemory) + 2;
//	u8 LastExpBit = (*At >> 7) & 1u;
//
//	At = (u8 *)(&floatMemory) + 3;
//	s8 Exponent = (*At << 1);
//	Exponent |= LastExpBit << 0;
//	Exponent -= 127;
//
//	u32 Mantissa = 0;
//
//	//Byte 3 of the mantissa minus bit 7
//	u8 *ManAt = (u8 *)(&Mantissa) + 3;
//	At = (u8 *)(&floatMemory) + 2;
//	*ManAt = (*At << 1);
//	
//	// Adding bit 7 to byte 3
//	At = (u8 *)(&floatMemory) + 1;
//	*ManAt |= (*At >> 7) << 0;
//
//	//Byte 2 of the mantissa minus bit 15
//	ManAt = (u8 *)(&Mantissa) + 2;
//	At = (u8 *)(&floatMemory) + 1;
//	*ManAt = (*At << 1);
//
//	// Adding bit 15 to byte 2
//	At = (u8 *)(&floatMemory);
//	*ManAt |= (*At >> 7) << 0;
//
//	//Byte 1 of the mantissa 
//	ManAt = (u8 *)(&Mantissa) + 1;
//	At = (u8 *)(&floatMemory);
//	*ManAt = (*At << 1);
//
//	//
//	// Return Value in case we have negative or positive zero
//	//
//	if ((Exponent == -127) && (Mantissa == 0))
//	{
//		if(Sign == 0) 
//		{ 
//			Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 3); 
//			Result[0] = 48;
//			Result[1] = '.';
//			Result[2] = 48;
//			return Result;
//		}
//		else
//		{
//			Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 4);
//			Result[0] = '-';
//			Result[1] = 48;
//			Result[2] = '.';
//			Result[3] = 48;
//			return Result;
//		}
//	}
//
//	//
//	// @NOTE: I'm not gonna return values for denormalized numbers (don't really see the point for my uses)
//	//
//
//	//
//	// Return Value in case we have an infinite
//	//
//	if ((Exponent == 128) && (Mantissa == 0))
//	{
//		if (Sign == 0)
//		{
//			Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 5);
//			Result[0] = '+';
//			Result[1] = 'i';
//			Result[2] = 'n';
//			Result[3] = 'f';
//			Result[4] = '.';
//			return Result;
//		}
//		else
//		{
//			Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 5);
//			Result[0] = '-';
//			Result[1] = 'i';
//			Result[2] = 'n';
//			Result[3] = 'f';
//			Result[4] = '.';
//			return Result;
//		}
//	}
//
//	//
//	// Return Value in case we have a NaN
//	//
//
//	if ((Exponent == 128) && (Mantissa != 0))
//	{
//		Result = (char *)HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, 3);
//		Result[0] = 'N';
//		Result[1] = 'a';
//		Result[2] = 'N';
//		return Result;
//	}
//
//	//
//	// Return Value for classical, boring Normalized Numbers
//	//
//
//	return 0;
//}

char * ls_ftoa(f32 x)
{
	HANDLE HeapHandle = GetProcessHeap();
	char *Result = 0;

	char *IntegerPart = ls_itoa((int)x);
	s32 fractValue = s32(x * 1000000 - ((s32)x * 1000000));
	char *FractPart = ls_itoa(fractValue);

	BOOL hasSucceded = 0;

	if (x < 0)
	{
		char *Negative = ls_concat("-", IntegerPart, 0);
		char *Part1 = ls_concat(Negative, ".", 0);
		Result = ls_concat(Part1, FractPart, 0);

		hasSucceded = HeapFree(HeapHandle, 0, Negative);
		Assert(hasSucceded);
		hasSucceded = HeapFree(HeapHandle, 0, Part1);
		Assert(hasSucceded);
	}
	else
	{
		char *Part1 = ls_concat(IntegerPart, ".", 0);
		Result = ls_concat(Part1, FractPart, 0);

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
	char* ErrorString = ls_concat(Message, toString, 0);
	HeapFree(HeapHandle, 0, toString);
	OutputDebugStringA(ErrorString);
	HeapFree(HeapHandle, 0, ErrorString);
}

void LogErrorf_(char* Message, f32 Error)
{
	HANDLE HeapHandle = GetProcessHeap();

	char *toString = ls_ftoa(Error);
	char* ErrorString = ls_concat(Message, toString, 0);
	HeapFree(HeapHandle, 0, toString);
	OutputDebugStringA(ErrorString);
	HeapFree(HeapHandle, 0, ErrorString);
}