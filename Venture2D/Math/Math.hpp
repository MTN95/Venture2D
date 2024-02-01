#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace venture::Math
{
	/**
	 * @brief The mathematical constant Pi (π).
	 */
	const float Pi = 3.1415926535f;

	/**
	 * @brief Convert degrees to radians.
	 * @param degrees The angle in degrees.
	 * @return The angle in radians.
	 */
	inline float DegToRad( float degrees )
	{
		return degrees * Pi / 180.0f;
	}

	/**
	 * @brief Convert radians to degrees.
	 * @param radians The angle in radians.
	 * @return The angle in degrees.
	 */
	inline float RadToDeg( float radians )
	{
		return radians * 180.0f / Pi;
	}

	/**
	 * @brief Compare two floating-point numbers with a tolerance.
	 * @param a The first floating-point number.
	 * @param b The second floating-point number.
	 * @param epsilon The tolerance value (default is machine epsilon).
	 * @return True if the numbers are nearly equal within the given tolerance, false otherwise.
	 */
	inline bool NearlyEqual( double a, double b, double epsilon = std::numeric_limits<double>::epsilon() )
	{
		// The smaller the epsilon, the greater the precision
		// Use std::abs to handle negative values
		return std::abs( a - b ) <= epsilon * std::max( { 1.0, std::abs( a ), std::abs( b ) } );
	}

	/**
	 * @brief Linear Interpolation function.
	 * @param a The start value.
	 * @param b The end value.
	 * @param t The interpolation parameter (0.0 to 1.0).
	 * @return The interpolated value.
	 */
	template <typename T>
	inline T Lerp( const T& a, const T& b, float t )
	{
		return a + ( b - a ) * t;
	}

	/**
	 * @brief Linearly interpolates towards a target value.
	 * @param current The current value.
	 * @param target The value to interpolate towards.
	 * @param deltaTime The time elapsed since the last update.
	 * @param interpSpeed The rate of interpolation.
	 * @return The interpolated value.
	 */
	template <typename T>
	inline T InterpTo( const T& current, const T& target, float deltaTime, float interpSpeed )
	{
		// If there's no change, or the interpSpeed is zero, return current value
		if ( NearlyEqual( current, target ) || interpSpeed <= 0.0f )
		{
			return current;
		}

		// Calculate the distance between current and target
		T delta = target - current;

		// If the delta is small enough, or if we're able to reach the target within the next delta time, jump to target
		if ( NearlyEqual( delta, T( 0 ) ) || ( std::abs( delta ) * deltaTime >= std::abs( target - current ) ) )
		{
			return target;
		}

		// Calculate the step to take
		T step = delta * interpSpeed * deltaTime;

		return current + step;
	}
};
