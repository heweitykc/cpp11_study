#include "stdafx.h"
#include "vector.h"
#include <cmath>

namespace GEOM
{
	Vector::Vector(double x, double y, char form = 'r') :_x(x), _y(y), _form(form)
	{
	}

	Vector Vector::operator+ (const Vector &b) const
	{
		return Vector(_x + b._x, _y + b._y);
	}

	Vector Vector::operator-(const Vector &b)const
	{
		return Vector(_x - b._x, _y - b._y);
	}

	Vector Vector::operator-()const
	{
		return Vector(-_x,-_y);
	}

	Vector Vector::operator*(double n)const
	{
		return Vector(n*_x, n*_y);
	}

	double Vector::get_x()
	{
		return _x;
	}

	double Vector::get_y()
	{
		return _y;
	}

}