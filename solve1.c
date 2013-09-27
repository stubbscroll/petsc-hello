/* minimal example of solving a linear equation system in petsc
   (in serial) */
/* based on http://www.mcs.anl.gov/petsc/petsc-current/src/ksp/ksp/examples/tutorials/ex1.c.html */
#include <petscksp.h>
#define SIZE 3
int main(int argc,char **argv) {
	Vec x,b;   /* approx solution, rhs */
	Mat A;     /* linear system matrix */
	KSP ksp;   /* linear solver context */
	PC pc;     /* preconditioner context */
	int size;
	PetscInt col[3],i;
	PetscScalar temp[SIZE];

	PetscInitialize(&argc,&argv,PETSC_NULL,PETSC_NULL);
	MPI_Comm_size(PETSC_COMM_WORLD,&size);
	if(size!=1) PetscPrintf(PETSC_COMM_WORLD,"warning, %d threads\n",size);
	/* create vectors */
	VecCreate(PETSC_COMM_WORLD,&x);
	VecSetSizes(x,PETSC_DECIDE,SIZE);
	VecSetFromOptions(x);
	VecDuplicate(x,&b);
	temp[0]=14.5; temp[1]=54; temp[2]=0.423;
	for(i=0;i<3;i++) VecSetValues(b,1,&i,&temp[i],INSERT_VALUES);
	/* need to assemble after setting values! do necessary
	   message passing etc to propagate matrix to all ranks */
	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	/* create matrix */
	MatCreate(PETSC_COMM_WORLD,&A);
	MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,SIZE,SIZE);
	MatSetFromOptions(A);
	MatSetUp(A);
	temp[0]=1; temp[1]=1; temp[2]=1;
	col[0]=0; col[1]=1; col[2]=2;
	for(i=0;i<3;i++) {
		MatSetValues(A,1,&i,3,col,temp,INSERT_VALUES);
		temp[i]=0;
	}
	/* need to assemble matrix for the same reasons as above */
	MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
	MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
	/* linear solver context! */
	KSPCreate(PETSC_COMM_WORLD,&ksp);
	/* operator is A matrix, also set matrix for preconditioning here */
	KSPSetOperators(ksp,A,A,DIFFERENT_NONZERO_PATTERN);
	/* get pc context from ksp context */
	KSPGetPC(ksp,&pc);
	/* set preconditioner type */
	PCSetType(pc,PCJACOBI);
	KSPSetTolerances(ksp,1e-6,PETSC_DEFAULT,PETSC_DEFAULT,PETSC_DEFAULT);
	KSPSetFromOptions(ksp);
	/* solve! */
	KSPSolve(ksp,b,x);
	/* display everything */
	MatView(A,PETSC_VIEWER_STDOUT_WORLD);
	VecView(b,PETSC_VIEWER_STDOUT_WORLD);
	VecView(x,PETSC_VIEWER_STDOUT_WORLD);
	KSPView(ksp,PETSC_VIEWER_STDOUT_WORLD);
	/* get rid of everything */
	KSPDestroy(&ksp);
	VecDestroy(&x);
	VecDestroy(&b);
	PetscFinalize();
	return 0;
}

