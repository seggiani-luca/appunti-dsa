#include "heap.h"
#include <iostream>
using namespace std;

void Heap::print() {
  for(int i = 0; i < _h.size(); i++) {
    if((i + 1 != 0) && ((i + 1 & (i)) == 0))
      cout << endl;
    cout << _h[i] << " ";
  }
  cout << endl;
}

void Heap::exchange(int a, int b) {
  int temp = _h[a];
  _h[a] = _h[b];
  _h[b] = temp;
}

void Heap::insert(int val) {
  _h.push_back(val);
  up(last()); 
}

int Heap::extract() {
  int r = _h[0];
  _h[0] = _h[last()];
  _h.pop_back();
  down(0);
  return r;
}
 
void Heap::up(int i) {
  if(i > 0) {
    int parent = (i - 2) / 2;
    if(_h[i] > _h[parent]) {
      exchange(i, parent);
      up(parent);
    }
  }
}

void Heap::down(int i) {
  int child = 2 * i + 1;
  if(child == last()) {
    if(_h[child] > _h[i]) {
      exchange(child, i);
    }
  } else if(child < last()) {
    //let the children fight
    if(_h[child] < _h[child + 1]) child++;
    if(_h[child] > _h[i]) {
      exchange(child, i);
      down(child);
    }
  }
}

void Heap::heapify(vector<int> vec) {
  _h = vec;
  for(int i = (last() / 2) - 1; i >= 0; i--) {
    down(i);
  }
}

void Heap::inorderHelper(int i) {
  if(i > last()) return;
  inorderHelper(2 * i + 1);
  cout << _h[i] << " ";
  inorderHelper(2 * i + 2);
}

void Heap::inorder() {
  inorderHelper(0);
  cout << endl;
}
