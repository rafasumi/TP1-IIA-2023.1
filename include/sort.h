#ifndef SORT_H
#define SORT_H

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  std::vector<int> value;
  int cost;
};

class SearchSort {
public:
  std::stringstream intermediate_states;

  virtual void sort(std::vector<int> target, int& cost, int& states) = 0;

protected:
  std::unordered_map<std::string, bool> explored;

  std::string vec_to_str(std::vector<int>& vec);
  bool goal_test(std::vector<int>& vec);
};

std::string search_sort(std::vector<int>& target, std::string& algorithm,
                        int& cost, int& states);

#endif