#include "DebugDrivingCourse.h"

#include <cstddef>

DebugDrivingCourse::DebugDrivingCourse(
	Slate::Renderer& renderer,
	const Slate::Mesh3DHandle& boxMesh)
{
	m_Road.Mesh = boxMesh;
	m_Road.Material =
		renderer.CreateMaterial(Slate::Color(45, 48, 52));
	m_Road.Transform.Position =
		{ 0.0f, -0.1f, 50.0f };
	m_Road.Transform.Scale =
		{ 12.0f, 0.2f, 200.0f };

	const Slate::MaterialHandle markingMaterial =
		renderer.CreateMaterial(Slate::Color(235, 225, 170));

	constexpr int firstMarkingPositionMetres = -40;
	constexpr int lastMarkingPositionMetres = 136;
	constexpr int markingSpacingMetres = 8;
	constexpr std::size_t markingCount =
		(lastMarkingPositionMetres - firstMarkingPositionMetres) /
		markingSpacingMetres + 1;
	m_RoadMarkings.reserve(markingCount);

	for (int zMetres = firstMarkingPositionMetres;
		zMetres <= lastMarkingPositionMetres;
		zMetres += markingSpacingMetres)
	{
		GameObject3D marking;
		marking.Mesh = boxMesh;
		marking.Material = markingMaterial;
		marking.Transform.Position =
			{ 0.0f, 0.015f, static_cast<float>(zMetres) };
		marking.Transform.Scale =
			{ 0.15f, 0.03f, 4.0f };
		m_RoadMarkings.push_back(marking);
	}
}

void DebugDrivingCourse::Render(Slate::Renderer& renderer) const
{
	renderer.DrawMesh3D(
		m_Road.Mesh,
		m_Road.Material,
		m_Road.Transform
	);

	for (const GameObject3D& marking : m_RoadMarkings)
	{
		renderer.DrawMesh3D(
			marking.Mesh,
			marking.Material,
			marking.Transform
		);
	}
}
