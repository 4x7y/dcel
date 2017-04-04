//
// Created by Xiaoqian Mu on 4/4/17.
//
#include "point_location_persistent_rbtree.h"
using namespace geo;

//bool PlCompare::less(PointLocationEdge* e1, PointLocationEdge* e2){
//    if(e1!= nullptr&&e2!= nullptr) {
//        if (e1->v_r->point.y > e2->v_r->point.y)
//            return true;
//        if(e1->v_r->point.y == e2->v_r->point.y) {
//            if (e1->v_r->point.x < e2->v_r->point.x)
//                return true;
//            else if(e1->v_r->point.x == e2->v_r->point.x){
//                if(e1->v_l->point.y > e2->v_l->point.y)
//                    return true;
//            }
//        }
//
//    }
//    return false;
//}
//
//bool PlCompare::less(PointLocationVertex* v2, PointLocationEdge *e1) {
//    double lx=e1->v_l->point.x;
//    double ly=e1->v_l->point.y;
//    double rx=e1->v_r->point.x;
//    double ry=e1->v_r->point.y;
//    double x=v2->vertex->point.x;
//    double y=v2->vertex->point.y;
//    if(x==lx&&y>ly)
//        return false;
//
//    if(y<ly+(x-lx)/(rx-lx)*(ry-ly))
//        return false;
//
//    return true;
//}
//
//bool PlCompare::less(PointLocationEdge *e1, PointLocationVertex *v2) {
//    double lx=e1->v_l->point.x;
//    double ly=e1->v_l->point.y;
//    double rx=e1->v_r->point.x;
//    double ry=e1->v_r->point.y;
//    double x=v2->vertex->point.x;
//    double y=v2->vertex->point.y;
//    if(x==lx&&y>ly)
//        return true;
//
//    if(y<ly+(x-lx)/(rx-lx)*(ry-ly))
//        return true;
//
//    return false;
//}
//
//PLPersistentRbTree::PLPersistentRbTree(std::vector<PointLocationEdge> nodes, std::vector<PointLocationVertex> vers) {
//    PlCompare* cmp = new PlCompare();
//
//    for(int i=0;i<vers.size();i++) {
//
//
//        std::shared_ptr<PLRBTree> rbtree = std::make_shared<PLRBTree>(cmp);
//        if (i== 0) {
//
//            for(int p=i+1;p<vers.size();p++)
//            {
//                if(vers[p].vertex->point.x==vers[i].vertex->point.x)
//                    i++;
//                else break;
//            }
//
//            for(int j=0;j<vers[i].edge_delete.size();j++){
//                rbtree->delete_value(vers[i].edge_delete[j]);
//            }
//
//            for(int k=0;k<vers[i].edge_insert.size();k++){
//                rbtree->insert(vers[i].edge_insert[k]);
//
//            }
//        }
//        else{
//            for(int p=i+1;p<vers.size();p++)
//            {
//                if(vers[p].vertex->point.x==vers[i].vertex->point.x)
//                    i++;
//                else break;
//            }
//
//            for(int m=0;m<=i;m++){
//                for(int j=0;j<vers[m].edge_delete.size();j++){
//                    rbtree->delete_value(vers[m].edge_delete[j]);
//                }
//
//                for(int k=0;k<vers[m].edge_insert.size();k++){
//                    rbtree->insert(vers[m].edge_insert[k]);
//
//                }
//            }
//
//        }
//
//        double x_coor=vers[i].vertex->point.x;
//        roots.push_back(x_coor);
//        trees.push_back(rbtree);
//
//    }
//
//    delete cmp;
//}
