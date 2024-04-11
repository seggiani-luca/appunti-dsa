#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Concorrente {
  int id;
  int arrivo;
  Concorrente(int i, int a) :
    id(i), arrivo(a) {}
};

bool compare(Concorrente a, Concorrente b) {
  return a.arrivo < b.arrivo;
}

void stampaVett(vector<Concorrente> vett) {
  for(int i = 0; i < vett.size(); i++) {
    cout << "[" << vett[i].id << "] [" << vett[i].arrivo << "]" << endl;
  }
}

void stampaVett(vector<int> vett) {
  for(int i = 0; i < vett.size(); i++) {
    cout << "[" << vett[i] << "]" << endl;
  }
}

vector<int> calcolaDistacchi(vector<Concorrente> vett) {
  vector<int> distacchi;
  for(int i = 0; i < vett.size() - 1; i++) {
    distacchi.push_back(vett[i + 1].arrivo - vett[i].arrivo);
  }
  return distacchi;
}

int main() {
  vector<Concorrente> concorrenti = {Concorrente(6, 2), Concorrente(2, 3), Concorrente(13, 5), Concorrente(4, 8), Concorrente(5, 18)};
  sort(concorrenti.begin(), concorrenti.end(), compare);
  cout << "Classifica:" << endl;
  stampaVett(concorrenti);
  vector<int> distacchi = calcolaDistacchi(concorrenti);
  sort(distacchi.begin(), distacchi.end());
  cout << "Distacchi:" << endl;
  stampaVett(distacchi);
}
