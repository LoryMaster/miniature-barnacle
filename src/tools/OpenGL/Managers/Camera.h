#pragma once

#include "tools\Maths\Maths.h"

struct Camera
{
	v4 pos;
	v4 target;
	
	union
	{
		struct
		{
			v3 xDir;
			v3 yDir;
			v3 zDir;
		};
		CoordSys Sys;		
	};
	
};

Camera *createCamera(MemoryArena *Memory, v4 pos, v4 target);