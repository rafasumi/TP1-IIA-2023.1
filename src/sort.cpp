#include "sort.h"
#include "aStar.h"
#include "bfs.h"
#include "dijkstra.h"
#include "greedy.h"
#include "iterative.h"
#include <algorithm>
#include <iostream>
#include <sstream>

std::string SearchSort::vec_to_str(std::vector<int>& vec) {
  std::stringstream stream;
  for (int& val : vec) {
    stream << val << " ";
  }

  std::string str = stream.str();
  str.pop_back();

  return str;
}

bool SearchSort::goal_test(std::vector<int>& vec) { return std::is_sorted(vec.begin(), vec.end()); }

std::string SearchSort::get_path(std::shared_ptr<Node> node) {
  std::string path = "";

  std::shared_ptr<Node> curr = node;
  while (curr != nullptr) {
    path = vec_to_str(curr->value) + "\n" + path;
    curr = curr->pred;
  }

  return path;
}

int SearchSort::heuristic(std::vector<int>& vec) {
  int estimative = 0;
  for (int i = 0; i < (int)vec.size(); i++) {
    if (vec[i] != i + 1)
      estimative++;
  }

  return estimative;
}

std::string search_sort(std::vector<int>& target, std::string& algorithm, int& cost,
                        int& expansions) {
  std::unique_ptr<SearchSort> algo;
  if (algorithm == "B") {
    algo.reset(new BFS);
  } else if (algorithm == "I") {
    algo.reset(new Iterative);
  } else if (algorithm == "U") {
    algo.reset(new Dijkstra);
  } else if (algorithm == "A") {
    algo.reset(new AStar);
  } else if (algorithm == "G") {
    algo.reset(new Greedy);
  } else {
    std::cerr << "Unknown algorithm '" << algorithm << "'\n";
    exit(EXIT_FAILURE);
  }

  std::string path = "";
  algo->sort(target, cost, expansions, path);

  return path;
}