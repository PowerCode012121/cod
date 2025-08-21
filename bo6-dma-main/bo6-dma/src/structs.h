#pragma once

struct Vector2
{
	float x, y;

	Vector2 operator-(Vector2 ape)
	{
		return { x - ape.x, y - ape.y };
	}

	Vector2 operator/(float ape)
	{
		return { x / ape, y / ape };
	}

	Vector2 operator*(float ape)
	{
		return { x * ape, y * ape };
	}

	Vector2 operator/=(float ape)
	{
		x /= ape;
		y /= ape;

		return *this;
	}
	
	Vector2 operator*=(float ape)
	{
		x *= ape;
		y *= ape;

		return *this;
	}

	float Length()
	{
		return sqrt((x * x) + (y * y));
	}

	float Dist(Vector2 ape)
	{
		return (*this - ape).Length();
	}
};

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0), z(0) {}

	// Constructor for initialization
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	Vector3 operator-(Vector3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	Vector3 operator+(Vector3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	Vector3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	Vector3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	Vector3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	Vector3 operator+=(Vector3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	Vector3 operator-=(Vector3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(Vector3 ape)
	{
		return (*this - ape).Length2D();
	}

	float Dot(Vector3& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	bool Valid()
	{
		return !std::isnan(x) && !std::isnan(y) && !std::isnan(z);
	}

	bool IsZero()
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}
};