#include <iostream>
using namespace std;

class Tree {
private:
  struct Node {
    int inf;
    char color;
    Node* left;
    Node* right;
    Node(int i, char c) : inf(i), color(c), left(nullptr), right(nullptr) {}
  };
  Node* root;
  void insert(int, char, Node*&);
  void deltree(Node*);
  void print(Node*);
  bool acc(Node*);
public:
  Tree() : root(nullptr) {}
  ~Tree() { deltree(root); }
  void insert(int inf, char color) { insert(inf, color, root); }
  void print() { print(root); }
};

void Tree::insert(int inf, char color, Node*& node) {
  if(node == nullptr) {
    node = new Node(inf, color);
    return;
  } else if(inf < node->inf) insert(inf, color, node->left);
  else if(inf > node->inf) insert(inf, color, node->right);
}

void Tree::deltree(Node* node) {
  if(node == nullptr)
    return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

bool Tree::acc(Node* node) {
  for(auto child: {node->left, node->right})
    if(child) {
      bool satisfies = true;
      for(auto nephew: {child->left, child->right})
      if(!nephew) satisfies = false;
      else if(nephew->color != node->color) satisfies = false;
      if(satisfies) return true;  
    }
  return false;
}

void Tree::print(Node* node) {
  if(node == nullptr) return;
  print(node->left);
  if(acc(node))
    cout << node->inf << endl;
  print(node->right);
}

int main() {
  int n;
  cin >> n;
  Tree tree;
  for(int i = 0; i < n; i++) {
    int inf; char color;
    cin >> inf >> color;
    tree.insert(inf, color);
  }
  tree.print();
  return 0;
}
