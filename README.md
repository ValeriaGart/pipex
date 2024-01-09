# PIPEX

Exploring processes by writing a programm that executes bash commands 🌸

## About

### The mandatory programm must take 4 arguments:

```
• file1 and file2 are file names.
• cmd1 and cmd2 - shell commands with their parameters.
```

The programm executes those commands and redirects them to the outfile.

### Bonus programm 

Can execute as many commands inbtw files as you want it to.

Moreover heredoc is implemented! You should use it this way:

```
- Instead of input file write "here_doc" 
- Next argument would be a delimiter for heredoc 
```

## How to run 

`make` compile without bonus 

`make bonus` compile with bonus part

`make clean` remove *.o files

`make fclean` remove *.o + executables

The way to run mandatory part is `./pipex file1 cmd1 cmd2 file2`

In bonus case you run it this way `./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`
