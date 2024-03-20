#include <iostream>
using namespace std;

/* LIST */

struct elem {
  elem* next;
  int inf;
};

void enqueue(elem*& s, int val) {
  elem* n = new elem;
  n->inf = val;
  n->next = nullptr;

  if(s == nullptr) {
    s = n;
    return;
  }

  elem* p, *q;
  for(p = s; p != nullptr; p = p->next) {
    q = p;
  }
  q->next = n;
}

void read(elem*& s, int n) {
  elem* prev = s;
  int c;
  for(int i = 0; i < n; i++) {
    cin >> c;
    enqueue(s, c);
  }
}

void print(elem* s) {
  for(; s != nullptr; s = s->next) {
    cout << s->inf << " ";
  }
  cout << endl;
}

void printtab(int n) {
  for(int i = 0; i < n; i++) {
    cout << "\t";
  }
}

/* MERGE */

void split(elem*& s1, elem*& s2) {
  if(s1 == nullptr || s1->next == nullptr) return;
  elem* p = s1->next;
  s1->next = p->next;
  p->next = s2;
  s2 = p;
  split(s1->next, s2);
}

void merge(elem*& s1, elem*& s2) {
  if(s2 == nullptr) return;
  if(s1 == nullptr) {
    s1 = s2;
    return;
  }
  if(s1->inf <= s2->inf) {
    merge(s1->next, s2);
  } else {
    merge(s2->next, s1);
    s1 = s2;
  }
}

void mergesort(elem*& s1, int depth = 0, bool dir = false) {
  printtab(depth);
  cout << "--- DEPTH: " << depth << " " << (dir ? "LEFT" : "RIGHT") << " ---" << endl;

  if(s1 == nullptr || s1->next == nullptr) return;
  elem* s2 = nullptr; 
  split(s1, s2);
  printtab(depth);
  cout << "Split list 1: "; print(s1);
  printtab(depth);
  cout << "Split list 2: "; print(s2);
  
  mergesort(s1, ++depth, false);
  mergesort(s2, ++depth, true);

  merge(s1, s2);
  printtab(depth);
  cout << "Merged depth " << depth << " sublists: "; print(s1);
}

/* MAIN */

int main() {
  elem* s = nullptr;
  read(s, 10);
  mergesort(s);
  print(s);
  return 0;
}
