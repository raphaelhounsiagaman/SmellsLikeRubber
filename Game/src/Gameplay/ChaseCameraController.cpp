#include "ChaseCameraController.h"

#include "Slate/Math/Quaternion.h"

#include <algorithm>
#include <cmath>

ChaseCameraController::ChaseCameraController(
	const ChaseCameraSettings& settings)
	: m_Settings(settings),
	  m_PitchRadians(settings.InitialPitchRadians),
	  m_DistanceMetres(settings.FollowDistanceMetres)
{}

void ChaseCameraController::Update(
	Slate::Camera3D& camera,
	const Slate::Vector3f& targetPositionMetres,
	float targetHeadingRadians,
	const ChaseCameraInput& input,
	float deltaTimeSeconds)
{
	const float timestepSeconds =
		std::clamp(deltaTimeSeconds, 0.0f, 0.1f);

	m_YawOffsetRadians +=
		static_cast<float>(input.OrbitDeltaPixels.X) *
		m_Settings.OrbitSensitivityRadiansPerPixel;
	m_PitchRadians -=
		static_cast<float>(input.OrbitDeltaPixels.Y) *
		m_Settings.OrbitSensitivityRadiansPerPixel;
	m_PitchRadians = std::clamp(m_PitchRadians, -1.2f, -0.05f);

	m_DistanceMetres = std::clamp(
		m_DistanceMetres -
			input.ZoomWheelSteps * m_Settings.ZoomMetresPerWheelStep,
		m_Settings.MinimumDistanceMetres,
		m_Settings.MaximumDistanceMetres
	);

	const float viewHeadingRadians =
		targetHeadingRadians + m_YawOffsetRadians;
	const float cosPitch = std::cos(m_PitchRadians);
	const Slate::Vector3f cameraForward
	{
		std::sin(viewHeadingRadians) * cosPitch,
		std::sin(m_PitchRadians),
		std::cos(viewHeadingRadians) * cosPitch
	};
	const Slate::Vector3f cameraTargetMetres =
		targetPositionMetres +
		Slate::Vector3f{ 0.0f, m_Settings.TargetHeightMetres, 0.0f };
	const Slate::Vector3f desiredPositionMetres =
		cameraTargetMetres - cameraForward * m_DistanceMetres;

	if (!m_IsInitialized)
	{
		camera.Transform.Position = desiredPositionMetres;
		m_IsInitialized = true;
	}
	else
	{
		const float followAlpha =
			1.0f - std::exp(
				-m_Settings.PositionResponsePerSecond * timestepSeconds
			);
		camera.Transform.Position =
			camera.Transform.Position +
			(desiredPositionMetres - camera.Transform.Position) * followAlpha;
	}

	const Slate::Vector3f toTarget =
		cameraTargetMetres - camera.Transform.Position;
	const float targetDistanceMetres = std::sqrt(
		toTarget.X * toTarget.X +
		toTarget.Y * toTarget.Y +
		toTarget.Z * toTarget.Z
	);

	if (targetDistanceMetres > 0.001f)
	{
		const float cameraYawRadians =
			std::atan2(toTarget.X, toTarget.Z);
		const float cameraPitchRadians =
			std::asin(toTarget.Y / targetDistanceMetres);
		const Slate::Quaternion pitchRotation =
			Slate::Quaternion::FromAxisAngle(
				{ 1.0f, 0.0f, 0.0f },
				-cameraPitchRadians
			);
		const Slate::Quaternion yawRotation =
			Slate::Quaternion::FromAxisAngle(
				{ 0.0f, 1.0f, 0.0f },
				cameraYawRadians
			);

		camera.Transform.Rotation =
			(yawRotation * pitchRotation).Normalized();
	}
}
