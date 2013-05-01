#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <QString>

//start
class Matrix {
public:
    Matrix(int rows, int cols);                 /* Allocates and zeros all cells. */
    Matrix(const Matrix& mat);                  /* Copy constructor - clones mat. */
    ~Matrix();
    double& operator()(int i, int j);
    double operator()(int i, int j) const;
    // Some useful Matrix operations
    Matrix& operator=(const Matrix& mat);       /* Deletes host content, clones mat. */
    Matrix operator+(const Matrix& mat) const;  /* Matrix addition. */
    Matrix operator*(const Matrix& mat) const;  /* Matrix multiplication. */
    bool operator==(const Matrix& mat) const;
    int getRows() const;
    int getCols() const;
    QString toString() const;
private:
    int m_Rows, m_Cols;
    double  **m_NumArray;
    //Some refactoring utility functions
    void sweepClean();                          /* Deletes all cells in the host. */
    void clone(const Matrix& mat);              /* Makes a copy of the host using new memory. */
    double rcprod(int row, const Matrix& mat, int col) const; 
                                                /* Computes dot product of the host's row with  mat's col. */
};
//end
#endif

