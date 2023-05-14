#ifndef SORT_H
#define SORT_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/*
 * Estrutura usada para armazenar informações de um nó no espaço de busca.
 */
struct Node {
  Node(std::vector<int>& value, int cost, std::shared_ptr<Node> pred)
      : value(value), cost(cost), pred(pred), valid(true) {}

  // Estado armazenado no nó
  std::vector<int> value;

  // Custo para chegar no nó a partir do nó inicial
  int cost;

  // Ponteiro para o nó antecessor
  std::shared_ptr<Node> pred;

  // Flag que indica se o nó é válido na fronteira
  bool valid;
};

/*
 * Especialização de Node para o algoritmo IDS
 */
struct DFSNode : Node {
  DFSNode(std::vector<int>& value, int cost, std::shared_ptr<Node> pred, int depth)
      : Node(value, cost, pred), depth(depth) {}

  int depth;
};

/*
 * Especialização de Node para algoritmos de busca com informação.
 */
struct HeuristicNode : Node {
  HeuristicNode(std::vector<int>& value, int cost, std::shared_ptr<Node> pred, int estimated)
      : Node(value, cost, pred), estimated(estimated) {}

  int estimated;
};

using NodePtr = std::shared_ptr<Node>;
using DFSNodePtr = std::shared_ptr<DFSNode>;
using HeuristicNodePtr = std::shared_ptr<HeuristicNode>;

/*
 * Classe usada para implementar função de hashing para vetores de inteiros.
 * É necessária para usar vetores como chaves de mapas.
 */
class int_vector_hash {
public:
  std::size_t operator()(std::vector<int> const& vec) const {
    std::size_t seed = vec.size();
    for (int x : vec) {
      x = ((x >> 16) ^ x) * 0x45d9f3b;
      x = ((x >> 16) ^ x) * 0x45d9f3b;
      x = (x >> 16) ^ x;
      seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

/*
 * Classe abstrata usada para definir atributos e métodos em comum para todos os
 * algoritmos de busca.
 */
class SearchSort {
public:
  virtual void sort(std::vector<int> target, int& cost, int& expansions, std::string& path) = 0;

protected:
  // Mapa usado para armazenar estados que já foram explorados
  std::unordered_map<std::vector<int>, bool, int_vector_hash> explored;

  // Método que converte vetor para representação em string
  std::string vec_to_str(std::vector<int>& vec);

  // Método que verifica se um vetor é a solução procurada
  bool goal_test(std::vector<int>& vec);

  // Obtém a representação em string do estado inicial até o nó passado como
  // parâmetro
  std::string get_path(std::shared_ptr<Node> node);

  // Implementação da função heurística
  int heuristic(std::vector<int>& vec);
};

std::string search_sort(std::vector<int>& target, std::string& algorithm, int& cost,
                        int& expansions);

#endif