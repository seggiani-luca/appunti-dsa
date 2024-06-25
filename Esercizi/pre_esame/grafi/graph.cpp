#include "graph.h"
#include <cmath>
#include <ostream>
#include <pthread.h>
#include <queue>
#include <stack>
#include <string>
#include <utility>

#define UNIT "km"

void Graph::insert_node(std::string& name) {
  nodes.push_back(std::list<Node>());
  node_labels.push_back(name);
  label_map.emplace(name, node_labels.size() - 1);
}

void Graph::insert_arc(int node1, int node2, float distance) {
  nodes[node1].push_back(Node(node2, distance));
}

void Graph::insert_arc(std::string& str1, std::string& str2, float distance) {
  int node1 = string_to_node(str1);
  int node2 = string_to_node(str2);
  insert_arc(node1, node2, distance);
}

void Graph::insert_bidirectional(int node1, int node2, float distance) {
  insert_arc(node1, node2, distance);
  insert_arc(node2, node1, distance);
}

void Graph::insert_bidirectional(std::string& str1, std::string& str2, float distance) {
  int node1 = string_to_node(str1);
  int node2 = string_to_node(str2);
  insert_bidirectional(node1, node2, distance);
}

void Graph::depth_visit(std::ostream& stream) const {
  std::stack<int> stack;
  std::vector<bool> markers(nodes.size(), false);
  for(int i = 0; i < nodes.size(); i++) {
    if(markers[i]) continue;
    stack.push(i);
    while(!stack.empty()) {
      int node = stack.top();
      stack.pop();
      if(!markers[node]) {
        stream << node_labels[node] << std::endl;
        markers[node] = true;
        for (auto it = nodes[node].rbegin(); it != nodes[node].rend(); ++it) 
          stack.push(it->node_number);
      }
    }
  }
}

void Graph::breadth_visit(std::ostream& stream) const {
  std::queue<int> queue;
  std::vector<bool> markers(nodes.size(), false);
  for(int i = 0; i < nodes.size(); i++) {
    if(markers[i]) continue;
    queue.push(i);
    while(!queue.empty()) {
      int node = queue.front();
      queue.pop();
      if(!markers[node]) {
        stream << node_labels[node] << std::endl;
        markers[node] = true;
        for(const auto& successor: nodes[node])
          queue.push(successor.node_number);
      }
    }
  }
}

std::list<int> Graph::shortest_path(std::string str1, std::string str2, float* distance) const {
  int node1 = string_to_node(str1);
  int node2 = string_to_node(str2);
  return shortest_path(node1, node2, distance);
}

std::list<int> Graph::shortest_path(int source, int target, float* distance) const {
  //setup
  std::vector<float> distances(nodes.size(), INFINITY);
  distances[source] = 0.0f;
  std::vector<int> previous(nodes.size(), -1);
  std::priority_queue<std::pair<int, float>> prio_queue;
  prio_queue.emplace(source, 0.0f);
  /*
  for(int i = 0; i < nodes.size(); i++)
    if(i != source)
      prio_queue.emplace(i, INFINITY); 
  */
  //loop
  while(!prio_queue.empty()) {
    std::pair<int, float> u = prio_queue.top();
    prio_queue.pop();
    for(const auto& node: nodes[u.first]) {
      float new_distance = u.second + node.arc_length;
      if(new_distance < distances[node.node_number]) {
        previous[node.node_number] = u.first;
        distances[node.node_number] = new_distance;
        prio_queue.emplace(node.node_number, new_distance);
      }
    }
  }

  if(distance)
    *distance = distances[target];

  std::list<int> sequence;
  int u = target;
  while(u != -1) {
    sequence.push_front(u);
    u = previous[u];
  }
  return sequence;
}

std::ostream& operator<<(std::ostream& stream, Graph& graph) {
  stream << "NODES:" << std::endl;
  for(int i = 0; i < graph.node_labels.size(); i++) {
    stream << "[" << i << "]" << " " << graph.node_labels[i] << std::endl;
  }
  stream << "ARCS:" << std::endl;
  for(int i = 0; i < graph.nodes.size(); i++) {
    for(const auto& node: graph.nodes[i]) {
      int i2 = node.node_number;
      stream << "[" << i << "] (" << graph.node_labels[i] << ") -> [" << i2
             << "] (" << graph.node_labels[i2] << ") distance " << node.arc_length 
             << UNIT << std::endl;
    }
  }
  return stream;  
}
