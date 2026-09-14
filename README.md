# Templated linked list

A doubly linked list template in C++, header only, written for a data
structures course. `LinkedList.h` is the whole implementation;
`main.cpp` is a test driver.

The list keeps `head`, `tail`, and a node count, and supports insertion at
either end or at an index, removal by value or position, forward and reverse
printing in both iterative and recursive forms, and `FindAll` to collect every
node matching a value.

## Installation

Requires CMake 3.25 or newer and a C++17 compiler. No dependencies.

```bash
git clone https://github.com/BryanZaneee/Data-Structure-Templated-Linked-List.git
cd Data-Structure-Templated-Linked-List
cmake -S . -B build
cmake --build build
```

Compiling directly works just as well, since it is one header and one
translation unit:

```bash
c++ -std=c++17 -o Project_1 main.cpp
```

## Usage

The driver picks a test by number read from stdin:

```bash
echo 1 | ./Project_1   # Remove() by value
echo 2 | ./Project_1   # RemoveHead() and RemoveTail()
echo 3 | ./Project_1   # RemoveAt() and other removals
echo 4 | ./Project_1   # recursive PrintForward and PrintReverse
```

Each prints the list before and after the operation so the result can be read
directly.

## Contributing

This is archived coursework and is not taking contributions.

## License

No license file is included, so this is "all rights reserved" by default.
