#ifndef SORT_H
#define SORT_H

#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  Node(std::vector<int>& value, int cost, std::string str,
       std::shared_ptr<Node> pred)
      : value(value), cost(cost), str(str), pred(pred) {}

  std::vector<int> value;
  int cost;
  std::string str;
  std::shared_ptr<Node> pred;
};

struct DFSNode : Node {
  DFSNode(std::vector<int>& value, int cost, std::string str,
          std::shared_ptr<Node> pred, int depth)
      : Node(value, cost, str, pred), depth(depth) {}

  int depth;
};

struct HeuristicNode : Node {
  HeuristicNode(std::vector<int>& value, int cost, std::string str,
                std::shared_ptr<Node> pred, int estimated)
      : Node(value, cost, str, pred), estimated(estimated) {}

  int estimated;
};

using NodePtr = std::shared_ptr<Node>;
using DFSNodePtr = std::shared_ptr<DFSNode>;
using HeuristicNodePtr = std::shared_ptr<HeuristicNode>;

class SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& states,
                    std::string& path) = 0;

protected:
  std::unordered_map<std::string, bool> explored;

  std::string vec_to_str(std::vector<int>& vec);
  bool goal_test(std::vector<int>& vec);
  std::string get_path(std::shared_ptr<Node> node);
  int heuristic(std::vector<int>& vec);
};

std::string search_sort(std::vector<int>& target, std::string& algorithm,
                        int& cost, int& states);

#endif