#include <iostream>

struct Node {
  int label;
  Node* left;
  Node* right;
  Node(int l) : label(l), left(nullptr), right(nullptr) {}
};

void insert(Node*& tree, int label) {
  if(!tree) {
    tree = new Node(label);
    return;
  }
  if(label <= tree->label)
    insert(tree->left, label);
  else insert(tree->right, label);
}

int count(Node* tree, int k, int& nodes) {
  if(!tree) return 0;
  int nodes_l = count(tree->left, k, nodes);
  int nodes_r = count(tree->right, k, nodes);
  if(nodes_l + nodes_r == k) nodes++;
  return 1 + nodes_l + nodes_r;
}

int evil_count(Node* t, int x, int& nodes) {
  if(!t) { nodes = 0; return 0; }
  int nodes_l, nodes_r;
  int conta_l = evil_count(t->left, x, nodes_l);
  int conta_r = evil_count(t->right, x, nodes_r);
  nodes = nodes_l + nodes_r + 1;
  return conta_l + conta_r + (x == nodes);
}

int main() {
  Node* tree = nullptr;
  int n, k;
  std::cin >> n >> k;
  for(int i = 0; i < n; i++) {
    int l; std::cin >> l;
    insert(tree, l);
  }
  
  int nodes = 0;
  count(tree, k, nodes);
  std::cout << nodes << std::endl;
  std::cout << evil_count(tree, k, nodes) << std::endl;
  std::cout << nodes << std::endl;
}

