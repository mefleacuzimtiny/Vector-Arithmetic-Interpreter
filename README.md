# MeFlea's Vector Arithmetic Interpreter
This is my custom interpreter for simple vector maths. The way it works is by taking a single-line input as follows:

```
[12 54] + (19 42) - ( {15 soe 126} + [19 23] )
```
... where vectors are of three types: rectangular, polar, and cardinal. Their respective syntax is as follows:
- inside square brackets, i.e `[12 54]` represents rectangular vectors where horizontal component is 12, and vertical component is 54
- inside round brackets, i.e `(19 42)` represents polar vectors, where `19` is the magnitude, and `42` is the angle in degrees
- inside curly brackets, i.e `{15 soe 126}` respresents cardinal vectors, which are like polar vectors, but a relative cardinal direction and bearing is provided. In the example given, `15` is the magnitude, `soe` represents "South of East", and `126` represents the angle relative to South of East. Together, this becomes "15 magnitude, 126 degrees South of East"

The interpreter does respect the mathematical order of operations as well as the parentheses. The interpreter works by generating a binary tree of only rectangular vectors. It does so by converting each term in the expression to its rectangular vector form, the mathematics of which are defined inside `vects.h`. Then, it traversers the binary tree and gets the answer in rectangular vector form, which is printed to the user in all three forms.

For debugging purposes, the interpreter also prints the traversal of the tree in in-fix, post-fix, and pre-fix notation, as well as the rectangular vector conversions.

# Build Instructions:
- The program does not have any dependencies outside the C++ Standard Library. Nothing needs to be linked together, simply compiling `main.cpp` with the other headers should compile the program.