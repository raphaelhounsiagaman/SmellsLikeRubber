#include "DebugDrivingCourse.h"

#include "Core/MetricUnits.h"
#include "Meshes/BoxMesh.h"

DebugDrivingCourse::DebugDrivingCourse(Slate::Renderer& renderer)
{
	const Slate::Mesh3DHandle boxMesh = CreateBoxMesh(renderer);

	m_Road.Mesh = boxMesh;
	m_Road.Material =
		renderer.CreateMaterial(Slate::Color(45, 48, 52));
	m_Road.Transform.Position =
		{ 0.0f, Metric::Metres(-0.1f), Metric::Metres(50.0f) };
	m_Road.Transform.Scale =
		{
			Metric::Metres(12.0f),
			Metric::Metres(0.2f),
			Metric::Metres(200.0f)
		};

	const Slate::MaterialHandle markingMaterial =
		renderer.CreateMaterial(Slate::Color(235, 225, 170));

	for (float zMetres = -40.0f; zMetres <= 140.0f; zMetres += 8.0f)
	{
		GameObject3D marking;
		marking.Mesh = boxMesh;
		marking.Material = markingMaterial;
		marking.Transform.Position =
			{ 0.0f, Metric::Metres(0.015f), Metric::Metres(zMetres) };
		marking.Transform.Scale =
			{
				Metric::Metres(0.15f),
				Metric::Metres(0.03f),
				Metric::Metres(4.0f)
			};
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
