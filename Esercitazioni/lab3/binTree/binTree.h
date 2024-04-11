#ifndef BINTREE_H
#define BINTREE_H

struct Node {
  int value;
  Node* left;
  Node* right;
  
  Node(int val) :
    value(val), left(nullptr), right(nullptr) {} 
};

class BinTree {
  Node* _root;
private:
  void deltree(Node*);
  void insertRic(int, Node*&);
  void view(Node*, int);
  Node* minRic(Node*);
  Node* maxRic(Node*);
  int minHeightRic(Node*);
  int maxHeightRic(Node*);
  Node* searchRic(int, Node*);
  int searchDepthRic(int, Node*);
  int depthRic(Node*);
public:
  BinTree();
  ~BinTree();
  Node* getRoot();
  void insertNode(int);
  void vos();
  void vod();
  void voa();
  Node* min();
  Node* max();
  int minHeight();
  int maxHeight();
  Node* search(int);
  int searchDepth(int);
  int depth();

  bool mode; //just switches between iterative and recursive 
};

#endif
