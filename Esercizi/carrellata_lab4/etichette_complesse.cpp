#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct Node {
  int key;
  string name;
  Node* left;
  Node* right;
  
  Node(int k, string n) :
    key(k), name(n) {}
};

void vos(Node* tree) {
  if(tree == nullptr) return;
  vos(tree->left);
  cout << "key: " << setw(2)<< tree->key << " | name: " << tree->name << endl;
  vos(tree->right);
}

void stampa(Node* tree) {

}

int main() {
  Node* tree = new Node(10, "Sheldon");
  tree->left = new Node(8, "Penny");
  tree->right = new Node(12, "Leonard");
  tree->left->left = new Node(4, "Raj");
  tree->left->right = new Node(9, "Bazinga");
  
  vos(tree);
}
