//! # lasi::sparse
//! Tridiagonal matrices are implemented here, as well as their operations
//! and specialized algorithms.
use crate::{Index, MatrixErrors, Position};

/// Contains a tridiagonal matrix

/// Contains a matrix who's only non zero terms are of the form $A_{ii}$,
/// $A_{i, i+1}$ or $A_{i+1, i}$.
pub struct Tri<T> {
    rows: Index,
    columns: Index,
    upper: Vec<T>,
    mid: Vec<T>,
    lower: Vec<T>,
}
