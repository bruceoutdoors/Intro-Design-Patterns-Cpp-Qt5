#include "matrix.h"
#include <assert.h>


// Allocates memory for a rows x cols array of double and 
// initializes each cell to zero.
//start id=ctor
Matrix:: Matrix(int rows, int cols):m_Rows(rows), m_Cols(cols) {
    m_NumArray = new double*[rows];
    for (int r = 0; r < rows; ++r) {
        m_NumArray[r]  = new double[cols];
        for(int c = 0; c < cols; ++c)
           m_NumArray[r][c]  = 0;
    }
}
//end
// Refactoring utility function
//start id=dtor
void Matrix::sweepClean() {
   for (int r = 0; r < m_Rows; ++r)
      delete[] m_NumArray[r] ;
   delete[] m_NumArray;
}

Matrix::~Matrix() {
   sweepClean();
}
//end

// Refactoring utility function
//start id=clone
void Matrix::clone(const Matrix& mat) {
   m_NumArray = new double*[mat.m_Rows];
   for (int r = 0; r < mat.m_Rows; ++r) {
       m_NumArray[r] = new double[mat.m_Cols];
       for(int c = 0; c < mat.m_Cols; ++c)
            m_NumArray[r][c] = mat(r,c);
   }
}   
//end
//start id=sub
double Matrix::operator()(int r, int c) const {
   assert (r >= 0 && r < m_Rows && c >= 0 && c < m_Cols);
   return m_NumArray[r][c];   
}

double& Matrix::operator()(int r, int c) {
   assert (r >= 0 && r < m_Rows && c >= 0 && c < m_Cols);
   return m_NumArray[r][c];
}
//end

bool Matrix::operator==(const Matrix& mat) const {
   if(m_Rows != mat.m_Rows || m_Cols != mat.m_Cols)
      return false;
   for (int r = 0; r < m_Rows; ++r)
      for(int c = 0; c < m_Cols; ++c)
         if(m_NumArray[r][c] != mat(r,c))
            return false;
   return true;
}

