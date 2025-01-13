<div align="center">
  <img src="./Logo.png" alt="Lox Logo" />
</div>


# Lox Compiler (C Implementation)

This repository contains the implementation of the **Lox compiler** written in C, based on the second part of the book *[Crafting Interpreters](https://craftinginterpreters.com/)* by Robert Nystrom. The project demonstrates a bytecode compiler and virtual machine (VM) for the Lox programming language.

## About Lox

Lox is a dynamically typed, class-based programming language designed to be simple yet expressive. This project implements the language as a bytecode compiler, offering faster execution compared to an interpreter.

## Features

### Features Taught in the Book

The following features will be implemented as guided by *Crafting Interpreters*:

- **Bytecode Compilation**: Convert source code into a compact bytecode format.
- **Virtual Machine**: Execute bytecode instructions efficiently.
- **Expressions**:
  - Arithmetic: `+`, `-`, `*`, `/`
  - Logical: `and`, `or`
  - Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Control Flow**:
  - Conditionals: `if`/`else`
  - Loops: `while`, `for`
- **Functions**: First-class functions with closures.
- **Classes and Objects**: Class-based object-oriented programming with methods.
- **Garbage Collection**: Simple mark-and-sweep garbage collector for memory management.

### Features Implemented by Me

In addition to the features taught in the book, I have added:

- **To be added**

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC, Clang)
- Make (for build automation)

### Clone the Repository

```bash
git clone https://github.com/supersaint7780/clox
cd clox
```

### Build the Compiler

1. Compile the project:
   ```bash
   make
   ```

### Run the Compiler

1. To execute a Lox script:
   ```bash
   ./build/lox path/to/script.lox
   ```

2. To start the REPL (interactive mode):
   ```bash
   ./clox
   ```

### Examples

**Hello World**
```lox
print "Hello, world!";
```

**Factorial Function**
```lox
fun factorial(n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}
print factorial(5); // Output: 120
```

## Grammar

The grammar of the Lox language is defined in the file [Grammar.md](./Grammar.md). This document provides a comprehensive overview of the language's syntax and structure.


## Acknowledgments

- *[Crafting Interpreters](https://craftinginterpreters.com/)* by Robert Nystrom, for the guidance and inspiration in building the Lox compiler.
- The open-source community for tools and libraries.