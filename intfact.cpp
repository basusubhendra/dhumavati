#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <pthread.h>
#include <vector>
#include <math.h>
#include "zeros.hpp"
using namespace std;
#define NZEROS 2001052

struct a {
    char* num;
    short int param;
};

int binary_search(unsigned int arr[], int l, int r, unsigned long long int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid; 
        if (arr[mid] > x) 
            return binary_search(arr, l, mid - 1, x); 
        return binary_search(arr, mid + 1, r, x); 
    } 
    return -1; 
}  

bool isRiemannZero(unsigned long long int x) {
    if (binary_search(zeros, 0, NZEROS - 1, x) > 0) {
        return true;
    } else {
        return false;
    }
    return false;
}

vector<unsigned long long int>* factorize(struct a* arg) {
    char* num = ((struct a*) arg)->num;
    short int param = ((struct a*) arg)->param;
    FILE* f = 0, *g = 0;
    vector<unsigned long long int>* result = new vector<unsigned long long int>();
    if (param == 1) {
          f = fopen64("./positive_values.txt","r");
          g = fopen64("./positive_changes.txt","r");
    } else if (param == 0) {
          f = fopen64("./negative_values.txt","r");
          g = fopen64("./negative_changes.txt","r");
    }
    unsigned long long int l = strlen(num) - 1;
    unsigned long long int ctr = 0;
    unsigned long long int nchanges = 0;
    char nn = 0, cc = 0;
    while (ctr < l) {
        int ret = fscanf(f, "%c", &nn);
	if (ret == EOF) {
		printf("\nAbnormal Termination\n");
		exit(2);
	}
        ret = fscanf(g, "%c", &cc);
	if (ret == EOF) {
		printf("\nAbnormal Termination\n");
		exit(2);
	}
	if (cc == '1') {
		++nchanges;
	}
        if (nn == num[ctr]) {
              bool isRiemann1 = isRiemannZero(nchanges);
              if (isRiemann1) {
		         cout << ctr << "\t\t" << l << "\t\t" << cc << "\t\t" <<nn << "*\t\t*" << nchanges << endl;
                         ++ctr;
		  if (ctr == l) break;
	      } else {
		  cout << ctr << "\t\t" << l << "\t\t" << cc << "\t\t" <<nn << " \t\t " << nchanges << endl;
	      }
        }
	if (cc == '1' && nn == '0') {
		nchanges = 0;
	}
	fflush(f);
	fflush(g);
    }
    fclose(f);
    fclose(g);
    return result;
}

int main(int argc, char* argv[]) {
    char* num = strdup(argv[1]);
    struct a* arg1 = new (struct a)();
    arg1->num = strdup(num);
    arg1->param = 0;
    pthread_t thread_id1, thread_id2;
    vector<unsigned long long int>* ret1 = factorize(arg1);
    return 0;
}
