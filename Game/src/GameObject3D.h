#pragma once

#include "Slate/Math/Math.h"
#include "Slate/Graphics/Handles.h"

struct GameObject3D
{
	// Position and mesh dimensions use metres. Scale is dimensionless relative
	// to the source mesh; a one-metre source mesh makes Scale read as metres.
	Slate::Transform3D Transform;
	Slate::Mesh3DHandle Mesh;
	Slate::MaterialHandle Material;
};
