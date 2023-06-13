#pragma once
#include <iostream>

using namespace std;

class Point{
    private:
        int x, y;

    public:
        Point(int a, int b){
            x=a;
            y=b;
        }
};

class QuadTree{
    private:    
        int total_points, white_nodes, black_nodes;

    public:
        QuadTree(Point a, Point b){
            total_points = 0;
            white_nodes = 0;
            black_nodes = 0;
        }
        
        ~QuadTree(){}
        
        int totalPoints(){
            return total_points;
        }
        
        int totalNodes(){   //No estoy seguro si te piden el total de nodos o ambos por separado. Discutamoslo entre los tres!
            //cout<<"White Nodes: "<<white_nodes<<" || Black Nodes: "<<black_nodes<<endl;
            return white_nodes + black_nodes;
        }
        
        void insert(Point p, int d){}

        //list(){}
        
        int countRegion(Point p, int d){}
    
        int AggregateRegion(Point p, int d){}
};
