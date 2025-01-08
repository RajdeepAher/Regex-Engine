# RegEx Engine in C++

This is a C++ engine written for regular expression matching. It supports various regular expression features and utilizes tokens, a lexer pass, a top-down recursive descent parser, and a backtracking mechanism.

## Features Supported

- **Match End (`$`)**: Matches the end of a string.
- **Wildcard (`.`)**: Matches any character except a newline.
- **Escaping (`\`)**: Escapes special characters.
- **Non-capturing Group (`(?:...)`)**: Groups without capturing.
- **Match Start (`^`)**: Matches the beginning of a string.
- **Range Element (`[^a-zA-Z059]`)**: Matches any character not in the specified range.
- **Quantifiers (`?`, `*`, `+`)**: Specifies match count (0-1, 0+, 1+).
- **Grouping (`(...)`)**: Groups expressions.
- **Alternative (`|`)**: Matches one of multiple alternatives.
- **Named Group (`(?<name>...)`)**: Names a capturing group.
- **Whitespace (`\s`)**: Matches whitespace.
- **Curly Brace Quantification (`{min,max}`)**: Matches a specific or range of occurrences.

## Architecture

- **Lexer**: The lexer tokenizes the regular expression input.
- **Top-down Recursive Descent Parser**: Parses the tokenized input following a top-down approach.
- **Backtracking Mechanism**: Handles the backtracking process to match expressions efficiently.

## Running the Project

To run all the tests after cloning the project, execute the following command in the terminal:

```bash
make all
make clean
```
or to run an individual test for say, lexer :

``` bash
make lexer
./lexer
make clean
```