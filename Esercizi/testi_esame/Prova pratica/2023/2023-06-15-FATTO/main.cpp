#include <iostream>
#include <utility>

class Tree {
private:
  struct Node  {
    int inf;
    Node* left;
    Node* right;
    explicit Node(int i) : inf(i), left(nullptr), right(nullptr) {}
  };
  Node* root;
  void deltree(Node*);
  void print(Node*, int a, int b) const;
  int get_unique(Node*) const;
public:
  Tree() : root(nullptr) {}
  ~Tree() { deltree(root); }
  void insert(int inf); 
  void print(int a, int b) const { print(root, a, b); }
};

void Tree::deltree(Node* node) {
  if(node == nullptr)
    return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

void Tree::insert(int inf) {
  Node** pun = &root;
  while(*pun != nullptr) {
    if(inf <= (*pun)->inf) pun = &(*pun)->left;
    else if(inf > (*pun)->inf) pun = &(*pun)->right;
  }
  *pun = new Node(inf);
  // non mi piace sta roba, always bet on the compiler
}

void Tree::print(Node* node, int a, int b) const {
  if(node == nullptr)
    return;
  print(node->left, a, b);
  int unique = get_unique(node);
  if(a <= unique && unique <= b)
    std::cout << node->inf << std::endl;
  print(node->right, a, b);
}

int Tree::get_unique(Node* node) const {
  if(node == nullptr)
    return 0;
  int val = 0;
  for(auto child: {std::make_pair(node->left, node->right), std::make_pair(node->right, node->left)}) {
    if(child.first) {
      bool is_leaf = true;
      for(auto nephew: {child.first->left, child.first->right}) {
        if(nephew) is_leaf = false;
      }
      if(is_leaf && !child.second) val = 1;
    } 
  }
  return val + get_unique(node->left) + get_unique(node->right);
}

int main() {
  int n, a, b;
  std::cin >> n >> a >> b;
  
  Tree tree;
  for(int i = 0; i < n; i++) {
    int inf;
    std::cin >> inf;
    tree.insert(inf);
  }
  
  tree.print(a, b);

  return 0;
}
