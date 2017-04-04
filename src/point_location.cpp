//
// Created by Xiaoqian Mu on 4/1/17.
//

#include <List>
#include "point_location.h"
#include <iostream>
using namespace geo;
using namespace std;


PointLocation::PointLocation(DoubleEdgeList* dcel){

    Create_edgeslist(dcel);
    Create_verticeslist(dcel);
    Create_PLTree();
    //double l=pl_tree.Find_location(360,100);

//    if(l!=-1) {
//        Vector2 p = Vector2(360, 100);
//        PointLocationVertex *ver = new PointLocationVertex(p);
//        DoubleEdgeListFace *f = pl_tree.Search_point(l, ver);
//        if(f!= nullptr) {
//            auto k = f->edge;
//        }
//        else{
//            std::cout<<"Out of the polygon"<<endl;
//        }
//    }
//    else{
//        std::cout<<"Out of the polygon"<<endl;
//    }
}

bool PointLocation::Find_point_location(Vector2 &p, geo::Triangle &triangle) {
    double l=pl_tree.Find_location(p.x,p.y);

    if(l!=-1) {
        PointLocationVertex *ver = new PointLocationVertex(p);
        PointLocationEdge *e = pl_tree.Search_point(l, ver);
        if(e!= nullptr) {
            triangle.point1.x=e->v_l->point.x;
            triangle.point1.y=e->v_l->point.y;
            triangle.point2.x=e->v_r->point.x;
            triangle.point2.y=e->v_r->point.y;
            triangle.point3.x=e->v_r->leaving->next->twin->origin->point.x;
            triangle.point3.y=e->v_r->leaving->next->twin->origin->point.y;
            return true;
        }
        else{
            //std::cout<<"Out of the polygon"<<endl;
            return false;
        }
    }
    else{
        //std::cout<<"Out of the polygon"<<endl;
        return false;
    }
}

void PointLocation::Create_edgeslist(DoubleEdgeList *dcel) {
    DoubleEdgeListHalfEdge* start;
    for(int i=0;i<dcel->edges.size();i++){
        start=dcel->edges.front();
        if(!start->visited) {
            PointLocationEdge new_edge =PointLocationEdge(start);
            edges.push_back(new_edge);
        }

        dcel->edges.pop_front();
        dcel->edges.push_back(start);

    }

//    for(auto it=dcel->edges.begin(); it!=dcel->edges.end();++it){
//        if(!it->visited)
//    }
}

void PointLocation::Create_verticeslist(DoubleEdgeList *dcel) {
    //DoubleEdgeListVertex* new_vertex=dcel->vertices.front();

    for(int i=0;i<dcel->vertices.size();i++){
        PointLocationVertex new_vertex=PointLocationVertex(dcel->vertices.front());
//        new_vertex.vertex=dcel->vertices.front();
//
        for(int j=0;j<edges.size();j++){
            if(edges[j].v_l==new_vertex.vertex){
                new_vertex.edge_insert.push_back(&edges[j]);
            }
            if(edges[j].v_r==new_vertex.vertex){
                new_vertex.edge_delete.push_back(&edges[j]);
            }
        }

        dcel->vertices.pop_front();
        dcel->vertices.push_back(new_vertex.vertex);
        vertices.push_back(new_vertex);

        int s=vertices.size();
        s=s+0;
    }
}

void PointLocation::Create_PLTree() {
    pl_tree=PLRbTree(edges,vertices);
}

//void PointLocation::Find_location(double x, double y) {
//    int low=0;
//    int high=pl_tree.roots.size()-1;
//    int mid=0;
//    int location=-1;
//
//    if(x>=pl_tree.roots[low]&&x<pl_tree.roots[low+1]) {
//        location = low;
//    }
//    if(x>=pl_tree.roots[high]&&x<pl_tree.roots[high+1]) {
//        location = high;
//    }
//
//    while(location<0) {
//        mid=(low+high)/2;
//        if(x>=pl_tree.roots[mid]&&x<pl_tree.roots[mid+1])
//            location=mid;
//        if(x<pl_tree.roots[mid]){
//            high=mid;
//        }
//        if(x>pl_tree.roots[mid+1])
//            low=mid;
//    }
//}

