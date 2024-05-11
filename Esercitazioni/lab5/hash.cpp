#include "hash.h"
#include <iostream>
#include <cstring>
using namespace std;

HashTable::HashTable(int size) {
  _size = size;
  _table = new Elem*[size];
  memset(_table, 0, size);
}

bool HashTable::insert(int key) {
  int index = hash(key);
  Elem* n = new Elem();
  n->key = key;
  n->next = _table[index];
  if(n->next != NULL)
    n->next->prev = n;
  _table[index] = n;
  return true;
}

int HashTable::hash(int key) {
  return key % _size;
}

void HashTable::print() {
  cout << "KEY\tVALUE\n";
  for(int i = 0; i < _size; i++) {
    cout << i << "\n";
    Elem* pun = _table[i];
    while(pun != nullptr) {
      cout << "\t" << pun->key << "\n";
      pun = pun->next;
    }
  }
}

bool HashTable::find(int key) {
  int index = hash(key);
  Elem* pun = _table[index];
  while(pun != nullptr) {
    if(pun->key == key)
      return true;
    pun = pun->next;
  }
  return false;
}
