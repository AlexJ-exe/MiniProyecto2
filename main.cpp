#include "QuadTreeADT.h"
#include <iostream>

using namespace std;

int main() {
 Quad plane2D(Point(0, 0), Point(8, 8));
  Node p1(Point(0, 0), 5);
  Node p2(Point(0, 1), 4);
  Node p3(Point(1, 0), 2);
  Node p4(Point(1, 1), 1);
  Node p5(Point(2, 1), 1);
  Node p6(Point(5, 1), 3);
  Node p7(Point(6, 2), 10);
  Node p8(Point(7, 7), 8);
  
  plane2D.insert(&p1);
  plane2D.insert(&p2);
  plane2D.insert(&p3);
  plane2D.insert(&p4);
  plane2D.insert(&p5);
  plane2D.insert(&p6);
  plane2D.insert(&p7);
  plane2D.insert(&p8);

Point center(4, 2);
int distance = 2;

  
  cout << "Contenido en la coordenada (5,1): ";
  Node * p = plane2D.search(Point(5, 1));
  if(p != NULL) cout << p->data << endl;
  else cout << "No existe el punto." << endl;
  // Contenido en la coordenada (5,1): 3

  cout << "Contenido en la coordenada (1,5): ";
  p = plane2D.search(Point(1, 5));
  if(p != NULL) cout << p->data << endl;
  else cout << "No existe el punto." << endl;
  // Contenido en la coordenada (1,5): No existe el punto.
  
  //Prueba de metodos requeridos

  //Prueba del método totalPoints
  cout << "Total Points test 2: "<< plane2D.totalPoints()<<endl;

  //Prueba del método totalNodes
  cout << "Total Nodes test 1: "<< plane2D.totalNodes()<<endl;

  // Obtener la lista de puntos almacenados en el Quadtree
  std::list<std::pair<Point, int>> pointList = plane2D.list();

  // Imprimir los puntos y sus valores asociados
  for (const auto& point : pointList) {
    std::cout << "Point: (" << point.first.x << ", " << point.first.y << "), Value: " << point.second << std::endl;
  }


  //Prueba del método countRegion
  int count = plane2D.countRegion(center, distance);
  std::cout << "Number of points in the region: " << count << std::endl;

  //Prueba del método aggregateRegion
  int aggregate = plane2D.aggregateRegion(center, distance);
  std::cout << "Aggregate value in the region: " << aggregate << std::endl;

  //Prueba del método remove
  cout << "Removing point at (5, 1)..." << endl;
  //plane2D.remove(Point(5, 1));

  // Prueba del método searchRegion
  
  /*cout << "Searching points in region with center (2, 2) and distance 3:" << endl;
  list<Node*> regionPoints = plane2D.searchRegion(Point(2, 2), 3);
  if (regionPoints.empty())
      cout << "No points found in the region." << endl;
  else {
      for (const auto& node : regionPoints) {
          Point point = node->pos;
          int value = node->data;
          cout << "Point (" << point.x << ", " << point.y << ") - Value: " << value << endl;
      }
  }*/

  //remove region

  return 0;
}