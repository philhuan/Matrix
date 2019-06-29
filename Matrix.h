//
// Created by hjw on 19-3-25.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iosfwd>
#include <ostream>
#include <cstring>

template <class T>
class Matrix {
public:

    /**
     * 构造函数
     * @param row 矩阵行数
     * @param column 矩阵列数
     */
    Matrix(int row, int column);

     /**
      * 构造函数
      * @param array 初始化的二维数组(强制转换为一维)
      * @param row 矩阵行数
      * @param column 矩阵列数
      */
    Matrix(T* array,int row,int column);

    /**
     * 复制构造函数
     * @param matrix 要复制的矩阵
     */
    Matrix(const Matrix& matrix);

    /**
     * 获得指定位置的值
     * @param i 行数
     * @param j 列数
     * @return 值
     */
    T get(int i,int j) const;

    /**
     * 设置指定位置的值
     * @param i 行数
     * @param j 列数
     * @param value 值
     * @return 是否成功
     */
    bool set(int i,int j,int value);

    /**
     * 设置矩阵所有元素为指定值
     * @param value 指定的值
     */
    void setAll(int value);

    /**
     * 矩阵加法运算符重载
     * @param matrix 需要进行+操作的矩阵
     * @return 新矩阵
     */
    Matrix operator+(const Matrix<T> &matrix)const;

    /**
     * 矩阵减法运算符重载
     * @param matrix 需要进行-操作的矩阵
     * @return 新矩阵
     */
    Matrix operator-(const Matrix<T> &matrix)const;

    /**
     * 矩阵乘法运算符重载
     * @param matrix 需要进行*操作的矩阵
     * @return 新矩阵
     */
    Matrix operator*(const Matrix<T> &matrix)const;

    /**
     * 矩阵+=运算符重载
     * @param matrix 需要进行+=操作的矩阵
     * @return 返回自身
     */
    Matrix<T>& operator+=(const Matrix<T> &matrix);

    /**
     * 矩阵-=运算符重载
     * @param matrix 需要进行-=操作的矩阵
     * @return 返回自身
     */
    Matrix<T>& operator-=(const Matrix<T> &matrix);


    /**
     * 重载<<的cout输出函数
     * @tparam T1 数据类型
     * @param os 输出目标ostream
     * @param matrix 要输出的Matrix<T1>对象
     * @return 返回目标ostream的引用
     */
    template <class T1>
    friend std::ostream& operator<<(std::ostream& os,const Matrix<T1>& matrix) ;

    /**
     * 析构函数
     */
    ~Matrix();

private:
    T** value;
    int row;
    int column;

    /**
     * 设置行列信息并开辟空间
     * @param row
     * @param column
     */
    void init(int row,int column);


};

template<class T>
Matrix<T>::Matrix(int row, int column) {
    init(row,column);
}

template<class T>
Matrix<T>::Matrix(const Matrix &matrix) {
    init(matrix.row,matrix.column);

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            value[i][j]=matrix.value[i][j];
        }
    }
}

template<class T>
void Matrix<T>::init(int row, int column) {
    this->row=row;
    this->column=column;

    value=new T*[row];
    for(int i=0;i<row;i++){
        value[i]=new T[column]();
    }
}

template<class T>
Matrix<T>::~Matrix() {
    for(int i=0;i<row;i++){
        delete[] value[i];
    }

    delete[] value;
}


template<class T>
bool Matrix<T>::set(int i, int j, int value) {
    if(i<0||i>=row||j<0||j>=column){
        std::cerr<<"ArrayIndexOutOfBounds"<< " row:"<<row<<" column"<<column
                 <<" i:"<< i<<" j:"<<j<<std::endl;
        return false;
    }

    this->value[i][j]=value;

    return true;
}

template<class T1>
std::ostream & operator<<(std::ostream &os, const Matrix<T1> &matrix) {
    for(int i=0;i<matrix.row;i++){
        for(int j=0;j<matrix.column;j++){
            os<<matrix.value[i][j]<<" ";
        }
        os<<std::endl;
    }

    return os;
}


template<class T>
Matrix<T>::Matrix(T* array, int row, int column) {
    init(row,column);

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            value[i][j]=array[i*column+j];
        }
    }
}

template<class T>
void Matrix<T>::setAll(int value) {

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            this->value[i][j]=value;
        }
    }
}

template<class T>
T Matrix<T>::get(int i, int j) const {
    return value[i][j];
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
    if(row!=matrix.row||column!=matrix.column){
        std::cerr<<"不同大小矩阵相加"<<std::endl;
        return Matrix(1,1);
    }
    Matrix<T> newMatrix(row,column);

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            newMatrix.value[i][j]=value[i][j]+matrix.value[i][j];
        }
    }
    return newMatrix;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const {
    if(row!=matrix.row||column!=matrix.column){
        std::cerr<<"不同大小矩阵相减"<<std::endl;
        return Matrix(0,0);
    }
    Matrix<T> newMatrix(row,column);

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            newMatrix.value[i][j]=value[i][j]-matrix.value[i][j];
        }
    }
    return newMatrix;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
    if(column!=matrix.row){
        std::cerr<<"不匹配的矩阵乘法"<<std::endl;
        return Matrix(0,0);
    }
    Matrix<T> newMatrix(row,matrix.column);

    for(int i=0;i<newMatrix.row;i++){
        for(int j=0;j<newMatrix.column;j++){
            for(int k=0;k<column;k++){
                newMatrix.value[i][j]+=value[i][k]*matrix.value[k][j];
            }
        }
    }

    return newMatrix;
}

template<class T>
Matrix<T> & Matrix<T>::operator+=(const Matrix<T> &matrix) {
    if(row!=matrix.row||column!=matrix.column){
        std::cerr<<"不同大小矩阵相加"<<std::endl;
        return *this;
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            value[i][j]+=matrix.value[i][j];
        }
    }

    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &matrix) {
    if(row!=matrix.row||column!=matrix.column){
        std::cerr<<"不同大小矩阵相减"<<std::endl;
        return *this;
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            value[i][j]-=matrix.value[i][j];
        }
    }
    return *this;
}



#endif //MATRIX_MATRIX_H
