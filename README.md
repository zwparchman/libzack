This library contains simple functionality that I finally got sick of copy-pasting.

The functionality includes

Timer - An easy to use timing class  

Channel - A go inspired channel class for inter-thread communication  

Defer - Runs a supplied function (lambdas included) on destruction. It can be deactivated so the function isn't called.

utility - a few math functions that work on all standard (real, complex numbers are untested) numeric types including linear interpolation (lerp), normalizing a value to a range, mapping a value from one range to another (remap), and clamping a value to a range.  
The utility functions use c assertions to enforce their preconditions, so compile with NDEBUG to prevent this library from killing your program.


#Building
make is required
A c++14 is required

    make libzacklib.so

#Testing

    git submodule init
    git submodule update
    make
    ./program
