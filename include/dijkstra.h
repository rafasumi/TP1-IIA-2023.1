#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "sort.h"
#include <vector>

/*
 * Uniform-cost search
 */
class Dijkstra : public SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path);
};

#endif