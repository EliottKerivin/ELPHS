pub mod dense;

/// Defines the various error codes that can be returned by functions
#[derive(Debug, PartialEq, Eq)]
pub enum MatrixErrors {
    /// The size of the allocation needed to create this matrix exceeds what
    /// can be represented with the used size type
    DimensionOverflow,
    /// Some the arguments are invalid, e.g. nonsensical dimensions
    InvalidArguments,
}
