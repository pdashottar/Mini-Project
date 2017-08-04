# Mini-Project

Implementation of Quine–McCluskey method in C and drawing of corresponding circuit diagram.

I have implemented Quine-McCluskey method to minimize Boolean expressions in C and drawn corresponding circuit diagrams in SVG file.

The main file which starts execution is mini_p.c, modular approach is taken care by linking rest other files with the main file.

Sample Input and Outputs are given below -

(a+b)*(a+c) -> a+b*c
(a+c)(a*d+a*~d)+a*c+c -> a+c
a*~b*d + a*~b*~d -> a*~b

For more information, a project report is also attached.
