#include "greedy.h"
#include <queue>

void Greedy::sort(std::vector<int> target, int& cost, int& states,
                  std::string& path) {
  auto heap_compare = [](const HeuristicNodePtr& x, const HeuristicNodePtr& y) {
    return x->estimated > y->estimated;
  };
  std::priority_queue<HeuristicNodePtr, std::vector<HeuristicNodePtr>,
                      decltype(heap_compare)>
      frontier(heap_compare);

  frontier.push(std::make_shared<HeuristicNode>(target, 0, vec_to_str(target),
                                                nullptr, heuristic(target)));

  while (!frontier.empty()) {
    HeuristicNodePtr node = frontier.top();
    frontier.pop();
    std::vector<int> node_val = node->value;
    if (goal_test(node_val)) {
      cost = node->cost;
      path = get_path(node);
      return;
    }

    if (explored.find(node->str) != explored.end())
      continue;
    explored[node->str] = true;
    states++;

    for (size_t i = 0; i < node_val.size() - 1; i++) {
      for (size_t j = i + 1; j < node_val.size(); j++) {
        std::vector<int> new_node = node_val;
        new_node[i] = node_val[j];
        new_node[j] = node_val[i];
        std::string new_str = vec_to_str(new_node);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node->cost + ((j == i + 1) ? 2 : 4);
          frontier.push(std::make_shared<HeuristicNode>(
              new_node, new_cost, new_str, node, heuristic(node_val)));
        }
      }
    }
  }
}