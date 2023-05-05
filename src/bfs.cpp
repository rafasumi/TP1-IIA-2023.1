#include "bfs.h"
#include <queue>

void BFS::sort(std::vector<int> target, int& cost, int& expansions, std::string& path) {
  if (goal_test(target)) {
    path = vec_to_str(target) + '\n';
    return;
  }

  std::queue<NodePtr> frontier;
  std::unordered_map<std::vector<int>, bool, int_vector_hash> frontier_nodes;

  frontier.push(std::make_shared<Node>(target, 0, nullptr));
  frontier_nodes[target] = true;

  while (!frontier.empty()) {
    NodePtr node = frontier.front();
    frontier.pop();
    std::vector<int> node_val = node->value;

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
        if (explored.find(new_val) == explored.end() ||
            frontier_nodes.find(new_val) == frontier_nodes.end()) {
          int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
          NodePtr new_node = std::make_shared<Node>(new_val, new_cost, node);
          if (goal_test(new_val)) {
            cost = new_cost;
            path = get_path(new_node);
            return;
          }
          frontier.push(new_node);
          frontier_nodes[new_val] = true;
        }
      }
    }
  }
}