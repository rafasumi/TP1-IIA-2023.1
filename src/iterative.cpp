#include "iterative.h"
#include <stack>

bool Iterative::limited_sort(std::vector<int>& target, int& cost, int& expansions,
                             std::string& path, int limit) {
  std::stack<DFSNodePtr> frontier;

  // Mapa que armazena os estados que estão na fronteira
  std::unordered_map<std::vector<int>, bool, int_vector_hash> frontier_nodes;

  frontier.push(std::make_shared<DFSNode>(target, 0, nullptr, 0));
  frontier_nodes[target] = true;

  while (!frontier.empty()) {
    DFSNodePtr node = frontier.top();
    frontier.pop();

    std::vector<int> node_val = node->value;
    if (goal_test(node_val)) {
      cost = node->cost;
      path = get_path(node);
      return true;
    }

    if (node->depth == limit)
      continue;

    frontier_nodes.erase(node_val);
    explored[node_val] = true;

    expansions++;
    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        if (node_val[i] < node_val[j])
          continue;

        std::vector<int> new_val = node_val;
        new_val[i] = node_val[j];
        new_val[j] = node_val[i];
        if (frontier_nodes.find(new_val) == frontier_nodes.end() &&
            explored.find(new_val) == explored.end()) {
          int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
          frontier.push(std::make_shared<DFSNode>(new_val, new_cost, node, node->depth + 1));
        }
      }
    }
  }

  return false;
}

void Iterative::sort(std::vector<int> target, int& cost, int& expansions, std::string& path) {
  int limit = 0;
  int temp_cost;
  std::string temp_path;
  while (true) {
    bool success = limited_sort(target, temp_cost, expansions, temp_path, limit);

    if (success)
      break;

    limit++;
    // O algoritmo "esquece" todos os nós explorados na iteração anterior
    explored.clear();
  }

  cost = temp_cost;
  path = temp_path;
}