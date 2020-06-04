#include "Vector2D.h"

#include <cmath>

#define PI 3.141592653589793238462643383279502884

Vector2D& Vector2D::operator=(const Vector2D& vec) {
    this->x = vec.x;
    this->y = vec.y;

    return *this;
}

Vector2D& Vector2D::add(const Vector2D& vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec) {
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec) {
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D operator+(Vector2D v1, const Vector2D& v2) {
    return v1.add(v2);
}

Vector2D operator-(Vector2D v1, const Vector2D& v2) {
    return v1.subtract(v2);
}

Vector2D operator*(Vector2D v1, const Vector2D& v2) {
    return v1.multiply(v2);
}

Vector2D operator/(Vector2D v1, const Vector2D& v2) {
    return v1.divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    return this->add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    return this->subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
    return this->multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
    return this->divide(vec);
}

Vector2D Vector2D::operator*(const double& i) {
	Vector2D newV(x,y);
    newV.x *= i;
    newV.y *= i;

    return newV;
}

Vector2D& Vector2D::zero() {
    this->x = 0;
    this->y = 0;

    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}

Vector2D Vector2D::rotate(double deg) {
    double rad = deg * PI / 180.0;
    double rotatedX = x * cos(rad) - y * sin(rad);
    double rotatedY = x * sin(rad) + y * cos(rad);
    return Vector2D(rotatedX, rotatedY);
}

double Vector2D::getRotateDeg() {
    return atan2(y, x) / PI * 180.0;
}

double Vector2D::length() {
	return sqrt(x*x+y*y);
}
