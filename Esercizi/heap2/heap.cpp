#include "heap.h"
#include <iostream>
#include <math.h>
using namespace std;

void Heap::print() {
  for(int i = 0; i < _h.size(); i++) {
    if((i + 1 != 0) && ((i + 1 & (i)) == 0))
      cout << endl;
    cout << _h[i] << " ";
  }
  cout << endl;
}

void Heap::printVett() {
  for(int i = 0; i < _h.size(); i++) {
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

void Heap::maxHeapify(int i) {
  int left = getLeft(i);
  int right = getRight(i);
  int winner;
  if((left < _h.size()) && (_h[left] > _h[i])) {
    winner = left;
  } else {
    winner = i;
  }
  if((right < _h.size()) && (_h[right] > _h[winner])) {
    winner = right;
  }

  if(_h[i] < _h[winner]) {
    exchange(i, winner);
    maxHeapify(winner);
  }
}

void Heap::maxHeapify(int i, int len) {
  //cout << "this goddamn bastard is trying to sort from " << i << " to " << len << endl;
  int left = getLeft(i);
  int right = getRight(i);
  int winner;
  if((left < len) && (_h[left] > _h[i])) {
    winner = left;
  } else {
    winner = i;
  }
  if((right < len) && (_h[right] > _h[winner])) {
    winner = right;
  }

  if(_h[i] < _h[winner]) {
    exchange(i, winner);
    maxHeapify(winner, len);
  }
}

void Heap::buildHeap() {
  int mid = floor(last() / 2);
  for(int i = mid; i >= 0; i--) {
    maxHeapify(i);
    print();
  }
}

void Heap::heapSort() {
  for(int i = 0; i < _h.size() - 1; i++) {
    exchange(0, last() - i);
    maxHeapify(0, last() - i);
    print();
  }
}
