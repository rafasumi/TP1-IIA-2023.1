#ifndef ITERATIVE_H
#define ITERATIVE_H

#include "sort.h"
#include <vector>

class Iterative : public SearchSort {
private:
  bool limited_sort(std::vector<int>& target, int& cost, int& states,
                    std::string& path, int limit);

public:
  virtual void sort(std::vector<int> target, int& cost, int& states,
                    std::string& path);
};

#endif