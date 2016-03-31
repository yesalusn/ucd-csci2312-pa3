//
// Created by Nikki on 2/11/2016.
//

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "Cluster.h"

using std::istream;
using std::ostream;
using std::endl;
using std::string;

namespace Clustering
{
	LNode::LNode(const Point &p, LNodePtr n):
	point(p), next(n)
	{}

	Cluster::Centroid::Centroid(unsigned int d, const Cluster &c):
	__dimensions(d), __c(c), __p(d)
	{
		if(__c.__size == 0)
		{
			__valid = false;
			toInfinity();
		}
	}

	const Point Cluster::Centroid::get() const
	{
		return __p;
	}

	void Cluster::Centroid::set(const Point &p)
	{
		__p = p;
	}

	bool Cluster::Centroid::isValid() const
	{
		return __valid;
	}

	void Cluster::Centroid::setValid(bool valid)
	{
		__valid = valid;
	}

	void Cluster::Centroid::compute()
	{
		//compute average of cluster's points
	}

	bool Cluster::Centroid::equal(const Point &point) const
	{
		//compare only double values and ignore id
		return false;
	}

	void Cluster::Centroid::toInfinity()
	{
		//sets a centroid of an empty cluster to an infinite point
	}

	Cluster::Cluster(unsigned int d):
	__dimensionality(d), __size(0), __points(nullptr), __id(++__idGenerator),
	centroid(__dimensionality, *this)
	{}

	Cluster::Cluster(const Cluster &other):
	__dimensionality(other.__dimensionality), __size(other.__size),
	__points(nullptr), __id(other.__id), centroid(other.__dimensionality, *this)
	{
		if(other.__points != nullptr)
		{
			LNodePtr currNode = other.__points; // temp ptr to other head
			Point point(currNode->point); //copy of other data
			LNodePtr newNode = new LNode(point, nullptr); // new node to hold new data
			__points = newNode; // point this head to new node
			currNode = currNode->next; // move temp ptr
			LNodePtr thisNode = __points; // temp ptr to this head

			while(currNode != nullptr) // loop thru other data
			{
				point = currNode->point;
				newNode = new LNode(point, nullptr);
				thisNode->next = newNode;
				thisNode = thisNode->next;
				currNode = currNode->next;
			}
		}
	}

	Cluster &Cluster::operator=(const Cluster &other)
	{
		if(this != &other)
		{
			LNodePtr currNode = __points;
			LNodePtr nextNode = nullptr;
			while(currNode != nullptr && __size > 0)
			{
				LNodePtr temp = currNode;
				currNode = currNode->next;
				delete temp;
				--__size;
			}
			__points = nullptr;
			__size = other.__size;
			currNode = __points;
			nextNode = other.__points;
			while(nextNode != nullptr)
			{
				LNodePtr newNode = new LNode(nextNode->point, nullptr);
				currNode->next;
				nextNode = nextNode->next;
			}
		}
		return *this;
	}

	Cluster::~Cluster()
	{
		LNodePtr currNode = __points;
		while (currNode != nullptr && __size > 0)
		{
			LNodePtr temp = currNode;
			currNode = currNode->next;
			delete temp;
		}
		__points = nullptr;
		__size = 0;
	}

	unsigned int Cluster::getSize() const
	{
		return __size;
	}

	unsigned int Cluster::getDimensionality() const
	{
		return __dimensionality;
	}

	unsigned int Cluster::getId() const
	{
		return __id;
	}

	void Cluster::add(const Point &p)
	{
		Point point(p);
		LNodePtr newNode = new LNode(point, nullptr);
		if(__points == nullptr && __size == 0)
		{
			__points = newNode;
			++__size;
			return;
		}
		else
		{
			if(point < __points->point)
			{
				newNode->next = __points;
				__points = newNode;
				++__size;
			}
			else
			{
				LNodePtr prevNode = __points;
				LNodePtr currNode = prevNode->next;
				if(currNode != nullptr)
				{
					bool inserted = false;
					while(!(inserted) && currNode != nullptr)
					{
						if(point < currNode->point)
						{
							newNode->next = currNode;
							prevNode->next = newNode;
							inserted = true;
							++__size;
						}
						else
						{
							prevNode = currNode;
							currNode = currNode->next;
						}
					}
				}
				if(currNode == nullptr)
				{
					prevNode->next = newNode;
					++__size;
				}
			}
		}
	}

	const Point &Cluster::remove(const Point &p)
	{
		if(__points != nullptr)
		{
			if(__points->point == p)
			{
				LNodePtr temp = __points;
				__points = __points->next;
				delete temp;
				--__size;
				return p;
			}
			else
			{
				LNodePtr currNode = __points->next;
				while(currNode != nullptr)
				{
					if(currNode->point == p)
					{
						LNodePtr temp = currNode;
						currNode = currNode->next;
						delete temp;
						--__size;
						return p;
					}
					currNode = currNode->next;
				}
			}

		}
		return p;
	}

	bool Cluster::contains(const Point &p) const
	{
		if(__points != nullptr)
		{
			LNodePtr currNode = __points;
			while (currNode != nullptr)
			{
				if(currNode->point == p)
					return true;
				else
					currNode = currNode->next;
			}
			return false;
		}
		else
			return false;
	}

	void Cluster::pickCentroids(unsigned int k, Point **pointArray)
	{	}

	const Point &operator[](unsigned int u) const
	{
		return Point(0);
	}

	ostream &operator<<(ostream &os, const Cluster &c)
	{
		if(c.__points != nullptr)
		{
			LNodePtr currNode = c.__points;
			while(currNode != nullptr)
			{
				os << currNode->point;
				currNode = currNode->next;
			}
		}
		else
			os << "There is no cluster." << endl;
		return os;
	}

	istream &operator>>(istream &is, Cluster &cluster)
	{
		string line;
		while(getline(is, line))
		{
			std::stringstream linestream(line);
			int d = (int)std::count(line.begin(), line.end(), " ,");
			Point p(d);
			linestream >> p;
		}
		return is;
	}

	bool operator==(const Cluster &lhs, const Cluster &rhs)
	{
		if(&lhs != &rhs)
		{
			if(lhs.getSize() == rhs.getSize())
			{
				LNodePtr thisOne = lhs.__points;
				LNodePtr thatOne = rhs.__points;

				while(thisOne != nullptr && thatOne != nullptr)
				{
					if (thisOne->point != thatOne->point)
						return false;
					thisOne = thisOne->next;
					thatOne = thatOne->next;
				}
				return true;
			}
			else
				return false;
		}
		else
			return true;
	}

	bool Clustering::operator!=(const Cluster &lhs, const Cluster &rhs)
	{
		bool notequal = true;
		if(lhs == rhs)
			notequal = false;
		return notequal;
	}

	Cluster &Cluster::operator+=(const Point &rhs)
	{
		this->add(rhs);
		return *this;
	}

	Cluster &Cluster::operator-=(const Point &rhs)
	{
		this->remove(rhs);
		return *this;
	}

	Cluster &Cluster::operator+=(const Cluster &rhs)
	{
		if (this != &rhs)
		{
			if(rhs.__points != nullptr)
			{
				if(this->__points == nullptr)
					*this = rhs;
				else
				{
					LNodePtr currNode = rhs.__points;
					while(currNode != nullptr)
					{
						if (!(this->contains(currNode->point)))
							this->add(currNode->point);
						currNode = currNode->next;
					}
				}
			}
		}
		return *this;
	}

	Cluster &Cluster::operator-=(const Cluster &rhs)
	{
		if (this != &rhs)
		{
			if(rhs.__points != nullptr)
			{
				if(this->__points != nullptr)
				{
					LNodePtr currNode = rhs.__points;
					while(currNode != nullptr)
					{
						if(this->contains(currNode->point))
							this->remove(currNode->point);
						currNode = currNode->next;
					}
				}
			}
		}
		return *this;
	}

	const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
	{
		Cluster newC(lhs);
		newC += rhs;
		return newC;
	}

	const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
	{
		Cluster newC(lhs);
		newC -= rhs;
		return newC;
	}

	const Cluster operator+(const Cluster &lhs, const Point &rhs)
	{
		Cluster newC(lhs);
		newC += rhs;
		return newC;
	}

	const Cluster operator-(const Cluster &lhs, const Point &rhs)
	{
		Cluster newC(lhs);
		newC -= rhs;
		return newC;
	}

	Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to):
			__p(p), __from(from), __to(to)
	{}

	void Cluster::Move::perform()
	{
		__to.add(__from.remove(__p));
		__to.centroid.setValid(false);
		__from.centroid.setValid(false);
	}
}