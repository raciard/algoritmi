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


typedef enum {r_ritardo_sort, r_data_sort, r_stazArr_sort,
    r_codice_sort, r_stazPart_sort,r_ricerca_bin, r_ricerca_lin, r_help, r_fine,r_err = -1} comando_e;

comando_e leggicomando(char comando[]);



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


void sort(Corsa* corse[], int n, int(*compareFun)(Corsa*, Corsa*)){
	Corsa* temp;
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

int ritardoCompare(Corsa* a, Corsa* b){
	return a->ritardo > b->ritardo;
}
int dataCompare(Corsa* a, Corsa* b){
	int r = strcmp(a->data, b->data);
	if (r > 0)
		return 1;
	else if(r < 0)
		return 0;
	else {
		r = strcmp(a->ora_partenza, b->ora_arrivo);
		if(r>0)
			return 1;
		else
			return 0;
	}
}

int codiceCompare(Corsa* a, Corsa* b){
	return strcmp(a->codice_tratta, b->codice_tratta) > 0;
}

int stazPartCompare(Corsa *a, Corsa *b){
	return strcmp(a->partenza, b->partenza) > 0;
}

int stazArrCompare(Corsa *a, Corsa *b){
	return strcmp(a->destinazione, b->destinazione) > 0;
}

void sortByRitardo(Corsa* corse[], int n){
	sort(corse, n, ritardoCompare);
}

void sortByData(Corsa* corse[], int n){
	return sort(corse, n, dataCompare);
}

void sortByCodice(Corsa* corse[], int n){
	return sort(corse, n, codiceCompare);
}
void sortByStazPart(Corsa* corse[], int n){
	return sort(corse, n, stazPartCompare);
}
void sortByStazArr(Corsa* corse[], int n){
	return sort(corse,n,stazArrCompare);
}




void stampaCorse(Corsa *corse[], int n){
	for(int i =0; i < n; i++)
		printf("Corsa: %s, Partenza: %s, Destinazione: %s,  Data Partenza: %s, Ora Partenza: %s, Ora Arrivo: %s, Ritardo: %d\n", corse[i]->codice_tratta, corse[i]->partenza,
				corse[i]->destinazione, corse[i]->data, corse[i]->ora_partenza, corse[i]->ora_arrivo, corse[i]->ritardo);
}



Corsa **searchByStazPart(Corsa* corse[], int n, char* str, int* nResults){
	
	*nResults = 0;
	size_t len = strlen(str);
	Corsa **results = (Corsa **)malloc(sizeof(Corsa*) * n);

	
	for(int i = 0; i < n; i++){
		if(strncmp(corse[i]->partenza, str, len) == 0){
			results[*nResults] = corse[i];
			(*nResults)++;
		}
	}

	return results;


}

Corsa **searchByStazPart_bin(Corsa* corse[], int n, char* str, int* nResults){
	*nResults = 0;
	size_t len = strlen(str);

	Corsa **results = (Corsa **)malloc(sizeof(Corsa*) * n);
	
	int pos,l = 0, r = n;
	int found = 0;
	while(!found){
		if((r - l) <= 1){
			return NULL;
		}
		pos = (l + r)/2;
		int diff = strncmp(corse[pos]->partenza, str, len);
		if(diff == 0){
			found = 1;
		} 
		else if (diff < 0){
			l = pos;
		}
		else r = pos;
		
	}
	if(found){
		results[0] = corse[pos];
        (*nResults) = 1;
		int lpos = pos, rpos = pos;
		while(lpos > 0 && strncmp(corse[--lpos]->partenza, str, len) == 0){
			results[*nResults] = corse[lpos];
			(*nResults)++;
		}
		while(rpos < (n-1) && strncmp(corse[++rpos]->partenza, str, len) == 0){
			results[*nResults] = corse[rpos];
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
	Corsa* corseByRitardo[BUFFER_SIZE],
		   *corseByData[BUFFER_SIZE],
		 	*corseByStazArr[BUFFER_SIZE],
			*corseByStazPart[BUFFER_SIZE],
				*corseByCodice[BUFFER_SIZE];
    int nRighe = leggiFile(fin, corse);

	for(int i = 0; i < nRighe; i++){

		corseByRitardo[i] = &corse[i];
		corseByData[i] = &corse[i];
		corseByStazArr[i] = &corse[i];
		corseByStazPart[i] = &corse[i];
		corseByCodice[i] = &corse[i];
	}
	sortByRitardo(corseByRitardo, nRighe);
	sortByData(corseByData, nRighe);
	sortByStazArr(corseByStazArr, nRighe);
	sortByStazPart(corseByStazPart, nRighe);
	sortByCodice(corseByCodice, nRighe);

	
	char comando[100];
	comando_e c;
	do{

		printf("Inserire un comando (\"h\" per istruzioni): \n");
		scanf(" %s", comando);
	
		c = leggicomando(comando);
		
		switch (c) {
			case r_ritardo_sort: {
				printf("\nOrdino per ritardo... \n");
				stampaCorse(corseByRitardo, nRighe);
				break;
			}
			case r_data_sort: {
				printf("\nOrdino per data... \n");
				stampaCorse(corseByData, nRighe);

				break;
			}
			case r_stazArr_sort: {
				printf("\nOrdino per stazione di arrivo... \n");
				stampaCorse(corseByStazArr, nRighe);
				break;
			}
			case r_stazPart_sort: {
				printf("\nOrdino per stazione di partenza... \n");
				stampaCorse(corseByStazPart, nRighe);

				break;
			}
			case r_codice_sort: {
				printf("\nOrdino per codice corsa... \n");
				stampaCorse(corseByCodice, nRighe);
				break;
			}
			case r_fine: { 
				break;
			}
			case r_help:{
				printf("\nOrdinamenti: \n"
						"\t per Ritardo: ritsort\n"
						"\t per Data: datasort\n"
						"\t per Stazione di arrivo: arrsort\n"
						"\t per Stazione di partenza: partsort\n"
						"\t per Codice: codsort\n"
						"Ricerca stazione partenza: \n"
						"\t ricerca lineare: riclin\n"
						"\t ricerca binaria: ricbin\n"
						"Per terminare il programma: fine\n\n");
				break;

			}
			case r_ricerca_bin:{
				char query[MAXS];
				int nResults;
				printf("Inserire la stazione di partenza da cercare: \n");
				scanf(" %s", query);
				Corsa** results = searchByStazPart_bin(corseByStazPart, nRighe, query, &nResults);
				stampaCorse(results, nResults);
				break;
			}
			case r_ricerca_lin:{
				char query[MAXS];
				int nResults;
				printf("Inserire la stazione di partenza da cercare: \n");
				scanf(" %s", query);
				Corsa** results =searchByStazPart(corseByStazPart, nRighe, query, &nResults);
				stampaCorse(results, nResults);
				break;
			}
			case r_err: {
				printf("Il comando che hai inserito non è valido!");
			}
		}




	}while(c != r_fine);

    fclose(fin);
	return 0;

}









comando_e leggicomando(char comando[]){



    char *tabella[r_fine + 1]={
            "ritsort","datasort","arrsort","codsort","partsort","ricbin",
			"riclin","h", "fine"}; 

    for(int i = 0; i <= r_fine; i++){
        if(strcmp(tabella[i], comando) == 0)
            return i;
    }
    return r_err;
}
