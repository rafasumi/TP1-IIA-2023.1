#include "aStar.h"
#include <queue>

void AStar::sort(std::vector<int> target, int& cost, int& expansions, std::string& path) {
  // Função de comparação usada na fila de prioridades
  auto heap_compare = [](const HeuristicNodePtr& x, const HeuristicNodePtr& y) {
    return (x->estimated + x->cost) >= (y->estimated + y->cost);
  };
  std::priority_queue<HeuristicNodePtr, std::vector<HeuristicNodePtr>, decltype(heap_compare)>
      frontier(heap_compare);
  
  // Mapa que armazena os estados que estão na fronteira
  std::unordered_map<std::vector<int>, HeuristicNodePtr, int_vector_hash> frontier_nodes;

  HeuristicNodePtr start_node =
      std::make_shared<HeuristicNode>(target, 0, nullptr, heuristic(target));
  frontier.push(start_node);
  frontier_nodes[target] = start_node;

  while (!frontier.empty()) {
    HeuristicNodePtr node = frontier.top();
    frontier.pop();

    if (!node->valid)
      continue;

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
        if (frontier_nodes.find(new_val) == frontier_nodes.end() &&
            explored.find(new_val) == explored.end()) {
          HeuristicNodePtr new_node =
              std::make_shared<HeuristicNode>(new_val, new_cost, node, heuristic(new_val));

          frontier.push(new_node);
          frontier_nodes[new_val] = new_node;
        } else if ((frontier_nodes.find(new_val) != frontier_nodes.end() &&
                    frontier_nodes[new_val]->cost > new_cost)) {
          frontier_nodes[new_val]->valid = false;

          HeuristicNodePtr new_node =
              std::make_shared<HeuristicNode>(new_val, new_cost, node, heuristic(new_val));
          frontier.push(new_node);
          frontier_nodes[new_val] = new_node;
        }
      }
    }
  }
}