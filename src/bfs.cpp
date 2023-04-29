#include "bfs.h"
#include <queue>

void BFS::sort(std::vector<int> target, int& cost, int& states) {
  if (goal_test(target)) {
    this->intermediate_states << vec_to_str(target) << '\n';
    return;
  }

  std::queue<Node> frontier;
  frontier.push({target, 0});

  while (!frontier.empty()) {
    Node node = frontier.front();
    frontier.pop();
    std::vector<int> node_val = node.value;

    std::string str = vec_to_str(node_val);
    this->intermediate_states << str << '\n';
    explored[str] = true;

    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        std::vector<int> new_node = node_val;
        new_node[i] = node_val[j];
        new_node[j] = node_val[i];
        std::string new_str = vec_to_str(new_node);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node.cost + ((j == i + 1) ? 2 : 4);
          if (goal_test(new_node)) {
            this->intermediate_states << new_str << '\n';
            states++;
            cost = new_cost;
            return;
          }
          frontier.push({new_node, new_cost});
        }
      }
    }

    states++;
  }
}