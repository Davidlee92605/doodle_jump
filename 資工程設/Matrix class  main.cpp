#include <iostream>
#include <stdio.h>
#include "function.h"

using namespace std;

class Matrix
{

public:
    Matrix();
    Matrix (const int , const int [50][50]);
    Matrix add(const Matrix) const;//add function
    Matrix subtract(const Matrix) const;//subtract function
    Matrix multiplication(const Matrix) const;//multiply function
    Matrix inc() const;//increased by 1
    void Transpose() const;//Transpose function
    void output() const;//Note that each output should be followed by a new
                        //line character.
private:
    int matrix[50][50];
    int matrix_size;
};
Matrix::Matrix()
{
    matrix_size = 0;
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            matrix[i][j]=0;
        }
    }
}
Matrix::Matrix(const int a, const int b[50][50])
{
    matrix_size = a;
    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            matrix[i][j] = b[i][j];
        }
    }
}
Matrix Matrix::add(const Matrix b) const
{
    Matrix a;
    a.matrix_size = b.matrix_size;
    for(int i=0;i<this->matrix_size;i++){
        for(int j=0;j<this->matrix_size;j++){
            a.matrix[i][j] = this->matrix[i][j]+b.matrix[i][j];
        }
    }
    return a;
}
Matrix Matrix::subtract(const Matrix b) const
{
    Matrix a;
    a.matrix_size = b.matrix_size;
    for(int i=0;i<this->matrix_size;i++){
        for(int j=0;j<this->matrix_size;j++){
            a.matrix[i][j] = this->matrix[i][j]-b.matrix[i][j];
        }
    }
    return a;
}
Matrix Matrix::multiplication(const Matrix b) const
{
    Matrix a;
    a.matrix_size = b.matrix_size;
    for(int i=0;i<this->matrix_size;i++){
        for(int j=0;j<this->matrix_size;j++){
            a.matrix[i][j]=0;
            for(int k=0;k<this->matrix_size;k++){
                a.matrix[i][j] = a.matrix[i][j]+this->matrix[i][k]*b.matrix[k][j];
            }
        }
    }
    return a;
}
Matrix Matrix::inc() const
{
    Matrix a;
    a.matrix_size = this->matrix_size;
    for(int i=0;i<this->matrix_size;i++){
        for(int j=0;j<this->matrix_size;j++){
            a.matrix[i][j] = this->matrix[i][j]+1;
            a.matrix[i][j] = a.matrix[i][j]%10;
        }
    }
    return a;
}
void Matrix::Transpose() const
{
    for(int i=0;i<this->matrix_size;i++){
        for(int j=0;j<this->matrix_size-1;j++){
            cout<<this->matrix[j][i]<<" ";
        }
        cout<<this->matrix[this->matrix_size-1][i];
        cout << endl;
    }
}
void Matrix::output() const
{
    for(int i=0;i<this->matrix_size;i++){
        for(int j=0;j<this->matrix_size-1;j++){
            cout << this->matrix[i][j]<<" ";
        }
        cout<<this->matrix[i][this->matrix_size-1];
        cout << endl;
    }
}
int main(){
    int N;
    int matrix1[50][50], matrix2[50][50];
    Matrix ans;

    cin >> N;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            cin >> matrix1[i][j];
        }
    }

    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            cin >> matrix2[i][j];
        }
    }

    Matrix a(N, matrix1), b(N, matrix2);

    ans = a.add( b );
    ans.output();
    cout << endl;

    ans = a.subtract( b );
    ans.output();
    cout << endl;

    ans = a.multiplication( b );
    ans.output();
    cout << endl;

    a.inc().output();
    cout << endl;
    b.inc().output();
    cout << endl;
    a.Transpose();
    cout << endl;
    b.Transpose();
} // end main
