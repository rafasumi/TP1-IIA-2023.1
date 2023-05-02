#ifndef GREEDY_H
#define GREEDY_H

#include "sort.h"
#include <vector>

class Greedy : public SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& states,
                    std::string& path);
};

#endif