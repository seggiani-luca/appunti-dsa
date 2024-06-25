#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <ostream>

class Graph {
  struct Node {
    int node_number;
    float arc_length;
    Node(int n, float d) : node_number(n), arc_length(d) {}
  };
  std::vector<std::list<Node>> nodes;
  std::vector<std::string> node_labels;
  std::unordered_map<std::string, int> label_map;
public:
  void insert_node(std::string&);
  void insert_arc(int, int, float);
  void insert_arc(std::string&, std::string&, float);
  void insert_bidirectional(int, int, float);
  void insert_bidirectional(std::string&, std::string&, float);

  std::string get_node(int node) const { return node_labels[node]; };
  int string_to_node(std::string& str) const { return label_map.find(str)->second; };

  void depth_visit(std::ostream&) const;
  void breadth_visit(std::ostream&) const;
  std::list<int> shortest_path(int, int, float* = 0) const;
  std::list<int> shortest_path(std::string, std::string, float* = 0) const;

  friend std::ostream& operator<<(std::ostream&, Graph&);
};

#endif
