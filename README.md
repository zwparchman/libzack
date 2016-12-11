This library contains simple functionality that I finally got sick of copy-pasting.

The functionality includes

Timer - An easy to use timing class  

Channel - A go inspired channel class for inter-thread communication  

Defer - Runs a supplied function (lambdas included) on destructoin. It can be deactivated so the function isn't called.

utility - a few math functions that work all standard (real, complex numbers are untested) numeric types including linear interpolation (lerp), normalizing a value to a range, mapping a value from one range to another (remap), and clamping a value to a range.  
The utility functions use c assertions to enforce their preconditions.


#Building
Just type "make libzacklib.so". Systems that can not use make are not supported. A c++14 compiler is required. 

#Testing
Testing currently does not work out of the box due to the way the google testing library is installed.
To enable testing point the compiler to the libgtest.a file on your system.

Feel free to request a way to make the test build more portable, but if there is no demand I won't improve it.
