//! # rags::dense
//! This module defines the dense matrix type and associated methods.

use crate::MatrixErrors;

use num_traits::{One, Zero};

/// A dense matrix
///
/// It contains its dimensions as well as a heap allocated contiguous array of
/// elements, stored in row major orderc (C style)
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Matrix<T> {
    rows: usize,
    columns: usize,
    elements: Vec<T>,
}

impl<T> Matrix<T> {
    /// Creates a new matrix with a function
    ///
    /// Creates a new matrix by passing the row and column index to the function,
    /// and assigning the result to the corresponding element
    pub fn from_fn<F>(rows: usize, columns: usize, mut f: F) -> Result<Self, MatrixErrors>
    where
        F: FnMut(usize, usize) -> T,
    {
        match usize::checked_mul(rows, columns) {
            None => Result::Err(MatrixErrors::DimensionOverflow),
            Some(dim) => {
                let mut elements = Vec::with_capacity(dim);
                for i in 0..rows {
                    for j in 0..columns {
                        elements.push(f(i, j));
                    }
                }
                Result::Ok(Matrix {
                    rows,
                    columns,
                    elements,
                })
            }
        }
    }

    /// Returns the number of rows
    pub fn rows(&self) -> usize {
        self.rows
    }
    /// Returns the number of columns
    pub fn columns(&self) -> usize {
        self.columns
    }
}

impl<T: Zero> Matrix<T> {
    /// Creates a matrix filled with zeros
    pub fn zeros(rows: usize, columns: usize) -> Result<Self, MatrixErrors> {
        Self::from_fn(rows, columns, |_i, _j| T::zero())
    }
}
impl<T: Zero + One> Matrix<T> {
    /// Creates the identity matrix
    pub fn identity(rows: usize, columns: usize) -> Result<Self, MatrixErrors> {
        if rows != columns {
            return Err(MatrixErrors::InvalidArguments);
        };
        Self::from_fn(
            rows,
            columns,
            |i, j| if i == j { T::one() } else { T::zero() },
        )
    }
}

#[cfg(test)]
mod test {
    use super::*;
    use crate::MatrixErrors::*;

    #[test]
    fn initialization() {
        // Check that the right erros get returned
        let m = Matrix::<i32>::zeros(usize::MAX, 2);
        assert_eq!(m, Err(DimensionOverflow));
        let m = Matrix::<i32>::identity(usize::MAX, usize::MAX);
        assert_eq!(m, Err(DimensionOverflow));
        let m = Matrix::<i32>::identity(6, 3);
        assert_eq!(m, Err(InvalidArguments));
        let m = Matrix::<i32>::from_fn(2, usize::MAX, |_i, _j| 0);
        assert_eq!(m, Err(DimensionOverflow));

        // Check that the created matrices are actually what we think
        let m = Matrix::<i32>::zeros(1, 1);
        assert_eq!(
            m,
            Ok(Matrix::<i32> {
                rows: 1,
                columns: 1,
                elements: vec![0]
            })
        );
        let m = Matrix::<i32>::identity(1, 1);
        assert_eq!(
            m,
            Ok(Matrix::<i32> {
                rows: 1,
                columns: 1,
                elements: vec![1]
            })
        );

        let m = Matrix::<i32>::zeros(5, 7);
        assert_eq!(
            m,
            Ok(Matrix::<i32> {
                rows: 5,
                columns: 7,
                elements: vec![0; 5 * 7]
            })
        );

        let m = Matrix::<i32>::identity(5, 5);
        assert_eq!(
            m,
            Ok(Matrix::<i32> {
                rows: 5,
                columns: 5,
                elements: vec![
                    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
                ]
            })
        );

        let m = Matrix::<usize>::from_fn(3, 4, |i, j| i * j);
        assert_eq!(
            m,
            Ok(Matrix::<usize> {
                rows: 3,
                columns: 4,
                elements: vec![0, 0, 0, 0, 0, 1, 2, 3, 0, 2, 4, 6]
            })
        );
    }
}
