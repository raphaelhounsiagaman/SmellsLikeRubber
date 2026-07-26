#pragma once

// SmellsLikeRubber uses SI units throughout gameplay:
//   1 world unit = 1 metre
//   time         = seconds
//   speed        = metres per second
//   acceleration = metres per second squared
//   angles       = radians
namespace Metric
{
	constexpr float Metres(float value) noexcept
	{
		return value;
	}

	constexpr float MetresPerSecond(float value) noexcept
	{
		return value;
	}

	constexpr float MetresPerSecondSquared(float value) noexcept
	{
		return value;
	}

	constexpr float Radians(float value) noexcept
	{
		return value;
	}

	constexpr float RadiansPerSecond(float value) noexcept
	{
		return value;
	}

	constexpr float KilometresPerHourToMetresPerSecond(float value) noexcept
	{
		return value / 3.6f;
	}
}
