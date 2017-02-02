#include "tools\Maths\Maths.h"

///////////////////////////////////////////
// VECTOR DEFINITIONS
///////////////////////////////////////////

v2	vec2(f32 x, f32 y)
{
	v2 Result = { x, y };
	return Result;
}

v3	vec3(f32 x, f32 y, f32 z)
{
	v3 Result = { x, y, z };
	return Result;
}

v4	vec4(f32 x, f32 y, f32 z, f32 w)
{
	v4 Result = { x, y, z, w };
	return Result;
}

v2i vec2(s32 x, s32 y)
{
	v2i Result = { x, y };
	return Result;
}

v3i vec3(s32 x, s32 y, s32 z)
{
	v3i Result = { x, y, z };
	return Result;
}

v4i vec4(s32 x, s32 y, s32 z, s32 w)
{
	v4i Result = { x, y, z, w };
	return Result;
}

v2 V2(v3 v)
{
	v2 Result = { v.x, v.y };
	return Result;
}

v3 V3(v4 v)
{
	v3 Result = { v.x, v.y, v.z };
	return Result;
}

v4 V4(v3 v)
{
	v4 Result = { v.x, v.y, v.z, 1.0f };
	return Result;
}

///////////////////////////////////////////
// VECTOR OPERATORS
///////////////////////////////////////////

f32 Length(v2 v)
{
	f32 Result = ls_sqrt((v.x*v.x) + (v.y*v.y));
	return Result;
}

f32 Length(v3 v)
{
	f32 Result = ls_sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
	return Result;
}

f32 Length(v4 v)
{
	f32 Result = ls_sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w));
	return Result;
}

f32 Length(v2i v)
{
	f32 Result = ls_sqrt((f32)(v.x*v.x) + (f32)(v.y*v.y));
	return Result;
}

f32 Length(v3i v)
{
	f32 Result = ls_sqrt((f32)(v.x*v.x) + (f32)(v.y*v.y) + (f32)(v.z*v.z));
	return Result;
}

f32 Length(v4i v)
{
	f32 Result = ls_sqrt((f32)(v.x*v.x) + (f32)(v.y*v.y) + (f32)(v.z*v.z) + (f32)(v.w*v.w));
	return Result;
}

v2 Normalize(v2 v)
{
	f32 L = Length(v);
	v2 Result = { v.x / L, v.y / L };

	return Result;
}

v3	Normalize(v3 v)
{
	f32 L = Length(v);
	v3 Result = { v.x / L, v.y / L, v.z / L };

	return Result;
}

v4	Normalize(v4 v)
{
	f32 L = Length(v);
	v4 Result = { v.x / L, v.y / L, v.z / L, v.w / L};

	return Result;
}

v2 Normalize(v2i v)
{
	f32 L = Length(v);
	v2 Result = { v.x / L, v.y / L };

	return Result;
}

v3 Normalize(v3i v)
{
	f32 L = Length(v);
	v3 Result = { v.x / L, v.y / L, v.z / L };

	return Result;
}

v4 Normalize(v4i v)
{
	f32 L = Length(v);
	v4 Result = { v.x / L, v.y / L, v.z / L, v.w / L };

	return Result;
}

v2	operator+(v2 v, v2 u)
{
	v2 Result = { v.x + u.x, v.y + u.y };
	return Result;
}

v3	operator+(v3 v, v3 u)
{
	v3 Result = { v.x + u.x, v.y + u.y, v.z + u.z };
	return Result;
}

v4	operator+(v4 v, v4 u)
{
	v4 Result = { v.x + u.x, v.y + u.y, v.z + u.z, v.w + u.w };
	return Result;
}

v2i operator+(v2i v, v2i u)
{
	v2i Result = { v.x + u.x, v.y + u.y };
	return Result;
}

v3i	operator+(v3i v, v3i u)
{
	v3i Result = { v.x + u.x, v.y + u.y, v.z + u.z };
	return Result;
}

v4i	operator+(v4i v, v4i u)
{
	v4i Result = { v.x + u.x, v.y + u.y, v.z + u.z, v.w + u.w };
	return Result;
}

v2	operator-(v2 v, v2 u)
{
	v2 Result = { v.x - u.x, v.y - u.y };
	return Result;
}

v3	operator-(v3 v, v3 u)
{
	v3 Result = { v.x - u.x, v.y - u.y, v.z - u.z };
	return Result;
}

v4	operator-(v4 v, v4 u)
{
	v4 Result = { v.x - u.x, v.y - u.y, v.z - u.z, v.w - u.w };
	return Result;
}

v2i operator-(v2i v, v2i u)
{
	v2i Result = { v.x - u.x, v.y - u.y };
	return Result;
}

v3i	operator-(v3i v, v3i u)
{
	v3i Result = { v.x - u.x, v.y - u.y, v.z - u.z };
	return Result;
}

v4i	operator-(v4i v, v4i u)
{
	v4i Result = { v.x - u.x, v.y - u.y, v.z - u.z, v.w - u.w };
	return Result;
}

v2	operator*(v2 v, f32 value)
{
	v2 Result = { v.x * value, v.y * value };
	return Result;
}

v3	operator*(v3 v, f32 value)
{
	v3 Result = { v.x * value, v.y * value, v.z * value };
	return Result;
}

v4	operator*(v4 v, f32 value)
{
	v4 Result = { v.x * value, v.y * value, v.z * value, v.w * value };
	return Result;
}

f32	operator*(v2 v, v2 u)
{
	return (v.x * u.x) + (v.y * u.y);
}

f32	operator*(v3 v, v3 u)
{
	return (v.x * u.x) + (v.y * u.y) + (v.z * u.z);
}

f32	operator*(v4 v, v4 u)
{
	return (v.x * u.x) + (v.y * u.y) + (v.z * u.z) + (v.w * u.w);
}

f32 operator*(v2i v, v2i u)
{
	return (f32)(v.x * u.x) + (v.y * u.y);
}

f32	operator*(v3i v, v3i u)
{
	return (f32)(v.x * u.x) + (v.y * u.y) + (v.z * u.z);
}

f32	operator*(v4i v, v4i u)
{
	return (f32)(v.x * u.x) + (v.y * u.y) + (v.z * u.z) + (v.w * u.w);
}

v3	operator^(v3 v, v3 u)
{
	v3 Result = {};
	Result.x = (v.y*u.z) - (v.z*u.y);
	Result.y = (v.z*u.x) - (v.x*u.z);
	Result.z = (v.x*u.y) - (v.y*u.x);

	return Result;
}

v3i	operator^(v3i v, v3i u)
{
	v3i Result = {};
	Result.x = (v.y*u.z) - (v.z*u.y);
	Result.y = (v.z*u.x) - (v.x*u.z);
	Result.z = (v.x*u.y) - (v.y*u.x);

	return Result;
}

///////////////////////////////////////////
// MATRIX OPERATIONS
///////////////////////////////////////////

Mat2 operator+(f32 value, Mat2 M)
{
	Mat2 Result = 
	{ 
		M.values[0][0] + value, 
		M.values[0][1] + value,
		M.values[1][0] + value,
		M.values[1][1] + value
	};

	return Result;
}

Mat2 operator+(Mat2 m1, Mat2 m2)
{
	Mat2 Result =
	{
		m1.values[0][0] + m2.values[0][0],
		m1.values[0][1] + m2.values[0][1],
		m1.values[1][0] + m2.values[1][0],
		m1.values[1][1] + m2.values[1][1]
	};

	return Result;
}

Mat3 operator+(f32 value, Mat3 M)
{
	Mat3 Result =
	{
		M.values[0][0] + value,
		M.values[0][1] + value,
		M.values[0][2] + value,
		M.values[1][0] + value,
		M.values[1][1] + value,
		M.values[1][2] + value,
		M.values[2][0] + value,
		M.values[2][1] + value,
		M.values[2][2] + value
	};

	return Result;
}

Mat3 operator+(Mat3 m1, Mat3 m2)
{
	Mat3 Result =
	{
		m1.values[0][0] + m2.values[0][0],
		m1.values[0][1] + m2.values[0][1],
		m1.values[0][2] + m2.values[0][2],
		m1.values[1][0] + m2.values[1][0],
		m1.values[1][1] + m2.values[1][1],
		m1.values[1][2] + m2.values[1][2],
		m1.values[2][0] + m2.values[2][0],
		m1.values[2][1] + m2.values[2][1],
		m1.values[2][2] + m2.values[2][2]
	};

	return Result;
}

Mat4 operator+(f32 value, Mat4 M)
{
	Mat4 Result =
	{
		M.values[0][0] + value,
		M.values[0][1] + value,
		M.values[0][2] + value,
		M.values[0][3] + value,
		M.values[1][0] + value,
		M.values[1][1] + value,
		M.values[1][2] + value,
		M.values[1][3] + value,
		M.values[2][0] + value,
		M.values[2][1] + value,
		M.values[2][2] + value,
		M.values[2][3] + value,
		M.values[3][0] + value,
		M.values[3][1] + value,
		M.values[3][2] + value,
		M.values[3][3] + value
	};

	return Result;
}

Mat4 operator+(Mat4 m1, Mat4 m2)
{
	Mat4 Result =
	{
		m1.values[0][0] + m2.values[0][0],
		m1.values[0][1] + m2.values[0][1],
		m1.values[0][2] + m2.values[0][2],
		m1.values[0][3] + m2.values[0][3],
		m1.values[1][0] + m2.values[1][0],
		m1.values[1][1] + m2.values[1][1],
		m1.values[1][2] + m2.values[1][2],
		m1.values[1][3] + m2.values[1][3],
		m1.values[2][0] + m2.values[2][0],
		m1.values[2][1] + m2.values[2][1],
		m1.values[2][2] + m2.values[2][2],
		m1.values[2][3] + m2.values[2][3],
		m1.values[3][0] + m2.values[3][0],
		m1.values[3][1] + m2.values[3][1],
		m1.values[3][2] + m2.values[3][2],
		m1.values[3][3] + m2.values[3][3]
	};

	return Result;
}

Mat2 operator-(f32 value, Mat2 M)
{
	Mat2 Result =
	{
		M.values[0][0] - value,
		M.values[0][1] - value,
		M.values[1][0] - value,
		M.values[1][1] - value
	};

	return Result;
}

Mat2 operator-(Mat2 m1, Mat2 m2)
{
	Mat2 Result =
	{
		m1.values[0][0] - m2.values[0][0],
		m1.values[0][1] - m2.values[0][1],
		m1.values[1][0] - m2.values[1][0],
		m1.values[1][1] - m2.values[1][1]
	};

	return Result;
}

Mat3 operator-(f32 value, Mat3 M)
{
	Mat3 Result =
	{
		M.values[0][0] - value,
		M.values[0][1] - value,
		M.values[0][2] - value,
		M.values[1][0] - value,
		M.values[1][1] - value,
		M.values[1][2] - value,
		M.values[2][0] - value,
		M.values[2][1] - value,
		M.values[2][2] - value
	};

	return Result;
}

Mat3 operator-(Mat3 m1, Mat3 m2) 
{
	Mat3 Result =
	{
		m1.values[0][0] - m2.values[0][0],
		m1.values[0][1] - m2.values[0][1],
		m1.values[0][2] - m2.values[0][2],
		m1.values[1][0] - m2.values[1][0],
		m1.values[1][1] - m2.values[1][1],
		m1.values[1][2] - m2.values[1][2],
		m1.values[2][0] - m2.values[2][0],
		m1.values[2][1] - m2.values[2][1],
		m1.values[2][2] - m2.values[2][2]
	};

	return Result;
}

Mat4 operator-(f32 value, Mat4 M)
{
	Mat4 Result =
	{
		M.values[0][0] - value,
		M.values[0][1] - value,
		M.values[0][2] - value,
		M.values[0][3] - value,
		M.values[1][0] - value,
		M.values[1][1] - value,
		M.values[1][2] - value,
		M.values[1][3] - value,
		M.values[2][0] - value,
		M.values[2][1] - value,
		M.values[2][2] - value,
		M.values[2][3] - value,
		M.values[3][0] - value,
		M.values[3][1] - value,
		M.values[3][2] - value,
		M.values[3][3] - value
	};

	return Result;
}

Mat4 operator-(Mat4 m1, Mat4 m2)
{
	Mat4 Result =
	{
		m1.values[0][0] - m2.values[0][0],
		m1.values[0][1] - m2.values[0][1],
		m1.values[0][2] - m2.values[0][2],
		m1.values[0][3] - m2.values[0][3],
		m1.values[1][0] - m2.values[1][0],
		m1.values[1][1] - m2.values[1][1],
		m1.values[1][2] - m2.values[1][2],
		m1.values[1][3] - m2.values[1][3],
		m1.values[2][0] - m2.values[2][0],
		m1.values[2][1] - m2.values[2][1],
		m1.values[2][2] - m2.values[2][2],
		m1.values[2][3] - m2.values[2][3],
		m1.values[3][0] - m2.values[3][0],
		m1.values[3][1] - m2.values[3][1],
		m1.values[3][2] - m2.values[3][2],
		m1.values[3][3] - m2.values[3][3]
	};

	return Result;
}

Mat2 operator*(f32 value, Mat2 M)
{
	Mat2 Result =
	{
		M.values[0][0] * value,
		M.values[0][1] * value,
		M.values[1][0] * value,
		M.values[1][1] * value
	};

	return Result;
}

Mat2 operator*(Mat2 m1, Mat2 m2)
{
	Mat2 Result =
	{
		(m1.values[0][0] * m2.values[0][0]) + (m1.values[0][1] * m2.values[1][0]),
		(m1.values[0][0] * m2.values[0][1]) + (m1.values[0][1] * m2.values[1][1]),
		
		(m1.values[1][0] * m2.values[0][0]) + (m1.values[1][1] * m2.values[1][0]),
		(m1.values[1][0] * m2.values[0][1]) + (m1.values[1][1] * m2.values[1][1])
	};

	return Result;
}

Mat3 operator*(f32 value, Mat3 M)
{
	Mat3 Result =
	{
		M.values[0][0] * value,
		M.values[0][1] * value,
		M.values[0][2] * value,
		M.values[1][0] * value,
		M.values[1][1] * value,
		M.values[1][2] * value,
		M.values[2][0] * value,
		M.values[2][1] * value,
		M.values[2][2] * value
	};

	return Result;
}

Mat3 operator*(Mat3 m1, Mat3 m2)
{
	Mat3 Result =
	{
		(m1.values[0][0] * m2.values[0][0]) + (m1.values[0][1] * m2.values[1][0]) + (m1.values[0][2] * m2.values[2][0]),
		(m1.values[0][0] * m2.values[0][1]) + (m1.values[0][1] * m2.values[1][1]) + (m1.values[0][2] * m2.values[2][1]),
		(m1.values[0][0] * m2.values[0][2]) + (m1.values[0][1] * m2.values[1][2]) + (m1.values[0][2] * m2.values[2][2]),
		
		(m1.values[1][0] * m2.values[0][0]) + (m1.values[1][1] * m2.values[1][0]) + (m1.values[1][2] * m2.values[2][0]),
		(m1.values[1][0] * m2.values[0][1]) + (m1.values[1][1] * m2.values[1][1]) + (m1.values[1][2] * m2.values[2][1]),
		(m1.values[1][0] * m2.values[0][2]) + (m1.values[1][1] * m2.values[1][2]) + (m1.values[1][2] * m2.values[2][2]),
		
		(m1.values[2][0] * m2.values[0][0]) + (m1.values[2][1] * m2.values[1][0]) + (m1.values[2][2] * m2.values[2][0]),
		(m1.values[2][0] * m2.values[0][1]) + (m1.values[2][1] * m2.values[1][1]) + (m1.values[2][2] * m2.values[2][1]),
		(m1.values[2][0] * m2.values[0][2]) + (m1.values[2][1] * m2.values[1][2]) + (m1.values[2][2] * m2.values[2][2])
	};

	return Result;
}

Mat4 operator*(f32 value, Mat4 M)
{
	Mat4 Result =
	{
		M.values[0][0] * value,
		M.values[0][1] * value,
		M.values[0][2] * value,
		M.values[0][3] * value,
		M.values[1][0] * value,
		M.values[1][1] * value,
		M.values[1][2] * value,
		M.values[1][3] * value,
		M.values[2][0] * value,
		M.values[2][1] * value,
		M.values[2][2] * value,
		M.values[2][3] * value,
		M.values[3][0] * value,
		M.values[3][1] * value,
		M.values[3][2] * value,
		M.values[3][3] * value
	};

	return Result;
}

Mat4 operator*(Mat4 m1, Mat4 m2)
{
	Mat4 Result =
	{
		(m1.values[0][0] * m2.values[0][0]) + (m1.values[0][1] * m2.values[1][0]) + (m1.values[0][2] * m2.values[2][0]) + (m1.values[0][3] * m2.values[3][0]),
		(m1.values[0][0] * m2.values[0][1]) + (m1.values[0][1] * m2.values[1][1]) + (m1.values[0][2] * m2.values[2][1]) + (m1.values[0][3] * m2.values[3][1]),
		(m1.values[0][0] * m2.values[0][2]) + (m1.values[0][1] * m2.values[1][2]) + (m1.values[0][2] * m2.values[2][2]) + (m1.values[0][3] * m2.values[3][2]),
		(m1.values[0][0] * m2.values[0][3]) + (m1.values[0][1] * m2.values[1][3]) + (m1.values[0][2] * m2.values[2][3]) + (m1.values[0][3] * m2.values[3][3]),
		
		(m1.values[1][0] * m2.values[0][0]) + (m1.values[1][1] * m2.values[1][0]) + (m1.values[1][2] * m2.values[2][0]) + (m1.values[1][3] * m2.values[3][0]),
		(m1.values[1][0] * m2.values[0][1]) + (m1.values[1][1] * m2.values[1][1]) + (m1.values[1][2] * m2.values[2][1]) + (m1.values[1][3] * m2.values[3][1]),
		(m1.values[1][0] * m2.values[0][2]) + (m1.values[1][1] * m2.values[1][2]) + (m1.values[1][2] * m2.values[2][2]) + (m1.values[1][3] * m2.values[3][2]),
		(m1.values[1][0] * m2.values[0][3]) + (m1.values[1][1] * m2.values[1][3]) + (m1.values[1][2] * m2.values[2][3]) + (m1.values[1][3] * m2.values[3][3]),
		
		(m1.values[2][0] * m2.values[0][0]) + (m1.values[2][1] * m2.values[1][0]) + (m1.values[2][2] * m2.values[2][0]) + (m1.values[2][3] * m2.values[3][0]),
		(m1.values[2][0] * m2.values[0][1]) + (m1.values[2][1] * m2.values[1][1]) + (m1.values[2][2] * m2.values[2][1]) + (m1.values[2][3] * m2.values[3][1]),
		(m1.values[2][0] * m2.values[0][2]) + (m1.values[2][1] * m2.values[1][2]) + (m1.values[2][2] * m2.values[2][2]) + (m1.values[2][3] * m2.values[3][2]),
		(m1.values[2][0] * m2.values[0][3]) + (m1.values[2][1] * m2.values[1][3]) + (m1.values[2][2] * m2.values[2][3]) + (m1.values[2][3] * m2.values[3][3]),
		
		(m1.values[3][0] * m2.values[0][0]) + (m1.values[3][1] * m2.values[1][0]) + (m1.values[3][2] * m2.values[2][0]) + (m1.values[3][3] * m2.values[3][0]),
		(m1.values[3][0] * m2.values[0][1]) + (m1.values[3][1] * m2.values[1][1]) + (m1.values[3][2] * m2.values[2][1]) + (m1.values[3][3] * m2.values[3][1]),
		(m1.values[3][0] * m2.values[0][2]) + (m1.values[3][1] * m2.values[1][2]) + (m1.values[3][2] * m2.values[2][2]) + (m1.values[3][3] * m2.values[3][2]),
		(m1.values[3][0] * m2.values[0][3]) + (m1.values[3][1] * m2.values[1][3]) + (m1.values[3][2] * m2.values[2][3]) + (m1.values[3][3] * m2.values[3][3])
	};

	return Result;
}

v2 operator*(Mat2 m, v2 v)
{
	v2 Result =
	{
		(m.values[0][0] * v.x) + (m.values[0][1] * v.y),
		
		(m.values[1][0] * v.x) + (m.values[1][1] * v.y)
	};

	return Result;
}

v3 operator*(Mat3 m, v3 v)
{
	v3 Result =
	{
		(m.values[0][0] * v.x) + (m.values[0][1] * v.y) + (m.values[0][2] * v.z),
		
		(m.values[1][0] * v.x) + (m.values[1][1] * v.y) + (m.values[1][2] * v.z),
		
		(m.values[2][0] * v.x) + (m.values[2][1] * v.y) + (m.values[2][2] * v.z)
	};

	return Result;
}

v4 operator*(Mat4 m, v4 v)
{
	v4 Result =
	{
		(m.values[0][0] * v.x) + (m.values[0][1] * v.y) + (m.values[0][2] * v.z) + (m.values[0][3] * v.w),
		
		(m.values[1][0] * v.x) + (m.values[1][1] * v.y) + (m.values[1][2] * v.z) + (m.values[1][3] * v.w),
		
		(m.values[2][0] * v.x) + (m.values[2][1] * v.y) + (m.values[2][2] * v.z) + (m.values[2][3] * v.w),

		(m.values[3][0] * v.x) + (m.values[3][1] * v.y) + (m.values[3][2] * v.z) + (m.values[3][3] * v.w)
	};

	return Result;
}

Mat2 Identity2()
{
	Mat2 Result = { 1, 0, 0, 1 };
	return Result;
}

Mat3 Identity3()
{
	Mat3 Result = {};
	Result.values[0][0] = 1;
	Result.values[1][1] = 1;
	Result.values[2][2] = 1;

	return Result;
}

Mat4 Identity4()
{
	Mat4 Result = {};
	Result.values[0][0] = 1;
	Result.values[1][1] = 1;
	Result.values[2][2] = 1;
	Result.values[3][3] = 1;

	return Result;
}

Mat2 UniformScale2(f32 factor)
{
	Mat2 Result = Identity2();
	Result = factor * Result;

	return Result;
}

Mat3 UniformScale3(f32 factor)
{
	Mat3 Result = Identity3();
	Result = factor * Result;

	return Result;
}

Mat4 UniformScale4(f32 factor)
{
	Mat4 Result = Identity4();
	Result = factor * Result;

	return Result;
}

Mat2 Scale(v2 v)
{
	Mat2 Result = Identity2();
	Result.values[0][0] = v.x;
	Result.values[1][1] = v.y;

	return Result;
}

Mat3 Scale(v3 v)
{
	Mat3 Result = Identity3();
	Result.values[0][0] = v.x;
	Result.values[1][1] = v.y;
	Result.values[2][2] = v.z;

	return Result;
}

Mat4 Scale(v4 v)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = v.x;
	Result.values[1][1] = v.y;
	Result.values[2][2] = v.z;
	Result.values[3][3] = v.w;

	return Result;
}

Mat4 Translate(v4 v)
{
	Mat4 Result = Identity4();
	Result.values[0][3] = v.x;
	Result.values[1][3] = v.y;
	Result.values[2][3] = v.z;
	Result.values[3][3] = v.w;

	return Result;
}

///////////////////////////////////////////
// MATRIX BAD ROTATION (WANT QUATERNIONS D=)
///////////////////////////////////////////

Mat4 RotateX(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[1][1] = (f32)ls_cos(Angle);
	Result.values[2][2] = (f32)ls_cos(Angle);
	Result.values[1][2] = (f32)-ls_sine(Angle);
	Result.values[2][1] = (f32)ls_sine(Angle);

	return Result;
}

Mat4 RotateY(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = (f32)ls_cos(Angle);
	Result.values[0][2] = (f32)ls_sine(Angle);
	Result.values[2][0] = (f32)-ls_sine(Angle);
	Result.values[2][2] = (f32)ls_cos(Angle);

	return Result;
}

Mat4 RotateZ(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = (f32)ls_cos(Angle);
	Result.values[1][1] = (f32)ls_cos(Angle);
	Result.values[1][0] = (f32)ls_sine(Angle);
	Result.values[0][1] = (f32)-ls_sine(Angle);

	return Result;
}

///////////////////////////////////////////
// PROJECTION MATRIXES
///////////////////////////////////////////

Mat4 PerspectiveProj(f32 near, f32 far, f32 right, f32 top)
{
	Mat4 Result = {};
	Result.values[0][0] = near / right;
	Result.values[1][1] = near / top;
	Result.values[2][2] = -((far + near) / (far - near));
	Result.values[2][3] = ((-2.0f*far*near) / (far - near));
	Result.values[3][2] = -1.0f;

	return Result;
}

Mat4 PerspectiveProj(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom)
{
	Mat4 Result = {};
	Result.values[0][0] = ((2.0f*near) / (right - left));
	Result.values[0][2] = ((right + left) / (right - left));
	Result.values[1][1] = ((2.0f*near) / (top - bottom));
	Result.values[1][2] = ((top + bottom) / (top - bottom));
	Result.values[2][2] = -((far + near) / (far - near));
	Result.values[2][3] = ((-2.0f*far*near) / (far - near));
	Result.values[3][2] = -1.0f;

	return Result;
}

Mat4 PerspectiveProjFOV(f32 FOV, f32 aspectRatio, f32 near, f32 far)
{
	Mat4 Result = {};

	f32 tanHalfFOV = (f32)ls_tan(FOV / 2.0f);

	Result.values[0][0] = (1.0f / (aspectRatio * tanHalfFOV));
	Result.values[1][1] = (1.0f / tanHalfFOV);
	Result.values[2][2] = -((far + near) / (far - near));
	Result.values[2][3] = ((-2.0f*far*near) / (far - near));
	Result.values[3][2] = -1.0f;

	return Result;
}

Mat4 OrthoProj(f32 near, f32 far, f32 right, f32 top)
{
	Mat4 Result = {};
	Result.values[0][0] = 1.0f / right;
	Result.values[1][1] = 1.0f / top;
	Result.values[2][2] = -(2.0f / (far - near));
	Result.values[2][3] = -((far + near) / (far - near));
	Result.values[3][3] = 1.0f;

	return Result;
}

Mat4 OrthoProj(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom)
{
	Mat4 Result = {};
	Result.values[0][0] = ((2.0f) / (right - left));
	Result.values[0][3] = -((right + left) / (right - left));
	Result.values[1][1] = ((2.0f) / (top - bottom));
	Result.values[1][3] = -((top + bottom) / (top - bottom));
	Result.values[2][2] = -((2.0f) / (far - near));
	Result.values[2][3] = -((far + near) / (far - near));
	Result.values[3][3] = 1.0f;

	return Result;
}
