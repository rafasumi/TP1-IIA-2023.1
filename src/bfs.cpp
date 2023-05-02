#include "bfs.h"
#include <queue>

void BFS::sort(std::vector<int> target, int& cost, int& states,
               std::string& path) {
  if (goal_test(target)) {
    path = vec_to_str(target) + '\n';
    return;
  }

  std::queue<NodePtr> frontier;
  frontier.push(std::make_shared<Node>(target, 0, vec_to_str(target), nullptr));

  while (!frontier.empty()) {
    NodePtr node = frontier.front();
    frontier.pop();
    std::vector<int> node_val = node->value;

    if (explored.find(node->str) != explored.end())
      continue;
    explored[node->str] = true;
    states++;

    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        std::vector<int> new_val = node_val;
        new_val[i] = node_val[j];
        new_val[j] = node_val[i];
        std::string new_str = vec_to_str(new_val);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
          NodePtr new_node =
              std::make_shared<Node>(new_val, new_cost, new_str, node);
          if (goal_test(new_val)) {
            cost = new_cost;
            path = get_path(new_node);
            return;
          }
          frontier.push(new_node);
        }
      }
    }
  }
}