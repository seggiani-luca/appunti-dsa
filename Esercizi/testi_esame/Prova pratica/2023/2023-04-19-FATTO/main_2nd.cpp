#include <cstdlib>
#include <iostream>
#include <map>
#include <set>

struct Node {
  int label;
  Node* left;
  Node* right;
  Node(int l) : label(l), left(nullptr), right(nullptr) {}
};
typedef Node* Tree;

void insert(Node*& node, int label) {
  if(node == nullptr) {
    node = new Node(label);
    return;
  } else if(label <= node->label) insert(node->left, label);
  else insert(node->right, label);
}

int get_points(Node*& node, std::map<int, std::multiset<int, std::greater<int>>>& nodes) {
  if(node == nullptr)
    return 0;
  int tmp = 0;
  if(!node->left && !node->right) {
    if(node->label == 0) tmp = 2;
    else if(node->label % 2 == 0) tmp = -1;
    else tmp = 1;
  }
  int points = get_points(node->left, nodes) + get_points(node->right, nodes); 
  nodes[points].insert(node->label);
  return tmp + points;
}

void deltree(Node* node) {
  if(node == nullptr)
    return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

int main() {
  int n, k;
  std::cin >> n >> k;

  Tree tree = nullptr;
  for(int i = 0; i < n; i++) {
    int inf; 
#ifdef TEST
      inf = std::rand() % 100;      
#else
      std::cin >> inf;
#endif
    insert(tree, inf);
  }

  std::map<int, std::multiset<int, std::greater<int>>> nodes;
  get_points(tree, nodes);
  for(auto node : nodes) {
    for(auto label : node.second) {
      if(k <= 0) break;
      std::cout << label << std::endl;
      k--;
    }
  }

  deltree(tree);

  return 0;
}
