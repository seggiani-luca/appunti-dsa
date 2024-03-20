#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

struct Richiesta {
  int id_;
  int prio_;
  // costruttore con lista init
  Richiesta(int id, int prio):
    id_(id) , prio_(prio){}
};

bool confrontaRichieste( Richiesta r1 , Richiesta r2) {
  if( r1.id_<r2.id_ )
    return true;
  else if(r1.id_ == r2.id_)
  {
  if(r1.prio_>r2.prio_)
    return true;
  else
    return false;
  }
  else
    return false;
}

void printArr(vector<Richiesta> vett) {
  for(int i = 0; i < vett.size(); i++) {
    cout << "RICHIESTA: " << vett[i].id_ << "\tPRIORITA': " << vett[i].prio_ << endl;
  }
}

int main() {
  int n;
  cout << "Inserisci la dimensione di istanza" << endl;
  cin >> n;

  vector<Richiesta> vett;
  for(int i = 0; i < n; i++) {
    vett.push_back(Richiesta(i / 2, i * 10));
  }
  cout << "UNSORTED:" << endl;
  printArr(vett);
  sort(vett.begin(), vett.end(), confrontaRichieste);
  cout << "SORTED:" << endl;
  printArr(vett);

  return 0;
}
