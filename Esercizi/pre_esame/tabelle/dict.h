#ifndef TABLE_H
#define TABLE_H
#include <utility>

// - DICTIONARY ABSTRACT CLASS -

template<typename Key, typename Value>
class Dictionary {
public:
  virtual bool is_present(Key) const = 0;
  virtual std::pair<bool, Value> find(Key) = 0;
  virtual bool insert(Key, Value) = 0;
  virtual bool erase(Key) = 0;
};

// - DICTIONARY LIST IMPLEMENTATION -

template<typename Key, typename Value>
class DictionaryList : public Dictionary<Key, Value> {
  struct Elem {
    Key key;
    Value info;
    Elem* next;
    Elem(Key k, Value i) 
    : key(k), info(i), next(nullptr) {}
  };
  Elem* head;
  Elem* tail;
public:
  DictionaryList() { head = nullptr; tail = nullptr; }
  bool is_present(Key) const override;
  std::pair<bool, Value> find(Key) override;
  bool insert(Key, Value) override;
  bool erase(Key) override;
  ~DictionaryList();
};

template<typename Key, typename Value>
bool DictionaryList<Key, Value>::is_present(Key key) const {
  Elem* pun = head;
  while(pun != nullptr) {
    if(pun->key == key) return true;
    pun = pun->next;
  }
  return false;
}

template<typename Key, typename Value>
std::pair<bool, Value> DictionaryList<Key, Value>::find(Key key) {
  Elem* pun = head;
  std::pair<bool, Value> result;
  while(pun != nullptr) {
    if(pun->key == key) {
      result.first = true;
      result.second = pun->info;
      return result;
    }
    pun = pun->next;
  }
  result.first = false;
  return result;
}

template<typename Key, typename Value>
bool DictionaryList<Key, Value>::insert(Key key, Value value) {
  if(is_present(key)) return false;
  Elem* n = new Elem(key, value);
  if(head == nullptr) {
    head = n;
    tail = head;
  } else {
    tail->next = n;
    tail = n;
  }
  return true;
}

template<typename Key, typename Value>
bool DictionaryList<Key, Value>::erase(Key key) {
  if(head == nullptr) return false;
  Elem *p, *q = nullptr;
  for(p = head; p != nullptr && p->key != key; p = p->next)
    q = p;
  if(p == head) {
    head = p->next;
    delete p;
    return true;
  }
  if(p == tail) {
    q->next = nullptr;
    tail = q;
    delete p;
    return true;
  }
  if(p != nullptr) {
    q->next = p->next;
    delete p;
    return true;
  }
  return false;
}

template<typename Key, typename Value>
DictionaryList<Key, Value>::~DictionaryList() {
  while(head != nullptr) {
    Elem* temp = head;
    head = head->next;
    delete temp;
  }
}

// - DICTIONARY BINARY SEARCH TREE IMPLEMENTATION -

template<typename Key, typename Value>
class DictionaryBST : public Dictionary<Key, Value> {
  struct Node {
    Key key;
    Value info;
    Node* left;
    Node* right;
    Node(Key k, Value i)
    : key(k), info(i), left(nullptr), right(nullptr) {}
  };
  Node* root;

  bool is_present(Key key, Node* root) const;
  void find(Key key, Node* root, std::pair<bool, Value>& result);
  bool insert(Key, Value, Node*&);
  bool erase(Key, Node*&);
  void delete_min(Value&, Node*&);
  void deltree(Node*);
public:
  DictionaryBST() { root = nullptr; }
  bool is_present(Key key) const override { return is_present(key, root); }

  std::pair<bool, Value> find(Key key) override { 
    std::pair<bool, Value> result;
    result.first = false;
    find(key, root, result); 
    return result;
  }
  
  bool insert(Key key, Value value) override { return insert(key, value, root); }
  bool erase(Key key) override { return erase(key, root); }
  ~DictionaryBST() { deltree(root); }
};

template<typename Key, typename Value>
bool DictionaryBST<Key, Value>::is_present(Key key, Node* root) const {
  if(root == nullptr)
    return false;
  if(root->key == key)
    return true;
  if(key < root->key)
     return is_present(key, root->left);
  else
    return is_present(key, root->right);
}

template<typename Key, typename Value>
void DictionaryBST<Key, Value>::find(Key key, Node* root, std::pair<bool, Value>& result) {
  if(root == nullptr)
    return;
  if(root->key == key) {
    result.first = true;
    result.second = root->info;
    return;
  }
  if(key < root->key)
    find(key, root->left, result);
  else
    find(key, root->right, result);
}

template<typename Key, typename Value>
bool DictionaryBST<Key, Value>::insert(Key key, Value value, Node*& root) {
  if(root == nullptr) {
    root = new Node(key, value);
    return true;
  }
  if(key < root->key) return insert(key, value, root->left);
  if(key > root->key) return insert(key, value, root->right);
  return false;
}

template<typename Key, typename Value>
bool DictionaryBST<Key, Value>::erase(Key key, Node*& root) {
  if(root == nullptr)
    return false;
  if(key < root->key) erase(key, root->left);
  else if(key > root->key) erase(key, root->right);
  else if(!root->left) {
    Node* temp = root;
    root = root->right;
    delete temp;
  } else if(!root->right) {
    Node* temp = root;
    root = root->left;
    delete temp;
  } else {
    delete_min(root->info, root->right);
  }
  return true;
}

template<typename Key, typename Value>
void DictionaryBST<Key, Value>::delete_min(Value& inf, Node*& node) {
  if(node->left) delete_min(inf, node->left);
  else {
    inf = node->info;
    Node* temp = node;
    node = node->right;
    delete temp;
  }
}

template<typename Key, typename Value>
void DictionaryBST<Key, Value>::deltree(Node* root) {
  if(root == nullptr)
    return;
  deltree(root->left);
  deltree(root->right);
  delete root;
}

// - DICTIONARY ORDERED ARRAY IMPLEMENTATION -

template<typename Key, typename Value>
class DictionaryArray : public Dictionary<Key, Value> {
  struct Elem {
    Key key;
    Value info;
  };
  Elem* array;
  int size;
  int current_size;
  
  bool is_present(Key, int, int) const;
  int find(Key, int, int);
public:
  DictionaryArray(int dim) {
    size = dim;
    array = new Elem[size];
    current_size = 0;
  }

  bool is_present(Key key) const override { return is_present(key, 0, current_size); }

  std::pair<bool, Value> find(Key key) override { 
    std::pair<bool, Value> result;
    int pos = find(key, 0, current_size);
    if(pos != -1) {
      result.first = true;
      result.second = array[pos].info;
    } else {
      result.first = false;
    }
    return result;
  }
  
  bool insert(Key, Value) override;
  bool erase(Key) override;
  ~DictionaryArray() { delete[] array; } 
};

template<typename Key, typename Value>
bool DictionaryArray<Key, Value>::is_present(Key key, int min, int max) const {
  if(min > max) return false;
  int mid = (min + max) / 2;
  if(key == array[mid].key) return true;
  if(key < array[mid].key) 
    return is_present(key, 0, mid - 1);
  else 
    return is_present(key, mid + 1, max);
}


template<typename Key, typename Value>
int DictionaryArray<Key, Value>::find(Key key, int min, int max) {
  if(min > max)
    return -1;
  int mid = (min + max) / 2;
  if(key == array[mid].key) {
    return mid;
  }
  if(key < array[mid].key) 
    return find(key, 0, mid - 1);
  else
    return find(key, mid + 1, max);
}

template<typename Key, typename Value>
bool DictionaryArray<Key, Value>::insert(Key key, Value value) {
  if(current_size == size || is_present(key, 0, current_size)) return false;
  int i = current_size - 1;
  for(; i >= 0 && array[i].key > key; i--) {
    array[i + 1] = array[i];
  }
  array[i + 1].key = key;
  array[i + 1].info = value;
  current_size++;
  return true;
}

template<typename Key, typename Value>
bool DictionaryArray<Key, Value>::erase(Key key) {
  int pos = find(key, 0, current_size);
  if(pos != -1) {
    for(; pos < current_size; pos++) {
      array[pos] = array[pos + 1];
    }
    current_size--;
    return true;
  } else {
    return false;
  }
}

// - HASH FUNCTORS -

template<typename Key>
struct hash_function /*: public std::unary_function<Key, unsigned int>, deprecato in C++17*/ {
  int size;
  explicit hash_function(int s) : size(s) {}
  virtual unsigned int operator()(Key k) = 0;
};

struct scan_law {
  int size;
  explicit scan_law(int s) : size(s) {}
  virtual unsigned int operator()(unsigned int, unsigned int) = 0;
};

// - DICTIONARY DIRECT ACCESS HASH IMPLEMENTATION -

template<typename Key, typename Value>
class DictionaryDirect : public Dictionary<Key, Value> {
  Value** table;
  unsigned int size;
  hash_function<Key>& hash;
public:
  DictionaryDirect(int, hash_function<Key>&);
  bool is_present(Key key) const override { return table[hash(key)]; }
  std::pair<bool, Value> find(Key) override;
  bool insert(Key, Value) override;
  bool erase(Key) override;
  ~DictionaryDirect(); 
};

template<typename Key, typename Value>
DictionaryDirect<Key, Value>::DictionaryDirect(int dim, hash_function<Key>& h) : hash(h) {
  size = dim;
  table = new Value*[size];
  for(int i = 0; i < size; i++) {
    table[i] = nullptr;
  }
}

template<typename Key, typename Value>
std::pair<bool, Value> DictionaryDirect<Key, Value>::find(Key key) {
  std::pair<bool, Value> result;
  Value* pun = table[hash(key)];
  if(pun) {
    result.first = true;
    result.second = *pun;
  } else {
    result.first = false;
  }
  return result;
}

template<typename Key, typename Value>
bool DictionaryDirect<Key, Value>::insert(Key key, Value value) {
  Value*& pun = table[hash(key)];
  if(pun) {
    return false;
  } else {
    pun = new Value(value);
    return true;
  }
}

template<typename Key, typename Value>
bool DictionaryDirect<Key, Value>::erase(Key key) {
  Value *& pun = table[hash(key)];
  if(pun) {
    delete pun;
    pun = nullptr;
    return true;
  } else {
    return false;
  }
}


template<typename Key, typename Value>
DictionaryDirect<Key, Value>::~DictionaryDirect() {
  for(int i = 0; i < size; i++) {
    delete table[i];
  }
  delete[] table;
}

// - DICTIONARY CHAINED HASH IMPLEMENTATION -

template<typename Key, typename Value>
class DictionaryChained : public Dictionary<Key, Value> {
  struct Elem {
    Key key;
    Value value;
    Elem* next;
    Elem(Key k, Value v) : key(k), value(v), next(nullptr) {}
  };
  Elem** table;
  unsigned int size;
  hash_function<Key>& hash;
public:
  DictionaryChained(int, hash_function<Key>&);
  bool is_present(Key) const override;
  std::pair<bool, Value> find(Key) override;
  bool insert(Key, Value) override;
  bool erase(Key) override;
  ~DictionaryChained(); 
};

template<typename Key, typename Value>
DictionaryChained<Key, Value>::DictionaryChained(int dim, hash_function<Key>& h) : hash(h) {
  size = dim;
  table = new Elem*[size];
  for(int i = 0; i < size; i++) {
    table[i] = nullptr;
  }
}

template<typename Key, typename Value>
bool DictionaryChained<Key, Value>::is_present(Key key) const {
  Elem* pun = table[hash(key)];
  while(pun) {
    if(pun->key == key) {
      return true;
    } else
      pun = pun->next;
  }
  return false;
}

template<typename Key, typename Value>
std::pair<bool, Value> DictionaryChained<Key, Value>::find(Key key) {
  std::pair<bool, Value> result;
  Elem* pun = table[hash(key)];
  while(pun) {
    if(pun->key == key) {
      result.first = true;
      result.second = pun->value;
      return result;
    } else
      pun = pun->next;
  }
  result.first = false;
  return result;
}

template<typename Key, typename Value>
bool DictionaryChained<Key, Value>::insert(Key key, Value value) {
  if(is_present(key)) return false;
  Elem*& pun = table[hash(key)];
  Elem* n = new Elem(key, value);
  n->next = pun;
  pun = n;
  return true;
}

template<typename Key, typename Value>
bool DictionaryChained<Key, Value>::erase(Key key) {
  unsigned int pos = hash(key);
  Elem* pun = table[pos];
  if(pun == nullptr) return false;
  if(pun->key == key) {
    table[pos] = pun->next;
    delete pun;
    return true;
  }
  while(pun->next) {
    if(pun->next->key == key) {
      Elem* temp = pun->next;
      pun->next = temp->next;
      delete temp;
      return true;
    }
    pun = pun->next;
  }
  return false;
}


template<typename Key, typename Value>
DictionaryChained<Key, Value>::~DictionaryChained() {
  for(int i = 0; i < size; i++) {
    delete table[i];
  }
  delete[] table;
}

// - DICTIONARY OPEN HASH IMPLEMENTATION -

template<typename Key, typename Value>
class DictionaryOpen : public Dictionary<Key, Value> {
  struct Elem {
    Key key;
    Value value;
    Elem(Key k, Value v) : key(k), value(v) {}
  };
  Elem** table;
  Elem* erased;
  unsigned int size;
  hash_function<Key>& hash;
  scan_law& scan;
public:
  DictionaryOpen(int, hash_function<Key>&, scan_law&);
  bool is_present(Key) const override;
  std::pair<bool, Value> find(Key) override;
  bool insert(Key, Value) override;
  bool erase(Key) override;
  ~DictionaryOpen(); 
};

template<typename Key, typename Value>
DictionaryOpen<Key, Value>::DictionaryOpen(int dim, hash_function<Key>& h, scan_law& s) : hash(h), scan(s) {
  size = dim;
  table = new Elem*[size];
  for(int i = 0; i < size; i++) {
    table[i] = nullptr;
  }
  erased = (Elem*) table;
}

template<typename Key, typename Value>
bool DictionaryOpen<Key, Value>::is_present(Key key) const {
  int i = hash(key);
  for(int j = 0; j < size; j++) {
    Elem* pun = table[scan(i, j)];
    if(pun == nullptr) return false;
    if(pun == erased) continue;
    if(pun->key == key) return true;
  }
  return false;
}

template<typename Key, typename Value>
std::pair<bool, Value> DictionaryOpen<Key, Value>::find(Key key) {
  std::pair<bool, Value> result;
  result.first = false;
  int i = hash(key);
  for(int j = 0; j < size; j++) {
    Elem* pun = table[scan(i, j)];
    if(pun == nullptr) return result;
    if(pun == erased) continue;
    if(pun->key == key) {
      result.first = true;
      result.second = pun->value;
      return result;
    }
  }
  return result;
}

template<typename Key, typename Value>
bool DictionaryOpen<Key, Value>::insert(Key key, Value value) { 
  if(is_present(key)) return false;
  int i = hash(key);
  for(int j = 0; j < size; j++) {
    Elem*& pun = table[scan(i, j)];
    if(pun == nullptr || pun == erased) {
      pun = new Elem(key, value);
      return true;
    }
  }
  return false;
}


template<typename Key, typename Value>
bool DictionaryOpen<Key, Value>::erase(Key key) {
  int i = hash(key);
  for(int j = 0; j < size; j++) {
    Elem*& pun = table[scan(i, j)];
    if(pun == nullptr) return false;
    if(pun == erased) continue;
    if(pun->key == key) {
      delete pun;
      pun = erased;
      return true;
    }
  }
  return false;
}


template<typename Key, typename Value>
DictionaryOpen<Key, Value>::~DictionaryOpen() {
  for(int i = 0; i < size; i++) {
    delete table[i];
  }
  delete[] table;
}


#endif
