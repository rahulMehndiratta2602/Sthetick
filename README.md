# Sthetick-
A new compiler language with C-like features
Sthetick Lexer code by :
######################################################################################################
2017A7PS1479H  Rahul Mehndiratta
2018A7PS0228H  Kartikey Papnai

######################################################################################################

This is the code for lexer which identifies tokens from a given test case(C program) The input is taken in via a text file to the lexer which returns tokens in a datastream.
Sthetick Parser code made by:

To compile :
>gcc lexer.c
To run:
>a.exe

######################################################################################################
2017A7PS1479H  Rahul Mehndiratta
2018A7PS0228H  Kartikey Papnai

######################################################################################################

The parser is the LL(1) type parser which uses the first and follow sets for creating a parse table.
This parse table is used for tree construction.

The files are named accordingly.

The input is taken in via a text file to the lexer which returns tokens in a datastream to be fed to 
the parser.

As the input file name is hardcoded, 
for different input files change the filename in the code accordingly.

######################################################################################################
Use the following commands in the cmd for windows:

To compile:
>g++ Parser.cc

run:
>a.exe
