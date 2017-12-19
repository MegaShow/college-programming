// 1011. Set Intersection
// MegaShow

//pre: A represents a set with m elements, B represents a set with n elements
//Post: returns the intersetion C of A and B, k is the number of elements in C.
void set_intersection(int A[], int m, int B[], int n, int C[], int &k){
    k = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(A[i] == B[j])
                C[k++] = A[i];
        }
    }
}

/* test
#include <cstdio>

int main(){
    int a[3] = {1, 3, 5};
    int b[2] = {3, 6};
    int c[10];
    int k;
    set_intersection(a, 3, b, 2, c, k);
    for(int i = 0; i < k; i++)
        printf("%d ", c[i]);
}*/