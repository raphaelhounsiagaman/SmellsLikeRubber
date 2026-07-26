#pragma once

#include "Core/MetricUnits.h"
#include "Slate/Graphics/Camera3D.h"

struct ChaseCameraSettings
{
	float TargetHeightMetres = Metric::Metres(1.0f);
	float FollowDistanceMetres = Metric::Metres(8.0f);
	float MinimumDistanceMetres = Metric::Metres(4.0f);
	float MaximumDistanceMetres = Metric::Metres(16.0f);
	float InitialPitchRadians = Metric::Radians(-0.35f);
	float PositionResponsePerSecond = 7.0f;
	float OrbitSensitivityRadiansPerPixel = 0.0025f;
	float ZoomMetresPerWheelStep = Metric::Metres(0.75f);
};

struct ChaseCameraInput
{
	Slate::Vector2i OrbitDeltaPixels{};
	float ZoomWheelSteps = 0.0f;
};

class ChaseCameraController
{
public:
	explicit ChaseCameraController(
		const ChaseCameraSettings& settings = {}
	);

	void Update(
		Slate::Camera3D& camera,
		const Slate::Vector3f& targetPositionMetres,
		float targetHeadingRadians,
		const ChaseCameraInput& input,
		float deltaTimeSeconds
	);

private:
	ChaseCameraSettings m_Settings;
	float m_YawOffsetRadians = 0.0f;
	float m_PitchRadians = 0.0f;
	float m_DistanceMetres = 0.0f;
	bool m_IsInitialized = false;
};
