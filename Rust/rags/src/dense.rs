//! # rags::dense
//! This module defines the dense matrix type and associated methods.

use crate::MatrixErrors;

use num_traits::{One, Zero};

use std::iter::{Iterator, zip};
use std::ops::Add;

/// Indexing type
type Index = usize;

/// A dense matrix
///
/// It contains its dimensions as well as a heap allocated contiguous array of
/// elements, stored in row major orderc (C style)
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Matrix<T> {
    rows: Index,
    columns: Index,
    elements: Vec<T>,
}

impl<T> Matrix<T> {
    /// Creates a new matrix with a function
    ///
    /// Creates a new matrix by passing the row and column index to the function,
    /// and assigning the result to the corresponding element
    pub fn from_fn<F>(rows: Index, columns: Index, mut f: F) -> Result<Self, MatrixErrors>
    where
        F: FnMut(Index, Index) -> T,
    {
        match Index::checked_mul(rows, columns) {
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
    pub fn rows(&self) -> Index {
        self.rows
    }
    /// Returns the number of columns
    pub fn columns(&self) -> Index {
        self.columns
    }

    /// Return an iterator over the elements of the matrix, in row major order
    pub fn iter(&'_ self) -> Iter<'_, T> {
        Iter::new(self)
    }

    /// Return a mutable iterator over the elements of the matrix, in row major order
    pub fn iter_mut(&'_ mut self) -> IterMut<'_, T> {
        IterMut::new(self)
    }
}

impl<T: Zero> Matrix<T> {
    /// Creates a matrix filled with zeros
    pub fn zeros(rows: Index, columns: Index) -> Result<Self, MatrixErrors> {
        Self::from_fn(rows, columns, |_i, _j| T::zero())
    }
}
impl<T: Zero + One> Matrix<T> {
    /// Creates the identity matrix
    pub fn identity(rows: Index, columns: Index) -> Result<Self, MatrixErrors> {
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

impl<T: Add<Output = T> + Zero> Add<Self> for Matrix<T> {
    type Output = Self;
    fn add(mut self, other: Matrix<T>) -> Self::Output {
        if self.rows() != other.columns() || self.columns() != other.columns() {
            panic!(
                "Both operands must have the same dimensions, found {} x {} and {} x {}",
                self.rows(),
                self.columns(),
                other.rows(),
                other.columns()
            );
        }
        for (a, b) in zip(self.elements.iter_mut(), other.elements) {
            *a = std::mem::replace(a, T::zero()) + b;
        }
        self
    }
}

/// Iterator over the elements of a Matrix
///
/// Iterates over the elements of a Matrix in row major order, which is to say
/// the entire first row, then the second, etc., consuming said matrix
pub struct IntoIter<T> {
    iter: std::vec::IntoIter<T>,
}

impl<T> IntoIter<T> {
    pub fn new(m: Matrix<T>) -> Self {
        IntoIter {
            iter: m.elements.into_iter(),
        }
    }
}

impl<T> Iterator for IntoIter<T> {
    type Item = T;
    fn next(&mut self) -> Option<Self::Item> {
        self.iter.next()
    }
}

impl<T> IntoIterator for Matrix<T> {
    type Item = T;
    type IntoIter = IntoIter<T>;
    fn into_iter(self) -> Self::IntoIter {
        IntoIter::new(self)
    }
}

pub struct Iter<'a, T> {
    iter: std::slice::Iter<'a, T>,
}

impl<'a, T> Iter<'a, T> {
    pub fn new(m: &'a Matrix<T>) -> Self {
        Self {
            iter: m.elements.iter(),
        }
    }
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;
    fn next(&mut self) -> Option<Self::Item> {
        self.iter.next()
    }
}

pub struct IterMut<'a, T> {
    iter: std::slice::IterMut<'a, T>,
}

impl<'a, T> IterMut<'a, T> {
    pub fn new(m: &'a mut Matrix<T>) -> Self {
        Self {
            iter: m.elements.iter_mut(),
        }
    }
}

impl<'a, T> Iterator for IterMut<'a, T> {
    type Item = &'a mut T;
    fn next(&mut self) -> Option<Self::Item> {
        self.iter.next()
    }
}

#[cfg(test)]
mod test {
    use super::*;
    use crate::MatrixErrors::*;

    #[test]
    fn initialization() {
        // Check that the right erros get returned
        let m = Matrix::<i32>::zeros(Index::MAX, 2);
        assert_eq!(m, Err(DimensionOverflow));
        let m = Matrix::<i32>::identity(Index::MAX, Index::MAX);
        assert_eq!(m, Err(DimensionOverflow));
        let m = Matrix::<i32>::identity(6, 3);
        assert_eq!(m, Err(InvalidArguments));
        let m = Matrix::<i32>::from_fn(2, Index::MAX, |_i, _j| 0);
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

        let m = Matrix::<Index>::from_fn(3, 4, |i, j| i * j);
        assert_eq!(
            m,
            Ok(Matrix::<Index> {
                rows: 3,
                columns: 4,
                elements: vec![0, 0, 0, 0, 0, 1, 2, 3, 0, 2, 4, 6]
            })
        );
    }

    #[test]
    fn iterators() {
        // into iter
        let mut m = Matrix::<Index>::from_fn(3, 5, |i, j| i + j)
            .unwrap()
            .into_iter();
        for i in 0..3 {
            for j in 0..5 {
                assert_eq!(Some(i + j), m.next());
            }
        }
        assert_eq!(None, m.next());

        // iter
        let m = Matrix::<Index>::from_fn(3, 5, |i, j| i + j).unwrap();
        let mut mi = m.iter();
        for i in 0..3 {
            for j in 0..5 {
                assert_eq!(Some(&(i + j)), mi.next());
            }
        }
        assert_eq!(None, mi.next());

        // iter_mut
        let mut m = Matrix::<Index>::from_fn(3, 5, |i, j| i + j).unwrap();
        let mut mi = m.iter_mut();
        for i in 0..3 {
            for j in 0..5 {
                assert_eq!(Some(&mut (i + j)), mi.next());
            }
        }
        assert_eq!(None, mi.next());

        // check that iter mut actually modifies the elements correctly
        for (i, el) in m.iter_mut().enumerate() {
            *el = i;
        }
        let mut k: Index = 0;
        assert_eq!(
            m,
            Matrix::<Index>::from_fn(3, 5, |_i, _j| {
                let tmp = k;
                k += 1;
                tmp
            })
            .unwrap()
        )
    }
}
