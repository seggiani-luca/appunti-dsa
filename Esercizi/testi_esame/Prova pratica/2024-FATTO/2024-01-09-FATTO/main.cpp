#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Tree {
  struct Node {
    int inf;
    int d;
    Node* left;
    Node* right;
    explicit Node(int i) : inf(i), d(INFINITY), left(nullptr), right(nullptr) {}
  };
  Node* root;
  void insert(int, Node*&);
  void deltree(Node*);
  void calculate_d(Node*, int, bool);
  void get_d_pairs(Node*, vector<pair<int,int>>&);
public:
  Tree() : root(nullptr) {}
  ~Tree() { deltree(root); }
  void insert(int inf) { insert(inf, root); }
  void get_d_pairs(vector<pair<int, int>>&);
};

void Tree::insert(int inf, Node*& node) {
  if(node == nullptr) {
    node = new Node(inf);
    return;
  }
  else if(inf < node->inf)
    insert(inf, node->left);
  else if(inf > node->inf)
    insert(inf,  node->right);
}

void Tree::deltree(Node* node) {
  if(node == nullptr) return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

void Tree::calculate_d(Node* node, int depth, bool even) {
  if(node == nullptr) return;
  if(node->inf % 2 == 1) { 
    //odd
    calculate_d(node->left, depth + 1, even);
    calculate_d(node->right, depth + 1, even);
  } else {
    //even
    calculate_d(node->left, 0, true);
    calculate_d(node->right, 0, true);
  } 
  if(depth < node->d && even)
      node->d = depth + 1;
  else
    node->d = -1;
}

void Tree::get_d_pairs(vector<pair<int, int>>& pairs) {
  calculate_d(root, 0, false);
  get_d_pairs(root, pairs);
}

void Tree::get_d_pairs(Node* node, vector<pair<int, int>>& pairs) {
  if(node == nullptr) return;
  get_d_pairs(node->left, pairs);
  pairs.push_back({node->d, node->inf});
  get_d_pairs(node->right, pairs);
}

int main() {
  int n, k;
  cin >> n >> k;
  Tree tree;
  for(int i = 0; i < n; i++) {
    int v; cin >> v;
    tree.insert(v);
  }
  vector<pair<int, int>> pairs;
  pairs.reserve(n);
  tree.get_d_pairs(pairs);  
  sort(pairs.begin(), pairs.end());
  for(auto i = pairs.rbegin(); i < pairs.rbegin() + k; i++) {
    cout << i->second << endl;
  }
}
