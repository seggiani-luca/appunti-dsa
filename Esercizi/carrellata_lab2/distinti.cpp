#include <iostream>
#include <vector>
using namespace std;

#define NULLHASH 0
#define SCANSTEP 3
#define TABSIZE 50

void printArr(int vett[], int n) {
  for(int i = 0; i < n; i++) {
    cout << vett[i] << "\t";
  }
  cout << endl;
}
void printArr(vector<int> vett) {
  for(int i = 0; i < vett.size(); i++) {
    cout << vett[i] << "\t";
  }
  cout << endl;
}

/*
vector<int> distingui(int vett[], int n) {
  vector<int> newVett;
  for(int i = 0; i < n; i++) {
    bool found = false;
    for(int j = 0; j < i; j++) {
      if(vett[j] == vett[i])
        found = true;
    }
    if(!found)
      newVett.push_back(vett[i]);
  }
  return newVett;
} //really inefficient! let's do hash
*/


//Hashing functions
struct Elem {
  int key;
  bool found;
};

int getHash(int key) {
    const int prime = 31;
    int hash = 7;
    
    hash = hash * prime + key;
  return key % TABSIZE;
}

bool isFound(Elem* table, int index) {
  int origIndex = index;
  while(table[index].key != NULLHASH) {
    if(table[index].key == index)
      break;
    index += SCANSTEP;
    if(index == origIndex)
      return false;
  }
  return table[index].found == false;
}

bool add(Elem* table, int index) {
  int origIndex = index;
  while(table[index].found == true || table[index].key != NULLHASH) {
    index += SCANSTEP;
    if(index == origIndex)
    return false;
  }
  table[index].found = true;
  table[index].key = index;
  return true;
}


vector<int> hashedDistingui(int vett[], int n) {
  Elem* table = new Elem[TABSIZE];
  vector<int> newVett;
  for(int i = 0; i < n; i++) {
    int origIndex;
    int index = getHash(vett[i]);
    if(isFound(table, index)) {
      add(table, index);
    newVett.push_back(vett[i]);
    } 
  }
  delete[] table;
  return newVett;
}

int main() {
  int vett[] = {1, 7, 9, 1, 1, 9, 2, -3, 2, -3};
  printArr(vett, 10);
  vector<int> newVett = hashedDistingui(vett, 10);
  printArr(newVett);
  return 0;
}
