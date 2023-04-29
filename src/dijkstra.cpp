#include "dijkstra.h"
#include <queue>

void Dijkstra::sort(std::vector<int> target, int& cost, int& states) {
  auto heap_compare = [](const Node& x, const Node& y) {
    return x.cost > y.cost;
  };
  std::priority_queue<Node, std::vector<Node>, decltype(heap_compare)> frontier(
      heap_compare);
  frontier.push({target, 0});

  while (!frontier.empty()) {
    Node node = frontier.top();
    frontier.pop();
    std::vector<int> node_val = node.value;
    if (goal_test(node_val)) {
      intermediate_states << vec_to_str(node_val) << '\n';
      cost = node.cost;
      return;
    }

    states++;

    std::string str = vec_to_str(node_val);
    intermediate_states << str << '\n';
    explored[str] = true;

    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        std::vector<int> new_node = node_val;
        new_node[i] = node_val[j];
        new_node[j] = node_val[i];
        std::string new_str = vec_to_str(new_node);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node.cost + ((j == i + 1) ? 2 : 4);
          frontier.push({new_node, new_cost});
        }
      }
    }
  }
}