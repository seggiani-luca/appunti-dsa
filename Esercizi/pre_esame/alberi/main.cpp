#include <cmath>
#include <iostream>
#include <limits>
#include "tree.h"
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
  Tree<float> tree;
  while(true) {
    bool exit = false;
    cout << "L'albero ha profondità: " << tree.depth() << endl;
    cout << "- Quale operazione vuoi effettuare?\ni - Inserisci\nd - Elimina nodo\nv - Visita albero\n"
    "V - Visualizza albero graficamente\nc - Cerca valore\nq - Esci dal programma" << endl;
    char c; cin >> c;
    switch(c) {
      case 'i': {
        cout << "Quale valore?" << endl;
        float inf;
        query_number(inf);
        tree.insert(inf);
        break;
      }
      case 'd': {
        cout << "Quale valore?" << endl;
        float inf;
        query_number(inf);
        tree.remove(inf);
        break;
      }
      case 'v': {
        cout << "Quale tipo di visita?\na - Anticipata\ns - Simmetrica\nd - Differita" << endl;
        while(true) {
          bool done = false;
          cin >> c;
          switch(c) {
            case 'a':
              tree.view(Tree<float>::view_type::a);
              done = true;
            break;
            case 's':
              tree.view(Tree<float>::view_type::s);
              done = true;
            break;
            case 'd':
              tree.view(Tree<float>::view_type::d);
              done = true;
            break;
            default:
              cout << "Visita invalida." << endl;
          }
          if(done) break;
        }
        break;
      }
      case 'V': {
        tree.visualize();
        break;
      }
      case 'c': {
        cout << "Quale valore?" << endl;
        float inf;
        query_number(inf);
        cout << (tree.search(inf) ? "Valore presente" : "Valore non presente") << endl; 
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
