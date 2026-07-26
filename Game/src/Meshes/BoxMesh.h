#pragma once

#include "Slate/Graphics/Handles.h"

namespace Slate
{
	class Renderer;
}

// Creates a one-metre cube centred at the origin.
Slate::Mesh3DHandle CreateBoxMesh(Slate::Renderer& renderer);
