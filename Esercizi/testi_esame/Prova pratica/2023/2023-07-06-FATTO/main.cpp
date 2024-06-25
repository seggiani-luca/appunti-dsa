#include <iostream>
#include <stdexcept>

bool concordant(int a, int b) {
  return (a % 2 == b % 2);
}

class Tree {
private:
  struct Node {
    int inf;
    Node* left;
    Node* right;
    explicit Node(int i) : inf(i), left(nullptr), right(nullptr) {} 
  };
  Node* root;
  void insert(int, Node*&);
  void print(Node*);
  void deltree(Node*);

  int nC(Node*);
  int nD(Node*);
public:
  Tree() : root(nullptr) {}
  ~Tree() { deltree(root); }
  void insert(int inf) { insert(inf, root); }
  void print() { print(root); }
};

void Tree::insert(int inf, Node*& node) {
  if(node == nullptr) {
    node = new Node(inf);
    return;
  } else if(inf < node->inf) insert(inf, node->left);
  else if(inf > node->inf) insert(inf, node->right);
}

void Tree::print(Node* node) {
  if(node == nullptr)
    return;
  print(node->left);
  if(nC(node) > nD(node))
    std::cout << node->inf << std::endl;
  print(node->right);
}

void Tree::deltree(Node* node) {
  if(node == nullptr)
    return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

int Tree::nC(Node* node) {
  if(node == nullptr)
    return 0;
  int total = 0;
  for(auto child: {node->left, node->right}) {
    if(child) {
      int val = concordant(node->inf, child->inf);
      if(!child->left && !child->right) val *= 2;
      total += val; 
    }
  }
  return (total + nC(node->left) + nC(node->right));
}

int Tree::nD(Node* node) {
  if(node == nullptr)
    return 0;
  int total = 0;
  for(auto child: {node->left, node->right}) {
    if(child) {
      int val = !concordant(node->inf, child->inf);
      if(!child->left && !child->right) val *= 2;
      total += val; 
    }
  }
  return (total + nD(node->left) + nD(node->right));
}

int main() {
  int n;

  std::cin >> n;
  if(n < 0) throw std::invalid_argument("N must be greater than 0");

  Tree tree; 
  for(int i = 0; i < n; i++) {
    int inf;
    std::cin >> inf;
    tree.insert(inf);
  }
  
  tree.print();
  
  return 0;
}
