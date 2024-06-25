#include <iostream>
using namespace std;

enum pal { sinistro, centrale, destro };

void stampa(pal pal) {
  switch(pal) {
    case sinistro:
      cout << "sinistro";
      break;
    case centrale:
      cout << "centrale";
      break;
    case destro:
      cout << "destro";
  }
}

void sposta(pal da, pal a) {
  stampa(da);
  cout << " -> ";
  stampa(a);
  cout << endl;
}

void hanoi(int n, pal da = sinistro, pal a = destro, pal aus = centrale) {
  if(n == 1) sposta(da, a);
  else {
    hanoi(n - 1, da, aus, a);
    sposta(da, a);
    hanoi(n - 1, aus, a, da);
  }
}

int main() {
  int n;
  cin >> n;
  hanoi(n);
  return 0;
}
