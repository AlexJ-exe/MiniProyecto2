#pragma once

#include "Node.h"
#include <list>
#include <vector>

class Quad {
    Point topLeft;
    Point botRight;
    Node* n;
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

    public:
    Quad();
    Quad(Point topL, Point botR);    
    int totalPoints();
    int totalNodes();
    void insert(Point p, int data);
    void insert(Node* node);
    std::list<std::pair<Point, int>> list();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
    Node* search(Point p);
    bool inBoundary(Point p);
    bool isEmpty();
    void clear();
    void remove(Point p);
    void printAs2DPlane();


    private:
    void countPoints(int& count);
    void countNodes(int& count);
    void listHelper(std::list<std::pair<Point, int>>& result);
    void aggregateRegionHelper(Point p, int d, int& aggregate);
    void countRegionHelper(Point p, int d, int& count);
    bool isWithinRegion(Point center, int distance, Point point);
    bool intersectsRegion(Point center, int distance, Point topLeft, Point botRight);
};
