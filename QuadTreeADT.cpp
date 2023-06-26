#include "QuadTreeADT.h"
#include <cmath>
#include <vector>
#include <iostream>
//#include <list>

Quad::Quad() {
  topLeft = Point(0, 0);
  botRight = Point(0, 0);
  n = nullptr;
  topLeftTree = nullptr;
  topRightTree = nullptr;
  botLeftTree = nullptr;
  botRightTree = nullptr;
}

Quad::Quad(Point topL, Point botR) {
  n = nullptr;
  topLeftTree = nullptr;
  topRightTree = nullptr;
  botLeftTree = nullptr;
  botRightTree = nullptr;
  topLeft = topL;
  botRight = botR;
}

void Quad::insert(Node* node)
{
  if (node == NULL)
    return;

    // Current quad cannot contain it
  if (!inBoundary(node->pos))
    return;

    // We are at a quad of unit area
    // We cannot subdivide this quad further
  if (abs(topLeft.x - botRight.x) <= 1
    && abs(topLeft.y - botRight.y) <= 1) {
    if (n == NULL)
      n = node;

    return;
  }

  if ((topLeft.x + botRight.x) / 2 > node->pos.x) {
        // Indicates topLeftTree
    if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
      if (topLeftTree == NULL) 
        topLeftTree = new Quad(
          Point(topLeft.x, topLeft.y),
          Point((topLeft.x + botRight.x) / 2,
            (topLeft.y + botRight.y) / 2));

      topLeftTree->insert(node);
    }

        // Indicates botLeftTree
    else {
      if (botLeftTree == NULL) 
        botLeftTree = new Quad(
          Point(topLeft.x,
            (topLeft.y + botRight.y) / 2),
          Point((topLeft.x + botRight.x) / 2,
            botRight.y));

      botLeftTree->insert(node);
    }
  }
  else {
        // Indicates topRightTree
    if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
      if (topRightTree == NULL) 
        topRightTree = new Quad(
          Point((topLeft.x + botRight.x) / 2,
            topLeft.y),
          Point(botRight.x,
            (topLeft.y + botRight.y) / 2));

      topRightTree->insert(node);
    }

        // Indicates botRightTree
    else {
      if (botRightTree == NULL)
        botRightTree = new Quad(
          Point((topLeft.x + botRight.x) / 2,
            (topLeft.y + botRight.y) / 2),
          Point(botRight.x, botRight.y));

      botRightTree->insert(node);
    }
  }
}

// Find a node in a quadtree
Node* Quad::search(Point p)
{
    // Current quad cannot contain it
  if (!inBoundary(p))
    return NULL;

    // We are at a quad of unit length
    // We cannot subdivide this quad further
  if (n != NULL)
    return n;

  if ((topLeft.x + botRight.x) / 2 > p.x) {
        // Indicates topLeftTree
    if ((topLeft.y + botRight.y) / 2 > p.y) {
      if (topLeftTree == NULL)
        return NULL;
      return topLeftTree->search(p);
    }

        // Indicates botLeftTree
    else {
      if (botLeftTree == NULL)
        return NULL;
      return botLeftTree->search(p);
    }
  }
  else {
        // Indicates topRightTree
    if ((topLeft.y + botRight.y) / 2 > p.y) {
      if (topRightTree == NULL)
        return NULL;
      return topRightTree->search(p);
    }

        // Indicates botRightTree
    else {
      if (botRightTree == NULL)
        return NULL;
      return botRightTree->search(p);
    }
  }
};

bool Quad::inBoundary(Point p) {
  return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

//
//Metodos Requeridos 
//

// Retorna el número total de puntos almacenados en el Quadtree
int Quad::totalPoints() {
  int count = 0;
  countPoints(count);
  return count;
}

// Cuenta recursivamente el número de puntos en el Quadtree
void Quad::countPoints(int& count) {
  if (n != nullptr)
    count++; // Incrementa el contador cuando se encuentra un nodo en este cuadrante

  // Realiza un recorrido recursivo en los cuadrantes hijos
  if (topLeftTree != nullptr)
    topLeftTree->countPoints(count);
  if (topRightTree != nullptr)
    topRightTree->countPoints(count);
  if (botLeftTree != nullptr)
    botLeftTree->countPoints(count);
  if (botRightTree != nullptr)
    botRightTree->countPoints(count);
}

int Quad::totalNodes() {
  int count = 0;
  countNodes(count);
  return count;
}

void Quad::countNodes(int& count) {
  count++; // Increment the counter for the current node (quadrant)

  // Recursively traverse the child quadrants
  if (topLeftTree != nullptr)
    topLeftTree->countNodes(count);
  if (topRightTree != nullptr)
    topRightTree->countNodes(count);
  if (botLeftTree != nullptr)
    botLeftTree->countNodes(count);
  if (botRightTree != nullptr)
    botRightTree->countNodes(count);
}

// Retorna una lista que contiene todos los nodos almacenados en el Quadtree
std::list<std::pair<Point, int>> Quad::list() {
  std::list<std::pair<Point, int>> result; // Contenedor para almacenar los puntos y sus valores asociados

  // Llama a la función auxiliar para realizar un recorrido en preorden y poblar la lista de resultados
  listHelper(result);

  return result;
}

void Quad::listHelper(std::list<std::pair<Point, int>>& result) {
  if (n != nullptr) {
    // Agrega el punto actual y su valor asociado a la lista de resultados
    result.push_back(std::make_pair(n->pos, n->data));
  }

  // Recorre recursivamente los cuadrantes hijos en preorden
  if (topLeftTree != nullptr)
    topLeftTree->listHelper(result);
  if (topRightTree != nullptr)
    topRightTree->listHelper(result);
  if (botLeftTree != nullptr)
    botLeftTree->listHelper(result);
  if (botRightTree != nullptr)
    botRightTree->listHelper(result);
}

// Retorna la cantidad de puntos en una región del plano
int Quad::countRegion(Point p, int d) {
  int count = 0;
  countRegionHelper(p, d, count);
  return count;
}

// Función auxiliar para contar los puntos en una región del plano de forma recursiva
void Quad::countRegionHelper(Point p, int d, int& count) {
  // Verifica si el cuadrante actual tiene un nodo y si el punto está dentro de la región
  if (n != nullptr && isWithinRegion(p, d, n->pos)) {
    count++; // Incrementa el contador si el punto está dentro de la región
  }

  // Recorre recursivamente los cuadrantes hijos que intersectan con la región
  if (topLeftTree != nullptr && intersectsRegion(p, d, topLeftTree->topLeft, topLeftTree->botRight)) {
    topLeftTree->countRegionHelper(p, d, count);
  }
  if (topRightTree != nullptr && intersectsRegion(p, d, topRightTree->topLeft, topRightTree->botRight)) {
    topRightTree->countRegionHelper(p, d, count);
  }
  if (botLeftTree != nullptr && intersectsRegion(p, d, botLeftTree->topLeft, botLeftTree->botRight)) {
    botLeftTree->countRegionHelper(p, d, count);
  }
  if (botRightTree != nullptr && intersectsRegion(p, d, botRightTree->topLeft, botRightTree->botRight)) {
    botRightTree->countRegionHelper(p, d, count);
  }
}

// Retorna la población estimada dentro de una región del plano
int Quad::aggregateRegion(Point p, int d) {
  int aggregate = 0;
  aggregateRegionHelper(p, d, aggregate);
  return aggregate;
}

// Función auxiliar para estimar la población dentro de una región del plano de forma recursiva
void Quad::aggregateRegionHelper(Point p, int d, int& aggregate) {
  // Verifica si el cuadrante actual tiene un nodo y si el punto está dentro de la región
  if (n != nullptr && isWithinRegion(p, d, n->pos)) {
    aggregate += n->data; // Incrementa la población estimada si el punto está dentro de la región
  }

  // Recorre recursivamente los cuadrantes hijos que intersectan con la región
  if (topLeftTree != nullptr && intersectsRegion(p, d, topLeftTree->topLeft, topLeftTree->botRight)) {
    topLeftTree->aggregateRegionHelper(p, d, aggregate);
  }
  if (topRightTree != nullptr && intersectsRegion(p, d, topRightTree->topLeft, topRightTree->botRight)) {
    topRightTree->aggregateRegionHelper(p, d, aggregate);
  }
  if (botLeftTree != nullptr && intersectsRegion(p, d, botLeftTree->topLeft, botLeftTree->botRight)) {
    botLeftTree->aggregateRegionHelper(p, d, aggregate);
  }
  if (botRightTree != nullptr && intersectsRegion(p, d, botRightTree->topLeft, botRightTree->botRight)) {
    botRightTree->aggregateRegionHelper(p, d, aggregate);
  }
}

// Verifica si un punto está dentro de la región definida por un punto central y una distancia
bool Quad::isWithinRegion(Point center, int distance, Point point) {
  int dx = abs(center.x - point.x);
  int dy = abs(center.y - point.y);
  return (dx <= distance && dy <= distance);
}

// Verifica si el cuadrante definido por su esquina superior izquierda y esquina inferior derecha
// intersecta con la región definida por un punto central y una distancia
bool Quad::intersectsRegion(Point center, int distance, Point topLeft, Point botRight) {
  int dxCentre = abs(center.x - (topLeft.x + botRight.x) / 2);
  int dyCentre = abs(center.y - (topLeft.y + botRight.y) / 2);
  int dxRegion = abs((topLeft.x - botRight.x) / 2);
  int dyRegion = abs((topLeft.y - botRight.y) / 2);

  int dx = dxCentre - dxRegion;
  int dy = dyCentre - dyRegion;

  int distanceX = std::max(dx, 0);
  int distanceY = std::max(dy, 0);

  return (distanceX <= distance && distanceY <= distance);
}

void Quad::insert(Point p, int data) {
  Node* newNode = new Node(p, data);
  insert(newNode);
}

bool Quad::isEmpty() {
  return (n == nullptr && topLeftTree == nullptr && topRightTree == nullptr && botLeftTree == nullptr && botRightTree == nullptr);
}

void Quad::clear() {
  // Liberar la memoria de los nodos del QuadTree
  delete n;
  delete topLeftTree;
  delete topRightTree;
  delete botLeftTree;
  delete botRightTree;

  // Establecer los punteros de los nodos a nullptr
  n = nullptr;
  topLeftTree = nullptr;
  topRightTree = nullptr;
  botLeftTree = nullptr;
  botRightTree = nullptr;
}

void Quad::remove(Point p) {
  if (n != nullptr && n->pos == p) {
    // Eliminar el nodo actual
    delete n;
    n = nullptr;
    return;
  }

  // Buscar en los subárboles si el punto está presente
  if (topLeftTree != nullptr && topLeftTree->inBoundary(p))
    topLeftTree->remove(p);
  if (topRightTree != nullptr && topRightTree->inBoundary(p))
    topRightTree->remove(p);
  if (botLeftTree != nullptr && botLeftTree->inBoundary(p))
    botLeftTree->remove(p);
  if (botRightTree != nullptr && botRightTree->inBoundary(p))
    botRightTree->remove(p);
}

void Quad::printAs2DPlane() {
  int minX = topLeft.x;
  int maxX = botRight.x-1;
  int minY = topLeft.y;
  int maxY = botRight.y-1;

  for (int y = maxY; y >= minY; y--) {
    for (int x = minX; x <= maxX; x++) {
      Point currentPoint(x, y);
      Node* node = search(currentPoint);

      if (node != nullptr) {
        // Si el nodo existe en el QuadTree, imprimir su valor o representación en el plano
        std::cout << node->data << " ";
      } else {
        // Si no hay un nodo en la posición actual, imprimir un carácter vacío o espacio en blanco
        std::cout << ". ";
      }
    }
    std::cout << std::endl;
  }
}





