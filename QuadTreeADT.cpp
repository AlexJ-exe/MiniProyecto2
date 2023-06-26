#include "QuadTreeADT.h"
#include <cmath>
#include <iostream>

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

// Retorna el número total de nodos en el Quadtree, incluido el nodo raíz
int Quad::totalNodes() {
  int count = 1; // Comienza con 1 para incluir el nodo raíz
  countNodes(count);
  return count;
}

// Cuenta recursivamente el número de nodos en el Quadtree, incluido el nodo actual
void Quad::countNodes(int& count) {
  if (n != nullptr)
    count++; // Incrementa el contador cuando se encuentra un nodo en este cuadrante

  // Realiza un recorrido recursivo en los cuadrantes hijos
  if (topLeftTree != nullptr)
    topLeftTree->countNodes(count);
  if (topRightTree != nullptr)
    topRightTree->countNodes(count);
  if (botLeftTree != nullptr)
    botLeftTree->countNodes(count);
  if (botRightTree != nullptr)
    botRightTree->countNodes(count);
}

// Inserta un punto y un dato en el Quadtree
void Quad::insert(Point p, int data) {
  Node* newNode = new Node(p, data);
  insert(newNode);
}

// Retorna una lista que contiene todos los nodos almacenados en el Quadtree
std::list<Node*> Quad::list() {
  std::list<Node*> nodeList;

  if (n != nullptr) {
    nodeList.push_back(n); // Agrega el nodo actual a la lista
  }

  // Realiza un recorrido recursivo en los cuadrantes hijos y agrega sus nodos a la lista
  if (topLeftTree != nullptr) {
    std::list<Node*> topLeftList = topLeftTree->list();
    nodeList.insert(nodeList.end(), topLeftList.begin(), topLeftList.end());
  }
  if (topRightTree != nullptr) {
    std::list<Node*> topRightList = topRightTree->list();
    nodeList.insert(nodeList.end(), topRightList.begin(), topRightList.end());
  }
  if (botLeftTree != nullptr) {
    std::list<Node*> botLeftList = botLeftTree->list();
    nodeList.insert(nodeList.end(), botLeftList.begin(), botLeftList.end());
  }
  if (botRightTree != nullptr) {
    std::list<Node*> botRightList = botRightTree->list();
    nodeList.insert(nodeList.end(), botRightList.begin(), botRightList.end());
  }

  return nodeList;
}

// Cuenta el número de nodos en el Quadtree que están dentro de un cuadrante dado por el punto p y la distancia d
int Quad::countRegion(Point p, int d) {
  int count = 0;
  countNodesInRegion(p, d, count);
  return count;
}

// Método auxiliar para contar los nodos en un cuadrante dado por el punto p y la distancia d
void Quad::countNodesInRegion(Point p, int d, int& count) {
  if (n != nullptr && inRegion(n->pos, p, d))
    count++; // Incrementa el contador cuando se encuentra un nodo dentro del cuadrante

  // Realiza un recorrido recursivo en los cuadrantes hijos que intersectan con el cuadrante dado
  if (topLeftTree != nullptr && intersectRegion(topLeftTree->topLeft, topLeftTree->botRight, p, d))
    topLeftTree->countNodesInRegion(p, d, count);
  if (topRightTree != nullptr && intersectRegion(topRightTree->topLeft, topRightTree->botRight, p, d))
    topRightTree->countNodesInRegion(p, d, count);
  if (botLeftTree != nullptr && intersectRegion(botLeftTree->topLeft, botLeftTree->botRight, p, d))
    botLeftTree->countNodesInRegion(p, d, count);
  if (botRightTree != nullptr && intersectRegion(botRightTree->topLeft, botRightTree->botRight, p, d))
    botRightTree->countNodesInRegion(p, d, count);
}

// Verifica si un punto se encuentra dentro de un cuadrante dado por el punto central y la distancia
bool Quad::inRegion(Point point, Point center, int distance) {
  int dx = abs(point.x - center.x);
  int dy = abs(point.y - center.y);
  return (dx <= distance && dy <= distance);
}

// Verifica si un cuadrante dado por los puntos topLeft1 y botRight1 intersecta con otro cuadrante dado por los puntos topLeft2 y botRight2
bool Quad::intersectRegion(Point topLeft1, Point botRight1, Point topLeft2, Point botRight2) {
  return !(topLeft1.x > botRight2.x || botRight1.x < topLeft2.x || topLeft1.y > botRight2.y || botRight1.y < topLeft2.y);
}

// Calcula la suma de los datos de los nodos en el Quadtree que están dentro de un cuadrante dado por el punto p y la distancia d
int Quad::aggregateRegion(Point p, int d) {
  int sum = 0;
  aggregateDataInRegion(p, d, sum);
  return sum;
}

// Método auxiliar para sumar los datos de los nodos en un cuadrante dado por el punto p y la distancia d
void Quad::aggregateDataInRegion(Point p, int d, int& sum) {
  if (n != nullptr && inRegion(n->pos, p, d))
    sum += n->data; // Agrega el dato del nodo al total

  // Realiza un recorrido recursivo en los cuadrantes hijos que intersectan con el cuadrante dado
  if (topLeftTree != nullptr && intersectRegion(topLeftTree->topLeft, topLeftTree->botRight, p, d))
    topLeftTree->aggregateDataInRegion(p, d, sum);
  if (topRightTree != nullptr && intersectRegion(topRightTree->topLeft, topRightTree->botRight, p, d))
    topRightTree->aggregateDataInRegion(p, d, sum);
  if (botLeftTree != nullptr && intersectRegion(botLeftTree->topLeft, botLeftTree->botRight, p, d))
    botLeftTree->aggregateDataInRegion(p, d, sum);
  if (botRightTree != nullptr && intersectRegion(botRightTree->topLeft, botRightTree->botRight, p, d))
    botRightTree->aggregateDataInRegion(p, d, sum);
}


//Metodos extras                     hoñmafknafkñasfnasfnafdasnoanñan
//


// Elimina un nodo del Quadtree
bool Quad::remove(Point p) {
  return removeNode(p, *this);
}

// Método auxiliar para eliminar un nodo del Quadtree
bool Quad::removeNode(Point p, Quad& quad) {
  if (quad.n != nullptr && quad.n->pos == p) {
    delete quad.n;
    quad.n = nullptr;
    return true;
  }

  if (quad.topLeftTree != nullptr && inBoundary(p, quad.topLeftTree)) {
    bool removed = removeNode(p, *quad.topLeftTree);
    if (removed)
      return true;
  }

  if (quad.topRightTree != nullptr && inBoundary(p, quad.topRightTree)) {
    bool removed = removeNode(p, *quad.topRightTree);
    if (removed)
      return true;
  }

  if (quad.botLeftTree != nullptr && inBoundary(p, quad.botLeftTree)) {
    bool removed = removeNode(p, *quad.botLeftTree);
    if (removed)
      return true;
  }

  if (quad.botRightTree != nullptr && inBoundary(p, quad.botRightTree)) {
    bool removed = removeNode(p, *quad.botRightTree);
    if (removed)
      return true;
  }

  return false;
}

//Verifica si un punto se encuentra dentro del cuadrante de un Quadtree dado
bool Quad::inBoundary(Point p, Quad* quad) {
  return (p.x >= quad->topLeft.x && p.x <= quad->botRight.x && p.y >= quad->topLeft.y && p.y <= quad->botRight.y);
}

// Busca todos los nodos dentro de una región dada por el punto p y la distancia d
std::list<Node*> Quad::searchRegion(Point p, int d) {
  std::list<Node*> nodes;
  searchNodesInRegion(p, d, nodes);
  return nodes;
}

// Método auxiliar para buscar los nodos dentro de una región dada por el punto p y la distancia d
void Quad::searchNodesInRegion(Point p, int d, std::list<Node*>& nodes) {
  if (n != nullptr && inRegion(n->pos, p, d))
    nodes.push_back(n); // Agrega el nodo actual a la lista

  // Realiza un recorrido recursivo en los cuadrantes hijos que intersectan con el cuadrante dado
  if (topLeftTree != nullptr && intersectRegion(topLeftTree->topLeft, topLeftTree->botRight, p, d))
    topLeftTree->searchNodesInRegion(p, d, nodes);
  if (topRightTree != nullptr && intersectRegion(topRightTree->topLeft, topRightTree->botRight, p, d))
    topRightTree->searchNodesInRegion(p, d, nodes);
  if (botLeftTree != nullptr && intersectRegion(botLeftTree->topLeft, botLeftTree->botRight, p, d))
    botLeftTree->searchNodesInRegion(p, d, nodes);
  if (botRightTree != nullptr && intersectRegion(botRightTree->topLeft, botRightTree->botRight, p, d))
    botRightTree->searchNodesInRegion(p, d, nodes);
}

// Elimina todos los nodos dentro de una región dada por el punto p y la distancia d
void Quad::removeRegion(Point p, int d) {
  std::list<Node*> nodesToRemove;
  searchNodesInRegion(p, d, nodesToRemove);

  for (Node* node : nodesToRemove) {
    remove(node->pos);
  }
}

