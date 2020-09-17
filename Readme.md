## Catenary Functions

### Description

To investigate a Maclaurin series approximation to the Catenary function, imagine that an architecture company wishes to code a real-time simulation walk-through that includes a Catenary Arch (as shown below). To do this they are prepared to implement the Catenary function by a fast but approximate Maclaurin series instead of slower but more accurate math library functions. This program investigates the accuracy of the series approximation to this function.

### Use

Compiles in Microsoft Visual Studio 2015. Also comes with precompiled executable instead.

### Algorithm

While the user wishes to continue, the integer value of the highest power of x in the series is selected (you should reject invalid integers). Then the user selects a range of x, somewhere between 
-10.0 and +10.0 over which the series is evaluated from 0 in ten equal increments (reject values
outside this range). Then the user chooses the value of the scale factor a.
For each value of x the Maclaurin series approximation to the Catenary function is output together with the exact value calculated from the math library using the exp() function. 