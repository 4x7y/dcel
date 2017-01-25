#ifndef util_hpp
#define util_hpp

namespace geo
{

template <typename __Tpp, int _Dim>
class Point_ {
};

// 2 Dimension Point
template <typename _Tp>
class Point2_ : public Point_<_Tp, 2>
{
public:
    _Tp x, y;
    
    Point2_(_Tp x, _Tp y)
    : x(x)
    , y(y)
    { }
    
    bool operator < (const Point2_ &p2);
};

template <typename _Tp>
bool Point2_<_Tp> :: operator < (const Point2_<_Tp> &p2)
{
	return (x < p2.x) || (x == p2.x && y < p2.y);
} 

typedef Point2_<double> Point2d;
typedef Point2_<float>  Point2f;
typedef Point2_<int>    Point2i;

inline Point2i point2i(int x, int y)
{
    return Point2i(x,y);
}

inline Point2f point2f(float x, float y)
{
    return Point2f(x, y);
}

inline Point2d point2d(double x, double y)
{
    return Point2d(x, y);
}

// 3 Dimension Point
template <typename _Tp>
class Point3_ : public Point_<_Tp,3>
{
public:
    _Tp x, y, z;
    
	Point3_(_Tp x, _Tp y, _Tp z)
	: x(x)
    , y(y)
    , z(z)
    { }
    
    bool operator < (const Point3_ &p2);
};
    
template<typename _Tp>
bool Point3_<_Tp>::operator < (const Point3_<_Tp> &p2)
{
    return  (x < p2.x) ||
            (x == p2.x && y < p2.y) ||
            (x == p2.x && y == p2.y && z < p2.z);
}

typedef Point3_<double> Point3d;
typedef Point3_<float>  Point3f;
typedef Point3_<int>    Point3i;

inline Point3i point3i(int x, int y, int z)
{
    return Point3i(x, y, z);
}

inline Point3f point3f(float x, float y, float z)
{
    return Point3f(x, y, z);
}

inline Point3d point3d(double x, double y, double z)
{
    return Point3d(x, y, z);
}

// Edge Base
template <typename _Tp, int Dimensions>
class Edge_ {
public:
    Point_<_Tp, Dimensions> s, t;
    
    Edge_(Point_<_Tp, Dimensions> s, Point_<_Tp, Dimensions> t)
		: s(s)
		, t(t)
    { }
};
    
// 2 Dimension
template <typename _Tp>
class Edge2_ : public Edge_<_Tp,2>
{
	Edge2_(Point2_<_Tp> s, Point2_<_Tp> t)
		: Edge_(s, t)
	{};
};
    
// 3 Dimension
template <typename _Tp>
class Edge3_ : public Edge_<_Tp,3>
{
	Edge3_(Point3_<_Tp> s, Point3_<_Tp> t)
		: Edge_(s, t)
	{};
};

typedef Edge2_<double> Edge2d;
typedef Edge2_<float>  Edge2f;
typedef Edge2_<int>    Edge2i;

typedef Edge3_<double> Edge3d;
typedef Edge3_<float>  Edge3f;
typedef Edge3_<int>    Edge3i;

}

#endif /* util_hpp */
