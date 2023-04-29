#include "sort.h"
#include "bfs.h"
#include "dijkstra.h"
#include "iterative.h"
#include <algorithm>
#include <iostream>

std::string SearchSort::vec_to_str(std::vector<int>& vec) {
  std::stringstream stream;
  for (int& val : vec) {
    stream << val << " ";
  }

  std::string str = stream.str();
  str.pop_back();

  return str;
}

bool SearchSort::goal_test(std::vector<int>& vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

std::string search_sort(std::vector<int>& target, std::string& algorithm,
                        int& cost, int& states) {
  SearchSort* algo;
  if (algorithm == "B") {
    algo = new BFS;
  } else if (algorithm == "I") {
    algo = new Iterative;
  } else if (algorithm == "U") {
    algo = new Dijkstra;
  } else if (algorithm == "A") {
  } else if (algorithm == "G") {
  } else {
    std::cerr << "Unknown algorithm '" << algorithm << "'\n";
    exit(EXIT_FAILURE);
  }

  algo->sort(target, cost, states);
  std::string intermediate_states = algo->intermediate_states.str();
  delete algo;

  return intermediate_states;
}