#include <algorithm>
#include <iostream>
using namespace std;

class Tree {
  struct Node {
    int inf;
    Node* left;
    Node* right;
    Node(int i) : inf(i), left(nullptr), right(nullptr) {}
  };
  Node* root;
  int k;
  void insert(int, Node*&);
  void print(Node*);
  void deltree(Node*);
  int height(Node*);
public:
  void insert(int inf) { insert(inf, root); }
  void print() { print(root); }
  Tree(int k_val) : root(nullptr), k(k_val) {}
  ~Tree() { deltree(root); }
};

void Tree::insert(int inf, Node*& node) {
  if(node == nullptr) {
    node = new Node(inf);
    return;
  }
  else if(inf < node->inf) 
    insert(inf, node->left);
  else if(inf > node->inf)
    insert(inf, node->right);
}

int Tree::height(Node* node) {
  if(node == nullptr) return 0;
  return 1 + max(height(node->left), height(node->right));
}

void Tree::print(Node* node) {
  if(node == nullptr) return;
  print(node->left);
  if(height(node->left) - height(node->right) < 1)
    cout << node->inf << endl;
  print(node->right);
}

void Tree::deltree(Node* node) {
  if(node == nullptr) return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

int main() {
  int n, k;
  cin >> n; cin >> k;
  Tree tree(k);
  for(int i = 0; i < n; i++) {
    int val; cin >> val;
    tree.insert(val);
  }
  tree.print();
}
