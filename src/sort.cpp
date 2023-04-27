#include "sort.h"
#include <algorithm>
#include <iostream>
#include <queue>

std::unordered_map<std::string, bool> explored;

std::string vec_to_str(std::vector<int>& vec) {
  std::stringstream stream;
  for (int& val : vec) {
    stream << val << " ";
  }

  std::string str = stream.str();
  str.pop_back();

  return str;
}

bool goal_test(std::vector<int>& vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

void bfs(std::vector<int> target, int& cost, int& states,
         std::stringstream& stream) {
  if (goal_test(target)) {
    stream << vec_to_str(target) << '\n';
    return;
  }

  std::queue<std::pair<std::vector<int>, int>> frontier;
  frontier.push(std::make_pair(target, 0));

  while (!frontier.empty()) {
    auto front = frontier.front();
    std::vector<int> node = front.first;
    int node_cost = front.second;
    frontier.pop();

    std::string str = vec_to_str(node);
    stream << str << '\n';
    explored[str] = true;
    for (size_t i = 0; i < node.size() - 1; i++) {
      for (size_t j = i + 1; j < node.size(); j++) {
        std::vector<int> new_node = node;
        new_node[i] = node[j];
        new_node[j] = node[i];
        std::string new_str = vec_to_str(new_node);
        if (explored.find(new_str) == explored.end()) {
          int new_cost = node_cost + ((j == i + 1) ? 2 : 4);
          if (goal_test(new_node)) {
            stream << new_str << '\n';
            states++;
            cost = new_cost;
            return;
          }
          frontier.push(make_pair(new_node, new_cost));
        }
      }
    }

    states++;
  }
}

std::string search_sort(std::vector<int>& target, std::string& algorithm,
                        int& cost, int& states) {
  std::stringstream intermediate_states;
  if (algorithm == "B") {
    bfs(target, cost, states, intermediate_states);
  } else if (algorithm == "I") {

  } else if (algorithm == "U") {

  } else if (algorithm == "A") {

  } else if (algorithm == "G") {
  }

  return intermediate_states.str();
}