#include "dict.h"
#include <iostream>
using namespace std;

struct hash_injective : public hash_function<int> {
  hash_injective(unsigned int s) : hash_function<int>(s) {}
  unsigned int operator()(int k) {
    return k % size;
  }
};

struct hash_knuth : public hash_function <int> {
  hash_knuth (unsigned int s) : hash_function <int>(s) {};
  unsigned int operator ()(int k) {
    k *= 2654435761;  // 2654435761 is (2^32 / ϕ) where ϕ is the golden ratio
    return k & size;
  }
};

struct linear_scan : public scan_law {
  linear_scan(unsigned int s) : scan_law(s) {}
  unsigned int operator()(unsigned int pos, unsigned int offset) {
    return (pos + offset) % size;
  }
};

int main() {
  unsigned int tableSize = 100;
  hash_knuth hash(tableSize);
  linear_scan scan(tableSize);
  DictionaryOpen<int, int> dict(tableSize, hash, scan);

  while(true) {
    cout << "Scegli un'operazione da eseguire:\ni - Inserisci\np - Controlla\nf - Trova\nd - Elimina\nq - Esci" << endl;
    char c; cin >> c;
    switch(c) {
      case 'i': {
        int key, value;
        cout << "Inserisci una coppia chiave - valore" << endl;
        cin >> key; cin >> value;
        if(dict.insert(key, value)) {
          cout << "Coppia " << key << " - " << value << " inserita" << endl; 
        } else {
          cout << "Chiave già esistente, impossibile inserire" << endl;
        }
        break;
      }
      case 'p': {
        cout << "Inserisci una chiave" << endl;
        int key;
        cin >> key;
        cout << (dict.is_present(key) ? "Chiave presente" : "Chiave inesistente") << endl;
        break;
      }
      case 'f': {
        cout << "Inserisci una chiave" << endl;
        int key;
        cin >> key;
        std::pair<bool, int> result = dict.find(key);
        if(result.first) {
          cout << "Trovata chiave " << key << " con valore " << result.second << endl;
        } else {
          cout << "Chiave inesistente" << endl;
        }
        break;
      }
      case 'd': {
        cout << "Inserisci una chiave" << endl;
        int key;
        cin >> key;
        if(dict.erase(key)) {
          cout << "Elemento con chiave " << key << " eliminato" << endl;
        } else {
          cout << "Chiave inesistente" << endl;
        }
        break;
      }
      case 'q': {
        cout << "Arrivederci" << endl;
        exit(0);
      }
    }
  }
  return 0;
}
