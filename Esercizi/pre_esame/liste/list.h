#ifndef LIST_H
#define LIST_H

#include <ostream>

template<class type>
class List {
private:
  struct Elem {
    type inf;
    Elem* next;
    Elem(type i, Elem* n = nullptr) : inf(i), next(n) {}
    Elem() { next = nullptr; }
  };
  Elem* root;

  Elem* mergeSort(Elem*); //prende la lista e restituisce la lista ordinata
  Elem* split(Elem*); //prende la lista, la lascia dimezzata e restituisce l'altra metà
  Elem* merge(Elem*, Elem*); //prende due liste e restituisce l'unione
public:
  List() : root(nullptr) {}
  ~List();
  int length();
  void tail_insert(type);
  bool tail_delete(type&);
  void head_insert(type);
  bool head_delete(type&);
  void order_insert(type);
  bool delete_element(type);
  bool contains(type);
  void sort();

  template<class T>
  friend std::ostream& operator<<(std::ostream&, const List<T>&); 
};

template<class T>
std::ostream& operator<<(std::ostream& stream, const List<T>& list) {
  typename List<T>::Elem* pun = list.root;
  while(pun) {
    stream << pun->inf << " ";
    pun = pun->next;
  }
  return stream;
}

template<class type>
List<type>::~List() {
  Elem* pun = root;
  while(pun != nullptr) {
    Elem* temp = pun;
    pun = pun->next;
    delete temp;
  }
}

template<class type>
int List<type>::length() {
  Elem* pun = root;
  int count = 0;
  while(pun) {
    pun = pun->next;
    count++;
  }
  return count;
}

template<class type>
void List<type>::tail_insert(type inf) {
  Elem* n = new Elem(inf);
  if(!root)
    root = n;
  else {
    Elem* pun = root;
    while(pun->next)
      pun = pun->next;
    pun->next = n;
  }
}

template<class type>
bool List<type>::tail_delete(type& result) {
  if(!root)
    return false;
  Elem* p, *q = nullptr;
  for(p = root; p->next; p = p->next)
    q = p;
  result = p->inf;
  if(p == root)
    root = nullptr;
  else
    q->next = nullptr;
  delete p;
  return true;
}

template<class type>
void List<type>::head_insert(type inf) {
  root = new Elem(inf, root);
}

template<class type>
bool List<type>::head_delete(type& result) {
  if(!root)
    return false;
  Elem* pun = root;
  result = pun->inf;
  root = root->next;
  delete pun;
  return true;
}

template<class type>
void List<type>::order_insert(type inf) {
  Elem* n = new Elem(inf);
  if(!root) {
    root = n;
    return;
  }
  Elem *p, *q = nullptr;
  for(p = root; p && p->inf < inf; p = p->next)
    q = p;
  if(!q) {
    n->next = root;
    root = n;
  } else {
    q->next = n;
    n->next = p;
  } 
}

template<class type>
bool List<type>::delete_element(type inf) {
  Elem* p, *q = nullptr;
  for(p = root; p && p->inf != inf; p = p->next)
    q = p;
  if(!p) return false;
  if(p == root) 
    root = root->next;
  else
    q->next= p->next;
  delete p;
  delete_element(inf);
  return true;
}

template<class type>
bool List<type>::contains(type inf) {
  Elem* pun = root;
  while(pun) {
    if(pun->inf == inf)
      return true;
    pun = pun->next;
  }
  return false;
}

template<class type>
void List<type>::sort() {
  root = mergeSort(root);
}

template<class type>
typename List<type>::Elem* List<type>::mergeSort(List<type>::Elem* list1) {
  if(!list1 || !list1->next) return list1;
  Elem* list2 = split(list1); 
  list1 = mergeSort(list1); 
  list2 = mergeSort(list2);
  return merge(list1, list2);
}

template<class type>
typename List<type>::Elem* List<type>::split(List<type>::Elem* list1) {
  Elem* slow = list1, *fast = list1;
  while(fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  Elem* list2 = slow->next;
  slow->next = nullptr;
  return list2;
}

template<class type>
typename List<type>::Elem* List<type>::merge(List<type>::Elem* list1, List<type>::Elem* list2) {
  if (!list1) return list2;
  if (!list2) return list1;

  Elem final; //questa cosa è un po' bruttina, però funziona
  Elem* tail = &final;

  while (list1 && list2) {
    if (list1->inf < list2->inf) {
      tail->next = list1;
      list1 = list1->next;
    } else {
      tail->next = list2;
      list2 = list2->next;
    }
    tail = tail->next;
  }
  tail->next = (list1) ? list1 : list2;
  return final.next;
}

#endif
