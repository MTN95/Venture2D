#pragma once
#include <iostream>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <type_traits>

/**
* @class Vec2D<T>
* @brief A template class representing a 2-dimensional vector.
* 
* Vec2D<T> is a template class that supports various arithmetic, comparison, and vector-specific operations. 
* It is restricted to use with numeric types (short, int, long, float, double, long double).
*
* @tparam T Numeric type of the vector components (must be one of the specified types).
*/
template <typename T>
class Vec2D
{
	static_assert (
		std::is_same_v<T, short> ||
		std::is_same_v<T, int> ||
		std::is_same_v<T, long> ||
		std::is_same_v<T, float> ||
		std::is_same_v<T, double> ||
		std::is_same_v<T, long double>,
		"T must be int, float, or double."
		);

public:
	
	//-Constructors----------------------------------------------------------------------------------------------------
	
	/**
	* @brief Constructs a new Vec2D<T> object with optional x and y values.
	* @param x The x-component of the vector (default is 0).
	* @param y The y-component of the vector (default is 0).
	*/
	explicit Vec2D<T>( const T& x = 0, const T& y = 0 )
		: m_x( x )
		, m_y( y )
	{}

	/**
	* @brief Copy-Constructs a new Vec2D<T> object with the other x and y values.
	* @param other The other Vec2D<T> object to copy from.
	*/
	Vec2D<T>( const Vec2D<T>& other )
		: m_x( other.m_x )
		, m_y( other.m_y )
	{}
	
	/**
	* @brief Move-Constructs a new Vec2D<T> object with the other x and y values.
	* @param other The other Vec2D<T> object to move from.
	*/
	Vec2D<T>( const Vec2D<T>&& other ) noexcept 		
		: m_x( std::move(other.m_x) )
		, m_y( std::move(other.m_y) )
	{}

	// ----------------------------------------------------------------------------------------------------------------

	//-Getters Functions------------------------------------------------------------------------------------------------
	
	/**
	* @brief Gets the x-component of the vector.
	* This method returns the x-component of the vector, allowing external access to it.
	* @return T The x-component of the vector.
	*/
	const T GetX() const { return m_x; }

	/**
	* @brief Gets they-component of the vector.
	* This method returns the y-component of the vector, allowing external access to it.
	* @return T The y-component of the vector.
	*/
	const T GetY() const { return m_y; }

	// ----------------------------------------------------------------------------------------------------------------
	
	//-Setters Functions------------------------------------------------------------------------------------------------

	/**
	* @brief Sets the x-component and y-component of the vector.
	* @param T The new x and y components to set.
	*/
	inline void Set(T x,T y) { SetX(x); SetY(y); }
	
	/**
	* @brief Resets the x-component and y-component of the vector to 0.
	*/
	inline void Reset() { std::cout << "Reset!\n"; SetX(0); SetY(0); }

	/**
	* @brief Sets the x-component of the vector.
	* @param T The new x-component to set.
	*/
	inline void SetX(T x) { m_x = x; }

	/**
	* @brief Sets the y-component of the vector.
	* @param T The new y-component to set.
	*/
	inline void SetY(T y) { m_y = y; }

	// ----------------------------------------------------------------------------------------------------------------
	
	//-Vector Operations-----------------------------------------------------------------------------------------------

	/**
	* @brief Logs the vector's components to the standard output.
	* It can optionally prepend a custom message to the output.
	* @param msg Optional message to prepend to the log output (default is an empty string).
	*/
	void Log( const std::string& msg = "" ) const
	{
		if(!msg.empty())
		{
			std::cout << msg << ' ';
		}

		std::cout << "X = " << m_x << ", "
			<< "Y = " << m_y << '\n';
	}

	/**
	* @brief Checks if this vector x and t components are 0
	* @return bool True if the vector is (0,0), false otherwise.
	*/
	bool IsZero() const
	{
		return ( m_x == 0 && m_y == 0 );
	}

	/**
	* @brief Calculates and returns the difference in each dimension between this vector and another.
	* @param other The other Vec2D<T> object to compare with.
	* @return Vec2D<T> A new Vec2D<T> object containing the absolute differences in each dimension.
	*/
	inline const Vec2D<T> Difference( const Vec2D<T>& other ) const 
	{ return Vec2D<T>{ std::abs( m_x - other.m_x ), std::abs( m_y - other.m_y ) }; }

	//-----------------------------------------------------------------------------------------------------------------

	/**
	* @brief Calculates and returns the length (magnitude) of the vector.
	* @return float The length of the vector.
	*/
	inline const T Length() const { return std::hypot( m_x, m_y ); }

	/**
	* @brief Calculates the distance between this and the other vector
	* @param other The other Vec2D<T> object to check the distance to.
	* @return float The distance from this vector to the other.
	*/
	inline const T Distance( const Vec2D<T>& other ) const { return (*this - other ).Length(); }

	/**
	* @brief Normalizes the vector, scaling it to a length of 1 while preserving its direction.
	* If the vector is zero, it returns the vector unchanged.
	* @return Vec2D<T> A new normalized Vec2D<T> object.
	*/
	Vec2D<T> Normalize() const
	{
		T len = Length();
		return len == 0 ? *this : *this / len;
	}

	/**
	* @brief Calculates the dot product of this vector with another.
	* @param other The other Vec2D<T> object.
	* @return float The dot product of the two vectors.
	*/
	inline const float Dot( const Vec2D<T>& other ) const { return m_x * other.m_x + m_y * other.m_y; }

	/**
	* @brief Calculates the angle between this vector and another in radians.
	* @param other The other Vec2D<T> object.
	* @return float The angle between the two vectors in radians.
	*/
	const float Angle( const Vec2D<T>& other ) const { return atan2( other.m_y - m_y, other.m_x - m_x ); }

	/**
	* @brief Projects this vector onto another vector.
	* @param other The Vec2D<T> object onto which to project this vector.
	* @return Vec2D<T> The projection of this vector onto the other vector.
	*/
	Vec2D<T> const Project( const Vec2D<T>& other ) const { return other * Dot( other ) / other.Dot( other ); }

	/**
	* @brief Checks if this vector is nearly equal to another, within a specified tolerance.
	* @param other The other Vec2D<T> object to compare with.
	* @param tolerance The tolerance for comparison (default is class-defined tolerance).
	* @return bool True if the vectors are nearly equal, false otherwise.
	*/
	bool NearlyEquals( const Vec2D<T>& other, T tolerance = T()) const
	{
		return std::abs( m_x - other.m_x ) < tolerance && std::abs( m_y - other.m_y ) < tolerance;
	}

	/**
	* @brief Performs a safe division of this vector by another vector.
	* This method divides each component of this vector by the corresponding component of the divisor vector.
	* If any component of the divisor is zero, an error is logged to the console and returns (0,0).
	* @param divisor The Vec2D object by which to divide this vector.
	* @return Vec2D<T> The result of the division. 
	*/
	Vec2D<T> SafeDivision( const Vec2D<T>& divisor ) const
	{
		if ( divisor.m_x == 0 || divisor.m_y == 0 )
		{
			// Handle division by zero case
			std::cerr << "Error: Division by zero in Vec2D" << std::endl;
			return Vec2D<T>(0, 0);
		}

		return Vec2D<T>( m_x / divisor.m_x, m_y / divisor.m_y );
	}

	/**
	* @brief Linearly interpolates between two Vec2D objects.
	* This method computes a linear interpolation between the vectors 'a' and 'b',
	* returning a vector that is 't' percent of the way from 'a' to 'b'.
	* @param a The start vector for interpolation.
	* @param b The end vector for interpolation.
	* @param t The interpolation factor, typically in the range [0, 1].
	* @return Vec2D<T> The interpolated vector.
	*/
	// Lerp Example
	/** Vec2D<float> vecA( 0.f, 0.f );
	*  Vec2D<float> vecB( 10.f, 10.f );
	*  Vec2D<float> interpolatedVec;

	*  std::cout << "Interpolating from VecA to VecB:" << std::endl;
	*  for ( float t = 0.0f; t <= 1.0f; t += 0.01f )
	*  {
	*		interpolatedVec = std::move(Vec2D<float>::Lerp( vecA, vecB, t ));
	*   	std::cout << "t = " << t << ": ";
	*   	interpolatedVec.Log("Lerping: ");
	*  } 
	*/
	static Vec2D<T> Lerp(const Vec2D<T>& a, const Vec2D<T>& b, float t) {
		return Vec2D<T>(a.m_x + t * (b.m_x - a.m_x), a.m_y + t * (b.m_y - a.m_y));
	}

	// ----------------------------------------------------------------------------------------------------------------

	//-Arithmetic Operators--------------------------------------------------------------------------------------------
	
	/**
	* @brief Adds the other vector to this vector.
	* @param other The other Vec2D<T> object to add.
	* @return Vec2D<T> The result of the vector addition.
	*/
	inline Vec2D<T> operator+( const Vec2D<T>& other ) const { return Vec2D<T>{ m_x + other.m_x, m_y + other.m_y }; }

	/**
	* @brief Subtracts the other vector from this vector.
	* @param other The other Vec2D<T> object to subtract.
	* @return Vec2D<T> The result of the vector subtraction.
	*/
	inline Vec2D<T> operator-( const Vec2D<T>& other ) const { return Vec2D<T>{ m_x - other.m_x, m_y - other.m_y }; }

	/**
	* @brief Multiplies this vector by the other vector.
	* @param other The other Vec2D<T> object to multiply.
	* @return Vec2D<T> The result of the vector multiplication.
	*/
	inline Vec2D<T> operator*( const Vec2D<T>& other ) const { return Vec2D<T>{ m_x * other.m_x, m_y * other.m_y }; }
	
	/**
	* @brief Divides this vector by the other vector.
	* @param other The other Vec2D<T> object to divide by.
	* @return Vec2D<T> The result of the vector division.
	* @throw std::domain_error if division by zero occurs.
	*/
	Vec2D<T> operator/( const Vec2D<T>& other ) const
	{
		if ( other.m_x == 0 || other.m_y == 0 )
		{
			throw std::domain_error( "Division by zero in Vec2D<T>" );
		}
		return Vec2D<T>{ m_x / other.m_x, m_y / other.m_y };
	}

	/**
	* @brief Adds a scalar to this vector
	* @param scalar The scalar to add.
	* @return Vec2D<T> The result of the scalar and vector addition.
	*/
	inline Vec2D<T> operator+( const T& scalar ) const { return Vec2D<T>{ m_x + scalar, m_y + scalar }; }
	
	/**
	* @brief Subtracts a scalar from this vector
	* @param scalar The scalar to subtract.
	* @return Vec2D<T> The result of the scalar and vector subtraction.
	*/
	inline Vec2D<T> operator-( const T& scalar ) const { return Vec2D<T>{ m_x - scalar, m_y - scalar }; }
	
	/**
	* @brief Multiplies a scalar by this vector
	* @param scalar The scalar to multiply.
	* @return Vec2D<T> The result of the scalar and vector multiplication.
	*/
	inline Vec2D<T> operator*( const T& scalar ) const { return Vec2D<T>{ m_x * scalar, m_y * scalar }; }
	
	/**
	* @brief Divides this vector by a scalar
	* @param scalar The scalar to divide by.
	* @return Vec2D<T> The result of the scalar and vector division.
	* @throw std::domain_error if division by zero occurs.
	*/
	Vec2D<T> operator/( const T& scalar ) const
	{
		if ( scalar == 0 )
		{
			throw std::domain_error( "Division by zero in Vec2D<T>" );
		}
		return Vec2D<T>{ m_x / scalar, m_y / scalar };
	}

	//-----------------------------------------------------------------------------------------------------------------

	//-Assignment Operators--------------------------------------------------------------------------------------------
	
	/**
	* @brief Copy-Assigns the values from another Vec2D<T> object to this one.
	* @param other The other Vec2D<T> object to assign from.
	* @return Vec2D<T>& A reference to this vector after assignment.
	*/
	inline Vec2D<T>& operator=( const Vec2D<T>& other )
	{
		m_x = other.m_x;
		m_y = other.m_y;
		return *this;
	}

	/**
	* @brief Move-Assigns the values from another Vec2D<T> object to this one.
	* @param other The other Vec2D<T> object to assign from.
	* @return Vec2D<T>& A reference to this vector after assignment.
	*/
	inline Vec2D<T>& operator=( const Vec2D<T>&& other ) noexcept
	{
		m_x = std::move(other.m_x);
		m_y = std::move(other.m_y);
		return *this;
	}

	/**
	* @brief Adds the other vector to this vector, and 
	* Assigns the results to this vector.
	* @param other The other Vec2D<T> object to add.
	* @return Vec2D<T>& A reference to this vector after addition and assignment.
	*/
	inline Vec2D<T>& operator+=( const Vec2D<T>& other )
	{
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}
	
	/**
	* @brief Subtracts this vector by the other vector , and
	* Assigns the results to this vector.
	* @param other The other Vec2D<T> object to subtract by.
	* @return Vec2D<T>& A reference to this vector after subtraction and assignment.
	*/
	inline Vec2D<T>& operator-=( const Vec2D<T>& other )
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}
	
	/**
	* @brief Multiplies the other vector by this vector, and
	* Assigns the results to this vector.
	* @param other The other Vec2D<T> object to multiply by.
	* @return Vec2D<T>& A reference to this vector after multiplication and assignment.
	*/
	inline Vec2D<T>& operator*=( const Vec2D<T>& other )
	{
		m_x *= other.m_x;
		m_y *= other.m_y;
		return *this;
	}
	
	/**
	* @brief Divides this vector by the other vector, and
	* Assigns the results to this vector.
	* @param other The other Vec2D<T> object to divide by.
	* @return Vec2D<T>& A reference to this vector after division and assignment.
	*/
	inline Vec2D<T>& operator/=( const Vec2D<T>& other )
	{
		m_x /= other.m_x;
		m_y /= other.m_y;
		return *this;
	}

	/**
	* @brief Adds a scalar to this vector and
	* Assigns the results to this vector.
	* @param scalar The scalar object to add.
	* @return Vec2D<T>& A reference to this vector after addition and assignment.
	*/
	inline Vec2D<T>& operator+=( const T& scalar )
	{
		m_x += scalar;
		m_y += scalar;
		return *this;
	}
	
	/**
	* @brief Subtracts a scalar from this vector and
	* Assigns the results to this vector.
	* @param scalar The scalar object to subtract by.
	* @return Vec2D<T>& A reference to this vector after subtraction and assignment.
	*/
	inline Vec2D<T>& operator-=( const T& scalar )
	{
		m_x -= scalar;
		m_y -= scalar;
		return *this;
	}
	
	/**
	* @brief Multiplies this vector by a scalar and 
	* Assigns the results to this vector.
	* @param scalar The scalar object to multiply by.
	* @return Vec2D<T>& A reference to this vector after multiplication and assignment.
	*/
	inline Vec2D<T>& operator*=( const T& scalar )
	{
		m_x *= scalar;
		m_y *= scalar;
		return *this;
	}
	
	/**
	* @brief Divides this vector by a scalar, and
	* Assigns the results to this vector.
	* @param scalar The scalar object to divide.
	* @return Vec2D<T>& A reference to this vector after division and assignment.
	*/
	inline Vec2D<T>& operator/=( const T& scalar )
	{
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}

	//-----------------------------------------------------------------------------------------------------------------

	//-Comparison Operators--------------------------------------------------------------------------------------------
	
	/**
	* @brief Checks if this vector is equal to another vector.
	* @param other The other Vec2D<T> object to compare with.
	* @return bool True if both x and y components are equal, false otherwise.
	*/
	inline bool operator==( const Vec2D<T>& other ) const { return m_x == other.m_x && m_y == other.m_y; }
	
	/**
	* @brief Checks if this vector is not equal to another vector.
	* @param other The other Vec2D<T> object to compare with.
	* @return bool True if both x and y components are not equal, false otherwise.
	*/
	inline bool operator!=( const Vec2D<T>& other ) const { return !( *this == other ); }
	
	/**
	* @brief Checks if this vector is less than another vector in a component-wise comparison.
	* @param other The other Vec2D<T> object to compare with.
	* @return bool True if both x and y components of this vector are less than those of the other vector, false otherwise.
	*/
	inline bool operator<( const Vec2D<T>& other ) const { return m_x < other.m_x && m_y < other.m_y; }
	
	/**
	* @brief Checks if this vector is less than or equal to another vector in a component-wise comparison.
	* @param other The other Vec2D<T> object to compare with.
	* @return bool True if both x and y components of this vector are less than or equal to those of the other vector, false otherwise.
	*/
	inline bool operator<=( const Vec2D<T>& other ) const { return m_x <= other.m_x && m_y <= other.m_y; }

	/**
	* @brief Checks if this vector is greater than another vector in a component-wise comparison.
	* @param other The other Vec2D<T> object to compare with.
	* @return bool True if both x and y components of this vector are greater than those of the other vector, false otherwise.
	*/
	inline bool operator>( const Vec2D<T>& other ) const { return m_x > other.m_x && m_y > other.m_y; }

	/**
	* @brief Checks if this vector is greater than or equal to another vector in a component-wise comparison.
	* @param other The other Vec2D<T> object to compare with.
	* @return bool True if both x and y components of this vector are greater than or equal to those of the other vector, false otherwise.
	*/
	inline bool operator>=( const Vec2D<T>& other ) const { return m_x >= other.m_x && m_y >= other.m_y; }

	//-----------------------------------------------------------------------------------------------------------------

	//-Stream operators documentation----------------------------------------------------------------------------------

	/**
	* @brief Outputs the vector to a stream.
	* @param os The output stream.
	* @param vec The Vec2D<T> object to output.
	* @return std::ostream& The modified output stream.
	*/
	friend std::ostream& operator<<( std::ostream& os, const Vec2D<T>& vec )
	{
		os << "[X,Y]:" << '[' << vec.m_x << ", " << vec.m_y << ']';
		return os;
	}

	//-----------------------------------------------------------------------------------------------------------------

private:
	T m_x, m_y;

	// static Vec2D<T> UnitX();
	// static Vec2D<T> UnitY();


};