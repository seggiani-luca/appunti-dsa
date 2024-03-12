#include <iostream>
using namespace std;

void stampa(int* vett, int dim) {
  for(int i = 0; i < dim; i++) {
    cout << vett[i] << " ";
  }
  cout << endl;
}

void sort(int* vett, int dim) {
  int current = 0;
  int p = 0;
  for(int i = 1; i < dim; i++) {
    cout << "iterazione " << i << ":" << endl;
    current = vett[i];
    p = i - 1;

    cout << "while:" << endl;
    while(p >= 0 && vett[p] > current) {
      vett[p + 1] = vett[p];
      p--;
      stampa(vett, dim);
    }
    vett[p + 1] = current;
    cout << "passo finale: " << endl;
    stampa(vett, dim);   
  }
}

int main() {
  const int dim = 10;
  int vett[dim];
  for(int i = 0; i < dim; ++i) {
    cin >> vett[i];
  }
  stampa(vett, dim);
  sort(vett, dim);
  stampa(vett, dim); 
}
