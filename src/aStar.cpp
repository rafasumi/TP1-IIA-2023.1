#include "aStar.h"
#include <queue>

void AStar::sort(std::vector<int> target, int& cost, int& expansions, std::string& path) {
  auto heap_compare = [](const HeuristicNodePtr& x, const HeuristicNodePtr& y) {
    return (x->estimated + x->cost) >= (y->estimated + y->cost);
  };
  std::priority_queue<HeuristicNodePtr, std::vector<HeuristicNodePtr>, decltype(heap_compare)>
      frontier(heap_compare);
  frontier.push(std::make_shared<HeuristicNode>(target, 0, nullptr, heuristic(target)));

  while (!frontier.empty()) {
    HeuristicNodePtr node = frontier.top();
    frontier.pop();
    std::vector<int> node_val = node->value;
    if (goal_test(node_val)) {
      cost = node->cost;
      path = get_path(node);
      return;
    }

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
        if (explored.find(new_val) == explored.end()) {
          HeuristicNodePtr new_node =
              std::make_shared<HeuristicNode>(new_val, new_cost, node, heuristic(new_val));

          frontier.push(new_node);
        }
      }
    }
  }
}