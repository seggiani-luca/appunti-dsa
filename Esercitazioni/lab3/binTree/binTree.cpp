#include "binTree.h"
#include <iostream>
#include <stack>

using namespace std;

BinTree::BinTree() { _root = nullptr; }
BinTree::~BinTree() {
  deltree(_root);
}

void BinTree::deltree(Node* root) {
  if(root != nullptr) {
    deltree(root->left);
    deltree(root->right);
    delete root;
  }
}

Node* BinTree::getRoot() { return _root; }

void BinTree::insertRic(int val, Node*& root) {
  if(root == nullptr) {
    root = new Node(val);
    return;
  }

  if(val <= root->value) 
    insertRic(val, root->left);
  else 
    insertRic(val, root->right); 
}

void BinTree::view(Node* root, int type) {
  switch(type) {
    case 1:
      if(root != nullptr) {
        view(root->left, type);
        cout << root->value << " ";
        view(root->right, type);
      }
    break;
    case 2:
      if(root != nullptr) {
        view(root->left, type);
        view(root->right, type);
        cout << root->value << " ";
      }
    break;
    case 3:
      if(root != nullptr) {
        cout << root->value << " ";
        view(root->left, type);
        view(root->right, type);
      }
    break;
  }
}

void BinTree::insertNode(int value) {
  if(mode) {
    insertRic(value, _root);
  } else {
    Node* newNode = new Node(value);
    Node* p = _root, *q = nullptr;
    if(p == nullptr) {
      _root = newNode;
      return;
    }
    while(p != nullptr) {
      q = p;
      if(value <= p->value) {
        p = p->left;
      } else {
        p = p->right;
      }
    }
    if(value <= q->value) {
      q->left = newNode;
    } else {
      q->right = newNode;
    }
  }
}

void BinTree::vos() {
  if(mode) {
    view(_root, 1);
  } else {
    stack<Node*> stack;
    Node* root = _root;
    while(!stack.empty() || root != nullptr) { 
      while(root != nullptr) {
        stack.push(root);
        root = root->left;
      }
      root = stack.top()->right;
      cout << stack.top()->value << " ";
      stack.pop();
    }
  }
  cout << endl;
}

void BinTree::vod() {
    if(mode) {
        view(_root, 2);
    } else {
        stack<Node*> stack;
        Node* root = _root;
        while(!stack.empty() || root != nullptr) {
            while(root != nullptr) {
                if(root->right != nullptr)
                    stack.push(root->right);
                stack.push(root);
                root = root->left;
            }
            root = stack.top();
            stack.pop();
            if(root->right != nullptr && (!stack.empty() && root->right == stack.top())) {
                stack.pop();
                stack.push(root);
                root = root->right;
            } else {
                cout << root->value << " ";
                root = nullptr;
            }
        }
    }
    cout << endl;
}

void BinTree::voa() {
  if(mode) {
    view(_root, 3);
  } else {
    stack<Node*> stack;
    stack.push(_root);
    while(!stack.empty()) {
      Node* top = stack.top();
      stack.pop();
      cout << top->value << " ";
      if(top->right)
        stack.push(top->right);
      if(top->left)
        stack.push(top->left);
    }
  }  
  cout << endl;
}

Node* BinTree::minRic(Node* root) {
  if(root == nullptr)
    return nullptr;
  if(root->left == nullptr)
    return root;
  return minRic(root->left);
}

Node* BinTree::maxRic(Node* root) {
  if(root == nullptr)
    return nullptr;
  if(root->right == nullptr)
    return root;
  return maxRic(root->right);
}

Node* BinTree::min() {
  if(mode) {
    return minRic(_root);
  } else {
    Node* temp = _root;
    while(temp->left != nullptr) {
      temp = temp->left;
    }
    return temp;
  }
}

Node* BinTree::max() {
  if(mode) {
    return maxRic(_root);
  } else {
    Node* temp = _root;
    while(temp->right != nullptr) {
      temp = temp->right;
    }
    return temp;
  }
}

int BinTree::minHeightRic(Node* root) {
  if(root == nullptr)
    return 0;
  return 1 + minHeightRic(root->left);
}

int BinTree::maxHeightRic(Node* root) {
  if(root == nullptr)
    return 0;
  return 1 + maxHeightRic(root->right);
}

int BinTree::minHeight() {
  if(mode) {
    return minHeightRic(_root);
  } else {
    Node* temp = _root;
    int count = 1;
    while(temp->left != nullptr) {
      temp = temp->left;
      count++;
    }
    return count;
  }
}

int BinTree::maxHeight() {
  if(mode) {
    return maxHeightRic(_root);
  } else {
    Node* temp = _root;
    int count = 1;
    while(temp->right != nullptr) {
      temp = temp->right;
      count++;
    }
    return count;
  }
}

Node* BinTree::searchRic(int key, Node* root) {
  if(root == nullptr)
    return nullptr;
  if(root->value == key)
    return root;
  if(key <= root->value)
    return searchRic(key, root->left);
  else
    return searchRic(key, root->right);
}

Node* BinTree::search(int key) {
  if(mode) {  
    return searchRic(key, _root);
  } else {
    Node* temp = _root;
    while(temp != nullptr) {
      if(temp->value == key)
        return temp;
      if(key <= temp->value)
        temp = temp->left;
      else
        temp = temp->right;
    } 
    return nullptr;
  }
}

int BinTree::searchDepthRic(int key, Node* root) {
  if(root == nullptr)
    return 0;
  if(root->value == key)
    return 1;
  if(key <= root->value)
    return 1 + searchDepthRic(key, root->left);
  else
    return 1 + searchDepthRic(key, root->right);
}

int BinTree::searchDepth(int key) {
  if(mode) {
    return searchDepthRic(key, _root);
  } else {
    Node* temp = _root;
    int count = 1;
    while(temp != nullptr) {
      if(temp->value == key)
        return count;
      if(key <= temp->value) {
        temp = temp->left;
        count++;
      } 
      else {
        temp = temp->right;
        count++;
      } 
    } 
    return 0;
  }
}

int BinTree::depthRic(Node* root) {
  if(root == nullptr)
    return 0;

  int left = depthRic(root->left);
  int right = depthRic(root->right);
  return 1 + (left > right ? left : right);
}

struct NodeHeight {
  Node* node;
  int depth;

  NodeHeight(Node* r, int d) :
    node(r), depth(d) {}
};

int BinTree::depth() {
  if(mode) {
    return depthRic(_root);
  } else {
    Node* temp = _root;
    if(temp == nullptr) 
      return 0;
    int max = 0;
    stack<NodeHeight*> stack;
    stack.push(new NodeHeight(_root, 1));
    while(!stack.empty()) {
      Node* temp = stack.top()->node;
      int height = stack.top()->depth;
      stack.pop();
      if(temp->left == nullptr && temp->right == nullptr) {
        if(height > max) max = height;
      }
      if(temp->left != nullptr) {
        stack.push(new NodeHeight(temp->left, height + 1));
      }
      if(temp->right != nullptr) {
        stack.push(new NodeHeight(temp->right, height + 1));
      }
    }
    return max;
  }
}
