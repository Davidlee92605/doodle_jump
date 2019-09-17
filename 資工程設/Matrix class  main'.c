#include <iostream>
#include <stdio.h>
//#include "function.h"
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
Matrix Matrix::add(const Matrix) const
{
    Matrix a;
    for(int i=0;i<matrix_size;i++){
        for(int j=0;j<matrix_size;j++){
            a.matrix[i][j] = matrix[i][j]+Matrix.matrix[i][j];
        }
    }
    return a;
}
/*Matrix Matrix::subtract(const Matrix) const
{

}
Matrix Matrix::multiplication(const Matrix) const
{

}
Matrix Matrix::inc() const
{

}
void Matrix::Transpose() const
{

}*/
void Matrix::output() const
{
    for(int i=0;i<matrix_size;i++){
        for(int j=0;j<matrix_size;j++){
            cout << matrix[i][j];
        }
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
 /*
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
    */
} // end main
