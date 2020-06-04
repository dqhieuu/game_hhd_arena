#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <iostream>

class Vector2D
{
public:
	double x;
	double y;

	Vector2D():x(0.0), y(0.0) {};
	Vector2D(double _x, double _y):x(_x), y(_y){};
	Vector2D& operator=(const Vector2D& vec);
	Vector2D& add(const Vector2D& vec);
	Vector2D& subtract(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);

	Vector2D rotate(double deg);
	double getRotateDeg();
	double length();

	friend Vector2D operator+(Vector2D v1, const Vector2D& v2);
	friend Vector2D operator-(Vector2D v1, const Vector2D& v2);
	friend Vector2D operator*(Vector2D v1, const Vector2D& v2);
	friend Vector2D operator/(Vector2D v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D operator*(const double& i);
	Vector2D& zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

#endif