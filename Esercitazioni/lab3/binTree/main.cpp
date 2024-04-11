#include "binTree.h"
#include <iostream>
using namespace std;

void insertInTree(BinTree& tree1, BinTree& tree2, int num) {
  for(int i = 0; i < num; i++) {
    int c; cin >> c;
    tree1.insertNode(c);
    tree2.insertNode(c);
  }
}

void testTree(BinTree& tree, int k) {
  cout << "Tree has depth " << tree.depth() << endl;

  cout << "# VIEWS" << endl;
  cout << "Vos: "; tree.vos();
  cout << "Vod: "; tree.vod();
  cout << "Voa: "; tree.voa();

  cout << "# MAXIMA AND MINIMA" << endl;
  cout << "Tree has minimum " << tree.min()->value << " at height " << tree.minHeight() << endl;
  cout << "Tree has maximum " << tree.max()->value << " at height " << tree.maxHeight() << endl;

  cout << "# KEY SEARCH" << endl;
  Node* ricFound = tree.search(k);
  if(ricFound == nullptr) {
    cout << "Search for key returned nullptr" << endl;
  } else {
    cout << "Search found match " << ricFound->value << " at height " << tree.searchDepth(k) << endl;
  }
}

int main() {
  BinTree ricTree, itTree;
  ricTree.mode = true;
  itTree.mode = false;

  cout << "Tree size?" << endl;
  int n; cin >> n;
  if(n <= 0) n = 1;

  cout << "Enter " << n << " values" << endl;
  insertInTree(ricTree, itTree, n);

  cout << "Enter search key" << endl;
  int k; cin >> k;

  cout << "== RECURSIVE FUNCTIONS ==" << endl;
  testTree(ricTree, k);
  cout << "== ITERATIVE FUNCTIONS ==" << endl;
  testTree(itTree, k);
  
  return 0;
}
