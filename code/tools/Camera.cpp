#include "tools\OpenGL\Managers\Camera.h"

Camera *createCamera(MemoryArena *Memory, v4 pos, v4 target)
{
	Camera * Result = {};

	Memory->Alloc(&Memory->PermanentMemory, (void **)&Result, sizeof(Camera));

	Result->pos = pos;
	Result->target = target;

	v4 UnnormalizedCameraZ4 = (pos - target);
	v3 UnnormalizedCameraZ3 = { UnnormalizedCameraZ4.x, UnnormalizedCameraZ4.y, UnnormalizedCameraZ4.z };
	Result->zDir = Normalize(UnnormalizedCameraZ3);

	v3 WorldY = { 0.0f, 1.0f, 0.0f };
	Result->xDir = WorldY ^ Result->zDir;
	Result->yDir = Result->zDir ^ Result->xDir;

	Result->worldX = {1.0f, 0.0f, 0.0f};
	Result->worldY = {0.0f, 1.0f, 0.0f};
	Result->worldZ = {0.0f, 0.0f, -1.0f};

	Result->speed = 0.05f;

	return Result;
}

Mat4 LookAt(CoordSys Sys, v4 cameraPos)
{
	v4 x = { Sys.x.x, Sys.x.y, Sys.x.z, 1.0f };
	v4 y = { Sys.y.x, Sys.y.y, Sys.y.z, 1.0f };
	v4 z = { Sys.z.x, Sys.z.y, Sys.z.z, 1.0f };

	Mat4 Result = Identity4();
	Result.row1 = x;
	Result.row2 = y;
	Result.row3 = z;

	Mat4 Pos = Identity4();
	Pos.values[0][3] = -cameraPos.x;
	Pos.values[1][3] = -cameraPos.y;
	Pos.values[2][3] = -cameraPos.z;

	return Result * Pos;
}

Mat4 LookAt(Camera Camera)
{
	v4 UnnormalizedCameraZ4 = (Camera.pos - Camera.target);
	v3 UnnormalizedCameraZ3 = { UnnormalizedCameraZ4.x, UnnormalizedCameraZ4.y, UnnormalizedCameraZ4.z };
	v3 Z3 = Normalize(UnnormalizedCameraZ3);

	v3 WorldY = { 0.0f, 1.0f, 0.0f };
	v3 X3 = WorldY ^ Z3;
	v3 Y3 = Z3 ^ X3;

	v4 x = { X3.x, X3.y, X3.z, 1.0f };
	v4 y = { Y3.x, Y3.y, Y3.z, 1.0f };
	v4 z = { Z3.x, Z3.y, Z3.z, 1.0f };

	Mat4 Result = Identity4();
	Result.row1 = x;
	Result.row2 = y;
	Result.row3 = z;

	Mat4 Pos = Identity4();
	Pos.values[0][3] = -Camera.pos.x;
	Pos.values[1][3] = -Camera.pos.y;
	Pos.values[2][3] = -Camera.pos.z;

	return Result * Pos;
}