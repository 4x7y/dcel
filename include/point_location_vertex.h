//
// Created by Xiaoqian Mu on 4/1/17.
//

#ifndef PROJECT_POINT_LOCATION_VERTEX_H
#define PROJECT_POINT_LOCATION_VERTEX_H

#include <vector>
#include "point_location_edge.h"
namespace geo {
    class PointLocationVertex {
    public:
        DoubleEdgeListVertex* vertex;

        std::vector<PointLocationEdge*> edge_delete;
        std::vector<PointLocationEdge*> edge_insert;

        PointLocationVertex(const Vector2& p):
        vertex(new DoubleEdgeListVertex(p)),
        edge_delete(),
        edge_insert(){};
        PointLocationVertex(DoubleEdgeListVertex* v){
            vertex=v;
        }

        void find_edge_delete(){

        };
        void find_edge_insert(){

        };

    };
}

#endif //PROJECT_POINT_LOCATION_VERTEX_H
