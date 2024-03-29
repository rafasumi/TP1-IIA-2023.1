#ifndef ITERATIVE_H
#define ITERATIVE_H

#include "sort.h"
#include <vector>

/*
 * Iterative deepening search
 */
class Iterative : public SearchSort {
private:
  bool limited_sort(std::vector<int>& target, int& cost, int& expansions, std::string& path,
                    int limit);

public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path);
};

#endif