#include <iostream>
#include "heap.h"

int main() {
  Heap heap;

  cout << "How many elements?" << endl;
  int n; cin >> n;
  cout << "Insert " << n << " elements." << endl;
  for(int i = 0; i < n; i++) {
    int c; cin >> c;
    heap.dumbInsert(c);
  }
  
  cout << "I've got the vector:" << endl;
  heap.printVett();
  cout << "Heapification happening" << endl;
  heap.buildHeap();
  heap.print();

  cout << "Sorting" << endl;
  heap.heapSort();
  heap.printVett();

  return 0;
}
