#include "tools\OpenGL\Managers\TransformManager.h"

TransformManager *createTransform(MemoryArena *Memory)
{
	TransformManager *Transform = 0;
	Memory->Alloc(&Memory->PermanentMemory, (void **)&Transform, sizeof(TransformManager));

	return Transform;
}

void SetTransform(TransformManager *Manager)
{
	Manager->Transform = Manager->ProjectionMatrix * Manager->ViewMatrix * Manager->ModelMatrix;
}

void SetModel(TransformManager *Manager, v4 translate, v4 scale, f32 AngleX, f32 AngleY)
{
	Manager->ModelMatrix = Translate(translate) * Scale(scale) * RotateX(AngleX) * RotateY(AngleY);
}

void SetModel(TransformManager *Manager, Mat4 TranslationM, Mat4 ScaleM, Mat4 RotM)
{
	Manager->ModelMatrix = TranslationM * ScaleM * RotM;
}

void SetView(TransformManager *Manager, Camera Camera)
{
	Manager->ViewMatrix = LookAt(Camera);
}

void SetStandardProjection(TransformManager *Manager)
{
	Manager->ProjectionMatrix = PerspectiveProjFOV(PI_32 / 4.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
}

void SetProjection(TransformManager *Manager, f32 FOV, f32 AspectRatio, f32 Near, f32 Far)
{
	Manager->ProjectionMatrix = PerspectiveProjFOV(FOV, AspectRatio, Near, Far);
}