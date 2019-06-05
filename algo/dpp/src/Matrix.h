#ifndef MATRIX_H
#define MATRIX_H
/**
 *  Desc: the implementation of two dim matrix
 */
#include <new>

#define SWAP(a,b,T) { T c = a; a = b; b = c;}

template<typename T>
class Array
{
public:
    Array() {
        value_ = NULL;
        size_ = 0;
    }
    
    Array(int size) {
        size_ = 0;
        value_ = NULL;
        SetSize(size);
    }
    ~Array() {
        size_ = 0;
        if (value_) {
            delete [] value_;
            value_ = NULL;
        }
    }

    void SetSize(int n) {
        if (n == size_) {
            return;
        }

        if (value_) {
            delete [] value_;
            value_ = NULL;
        }
        size_ = n;
        //value_ = new(std::nothrow) T[n];
        value_ = new T[n];
    }

    int Size() { return size_;}

    T* Data() { return value_;}

    T& operator() (int i) {
        T* v = value_ + i;
        return (*v);
    }

    T dot(Array<T> &o) const {
        T ret = (T)0;
        if (size_ != o.Size()) {
            return ret;
        }
        
        for (int i=0; i<o.Size(); ++i) {
            ret += value_[i] * o(i);
        }
        return ret;
    }

private:
    T* value_;
    int size_;
};

template<typename T>
class Matrix
{
public:
    Matrix() {  
        row_ = 0;
        col_ = 0;
        value_ = NULL;
    }                
    Matrix(int row, int col) {
        row_ = 0;
        col_ = 0;
        value_ = NULL;
        SetSize(row, col);
    }

    Matrix(int row, int col, T v) {
        row_ = 0;
        col_ = 0;
        value_ = NULL;
        SetSize(row, col);
        for (int i=0; i<row; ++i) {
            for (int j=0; j<col; ++j) {
                T* p = value_ + (i * col_ + j);
                *p = v;
            }
        }
    }

    ~Matrix() {
        if (value_ != NULL) {
            delete [] value_;
        }
    }

    int GetRow() { return row_;}
    
    int GetCol() { return col_;}
    T* GetData() { return value_;}
    void Swap(Matrix<T> &mat) {
        SWAP(row_, mat.row_,int);
        SWAP(col_, mat.col_,int);
        SWAP(value_, mat.value_,T*);
    }
    void SetSize(int row, int col) {
        if (row_ == row && col_ == col) {
            return;
        }
        if (value_ != NULL) {
            delete [] value_;
        }

        row_ = row;
        col_ = col;
        value_ = new(std::nothrow) T[(row_ * col_)];
    }
        
    T& operator() (int i, int j) {
        T* v = value_ + (i * col_ + j);
        return (*v);
    }

    T* operator() (int i) {
        T* v = value_ + (i * col_);
        return v;
    }
    
private:
    int row_;
    int col_;
    T *value_;
};

#endif
