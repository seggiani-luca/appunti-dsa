#ifndef TREE_H
#define TREE_H

#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>
#include <sstream>

template<class type>
class Tree {
private:
  struct Node {
    type label;
    Node* left;
    Node* right;
    Node(type b, Node* l = nullptr, Node* r = nullptr) : label(b), left(l), right(r) {}
    Node() { left = right = nullptr; }
  };
  Node* root;
  void deltree(Node*);
  void inorder(Node*);
  void postorder(Node*);
  void preorder(Node*);
  void insert_node(type, Node*&);
  void delete_node(type, Node*&);
  void delete_min(type&, Node*&);
  int depth_wrapped(Node*);
  bool search_node(type, Node*);
public:
  Tree() : root(nullptr) {}
  ~Tree();
  void insert(type);
  void remove(type);  
  enum class view_type{ a, s, d };
  void view(view_type);
  void visualize();
  int depth();
  bool search(type);
};

template<class type>
void Tree<type>::deltree(Tree<type>::Node* node) {
  if(node == nullptr) return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

template<class type>
Tree<type>::~Tree() {
  deltree(root);
}

template<class type>
void Tree<type>::preorder(Tree<type>::Node* node) {
  if(!node) return;
  std::cout << node->label << "\t";
  preorder(node->left);
  preorder(node->right);
}

template<class type>
void Tree<type>::inorder(Tree<type>::Node* node) {
  if(!node) return;
  inorder(node->left);
  std::cout << node->label << "\t";
  inorder(node->right);
}

template<class type>
void Tree<type>::postorder(Tree<type>::Node* node) {
  if(!node) return;
  postorder(node->left);
  postorder(node->right);
  std::cout << node->label << "\t";
}

template<class type>
void Tree<type>::view(view_type c) {
  switch(c) {
    case view_type::a:
      preorder(root);
    break;
    case view_type::s:
      inorder(root);
    break;
    case view_type::d:
      postorder(root);
    break;
  }
  std::cout << std::endl;
}

template<class type>
void Tree<type>::insert_node(type inf, Node*& node) {
  if(!node) {
    node = new Node(inf);
    return;
  }
  if(inf < node->label) insert_node(inf, node->left);
  if(inf > node->label) insert_node(inf, node->right);
  return;
}

template<class type>
void Tree<type>::insert(type inf) {
  insert_node(inf, root);
}

template<class type>
void Tree<type>::visualize() {
  if(!root) return;
  int width = std::pow(2, depth()) - 1;
  std::vector<std::vector<std::string>> levels(depth(), std::vector<std::string>(width, " "));

  std::queue<std::tuple<Node*, int, int>> nodes;
  nodes.push(std::make_tuple(root, 0, (width - 1) / 2));

  while(!nodes.empty()) {
    std::tuple<Node*, int, int> node = nodes.front();
    nodes.pop();
    int level = std::get<1>(node);
    int pos = std::get<2>(node);
    Node* current = std::get<0>(node);
    std::stringstream ss;
    ss << current->label;
    levels[level][pos] = ss.str();
    int offset = std::pow(2, depth() - level - 2);
    if(current->left) nodes.push(std::make_tuple(current->left, level + 1, pos - offset));
    if(current->right) nodes.push(std::make_tuple(current->right, level + 1, pos + offset));
    
  }

  for(int i = 0; i < levels.size(); i++) {
    std::vector<std::string> level = levels[i];
    for(int j = 0; j < level.size(); j++) {
      std::cout << level[j] << " ";
    }
    std::cout << std::endl;
  }
}

template<class type>
int Tree<type>::depth_wrapped(Node* node) {
  if(!node) return 0;
  return 1 + std::max(depth_wrapped(node->left), depth_wrapped(node->right));
}

template<class type>
int Tree<type>::depth() {
  return depth_wrapped(root);
}

template<class type>
void Tree<type>::delete_node(type inf, Node*& node) {
  if(!node) return;
  if(inf < node->label) delete_node(inf, node->left);
  else if(inf > node->label) delete_node(inf, node->right);
  else if(!node->left) {
    Node* temp = node;
    node = node->right;
    delete temp;
  } else if(!node->right) {
    Node* temp = node;
    node = node->left;
    delete temp;
  } else {
    delete_min(node->label, node->right);
  }
}

template<class type>
void Tree<type>::delete_min(type& inf, Node*& node) {
  if(node->left) delete_min(inf, node->left);
  else {
    inf = node->label;
    Node* temp = node;
    node = node->right;
    delete temp;
  }
}

template<class type>
void Tree<type>::remove(type inf) {
  delete_node(inf, root);
}

template<class type>
bool Tree<type>::search_node(type inf, Node* node) {
  if(!node) return false;
  if(inf == node->label) return true;
  if(inf < node->label) return search_node(inf, node->left);
  else return search_node(inf, node->right);
}

template<class type>
bool Tree<type>::search(type inf) {
  return search_node(inf, root);
}

#endif
