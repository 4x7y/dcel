#ifndef GEO_STATUS_HPP
#define GEO_STATUS_HPP

#include <utility>
#include <iostream>

#include "geo_rbtree.hpp"

namespace geo
{



template<typename LinePtr, typename PointPtr, typename _Tp>
class Status
{
	typedef RBTree<LinePtr, Status<LinePtr, PointPtr, _Tp>> Tree;
		
	Tree*	m_tree;
	_Tp		m_curr_x;

	bool isUpperPoint(const PointPtr& point, const LinePtr& line) const
	{
		if (point->y > line->y(m_curr_x))
		{
			return true;
		}

		return false;
	}

public:

	bool less(LinePtr& line1, LinePtr& line2)
	{
		if (line1->y(m_curr_x) < line2->y(m_curr_x))
		{
			return true;
		};

		return false;
	}
	
	Status() {
		m_tree = new Tree(this);
	};

	~Status() {
		delete m_tree;
	}

	void insert(LinePtr line)
	{
		m_tree->insert(line);
	}

	void set_x(_Tp x)
	{
		m_curr_x = x;
	}
};


} // namespace geo


#endif /* GEO_STATUS_HPP */