#include "iterative.h"
#include <stack>

bool Iterative::limited_sort(std::vector<int>& target, int& cost, int& states,
                             std::string& path, int limit) {
  std::stack<DFSNodePtr> frontier;
  frontier.push(
      std::make_shared<DFSNode>(target, 0, vec_to_str(target), nullptr, 0));

  while (!frontier.empty()) {
    DFSNodePtr node = frontier.top();
    frontier.pop();

    std::vector<int> node_val = node->value;
    if (goal_test(node_val)) {
      cost = node->cost;
      path = get_path(node);
      return true;
    }

    if (explored.find(node->str) != explored.end())
      continue;
    explored[node->str] = true;

    if (node->depth == limit)
      continue;

    // Not sure this increment is right
    states++;

    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        std::vector<int> new_node = node_val;
        new_node[i] = node_val[j];
        new_node[j] = node_val[i];
        std::string new_str = vec_to_str(new_node);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
          frontier.push(std::make_shared<DFSNode>(new_node, new_cost, new_str,
                                                  node, node->depth + 1));
        }
      }
    }
  }

  return false;
}

void Iterative::sort(std::vector<int> target, int& cost, int& states,
                     std::string& path) {
  int limit = 0;
  int temp_cost;
  std::string temp_path;
  while (true) {
    bool success = limited_sort(target, temp_cost, states, temp_path, limit);

    if (!success) {
      limit++;
      explored.clear();
    } else {
      break;
    }
  }

  cost = temp_cost;
  path = temp_path;
}