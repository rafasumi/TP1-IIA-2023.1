#include "dijkstra.h"
#include <queue>

void Dijkstra::sort(std::vector<int> target, int& cost, int& expansions, std::string& path) {
  auto heap_compare = [](const NodePtr x, const NodePtr y) { return x->cost >= y->cost; };
  std::priority_queue<NodePtr, std::vector<NodePtr>, decltype(heap_compare)> frontier(heap_compare);
  std::unordered_map<std::vector<int>, bool, int_vector_hash> frontier_nodes;

  frontier.push(std::make_shared<Node>(target, 0, nullptr));
  frontier_nodes[target] = true;

  while (!frontier.empty()) {
    NodePtr node = frontier.top();
    frontier.pop();
    std::vector<int> node_val = node->value;
    if (goal_test(node_val)) {
      cost = node->cost;
      path = get_path(node);
      return;
    }

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
        int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
        if (explored.find(new_val) == explored.end() ||
            frontier_nodes.find(new_val) == frontier_nodes.end()) {
          frontier.push(std::make_shared<Node>(new_val, new_cost, node));
          frontier_nodes[new_val] = true;
        }
      }
    }
  }
}