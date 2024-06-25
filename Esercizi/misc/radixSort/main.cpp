#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define k 26

void radix(vector<string>& vec, int len) {
  vector<vector<string>> temp;
  temp.reserve(k);
  for(int t = 1; t <= len; t++) {
    cout << "working on " << len - t << endl;
    for(int i = 0; i < vec.size(); i++) {
      temp[vec[i][len - t]-'@'].push_back(vec[i]);
      cout << " put " << vec[i] << " in " << vec[i][len - t]-'@' << endl;
    }
    int count = 0;
    for(int i = 0; i < k; i++) {
      for(int j = 0; j < temp[i].size(); j++) {
        vec[count] = temp[i][j];
        count++;
      }
      temp[i].clear();
    }
  } 
}

int main() {
  vector<string> vec = {
    "Dragon",
    "Rocket",
    "Window",
    "Banana",
    "Spirit",
    "Marvel",
    "Wisdom",
    "Pocket",
    "Turtle",
    "Palace",
    "Hammer",
    "Shadow",
    "Candle",
    "Jungle"};
  radix(vec, 6);
  for(int i = 0; i < 14; i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}
