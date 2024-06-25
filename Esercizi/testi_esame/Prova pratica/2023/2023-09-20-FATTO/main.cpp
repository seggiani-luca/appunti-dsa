#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define DEPTH 3

class Tree {
private:
  struct Node {
    int inf;
    int weight;
    int s;
    Node* left;
    Node* right;
    Node(int i, int w) : inf(i), weight(w), s(0), left(nullptr), right(nullptr) {}
  };
  Node* root;
  int n;
  int k;

  void insert(int, int, Node*&);
  void deltree(Node*);
  void do_get_s(Node*);
  int get_s(Node*, int);
  void insert_vec(Node*, vector<pair<int, int>>&);
  bool p(Node* node) { return (node->weight * k < node->s); }
public:
  Tree(int n_val, int k_val) : k(k_val), n(n_val), root(nullptr) {}
  ~Tree() { deltree(root); }
  void insert(int i, int w) { insert(i, w, root); }
  void print();
};

void Tree::insert(int i, int w, Node*& node) {
  if(node == nullptr) {
    node = new Node(i, w);
    return;
  } else if(i < node->inf) insert(i, w, node->left);
  else if(i > node->inf) insert(i, w, node->right);
}

void Tree::deltree(Node* node) {
  if(node == nullptr)
    return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

void Tree::do_get_s(Node* node) {
  if(node == nullptr)
    return;
  node->s = get_s(node, DEPTH);
  do_get_s(node->left);
  do_get_s(node->right);
}

int Tree::get_s(Node* node, int depth) {
  if(depth == 0 || node == nullptr) return 0;
  if(depth < DEPTH) return node->weight + get_s(node->left, depth - 1) + get_s(node->right, depth - 1);
  else return get_s(node->left, depth - 1) + get_s(node->right, depth - 1);
}

void Tree::insert_vec(Node* node, vector<pair<int, int>>& pairs) {
  if(node == nullptr)
    return;
  insert_vec(node->left, pairs);
  if(p(node))
    pairs.push_back({node->weight, node->inf});
  insert_vec(node->right, pairs);
}

void Tree::print() {
  do_get_s(root);
  vector<pair<int, int>> pairs;
  pairs.reserve(n);
  insert_vec(root, pairs);

  pair<int, int> max = *pairs.begin();
  for(auto it = pairs.begin() + 1; it < pairs.end(); it++) {
    if(it->first > max.first) max = *it;
    else if(it->first == max.first && it->second > max.second) max = *it; 
  }
  cout << max.second << endl;
}

int main() {
  int n, k;
  cin >> n >> k;
  Tree tree(n, k);
  for(int i = 0; i < n; i++) {
    int inf, weight;
    cin >> inf >> weight;
    tree.insert(inf, weight);
  }
  tree.print();
}
