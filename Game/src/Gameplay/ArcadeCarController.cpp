#include "ArcadeCarController.h"

#include "Slate/Math/Quaternion.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace
{
	float MoveTowards(float current, float target, float maximumDelta)
	{
		if (current < target)
		{
			return std::min(current + maximumDelta, target);
		}
		return std::max(current - maximumDelta, target);
	}
}

ArcadeCarController::ArcadeCarController(
	const ArcadeCarSettings& settings)
	: m_Settings(settings)
{}

void ArcadeCarController::Update(
	Slate::Transform3D& transform,
	const ArcadeCarInput& input,
	float deltaTimeSeconds)
{
	// Avoid a large simulation jump after pausing in the debugger or dragging
	// the window. All calculations below use seconds and SI-derived units.
	const float timestepSeconds =
		std::clamp(deltaTimeSeconds, 0.0f, 0.1f);
	const float throttle = std::clamp(input.Throttle, -1.0f, 1.0f);
	const float steering = std::clamp(input.Steering, -1.0f, 1.0f);

	if (throttle > 0.0f)
	{
		if (m_SpeedMetresPerSecond < 0.0f)
		{
			m_SpeedMetresPerSecond = MoveTowards(
				m_SpeedMetresPerSecond,
				0.0f,
				m_Settings.BrakingDecelerationMetresPerSecondSquared *
					throttle * timestepSeconds
			);
		}
		else
		{
			m_SpeedMetresPerSecond +=
				m_Settings.ForwardAccelerationMetresPerSecondSquared *
				throttle *
				timestepSeconds;
		}
	}
	else if (throttle < 0.0f)
	{
		if (m_SpeedMetresPerSecond > 0.0f)
		{
			m_SpeedMetresPerSecond = MoveTowards(
				m_SpeedMetresPerSecond,
				0.0f,
				m_Settings.BrakingDecelerationMetresPerSecondSquared *
					-throttle * timestepSeconds
			);
		}
		else
		{
			m_SpeedMetresPerSecond +=
				m_Settings.ReverseAccelerationMetresPerSecondSquared *
				throttle *
				timestepSeconds;
		}
	}
	else
	{
		m_SpeedMetresPerSecond = MoveTowards(
			m_SpeedMetresPerSecond,
			0.0f,
			m_Settings.CoastingDragMetresPerSecondSquared * timestepSeconds
		);
	}

	m_SpeedMetresPerSecond = std::clamp(
		m_SpeedMetresPerSecond,
		-m_Settings.MaximumReverseSpeedMetresPerSecond,
		m_Settings.MaximumForwardSpeedMetresPerSecond
	);

	const float absoluteSpeedMetresPerSecond =
		std::abs(m_SpeedMetresPerSecond);
	if (absoluteSpeedMetresPerSecond > 0.01f && steering != 0.0f)
	{
		const float normalizedSpeed = std::clamp(
			absoluteSpeedMetresPerSecond /
				m_Settings.MaximumForwardSpeedMetresPerSecond,
			0.0f,
			1.0f
		);
		const float steeringAuthority =
			std::lerp(0.25f, 1.0f, normalizedSpeed);
		const float travelDirection =
			m_SpeedMetresPerSecond >= 0.0f ? 1.0f : -1.0f;

		m_HeadingRadians +=
			steering *
			m_Settings.MaximumSteeringRateRadiansPerSecond *
			steeringAuthority *
			travelDirection *
			timestepSeconds;
		m_HeadingRadians = std::remainder(
			m_HeadingRadians,
			2.0f * std::numbers::pi_v<float>
		);
	}

	const Slate::Vector3f forward
	{
		std::sin(m_HeadingRadians),
		0.0f,
		std::cos(m_HeadingRadians)
	};
	const float distanceMetres =
		m_SpeedMetresPerSecond * timestepSeconds;

	transform.Position =
		transform.Position + forward * distanceMetres;
	transform.Rotation = Slate::Quaternion::FromAxisAngle(
		{ 0.0f, 1.0f, 0.0f },
		m_HeadingRadians
	);
}
