//
// Created by Xiaoqian Mu on 4/2/17.
//
#include "point_location_rbtree.h"

using namespace geo;

bool PlCompare::less(PointLocationEdge* e1, PointLocationEdge* e2){
    if(e1!= nullptr&&e2!= nullptr) {
        if (e1->v_r->point.y > e2->v_r->point.y)
            return true;
        if(e1->v_r->point.y == e2->v_r->point.y) {
            if (e1->v_r->point.x < e2->v_r->point.x)
                return true;
            else if(e1->v_r->point.x == e2->v_r->point.x){
                if(e1->v_l->point.y > e2->v_l->point.y)
                    return true;
            }
        }

    }
    return false;
}

bool PlCompare::less(PointLocationVertex* v2, PointLocationEdge *e1) {
    double lx=e1->v_l->point.x;
    double ly=e1->v_l->point.y;
    double rx=e1->v_r->point.x;
    double ry=e1->v_r->point.y;
    double x=v2->vertex->point.x;
    double y=v2->vertex->point.y;
    if(x==lx&&y>ly)
        return false;

    if(y<ly+(x-lx)/(rx-lx)*(ry-ly))
        return false;

    return true;
}

bool PlCompare::less(PointLocationEdge *e1, PointLocationVertex *v2) {
    double lx=e1->v_l->point.x;
    double ly=e1->v_l->point.y;
    double rx=e1->v_r->point.x;
    double ry=e1->v_r->point.y;
    double x=v2->vertex->point.x;
    double y=v2->vertex->point.y;
    if(x==lx&&y>ly)
        return true;

    if(y<ly+(x-lx)/(rx-lx)*(ry-ly))
        return true;

    return false;
}

PLRbTree::PLRbTree(std::vector<PointLocationEdge> nodes, std::vector<PointLocationVertex> vers) {
    PlCompare* cmp = new PlCompare();

    for(int i=0;i<vers.size();i++) {


        std::shared_ptr<PLRBTree> rbtree = std::make_shared<PLRBTree>(cmp);
        if (i== 0) {

            for(int p=i+1;p<vers.size();p++)
            {
                if(vers[p].vertex->point.x==vers[i].vertex->point.x)
                    i++;
                else break;
            }

            for(int j=0;j<vers[i].edge_delete.size();j++){
                rbtree->delete_value(vers[i].edge_delete[j]);
            }

            for(int k=0;k<vers[i].edge_insert.size();k++){
                rbtree->insert(vers[i].edge_insert[k]);

            }
        }
        else{
            for(int p=i+1;p<vers.size();p++)
            {
                if(vers[p].vertex->point.x==vers[i].vertex->point.x)
                    i++;
                else break;
            }

            for(int m=0;m<=i;m++){
                for(int j=0;j<vers[m].edge_delete.size();j++){
                    rbtree->delete_value(vers[m].edge_delete[j]);
                }

                for(int k=0;k<vers[m].edge_insert.size();k++){
                    rbtree->insert(vers[m].edge_insert[k]);

                }
            }

        }

        double x_coor=vers[i].vertex->point.x;
        roots.push_back(x_coor);
        trees.push_back(rbtree);

    }

    delete cmp;
}
//
//PLRbTree::PLRbTree(std::vector<PointLocationEdge> nodes, std::vector<PointLocationVertex> vers) {
//    PlCompare* cmp= new PlCompare();
//    tree=RBTree<PointLocationEdge*, PointLocationVertex*, PlCompare>(cmp);
//    for(int i=0;i<vers.size();i++) {
//        if(i==0){
//            for(int j=0;j<vers[0].edge_insert.size();j++)
//                tree.insert(vers[0].edge_insert[j]);
//
//            roots.push_back(tree.root->value);
//        }
//        else{
////            for(int j=0;j<vers[i].edge_delete.size();j++){
////                if(tree.root->value->v_r->point.y>vers[i].edge_delete[j]->v_r->point.y){
////
////                }
////
////            }
//        }
//
//    }
//    delete cmp;
//}

int PLRbTree::Find_location(double x, double y) {
    int low=0;
    int high=roots.size()-1;
    int mid=0;
    int location=-1;
    if(x<roots[low]||x>roots[high])
        return -1;

    if(x>=roots[low]&&x<roots[low+1]) {
        location = low;
    }
    if(x>=roots[high]&&x<roots[high+1]) {
        location = high;
    }

    while(location<0) {
        mid=(low+high)/2;
        if(x>=roots[mid]&&x<roots[mid+1])
            location=mid;
        if(x<roots[mid]){
            high=mid;
        }
        if(x>roots[mid+1])
            low=mid;
    }
    return location;
}

//DoubleEdgeListFace* PLRbTree::Search_point(int loc, PointLocationVertex* ver) {
//
//    PointLocationEdge* edge_below=new PointLocationEdge();
//    PointLocationEdge* edge_above=new PointLocationEdge();
//    if(trees[loc]->get_smaller(ver,edge_below)&&trees[loc]->get_larger(ver,edge_above))
//        return edge_below->v_l->leaving->getFace();
//    else{
//        return nullptr;
//    }
//}

PointLocationEdge* PLRbTree::Search_point(int loc, PointLocationVertex* ver) {

    PointLocationEdge* edge_below=new PointLocationEdge();
    PointLocationEdge* edge_above=new PointLocationEdge();
    if(trees[loc]->get_smaller(ver,edge_below)&&trees[loc]->get_larger(ver,edge_above))
        return edge_below;
    else{
        return nullptr;
    }
}
bool PLRbTree::above(double lx, double ly, double rx, double ry, double x, double y) {
    if(x==lx&&y>ly)
        return true;

    if(y<ly+(x-lx)/(rx-lx)*(ry-ly))
        return true;

    return false;
}

