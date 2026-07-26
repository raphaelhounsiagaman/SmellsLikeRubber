#pragma once

#include "Core/MetricUnits.h"
#include "Slate/Math/Transform.h"

struct ArcadeCarInput
{
	float Throttle = 0.0f;
	float Steering = 0.0f;
};

struct ArcadeCarSettings
{
	float MaximumForwardSpeedMetresPerSecond =
		Metric::KilometresPerHourToMetresPerSecond(72.0f);
	float MaximumReverseSpeedMetresPerSecond =
		Metric::MetresPerSecond(5.0f);
	float ForwardAccelerationMetresPerSecondSquared =
		Metric::MetresPerSecondSquared(6.0f);
	float ReverseAccelerationMetresPerSecondSquared =
		Metric::MetresPerSecondSquared(4.0f);
	float BrakingDecelerationMetresPerSecondSquared =
		Metric::MetresPerSecondSquared(12.0f);
	float CoastingDragMetresPerSecondSquared =
		Metric::MetresPerSecondSquared(1.5f);
	float MaximumSteeringRateRadiansPerSecond =
		Metric::RadiansPerSecond(1.8f);
};

class ArcadeCarController
{
public:
	explicit ArcadeCarController(
		const ArcadeCarSettings& settings = {}
	);

	void Update(
		Slate::Transform3D& transform,
		const ArcadeCarInput& input,
		float deltaTimeSeconds
	);

	float GetSpeedMetresPerSecond() const
	{
		return m_SpeedMetresPerSecond;
	}

	float GetHeadingRadians() const
	{
		return m_HeadingRadians;
	}

private:
	ArcadeCarSettings m_Settings;
	float m_SpeedMetresPerSecond = 0.0f;
	float m_HeadingRadians = 0.0f;
};
