#include <iostream>
using namespace std;

int* grandi(int vett[], int n, int k) {
  int* freqVett = new int[k];
  for(int i = 0; i < k; i++) {
    freqVett[i] = vett[i];
  }
  for(int i = k; i < n; i++) {
    int good = true;
    for(int j = 0; j < k; j++) {
      if(vett[i] == freqVett[j])
        good = false;
    }
    if(!good) continue;
    for(int j = 0; j < k; j++) {
      if(vett[i] > freqVett[j]) { 
        freqVett[j] = vett[i];
        break;
      }
    }
  }
  return freqVett;
}

void printVett(int vett[], int n) {
  for(int i = 0; i < n; i++) {
    cout << vett[i] << " ";
  }
  cout << endl;
}

int main() {
  int vett[] = {1, 7, 9, 1, 1, 9, 8};
  
  printVett(vett, 7);
  int* freqVett = grandi(vett, 7, 3);
  printVett(freqVett, 3);
  return 0;
}
