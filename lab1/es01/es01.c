#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXS 30
#define BUFFER_SIZE 1000
typedef struct {
    char codice_tratta[MAXS];
    char partenza[MAXS];
    char destinazione[MAXS];
    char data[MAXS];
    char ora_partenza[MAXS];
    char ora_arrivo[MAXS];
    int ritardo;
} Corsa;

typedef enum {r_date, r_partenza, r_capolinea,
    r_ritardo, r_ritardo_tot, r_fine, r_err = -1} comando_e;

int leggiFile(FILE* f, Corsa corse[]){
    int nRighe = 0;
    int i = 0;
    fscanf(f, "%d ", &nRighe);

    while(fscanf(f, "%s %s %s %s %s %s %d ", corse[i].codice_tratta,
                 corse[i].partenza, corse[i].destinazione, corse[i].data,corse[i].ora_partenza, corse[i].ora_arrivo,
                 &(corse[i].ritardo)) == 7){
        i++;
    }
    return nRighe;
}


void sort(Corsa corse[], int n, int(*compareFun)(Corsa, Corsa)){
	Corsa temp;
	int j;
	for(int i = 1; i < n; i++){
		temp = corse[i];
		j = i - 1;
		while(j>=0 && compareFun(corse[j], temp)){
			corse[j+1] = corse[j];
			j--;
		}
		
	corse[j+1] = temp;
	}
	
}

int ritardoCompare(Corsa a, Corsa b){
	return a.ritardo > b.ritardo;
}
int dataCompare(Corsa a, Corsa b){
	int r = strcmp(a.data, b.data);
	if (r > 0)
		return 1;
	else if(r < 0)
		return 0;
	else {
		r = strcmp(a.ora_partenza, b.ora_arrivo);
		if(r>0)
			return 1;
		else
			return 0;
	}
}

int codiceCompare(Corsa a, Corsa b){
	return strcmp(a.codice_tratta, b.codice_tratta) > 0;
}

int stazPartCompare(Corsa a, Corsa b){
	return strcmp(a.partenza, b.partenza) > 0;
}

int stazArrCompare(Corsa a, Corsa b){
	return strcmp(a.destinazione, b.destinazione) > 0;
}

void sortByRitardo(Corsa corse[], int n){
	sort(corse, n, ritardoCompare);
}

void sortByData(Corsa corse[], int n){
	return sort(corse, n, dataCompare);
}

void sortByCodice(Corsa corse[], int n){
	return sort(corse, n, codiceCompare);
}
void sortByStazPart(Corsa corse[], int n){
	return sort(corse, n, stazPartCompare);
}
void sortByStazArr(Corsa corse[], int n){
	return sort(corse,n,stazArrCompare);
}




void stampaCorse(Corsa corse[], int n){
	for(int i =0; i < n; i++)
		printf("Corsa: %s, Partenza: %s, Destinazione: %s,  Data Partenza: %s, Ora Partenza: %s, Ora Arrivo: %s, Ritardo: %d\n", corse[i].codice_tratta, corse[i].partenza,
				corse[i].destinazione, corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
}



Corsa *searchByStazPart(Corsa corse[], int n, char* str, int* nResults){
	
	*nResults = 0;
	size_t len = strlen(str);
	Corsa *results = (Corsa *)malloc(sizeof(Corsa) * n);

	
	for(int i = 0; i < n; i++){
		if(strncmp(corse[i].partenza, str, len) == 0){
			results[*nResults] = corse[i];
			(*nResults)++;
		}
	}

	return results;


}



int main() {
    FILE* fin;


    if((fin = fopen("log.txt", "r")) == NULL){
        printf("Errore nella lettura del file\n");
        return -1;
    }

    Corsa corse[BUFFER_SIZE];
    int nRighe = leggiFile(fin, corse);

	int nResults;
	
	stampaCorse(searchByStazPart(corse, nRighe, "Pol", &nResults), nResults);

    fclose(fin);
	return 0;

}
