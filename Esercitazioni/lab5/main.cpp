#include "hash.h"
#include <iostream>
using namespace std;

int main() {
  cout << "Quanto la voi grossa sta tabella?\n";
  int size; cin >> size;
  HashTable table = HashTable(size);
  cout << "Damme un tot di interi\n";
  for(int i = 0; i < 10; i++) {
    int c; cin >> c;
    if(table.insert(c))
      cout << "Chiave aggiunta\n";
    else
      cout << "Nse po fa\n";
  }
  table.print();
  cout << "Ora damme un tot di interi da cerca\n"; 
  for(int i = 0; i < 5; i++) {
  int c; cin >> c;
    if(table.find(c))
      cout << "Il " << c << " ce sta\n";
    else 
      cout << "Il  " << c << " nce sta\n";
  }
  return 0;
}
