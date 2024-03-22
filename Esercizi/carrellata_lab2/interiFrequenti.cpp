#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Elem {
  int freq;
  int val;
};

bool compareElem(Elem a, Elem b) {
  return a.freq < b.freq;
}

void frequenti(vector<int> vett, int k) {
  vector<Elem> elems;
  for(int i = 0; i < vett.size(); i++) {
    bool found = false;
    for(int j = 0; j < elems.size(); j++) {
      if(elems[j].val == vett[i]) {
        elems[j].freq++;
        found = true;
      }
    }
    if (!found) {
      Elem elem;
      elem.val = vett[i];
      elem.freq = 1;
      elems.push_back(elem);
    }
  }
  sort(elems.begin(), elems.end(), compareElem);
  auto iterator = elems.end() - 3;
  for(; iterator < elems.end(); iterator++) {
    cout << iterator->val << "\t";
  }
  cout << endl;
}

void printVett(vector<int> vett) {
  for(int i = 0; i < vett.size(); i++) {
    cout << vett[i] << " ";
  }
  cout << endl;
}

int main() {
  vector<int> vett = {1, 2, 2, 3, 3, 3, 7, 9, 1, 1, 9, 8, 1, 3, 8}; 
  printVett(vett);
  frequenti(vett, 3);
  return 0;
}
