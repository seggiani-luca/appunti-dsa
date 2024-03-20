#include <iostream>
#include <vector>
using namespace std;

void sort(vector<int>& vec) {
  int current = 0;
  int p = 0;
  for(int i = 1; i < vec.size(); ++i) {
    current = vec[i];
    p = i - 1;
  
    while(p >= 0 && vec[p] > current) {
      vec[p + 1] = vec[p];
      p--;
    }
    vec[p + 1] = current;
  }
}

vector<int> read() {
  vector<int> vec;
  for(int i = 0; i < 10; ++i) {
    int a; cin >> a;
    vec.push_back(a);
  }
  return vec;
}

void print(vector<int> vec) {
  for(int i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

int main() {
  vector<int> vec = read();
  sort(vec);
  print(vec);
  return 0;
}
