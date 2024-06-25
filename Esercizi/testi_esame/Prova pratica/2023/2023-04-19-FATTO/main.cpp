#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

class Tree {
private:
  struct Node {
    int inf;
    Node* left;
    Node* right;
    Node(int i) : inf(i), left(nullptr), right(nullptr) {}
  };
  Node* root;
  int n;
  void deltree(Node*);
  void insert(int, Node*&);
  void get_leaves(Node*, std::list<Node*>&, bool);
  void get_count(Node*, std::vector<std::pair<int, int>>&);
public:
  Tree() : root(nullptr), n(0) {}
  ~Tree() { deltree(root); }
  void insert(int i) { insert(i, root); }
  void print(int);
};

void Tree::deltree(Node* node) {
  if(node == nullptr) 
    return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

void Tree::insert(int inf, Node*& node) {
  if(node == nullptr) {
    node = new Node(inf);
    n++;
    return;
  } else if(inf <= node->inf) insert(inf, node->left);
  else insert(inf, node->right);
}

void Tree::get_leaves(Node* node, std::list<Node*>& leaves, bool father = true) {
  if(node == nullptr)
    return;
  if(!node->left && !node->right && !father)
    leaves.push_back(node);
  get_leaves(node->left, leaves, false);
  get_leaves(node->right, leaves, false);
}

void Tree::get_count(Node* node, std::vector<std::pair<int, int>>& pairs) {
  if(node == nullptr)
    return;
  int val = 0;
  std::list<Node*> leaves;
  get_leaves(node, leaves);
  for(auto leaf: leaves) {
    if(leaf->inf == 0) {
      val += 2;
      continue;
    }
    if(leaf->inf % 2 == 1)
      val++;
    else val--;
  }
  pairs.push_back({val, node->inf});
  get_count(node->left, pairs);
  get_count(node->right, pairs);
}

bool sort_fun(std::pair<int, int>& a, std::pair<int, int>& b) {
  if(a.first > b.first) return false;
  else if(a.first < b.first) return true;
  else if(a.second < b.second) return false;
  else return true;
}

void Tree::print(int k) {
  std::vector<std::pair<int, int>> pairs;
  pairs.reserve(n);
  get_count(root, pairs);
  std::sort(pairs.begin(), pairs.end(), sort_fun);
  for(auto it = pairs.begin(); it < pairs.begin() + k; it++) {
    std::cout << it->second << std::endl;
  }
}

int main() {
  int n, k;
  std::cin >> n >> k;
  Tree tree;
  for(int i = 0; i < n; i++) {
    int inf;
    std::cin >> inf;
    tree.insert(inf);
  }
  try { tree.print(k); } catch(int) {};
  return 0;
}
