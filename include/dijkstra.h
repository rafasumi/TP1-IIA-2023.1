#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "sort.h"
#include <vector>

class Dijkstra : public SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& states);
};

#endif