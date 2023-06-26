#include "QuadTreeADT.h"
#include <iostream>

using namespace std;

int main() {
  Quad plane2D(Point(-10, -10), Point(10, 10));
  Node p1(Point(-5, -5), 10);
  Node p2(Point(-2, 3), 7);
  Node p3(Point(1, -4), 5);
  Node p4(Point(3, 1), 3);
  Node p5(Point(5, 5), 9);

  plane2D.insert(&p1);
  plane2D.insert(&p2);
  plane2D.insert(&p3);
  plane2D.insert(&p4);
  plane2D.insert(&p5);
  
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

  // Mostrar los puntos en la lista
  list<Node*> pointList = plane2D.list();//Declaración lista
  for (const auto& node : pointList) {
    Point point = node->pos;
    int value = node->data;
    cout << "Point (" << point.x << ", " << point.y << ") - Value: " << value << std::endl;
  }

  //Delacración centro y distancia
  Point center(1, 1);
  int distance = 2;

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
  cout << "Searching points in region with center (2, 2) and distance 3:" << endl;
  list<Node*> regionPoints = plane2D.searchRegion(Point(2, 2), 3);
  if (regionPoints.empty())
      cout << "No points found in the region." << endl;
  else {
      for (const auto& node : regionPoints) {
          Point point = node->pos;
          int value = node->data;
          cout << "Point (" << point.x << ", " << point.y << ") - Value: " << value << endl;
      }
  }

  //remove region

  return 0;
}