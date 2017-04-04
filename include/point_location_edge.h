//
// Created by Xiaoqian Mu on 4/1/17.
//
#include "geo_dcel_vertex.hpp"
#include "geo_dcel_halfedge.hpp"
#include "geo_dcel_face.hpp"

#ifndef PROJECT_POINT_LOCATION_EDGE_H
#define PROJECT_POINT_LOCATION_EDGE_H

namespace geo
{
class PointLocationEdge{
public:
    DoubleEdgeListVertex* v_l;
    DoubleEdgeListVertex* v_r;

    DoubleEdgeListFace* face_up;

    PointLocationEdge()
    : v_l(nullptr),
      v_r(nullptr)
    {};

    PointLocationEdge(DoubleEdgeListHalfEdge* halfedge) {
        if (halfedge->origin->point.x < halfedge->twin->origin->point.x) {
            v_l = halfedge->origin;
            v_r = halfedge->twin->origin;
        } else {
            v_r = halfedge->origin;
            v_l = halfedge->twin->origin;
        }
        halfedge->visited = true;
        halfedge->twin->visited = true;

    }

};

}
#endif //PROJECT_POINT_LOCATION_EDGE_H
