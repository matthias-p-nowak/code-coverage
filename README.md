# code-coverage
A simple combination of a CPP-makro and a c++ program that helps with "uncovered" code.

# Simple case

Let's say, I have written a program, and am going to write some tests, like for CUNIT. Usually, I will first write a test and then implement functionality that will make this test work. During that writing of code, I implement some **if/else** switches. There should be a test for each branch. 

Just as a template, I write *UNREACHED* as a makro in those branches. During the testing, the makros will write out the location and the program <u>reached</u> will collect those lines and remove the *UNREACHED* makros from the source files.

This is not a proper replacement for advanced code analysis tools, but will work with simple IDE's like <u>geany</u>.

## Files
  * *tt.h* contains the makro definition, I use for printouts.
  * *tt.c* is a file with a location I am going to test.
  * *reached.h* is the one header file I am using for precompiled headers.
  * *reached.cc* is a short C++ program that scans the result file and then rewrites the source files skipping all indicated locations.

## Example
*Run the investigated program:*  
`./tt 2>res`

*Run the <u>reached</u> program as*  
`./reached res`
