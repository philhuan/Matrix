#include <iostream>
#include "Matrix.h"

using  namespace std;

int main() {

    Matrix<int> matrix(5,5);
    cout<<matrix<<endl;

    double data[][3]={
            {1,2,3},
            {4,5,6},
            {7,8,9}
    };
    Matrix<double> matrix1((double*)data,3,3);
    cout<<matrix1<<endl;

    cout<<matrix.set(2,4,8)<<endl;
    cout<<matrix<<endl;

    cout<<matrix.get(2,4)<<endl;

    cout<<matrix.set(2,5,8)<<endl;

    matrix.setAll(6);

    cout<<matrix<<endl;


    int A[][3]={
            {1,2,3},
            {4,5,6}
    };
    int B[][2]={
            {1,4},
            {2,5},
            {3,6}
    };

    Matrix<int> ma((int*)A,2,3);
    Matrix<int> mb((int*)B,3,2);

    cout<<(ma*mb)<<endl;

    int X[][3]={
            {1,1,1},
            {2,2,2}
    };
    int Y[][3]={
            {2,2,2},
            {1,1,1}
    };

    Matrix<int> mx((int*)X,2,3);
    Matrix<int> my((int*)Y,2,3);

    cout<<(mx+my)<<endl;

    cout<<(mx-my)<<endl;

    cout<<(mx+=my)<<endl;

    cout<<(mx-=my)<<endl;

    return 0;
}