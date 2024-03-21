#include <iostream>
using namespace std;

struct Node {
  int inf;
  Node* next;
};

void push_front(Node*& list, int val) {
 Node* n = new Node;
  n->inf = val;
  n->next = nullptr;
  if(list == nullptr) {
    list = n;
    return;
  }
  n->next = list;
  list = n;
}

void push_back(Node*& list, int val) {
  Node* n = new Node;
  n->inf = val;
  n->next = nullptr;
  if(list == nullptr) {
    list = n;
    return;
  }
  Node* q;
  for(q = list; q->next != nullptr; q = q->next);
  q->next = n;
}

bool pop_front(Node*& list, int& dest) {
  if(list == nullptr) return false;
  dest = list->inf;
  Node* p = list;
  list = list->next;
  delete p;
  return true;
}

bool pop_front(Node*& list) {
  if(list == nullptr) return false;
  Node* p = list;
  list = list->next;
  delete p;
  return true;
}

bool pop(Node* node) {
  if(node == nullptr) return false;
  Node* middle = node->next;
  if(middle == nullptr) return false;
  Node* last = node->next->next;
  if(last != nullptr)
    node->next = last;
  delete middle;
  return true;
}

bool pop_back(Node*& list, int& dest) {
  if(list == nullptr) return false;
  Node* q, *p;
  for(q = list; q->next != nullptr; q = q->next)
    p = q;
  p->next = nullptr;
  dest = q->inf;
  delete q;
  return true;
}

void print_list(Node*& list) {
  for(Node* p = list; p != nullptr; p = p->next) {
    cout << p->inf << "\t";
  } 
  cout << endl;
}

Node* search_list(Node*& list, int val) {
  for(Node* q = list; q->next != nullptr; q=q->next) {
    if(q->inf == val)
      return q;
  }
  return nullptr;
}

bool search_previous(Node*& list, int val, Node*& node) {
  Node *p = nullptr, *q;
  for(q = list; q->next != nullptr; q=q->next) {
    if(q->inf == val) {
      node = p;
      return true;
    }
    p = q;
  }
  return false;
}

bool search_pop(Node*& list, int val) {
  Node* prev;
  if(search_previous(list, val, prev)) {
    if(prev == nullptr) {
      pop_front(list);
      return true;
    }     
    pop(prev);
    return true;
  } else return false;
}

int main() {
  Node* list = nullptr;
  for(int i = 0; i < 5; i++) {
    int c;
    cin >> c;
    push_back(list, c);
  }
 for(int i = 0; i < 5; i++) {
    int c;
    cin >> c;
    push_front(list, c);
  }
  print_list(list);
  int c;
  cin >> c;
  
  if(search_pop(list, c)) {
    push_front(list, c);
  }

  print_list(list);
  return 0;
}
