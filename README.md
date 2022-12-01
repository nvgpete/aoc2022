### These are solutions written in c for the Advent of Code - 2022. 
See https://adventofcode.com/2022

### Note: 
**This is a work in progress; examples below will be updated as puzzles for
the various days are completed.**


Each problem generally has two parts. Examples of filenames for day 5 are:
- d05a.c - solution for first part
- d05b.c - solution for second part
- d05.txt - problem data set; the same for both parts.

Very often the files of the sort d02b.c may not exist if the two parts of
the problem were similar enough to do both in d02a.c.

There may be a file like d03notes.txt if I felt more explanation was needed,
or just felt like making general comments. Sometimes it is just additional
compilation notes.

Sometimes the problem data set files (eg. d03.txt) do not exist because the
problem data was simple enough to be provided on the web page. Other times
it is there, but I have not attempted to read it. In either case the notes
file will give the input and my reasoning.

Sometimes there may also be a php version of the program for reasons
described in the notes.

Compilation is generally something like  
gcc/clang -O3 -Wall -o d01a d01a.c  
with exceptions listed in the notes.

These are not examples of good coding style nor necessarily of good code
as they are one-offs where getting them to work quickly and correctly was the
main objective. (Though I have cleaned them up a bit to remove debugging
printfs() and such.) (Also, unlike most people, I find code with a minimum of
extraneous spaces easier to read. YMMV) Most of them are short enough and
straightforward enough to not require any comments.

## Synopsis of each days problem

