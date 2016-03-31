//
// Created by Nikki on 3/29/2016.
//

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

#include "Point.h"
#include "Exceptions.h"

using std::istream;
using std::ostream;
using std::string;
using std::cout;
using std::endl;

namespace Clustering
{

	unsigned int __idGen = 0;

	const char POINT_VALUE_DELIM = ',';

	void Point::rewindIdGen()
	{
		--__idGen;
	}

	Point::Point(unsigned int i)
	{
		if(i <= 0)
			throw ZeroDimensionsEx();

		__id = ++__idGen;
		__dim = i;

		for(int j = 0; j < __dim; ++j)
		{
			__values[j] = 0.0;
		}
	}

	Point::Point(unsigned int i, double *pDouble):
	__id(++__idGen), __dim(i)
	{
		for(int j = 0; j < __dim; ++j)
		{
			__values[j] = pDouble[j];
		}
	}

	Point::Point(const Point &point):
	__id(point.__id), __dim(point.__dim)
	{
		for(int j = 0; j  < __dim; ++j)
		{
			__values[j] = point.__values[j];
		}
	}

	Point &Point::operator=(const Point &point)
	{
		if(__dim  != point.__dim)
			throw DimensionalityMismatchEx(__dim, point.__dim);

		if(this == &point)
			return *this;

		__id = point.__id;
		__dim = point.__dim;

		for(int j = 0; j < __dim; ++j)
		{
			__values[j] = point.__values[j];
		}

		return *this;
	}

	Point::~Point()
	{
		delete []__values;
	}

	int Point::getId() const
	{
		return __id;
	}

	unsigned int Point::getDims() const
	{
		return __dim;
	}

	void Point::setValue(unsigned int i, double d)
	{
		//throw(OutOfBoundsEx)
		__values[i] = d;
	}

	double Point::getValue(unsigned int i) const
	{
		//throw(OutOfBoundsEx)
		return __values[i];
	}

	double Point::distanceTo(const Point &point) const
	{
		//throw(DimensionalityMismatchEx)
		if (*this != point && __dim == point.getDims())
		{
			double sum = 0;
			double distance;
			for (int i = 0; i < __dim; ++i)
			{
				sum += pow(__values[i] - point.getValue(i), 2);
			}
			distance = sqrt(sum);
			return distance;
		}
		else
			return 0;
	}

	Point &Point::operator*=(double d)
	{
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] *= d;
		}
		return *this;
	}

	Point &Point::operator/=(double d)
	{
		if(d != 0)
		{
			for (int i = 0; i < __dim; ++i)
			{
				__values[i] /= d;
			}
		}
		return *this;
	}

	const Point Point::operator*(double d) const
	{
		Point p(*this);
		p *= d;
		return p;
	}

	const Point Point::operator/(double d) const
	{
		Point p(*this);
		p /= d;
		return p;
	}

	double &Point::operator[](unsigned int index)
	{
		//throw(OutOfBoundsEx)
		return __values[index];
	}

	const double &Point::operator[](unsigned int index) const
	{
		throw(OutOfBoundsEx)
		return __values[index];
	}

	Point &operator+=(Point &point, const Point &point1)
	{
		// throw(DimensionalityMismatchEx)
		if (point.__dim == point1.__dim)
		{
			for (int i = 0; i < point.__dim; ++i)
			{
				point.__values[i] += point1.__values[i];
			}
		}
		return point;
	}

	Point &operator-=(Point &point, const Point &point1)
	{
		//throw(DimensionalityMismatchEx)
		if (point.__dim == point1.__dim)
		{
			for (int i = 0; i < point.__dim; ++i)
			{
				point.__values[i] -= point1.__values[i];
			}
		}
		return point;
	}

	const Point operator+(const Point &point, const Point &point1)
	{
		Point p(point);
		p += point1;
		return p;
	}

	const Point operator-(const Point &point, const Point &point1)
	{
		Point p(point);
		p -= point1;
		return p;
	}

	bool operator==(const Point &point, const Point &point1)
	{
		throw(DimensionalityMismatchEx)
		if(point.__id == point1.__id)
		{
			if(point.__dim == point1.__dim)
			{
				for(int j = 0; j < point.__dim; ++j)
				{
					if (point.__values[j] != point1.__values[j])
						return false;
				}
				//iff all things are equal
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool operator!=(const Point &point, const Point &point1)
	{
		return (!(point == point1));
	}

	bool operator<(const Point &point, const Point &point1)
	{
		throw(DimensionalityMismatchEx)
		if(point.__dim == point1.__dim)
		{
			for(int j = 0; j < point.__dim; ++j)
			{
				if(point.__values[j] < point1.__values[j])
					return true;
				if(point.__values[j] > point1.__values[j])
					return false;
			}
		}
		else
			return false;
	}

	bool operator>(const Point &point, const Point &point1)
	{
		if(point != point1 || !(point < point1))
			return true;
		else
			return false;
	}

	bool operator<=(const Point &point, const Point &point1)
	{
		if(point < point1 || point == point1)
			return true;
		else
			return false;
	}

	bool operator>=(const Point &point, const Point &point1)
	{
		if(point > point1 || point == point1)
			return true;
		else
			return false;
	}

	ostream &operator<<(ostream &os, const Point &point)
	{
		os << point.__id;
		int i = 0;
		for (; i < (point.__dim - 1); ++i)
		{
			os << point.__values[i] << " ,";
		}
		os << point.__values[i] << endl;
		return os;
	}

	istream &operator>>(istream &is, Point &point)
	{
		throw(DimensionalityMismatchEx)
		int i = 0;
		double d = 0.0;
		string value;
		while(getline(is, value, ','))
		{
			d = std::stod(value);
			point.setValue(i++, d);
		}
		return is;
	}
}