#include "sort.h"
#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[]) {
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0]
              << " <B|I|U|A|G> <size> <...values> [PRINT]\n";
    return 1;
  }

  std::string algorithm = argv[1];
  int n = std::stoi(argv[2]);
  std::vector<int> target(n);
  bool print = false;
  if (strcmp(argv[argc - 1], "PRINT") == 0) {
    print = true;
  }

  for (int i = 3; i < n + 3; i++) {
    target[i - 3] = std::stoi(argv[i]);
  }

  int cost = 0;
  int states = 0;
  std::string s = search_sort(target, algorithm, cost, states);

  std::cout << cost << " " << states << '\n';

  if (print) {
    std::cout << s;
  }

  return 0;
}
