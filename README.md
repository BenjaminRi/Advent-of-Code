# Advent of Code solutions in C++98

## How to run

Open your favourite console, compile the source code of a solution, which is always contained in one single file called `main.cpp`, with your favourite C++ compiler, like this: `g++ main.cpp`. Run the solution against the input which is given to the program via stdin like this: `a < sample1\in.txt`.

## Goals

The goal of this project is to solve the challenges with code that satisfies the following three criteria:

- Good performance, low usage of CPU cycles and RAM
- Beautiful and easy to read, as terse and expressive as possible, without code duplication
- Robust and handles all possible inputs without crashing or unexpected behaviour

I call code that satisfies these criteria *elegant*. Because these criteria are idealistic and hard to quantify, it is left up to the reader to decide if the solutions are elegant.

## Why C++98?

C++98 is one of the few languages in which it is even possible to write elegant code. Higher level languages often have just-in-time-compilation and a garbage collector which distorts the performance of the actual program. They also often lack performance. Lower level languages like C make it difficult to write beautiful code (though it is certainly possible to write elegant C code, just more tedious). For example, C does not have namespaces like C++ which causes function and struct names to be cluttered.

Another contender would have been Rust, which seems to have all the performance benefits of C++ combined with increased robustness and more powerful macros. Unfortunately, I did not have time to both learn Rust from scratch and solve the problems.

I chose C++98 and not a newer standard because for these small problems, the new standards like C++11 don't give me anything I really need. Yes, `auto` is nice and `std::unique_ptr` is extremely useful, but for these small programs, it's just not worth sacrificing the broad compatibility of C++98 for a couple neat features. For larger projects, C++11 is a vastly superior choice due to its move semantics.