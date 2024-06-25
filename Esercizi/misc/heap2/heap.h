#ifndef HEAP_H
#define HEAP_H

#include <vector>
using namespace std;

class Heap {
  vector<int> _h;

  int getLeft(int i) { return 2 * i + 1; };
  int getRight(int i) { return 2 * i + 2; };
  void exchange(int, int);
  void up(int);
  void down(int);
  int last() { return _h.size() - 1; }
  void maxHeapify(int);
  void maxHeapify(int, int);
public:
  void print();
  void printVett();
  void insert(int);
  void dumbInsert(int i) { _h.push_back(i); };
  int extract();
  void buildHeap();
  void heapSort();
};


#endif
