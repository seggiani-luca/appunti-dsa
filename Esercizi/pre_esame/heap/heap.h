#ifndef HEAP_H
#define HEAP_H

#include <ostream>

template<class type>
class Heap {
private:
  type* heap;
  int last;
  int size;
  void up(int);
  void down(int);
  void exchange(int&, int&);
  int parent(int);
  int son(int);
public:
  Heap(int);
  ~Heap();
  void insert(type inf);
  type extract();
  
  template<class T>
  friend std::ostream& operator<<(std::ostream&, const Heap<T>&);
};

template<class T>
std::ostream& operator<<(std::ostream& stream, const Heap<T>& heap) {
  if(heap.last == -1) return stream;
  for(int i = 0; i <= heap.last; i++) {
    stream << heap.heap[i] << " ";
  }
  stream << std::endl;
  return stream;
}

template<class type>
Heap<type>::Heap(int n) {
  heap = new type[n];
  last = -1;
  size = n;
}

template<class type>
Heap<type>::~Heap() {
  delete[] heap;
}

template<class type>
void Heap<type>::exchange(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

template<class type>
inline int Heap<type>::parent(int i) {
  return (i - 1) / 2;
}

template<class type>
inline int Heap<type>::son(int i) {
  return 2 * i + 1; //figlio destro a son() + 1
}

template<class type>
void Heap<type>::up(int i) {
  if(i > 0)
    if(heap[i] > heap[parent(i)])
      exchange(heap[i], heap[parent(i)]);
}

template<class type>
void Heap<type>::down(int i) {
  int s = son(i);
  if(s == last) {
    if(heap[i] < heap[s])
        exchange(heap[i], heap[last]);
  } else if (s < last) {
    if(heap[s] < heap[s + 1]) s++;
    if(heap[s] > heap[i]) {
      exchange(heap[i], heap[s]);
      down(s);
    }
  }
}

template<class type>
void Heap<type>::insert(type inf) {
  if(last >= size - 1) return;
  heap[++last] = inf;
  up(last);
}

template<class type>
type Heap<type>::extract() {
  if(last == -1) return 0;
  type r = heap[0];
  exchange(heap[0], heap[last--]);
  down(0);
  return r;
}


#endif
