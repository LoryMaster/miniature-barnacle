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

	return Result;
}