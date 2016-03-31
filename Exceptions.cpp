//
// Created by Nikki on 3/29/2016.
//

#include <string>
#include <iostream>

#include "Exceptions.h"

using std::string;
using std::ostream;
using std::istream;

namespace Clustering
{
	OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r):
	__current(c), __rhs(r)
	{
		this->__name = "OutOfBoundsEx";
	}

	unsigned int OutOfBoundsEx::getCurrent() const
	{
		return __current;
	}

	int OutOfBoundsEx::getRhs() const
	{
		return __rhs;
	}

	string OutOfBoundsEx::getName() const
	{
		return __name;
	}

	ostream &operator<<(ostream &os, const OutOfBoundsEx &ex)
	{
		os << ex.getName() << ", " << ex.getCurrent() << ", " << ex.getRhs();
		return os;
	}

	DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r):
	__current(c), __rhs(r)
	{
		this->__name = "DimensionalityMismatchEx";
	}

	unsigned int DimensionalityMismatchEx::getCurrent() const
	{
		return __current;
	}

	unsigned int DimensionalityMismatchEx::getRhs() const
	{
		return __rhs;
	}

	string DimensionalityMismatchEx::getName() const
	{
		return __name;
	}

	ostream &operator<<(ostream &os, const DimensionalityMismatchEx &ex)
	{
		os << ex.getName() << ", " << ex.getCurrent() << ", " << ex.getRhs();
		return os;
	}

	ZeroClustersEx::ZeroClustersEx()
	{
		this->__name = "ZeroClustersEx";
	}

	string ZeroClustersEx::getName() const
	{
		return __name;
	}

	ostream &operator<<(ostream &os, const ZeroClustersEx &ex)
	{
		os << ex.getName();
		return os;
	}

	DataFileOpenEx::DataFileOpenEx(string filename):
	__filename(filename)
	{
		this->__name = "DataFileOpenEx";
	}

	string DataFileOpenEx::getFilename() const
	{
		return __filename;
	}

	string DataFileOpenEx::getName() const
	{
		return __name;
	}

	ostream &operator<<(ostream &os, const DataFileOpenEx &ex)
	{
		os << ex.getName() << ", " << ex.getFilename();
		return os;
	}

	ZeroDimensionsEx::ZeroDimensionsEx()
	{
		this->__name = "ZeroDimensionsEx";
	}

	string ZeroDimensionsEx::getName() const
	{
		return __name;
	}

	ostream &operator<<(ostream &os, const ZeroDimensionsEx &ex)
	{
		os << ex.getName();
		return os;
	}

	EmptyClusterEx::EmptyClusterEx()
	{
		this->__name = "EmptyClusterEx";
	}

	string EmptyClusterEx::getName() const
	{
		return __name;
	}

	ostream &operator<<(ostream &os, const EmptyClusterEx &ex)
	{
		os << ex.getName();
		return os;
	}
}