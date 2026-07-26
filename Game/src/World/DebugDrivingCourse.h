#pragma once

#include "GameObject3D.h"
#include "Slate/Graphics/Renderer.h"

#include <vector>

class DebugDrivingCourse
{
public:
	explicit DebugDrivingCourse(Slate::Renderer& renderer);

	void Render(Slate::Renderer& renderer) const;

private:
	GameObject3D m_Road;
	std::vector<GameObject3D> m_RoadMarkings;
};
