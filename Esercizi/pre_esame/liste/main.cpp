#include <cmath>
#include <iostream>
#include "list.h"
#include <limits>
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
  List<double> list;
  while(true) {
    bool exit = false;
    cout << "- La lista ha l'aspetto: " << list << "con lunghezza " << list.length() << endl;
    cout << "Scegli un'operazione:\ni - Inserisci in testa\nI - Inserisci in coda\n"
            "d - Elimina testa\nD - Elimina coda\no - Inserisci ordinato\nO - Ordina lista\n"
            "e  - Elimina elemento\nc - Cerca elemento\nq - Esci dal programma" << endl;
    char c; cin >> c;
    switch(c) {
      case 'i': {
        cout << "Inserisci valore:" << endl;
        double inf;
        query_number(inf);
        list.head_insert(inf);
        break; 
      }
      case 'I': {
        cout << "Inserisci valore:" << endl;
        double inf;
        query_number(inf);
        list.tail_insert(inf);
        break; 
      }
      case 'd': {
        double result;
        if(list.head_delete(result))
          cout << "Rimosso " << result << endl;
        else
          cout << "Rimosso nulla" << endl;
        break;
      }
      case 'D': {
       double result;
        if(list.tail_delete(result))
          cout << "Rimosso " << result << endl;
        else
          cout << "Rimosso nulla" << endl;
        break; 
      } 
      case 'o': {
        cout << "Inserisci valore:" << endl;
        double inf;
        query_number(inf);
        list.order_insert(inf);
        break;
      }
      case 'O': {
        list.sort();
        break;
      }
      case 'e': {
        cout << "Quale elemento?" << endl;
        double inf;
        query_number(inf);
        cout << (list.delete_element(inf) ? "Elemento rimosso" : "Elemento non rimosso") << endl;
        break;
      }
      case 'c': {
        cout << "Quale elemento?" << endl;
        double inf;
        query_number(inf);
        cout << (list.contains(inf) ? "Contiene" : "Non contiene") << endl;
        break;
      }
      case 'q': {
        cout << "Arrivederci" << endl;
        exit = true;
        break;
      }
      default:
        cout << "Operazione invalida" << endl;
    }
    if(cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if(exit) break;
  }
  return 0;
}
