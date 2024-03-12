#include <iostream>
using namespace std;

void stampaBuco(int* vett, int dim, int buco) {
  for(int i = 0; i < dim; i++) {
    if(i == buco) continue;
    cout << vett[i] << " ";
  }
  cout << endl;
}

void stampaSegno(int* vett, int dim, int pos) {
  if(pos > dim - 1) return;
  if(vett[pos] >= 0) cout << "+\n";
  else cout << "-\n";
}

int main() {
  int vett[] = {3, 6, -2, 1};
  stampaBuco(vett, 4, 1);
  stampaSegno(vett, 4, 2);
  return 0;
}
