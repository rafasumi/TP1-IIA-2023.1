#include "iterative.h"
#include <stack>

bool Iterative::limited_sort(std::vector<int>& target, int& cost, int& states,
                             int limit) {
  std::stack<DFSNode> frontier;
  frontier.push({target, 0, 0});

  while (!frontier.empty()) {
    DFSNode node = frontier.top();
    frontier.pop();

    std::vector<int> node_val = node.value;
    if (goal_test(node_val)) {
      intermediate_states << vec_to_str(node_val) << '\n';
      cost = node.cost;
      return true;
    }

    states++;

    std::string str = vec_to_str(node_val);
    intermediate_states << str << '\n';
    explored[str] = true;

    if (node.depth == limit)
      continue;

    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        std::vector<int> new_node = node_val;
        new_node[i] = node_val[j];
        new_node[j] = node_val[i];
        std::string new_str = vec_to_str(new_node);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node.cost + ((j == i + 1) ? 2 : 4);
          frontier.push({new_node, new_cost, node.depth + 1});
        }
      }
    }
  }

  return false;
}

void Iterative::sort(std::vector<int> target, int& cost, int& states) {
  int limit = 0;
  int temp_cost;
  while (true) {
    temp_cost = 0;

    bool success = limited_sort(target, temp_cost, states, limit);

    if (!success) {
      limit++;
      explored.clear();
    } else {
      break;
    }
  }

  cost = temp_cost;
}