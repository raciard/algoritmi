#include <stdio.h>
#include <stdlib.h>


int **malloc2dR(int nr, int nc){
	int** mat = (int**) malloc(nr*sizeof(int*));
	for(int i = 0; i < nr; i++)
		mat[i] = (int *)malloc(nc * sizeof(int));
	return mat;
	
}

void separa(int **mat, int nr, int nc, int** black, int *nb, int** white, int *nw){
	int dim = nr*nc;
	int white_dim = dim / 2 + dim%2,
		black_dim = dim / 2;
	*white = (int*) malloc(white_dim * sizeof(int));

	*black  = (int*) malloc(black_dim* sizeof(int));
	*nb =0;
	*nw = 0;
	for(int r = 0; r < nr; r++)
		for(int c = 0; c < nc; c++){
			if((r+c) % 2){
				(*black)[*nb] = mat[r][c];
				(*nb)++;
			}
			else{
				(*white)[*nw] = mat[r][c];
				(*nw)++;
			}
		}

}


int **readMatrix(FILE* fin, int* nr, int* nc){
	fscanf(fin, "%d %d ", nr,nc);
	int** mat = malloc2dR(*nr,*nc);
	for(int r =0; r < *nr; r++)
		for (int c =0; c < *nc; c++)
			fscanf(fin, "%d ", &mat[r][c]);

	return mat;


}

void printM(int ** mat, int nr, int nc){
	for(int r =0; r < nr; r++){
		for(int c =0; c < nc; c++)
			printf("%d ", mat[r][c]);
		printf("\n");	
	}
	printf("\n");
}


int main(){
	FILE* file = fopen("mat.txt", "r");
	int nr, nc;
	int** mat = readMatrix(file, &nr, &nc);
	printM(mat, 3, 3);

	int* black, *white, nb, nw;
	printf("Matrice letta: \n");
	separa(mat, nr,nc, &black,&nb,&white,&nw);
	printf("I bianchi sono: \n");
	for(int i =0; i < nw; i++)
		printf("%d ", white[i]);
	printf("\nI neri sono: \n");
	for(int i =0; i < nb; i++)
		printf("%d ", black[i]);


}
