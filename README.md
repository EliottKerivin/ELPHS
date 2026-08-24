# ELPHS
## About
This project is my first large(-ish) project, entirely left to my own devices. It is also the first time I really code in C, and is solely educational. It has no aspirations to be useful to anyone, and certainly makes no guarantees about anything at all. It is a pure hobby project, as the best way to learn is by doing.

The name is courtesy of my little sister.

## Requirements
The code here is written with C23 in mind. Normally, it should mostly be standard compliant, though some reasonable (and documented) assumptions are made, for example that IEEE 754 floating point arithmetic is also supported. It might work on platforms other than Linux, but this isn't tested (not that it's guaranteed to work on Linux, though it is developed on Fedora). Also, [CMake](https://cmake.org) is required for building, and [Doxygen](https://doxygen.nl) is used for the documentation. However, this last one is not required.

## Documentation
Here's the link to the [documentation](https://EliottKerivin.github.io/ELPHS).

## Inspiration
In an attempt to do things right, I have taken some inspiration from [SCIP](https://scipopt.org) and [GSL](https://gnu.org/software/gsl). By this, I mean the broad strokes, like how to handle errors, bound checking in accessors, how to format documentation, and other such general things.
