#ifndef HASH
#define HASH
#define NULL 0

struct Elem {
  int key;
  Elem* next;
  Elem* prev;
  Elem() : next(NULL), prev(NULL) {}
};

class HashTable {
  Elem** _table;
  int _size;

public:
  HashTable(int);
  bool insert(int);
  void print();
  int hash(int);
  bool find(int);
};

#endif
