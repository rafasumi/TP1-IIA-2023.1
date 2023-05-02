#include "dijkstra.h"
#include <queue>

void Dijkstra::sort(std::vector<int> target, int& cost, int& states,
                    std::string& path) {
  auto heap_compare = [](const NodePtr x, const NodePtr y) {
    return x->cost > y->cost;
  };
  std::priority_queue<NodePtr, std::vector<NodePtr>, decltype(heap_compare)>
      frontier(heap_compare);
  std::unordered_map<std::string, NodePtr> frontier_nodes;
  frontier.push(std::make_shared<Node>(target, 0, vec_to_str(target), nullptr));

  while (!frontier.empty()) {
    NodePtr node = frontier.top();
    frontier.pop();
    std::vector<int> node_val = node->value;
    if (goal_test(node_val)) {
      cost = node->cost;
      path = get_path(node);
      return;
    }

    frontier_nodes.erase(node->str);
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
        int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
        if (explored.find(new_str) == explored.end() ||
            frontier_nodes.find(new_str) == frontier_nodes.end()) {
          NodePtr new_node =
              std::make_shared<Node>(new_val, new_cost, new_str, node);
         
          frontier.push(new_node);
          frontier_nodes[new_str] = new_node;
        } else if (frontier_nodes.find(new_str) != frontier_nodes.end() &&
                   frontier_nodes[new_str]->cost > new_cost) {
          frontier_nodes[new_str]->cost = new_cost;
        }
      }
    }
  }
}