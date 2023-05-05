#ifndef SORT_H
#define SORT_H

#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  Node(std::vector<int>& value, int cost, std::shared_ptr<Node> pred)
      : value(value), cost(cost), pred(pred) {}

  std::vector<int> value;
  int cost;
  std::shared_ptr<Node> pred;
};

struct DFSNode : Node {
  DFSNode(std::vector<int>& value, int cost, std::shared_ptr<Node> pred, int depth)
      : Node(value, cost, pred), depth(depth) {}

  int depth;
};

struct HeuristicNode : Node {
  HeuristicNode(std::vector<int>& value, int cost, std::shared_ptr<Node> pred, int estimated)
      : Node(value, cost, pred), estimated(estimated) {}

  int estimated;
};

using NodePtr = std::shared_ptr<Node>;
using DFSNodePtr = std::shared_ptr<DFSNode>;
using HeuristicNodePtr = std::shared_ptr<HeuristicNode>;

class int_vector_hash {
public:
  std::size_t operator()(std::vector<int> const& vec) const {
    std::size_t seed = vec.size();
    for (int x : vec) {
      x = ((x >> 16) ^ x) * 0x45d9f3b;
      x = ((x >> 16) ^ x) * 0x45d9f3b;
      x = (x >> 16) ^ x;
      seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

class SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path) = 0;

protected:
  std::unordered_map<std::vector<int>, bool, int_vector_hash> explored;

  std::string vec_to_str(std::vector<int>& vec);
  bool goal_test(std::vector<int>& vec);
  std::string get_path(std::shared_ptr<Node> node);
  int heuristic(std::vector<int>& vec);
};

std::string search_sort(std::vector<int>& target, std::string& algorithm, int& cost,
                        int& expansions);

#endif