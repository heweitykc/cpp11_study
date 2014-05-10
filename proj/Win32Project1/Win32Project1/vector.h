#pragma once

namespace GEOM
{
	class Vector
	{
	private:
		double _x;
		double _y;
		char _form;
	public:
		Vector();
		Vector(double n1, double n2, char form);
		Vector operator+(const Vector &b)const;
		Vector operator-(const Vector &b)const;
		Vector operator-()const;
		Vector operator*(double n)const;
		double get_x();
		double get_y();
	};
}