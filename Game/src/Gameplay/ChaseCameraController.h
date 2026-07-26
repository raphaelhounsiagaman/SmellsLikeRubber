#pragma once

#include "Slate/Graphics/Camera3D.h"

struct ChaseCameraSettings
{
	float TargetHeightMetres = 1.0f;
	float FollowDistanceMetres = 8.0f;
	float MinimumDistanceMetres = 4.0f;
	float MaximumDistanceMetres = 16.0f;
	float InitialPitchRadians = -0.35f;
	float PositionResponsePerSecond = 7.0f;
	float OrbitSensitivityRadiansPerPixel = 0.0025f;
	float ZoomMetresPerWheelStep = 0.75f;
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
