#ifndef BFS_H
#define BFS_H

#include "sort.h"
#include <vector>

/*
 * Breadth-first search
 */
class BFS : public SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path);
};

#endif