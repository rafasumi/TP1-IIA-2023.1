#ifndef A_STAR_H
#define A_STAR_H

#include "sort.h"
#include <vector>

class AStar : public SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path);
};

#endif