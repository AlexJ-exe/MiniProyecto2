#include "QuadTreeADT.h"
#include <cmath>
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

  if (!inBoundary(p))
    return count;
  if (n != nullptr)
    count++;
  if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1)
    return count;
  if (topLeftTree != nullptr)
    count += topLeftTree->countRegion(p, d);
  if (topRightTree != nullptr)
    count += topRightTree->countRegion(p, d);
  if (botLeftTree != nullptr)
    count += botLeftTree->countRegion(p, d);
  if (botRightTree != nullptr)
    count += botRightTree->countRegion(p, d);
  return count;
}


