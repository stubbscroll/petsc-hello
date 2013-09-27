# minimal make file for minimal petsc program
# build with "make hello1"
CFLAGS     =
FFLAGS     =
CPPFLAGS   =
FPPFLAGS   =
LOCDIR     =   ~/STATOIL/petsc/hello
EXAMPLESC  =   hello1.c solve1.c
EXAMPLESF  =
MANSEC     =
CLEANFILES =
NP         = 1

include ${PETSC_DIR}/conf/variables
include ${PETSC_DIR}/conf/rules
# it seems the next line is not really needed
include ${PETSC_DIR}/conf/test

hello1: hello1.o  chkopts
	-${CLINKER} -o hello1 hello1.o  ${PETSC_SYS_LIB}
	${RM} hello1.o

solve1: solve1.o chkopts
	-${CLINKER} -o solve1 solve1.o  ${PETSC_SYS_LIB}
	${RM} solve1.o

