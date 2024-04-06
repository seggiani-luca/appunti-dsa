#include <iostream>
using namespace std;

void setaccia(int n) {
  bool num[n];

  //preparazione array
  num[0] = false; num[1] = true;
  for(int i = 2; i < n; i++) {
    num[i] = true;
  }
  
  int i = 2;
  while(i*i < n) {
    while(num[i] == false) i++;
    
    int m = 2;
    while(i * m < n) {
      num[i * m] = false;
      m++;
    }
    i++;
  }

  for(int i = 0; i < n; i++) {
    if(num[i] == true) {
      cout << i << " ";
    }
  }
}

int main() {
  cout << "Inserisci n" << endl;
  int n;
  cin >> n;
  setaccia(n);
  return 0;
}
