#ifndef GREEDY_H
#define GREEDY_H

#include "sort.h"
#include <vector>

/*
 * Greedy best-first search
 */
class Greedy : public SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path);
};

#endif