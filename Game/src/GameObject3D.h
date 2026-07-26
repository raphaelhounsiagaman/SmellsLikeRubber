#pragma once

#include "Slate/Math/Math.h"
#include "Slate/Graphics/Handles.h"

struct GameObject3D
{
	Slate::Transform3D Transform;
	Slate::Mesh3DHandle Mesh;
	Slate::MaterialHandle Material;
};
