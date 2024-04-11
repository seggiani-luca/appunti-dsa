#include <iostream>
#include "heap.h"

int main() {
  Heap heap;
  Heap heapyHeap;
  vector<int> vec;

  cout << "How many elements?" << endl;
  int n; cin >> n;
  cout << "Insert " << n << " elements." << endl;
  for(int i = 0; i < n; i++) {
    int c; cin >> c;
    heap.insert(c);
    vec.push_back(c);
  }
  
  cout << "Straight insertion gave:" << endl;
  heap.print();

  heapyHeap.heapify(vec);
  cout << "Heapification gave:" << endl;
  heapyHeap.print();


  cout << "Removing successive n elements..." << endl;
  for(int i = 0; i < n; i++) {
    cout << heap.extract() << " ";
  }
  cout << endl;

  cout << "Printing heapified vector in order" << endl;
  heapyHeap.inorder();

  return 0;
}
