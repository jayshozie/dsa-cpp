# Data Structures and Algorithms in C

This is a joint project with [terra](https://github.com/terra2o), implementing
some data structures and algorithms in C.

# Prerequisites

1. GNUMake
2. A C Compiler

# Build

First, you need to decide whether you want the static version or the shared
version.
```bash
~/ $ git clone git@github.com:jayshozie/dsa-c
~/ $ cd dsa-c
# Shared Library (dsa.so) (Smaller)
~/dsa-c $ make shared
# Static Library (dsa.a) (Bigger, but contained)
~/dsa-c $ make static
```

# License

This project is licensed under [GNU General Public License v3](./LICENSE).
