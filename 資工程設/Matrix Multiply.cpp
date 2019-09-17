#include <iostream>
//#include "function.h"
using namespace std;
class Matrix {
private:
    int size;
    int **arr;
    int get_count;
public:
    Matrix(int n, int **data) {
        size = n;
        arr = data;
        get_count = 0;
    }
    int *get_row(int row) {
        int *tmparr = new int[size];
        for (int i = 0; i < size; i++) {
            tmparr[i] = arr[row][i];
        }
        get_count++;
        return tmparr;
    }
    int *get_column(int col) {
        int *tmparr = new int[size];
        for (int i = 0; i < size; i++) {
            tmparr[i] = arr[i][col];
        }
        get_count++;
        return tmparr;
    }
    int get_size() {
        return size;
    }
    void remove(int *array) {
        delete[] array;
        get_count--;
    }
    ~Matrix() {
        if (get_count != 0) {
            std::cout << "[ERROR] something not recylced!\n";
        }
    }
};

int calculate(Matrix A, Matrix B);

int calculate(Matrix A, Matrix B)
{
    int n=A.get_size();
    int ans = 0;
    int *a, *b;
    for(int i=0;i<n;i++){
        a = A.get_row(i);
        for(int j=0;j<n;j++){
            b = B.get_column(j);
            for(int k=0;k<n;k++){
                ans = ans + a[k]*b[k];
            }
            B.remove(b);
        }
        A.remove(a);
    }
    return ans;
}
int **create_matrix(int n) {
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
    return arr;
}

void read_matrix(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0 ;j < n; j++) {
            cin >> arr[i][j];
        }
    }
}

int main() {
    int n;
    cin >> n;
    int **A = create_matrix(n);
    read_matrix(A, n);
    Matrix MA(n, A);
    int **B = create_matrix(n);
    read_matrix(B, n);
    Matrix MB(n, B);
    cout << calculate(MA, MB) << '\n';
}
