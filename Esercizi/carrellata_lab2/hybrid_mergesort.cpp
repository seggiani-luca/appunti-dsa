#include <iostream>
#include <vector>
using namespace std;

int treshold;
int seed;

void insertion_sort(int vett[], int beg, int end) {
  int current = 0, p = 0;
  for(int i = beg + 1; i < end; i++) {
    current = vett[i];
    p = i - 1;

    while(p >= 0 && vett[p] > current) {
      vett[p + 1] = vett[p];
      p--;
    }
    vett[p + 1] = current;
  }
}

void print_vett(int vett[], int size) {
  for(int i = 0; i < size; i++) {
    cout << vett[i] << "\t";
  }
  cout << endl;
}

void merge(int arr[], int beg, int mid, int end) {
    int iS = beg;
    int iD = mid;

    vector<int> temp;

    while(true) {
        if(arr[iS] <= arr[iD]) {
            temp.push_back(arr[iS++]);
            if(iS >= mid) {
                while(iD < end) temp.push_back(arr[iD++]);
                break;
            }
        } else {
            temp.push_back(arr[iD++]);
            if(iD >= end) {
                while(iS < mid) temp.push_back(arr[iS++]);
                break;
            }
        }
    }

    for(int i = 0; i < temp.size(); i++) {
        arr[i + beg] = temp[i];
    }

}

void mergeSort(int vett[], int beg, int end) {
    if(beg + 1 < end) {
        if(end - beg < treshold) {
          insertion_sort(vett, beg, end);
          return;
        }
        int mid = (beg + end) / 2;
        mergeSort(vett, beg, mid);
        mergeSort(vett, mid, end);
        merge(vett, beg, mid, end);
    }
}

int main(int argc, char** argv) {
  
  int size = atoi(argv[1]);
  
  if(argc > 2)   
    treshold = atoi(argv[2]);
  else treshold = 0;

  if(argc > 3)
    seed = atoi(argv[3]);
  else seed = time(NULL);
  
  int* vett = new int[size];
  srand(seed);
  for(int i = 0; i < size; i++) {
    vett[i] = rand() % 99;
  }

  print_vett(vett, size);
  mergeSort(vett, 0, size);
  print_vett(vett, size);

  delete[] vett;
}

