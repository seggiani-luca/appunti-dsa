#ifndef HEAP_H
#define HEAP_H

#include <vector>
using namespace std;

class Heap {
  vector<int> _h;

  void exchange(int, int);
  void up(int);
  void down(int);
  int last() { return _h.size() - 1; }
  void inorderHelper(int);
public:
  void insert(int);
  int extract();
  void heapify(vector<int>);
  void print();
  void inorder();
};

#endif
