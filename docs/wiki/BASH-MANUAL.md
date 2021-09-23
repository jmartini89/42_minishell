# DEFINITIONS
### TOKEN
```
WORD
    sequence of characters treated as a unit
    may not include unquoted metacharacters
OPERATOR
    unquoted metacharacter
```
test
### METACHARACTERS
```
space, tab, newline
| & ; ( ) < >
```

### ESCAPE CHARACTER
```
non-quoted backslash \
preserves literal value of next character that follows
```

### BUILTIN
```
command implemented in shell
```

### QUOTES
```
SINGLE
    preserves the literal value of each character within the quotes
DOUBLE
    preserves the literal value of all characters within the quotes
    exception: $ ‘ \ !
```

# OPERATIONS

1. Reads input.

2. Breaks the input into words and operators, obeying the quoting rules.
These tokens are separated by metacharacters.
Alias expansion is performed by this step.

3. Parses the tokens into simple and compound commands.

4. Performs the various shell expansions,
breaking the expanded tokens into lists of filenames and commands and arguments.

5. Performs any necessary redirections
and removes the redirection operators and their operands from the argument list.

6. Executes the command.

7. Optionally waits for the command to complete and collects its exit status.