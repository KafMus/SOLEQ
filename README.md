# SOLEQ - Systems Of Linear EQuations
This "library" tries to solve SOLEQs.

The main test for DiagThree is 6th one, you can solve your own SOLEQ
with tridiagonal matrix using it.

## TODO

I don't like how we include files:
```
#include <diagthree.hpp>
#include <matrix.hpp>
```
I think it will be much better if we do this:
```
#include <SOLEQ/diagthree.hpp>
#include <SOLEQ/matrix.hpp>
```
