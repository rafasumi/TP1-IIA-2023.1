#ifndef ITERATIVE_H
#define ITERATIVE_H

#include "sort.h"
#include <vector>

struct DFSNode : Node {
  int depth;
};

class Iterative : public SearchSort {
private:
  bool limited_sort(std::vector<int>& target, int& cost, int& states,
                    int limit);

public:
  virtual void sort(std::vector<int> target, int& cost, int& states);
};

#endif