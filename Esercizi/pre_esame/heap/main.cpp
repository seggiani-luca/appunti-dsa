#include <iostream>
#include <limits>
#include <cmath>
#include "heap.h"
using namespace std;

template<class type>
void query_number(type& num, double minBound = -INFINITY, double maxBound = INFINITY) {
  while(true) {
    std::cin >> num;
    bool fail = false;

    if(cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
      cout << "Valore fuori dal dominio ammesso." << endl;
      fail = true;
    }

    if(num < minBound || num > maxBound) {
      cout << "Valore fuori dai bound." << endl;
      fail = true;
    }

    if(!fail) break;
  }
}

int main() {
  cout << "Dimensione dell'heap?" << endl;
  int n;
  query_number(n);
  Heap<int> heap(n);
  while(true) {
    bool exit = false;
    cout << "L'heap ha l'aspetto: " << heap << endl;
    cout << "- Quale operazione vuoi effettuare?\ni - Inserisci\ne - Estrai\n" 
            "q - Esci dal programma" << endl;
    char c; cin >> c;
    switch(c) {
      case 'i': {
        cout << "Quale valore?" << endl;
        int inf;
        query_number(inf);
        heap.insert(inf);
        break;
      }
      case 'e': {
        cout << "Estratto " << heap.extract() << endl;
        break;
      }
      case 'q': {
          exit = true;
          break;
      }
      default:
        cout << "Operazione invalida." << endl;
    }
    if(cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if(exit) break;
  }
  return 0;
}
