This project has been created as part of the 42 curriculum by thfernan.

## Description

**pipex** is a system programming project from the 42 curriculum that recreates the behavior of shell pipes. The program mimics the following shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

The project is divided into two parts:

- **pipex (mandatory)**: handles two commands with input/output redirection
- **pipex_bonus**: supports multiple pipes and here_doc functionality

This project focuses on:

- Process creation and management (fork, execve)
- Inter-process communication (pipes)
- File descriptor manipulation (dup2)
- Memory management in C

## Instructions

### Compilation

To compile the mandatory part:
```bash
make
```

This will generate the executable:
```bash
./pipex
```

To compile the bonus:
```bash
make bonus
```

This will generate:
```bash
./pipex_bonus
```

To clean object files:
```bash
make clean
```

To remove all binaries and objects:
```bash
make fclean
```

To recompile everything:
```bash
make re
```

## Usage

### Mandatory
```bash
./pipex file1 cmd1 cmd2 file2
```

This behaves like:
```bash
< file1 cmd1 | cmd2 > file2
```

**Example:**
```bash
./pipex infile "ls -l" "wc -l" outfile
```

Equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

### Bonus

**Multiple pipes:**
```bash
./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Equivalent to:
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2
```

**Here_doc:**
```bash
./pipex_bonus here_doc LIMITER cmd1 cmd2 file
```

Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> file
```

**Example:**
```bash
./pipex_bonus here_doc EOF "cat -e" "wc -l" outfile
heredoc> Hello
heredoc> World
heredoc> EOF
```

## Testing

### Memory leaks

Check for memory leaks with valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
--trace-children=yes --track-fds=yes \
--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
./pipex infile "cat -e" "wc -l" outfile
```

### Error handling

Test with:
- Non-existent files
- Invalid commands
- Permission errors
- Empty arguments
```bash
./pipex nonexistent "ls" "wc" outfile
./pipex infile "invalid_cmd" "wc" outfile
```

## Resources

Algorithm and project references:

- 42 Subject PDF — *pipex*
- https://www.rozmichelle.com/pipes-forks-dups/
- https://www.youtube.com/watch?v=6xbLgZpOBi8

## AI usage

AI tools were used during the development of this project to:

- Assist with debugging memory leaks and valgrind errors
- Validate Makefile structure
- Organization of this README

All algorithmic decisions, implementations, and final code were written and validated by the author.

## Notes

- The project follows the Norm of 42
- Error handling is implemented for invalid files, commands, and arguments
- All file descriptors are properly closed
- Memory is properly freed (no leaks)
- Exit codes follow shell conventions (127 for command not found, 1 for other errors)