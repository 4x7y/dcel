//
// Created by Xiaoqian Mu on 4/4/17.
//

#ifndef PROJECT_POINT_LOCATION_PERSISTENT_RBTREE_H
#define PROJECT_POINT_LOCATION_PERSISTENT_RBTREE_H
#include "geo_rbtree.hpp"
#include "point_location_edge.h"
#include "point_location_vertex.h"
#include <stdio.h>
#include <vector>

//namespace geo{
////template<typename ValueT, typename SearchT, class Compare>
//    class PlCompare{
//    public:
//        bool less(PointLocationEdge* e1, PointLocationEdge* e2);
//        bool less(PointLocationVertex* v2,PointLocationEdge* e1 );
//        bool less(PointLocationEdge* e1, PointLocationVertex* v2);
//
//    };
//    class PLPersistentRbTree{
//    public:
//
//        typedef RBTree<PointLocationEdge*, PointLocationVertex*, PlCompare> PLRBTree;
//
//        std::vector<double> roots;
//        std::vector<std::shared_ptr<PLRBTree>> trees;
//        RBTree<PointLocationEdge*, PointLocationVertex*, PlCompare> tree;
//
//        std::shared_ptr<PLRBTree> ptree;
//        std::vector<RBTree<PointLocationEdge*, PointLocationVertex*, PlCompare>::Node*> tree_roots;
//
//        PLPersistentRbTree():roots(),trees(){};
//        PLPersistentRbTree(std::vector<PointLocationEdge> nodes, std::vector<PointLocationVertex> vers);
//
//        int Find_location(double x, double y);
//
//        PointLocationEdge* Search_point(int loc, PointLocationVertex* ver);
//        bool above(double lx, double ly, double rx, double ry,double x,double y);
//    };
//}
#endif //PROJECT_POINT_LOCATION_PERSISTENT_RBTREE_H
