#include <stdio.h>
#include <stdlib.h>

typedef struct {char **scelte; int num_scelte; } Livello;

int princ_molt(int pos, Livello *val, int *sol,int n, int cnt) { 
	int i;
	if (pos >= n) {
        printf("Playlist #%d: ", cnt);
		for (i = 0; i < n; i++)
		  printf(" %s ", val[i].scelte[sol[i]]);
		printf("\n");
		return cnt+1;
	  }
	for (i = 0; i < val[pos].num_scelte; i++) {
		sol[pos] = i;
		cnt = princ_molt(pos+1, val, sol, n, cnt);
	}
	return cnt;
}

int leggiFile(FILE* f, Livello** val){
	int nLivelli;
	fscanf(f, "%d", &nLivelli);
	(*val) = (Livello* )malloc(sizeof(Livello) * nLivelli);
	Livello* livelli = *val;
	for(int i = 0; i < nLivelli; i++){
		fscanf(f, " %d", &livelli[i].num_scelte);
		livelli[i].scelte = malloc(sizeof(char*) * (livelli[i].num_scelte));
		for(int j = 0; j< livelli[i].num_scelte; j++){
			livelli[i].scelte[j] = malloc(sizeof(char) * 100);
			fscanf(f, " %s", livelli[i].scelte[j]);
		}
	}

    return nLivelli;

}



int main(){
	FILE* fin = fopen("brani.txt", "r");
	if(fin == NULL){
		printf("Errore nella lettura del file\n");
		return 0;
	}

	Livello* livelli;
	int nLivelli = leggiFile(fin, &livelli);
	int* sol = malloc(sizeof(int) * nLivelli);
	int nSol = princ_molt(0, livelli,sol,nLivelli, 0);
	printf("\nGenerate %d playlist\n", nSol);
}



