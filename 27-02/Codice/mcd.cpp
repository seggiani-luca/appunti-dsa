#include <iostream>
using namespace std;

int mcd(int a, int b) {
  while(a != b) {
    if(a > b) a -= b;
    else b -= a;
  }
  return a;
}

int betterMcd(int a, int b) {
  while(b > 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

int main() {
  cout << "Inserisci due interi" << endl;
  int a, b;
  cin >> a >> b;
  cout << "L'mcd e' " << betterMcd(a,b) << endl; 
  return 0;
}
