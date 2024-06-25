#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

#define BUF_LEN 100

void strreverse( char *str ) {
    char *str_end = strchr( str, 0 );
    std::reverse( str, str_end );
}

int plsc(char* str1, char* str2, bool verbose) {
  int n = strlen(str1);
  int m = strlen(str2);
  int A[m + 1][n + 1];
  for(int j = 0; j < n + 1; j++) A[0][j] = 0;
  for(int i = 1; i < m + 1; i++) {
    A[i][0] = 0;
    for(int j = 1; j < n + 1; j++) {
      if(str1[j - 1] == str2[i - 1]) {
        A[i][j] = A[i - 1][j - 1] + 1;
      } else {
        A[i][j] = max(A[i -1][j], A[i][j - 1]);
      }
    }
  }
  if(verbose) {
    for(int i = -1; i < m + 1; i++) {
      for(int j = -1; j < n + 1; j++) {
        if(i == -1) {
          if(j >= 1) {
            cout << str1[j - 1];  
          } else {
            cout << ".";
          }
        } 
        else if(j == -1) {
          if(i >= 1) {
            cout << str2[i - 1];  
          } else {
            cout << ".";
          }
        } 
        else {
          cout << A[i][j];
        }
        cout << "\t";
      }
      cout << endl;
    }
  } 
  return A[m][n];
}

int plsc(char* str1, char* str2, bool verbose, char*& dest) {
  int n = strlen(str1);
  int m = strlen(str2);
  int A[m + 1][n + 1];
  for(int j = 0; j < n + 1; j++) A[0][j] = 0;
  for(int i = 1; i < m + 1; i++) {
    A[i][0] = 0;
    for(int j = 1; j < n + 1; j++) {
      if(str1[j - 1] == str2[i - 1]) {
        A[i][j] = A[i - 1][j - 1] + 1;
      } else {
        A[i][j] = max(A[i -1][j], A[i][j - 1]);
      }
    }
  }
  if(verbose) {
    for(int i = -1; i < m + 1; i++) {
      for(int j = -1; j < n + 1; j++) {
        if(i == -1) {
          if(j >= 1) {
            cout << str1[j - 1];  
          } else {
            cout << ".";
          }
        } 
        else if(j == -1) {
          if(i >= 1) {
            cout << str2[i - 1];  
          } else {
            cout << ".";
          }
        } 
        else {
          cout << A[i][j];
        }
        cout << "\t";
      }
      cout << endl;
    }
  }
  int si = 0;
  dest = new char[A[m][n] + 1];
  dest[A[m][n]] = '\0';
  int i = m, j = n;
  while(A[i][j] != 0) {
    if(str1[j - 1] == str2[i - 1]) {
      dest[si] = str1[j - 1];
      si++;
      i--, j--;
    } else {
      if(A[i - 1][j] > A[i][j - 1])
        i--;
      else j--;
    }
  }
  strreverse(dest);
  return A[m][n];
}

void get_string(char*& str) {
  str = new char[BUF_LEN];
  cin.getline(str, BUF_LEN);
}

int main() {
  char* string1;
  char* string2;
  get_string(string1);
  get_string(string2);
  char* dest;
  cout << plsc(string1, string2, true, dest) << " : ",
  cout << dest << endl;
  delete[] string1, delete[] string2, delete[] dest;
  return 0;
}
