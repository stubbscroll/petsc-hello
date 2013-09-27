"Hello world" in PETSc using cmake.

Programs:
- hello1: minimal hello world program
- solve1: rather minimal program that solves a system of equations

CMakeLists.txt: the cmake build file. It uses modules for locating the PETSc
library (placed in the directory cmake-modules), these modules are taken from
https://github.com/jedbrown/cmake-modules

A regular makefile is also included.

The usual PETSc requirements apply: prerequisite libraries (most notably MPI)
and the environment variables PETSC_DIR and PETSC_ARCH must be set.

How to build:

mkdir build
cd build
cmake -D CMAKE_C_COMPILER=${PETSC_DIR}/${PETSC_ARCH}/bin/mpicc ..
make

(In subsequent build runs in the same build tree, use `cmake ..`.)

Now there should be two executables (hello1, solve1) in the build directory.

Please note that PETSc (by default) uses MPI, so we need to change the
compiler. This is what the extra argument to cmake does. Neglecting to
change the compiler will lead to MPI-related linking errors.

In the future I might add more example files to this repository.

