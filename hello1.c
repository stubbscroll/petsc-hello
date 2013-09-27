/* minimal petsc program */
/* adapted (stolen) from http://petsc.wordpress.com/2012/07/23/1-hello-world/ */
#include "petsc.h"
int main( int argc, char *argv[]) {
	PetscInitialize(&argc,&argv,PETSC_NULL,PETSC_NULL);
	PetscPrintf(PETSC_COMM_WORLD,"Hello World\n");
	PetscFinalize();
	return 0;
}


