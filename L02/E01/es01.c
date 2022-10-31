#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b){
	if (a == b){
		return a;
	}
	if(a % 2){
		if(b % 2){
			return gcd(abs((a-b)/2),b);
		}
		else{
			return gcd(a, b/2);
		}
	}
	else{
		if(b % 2){
			return gcd(b,a/2);
		}
		else
			return 2 * gcd(a/2,b/2);
	}
}

int main(){
	int num1, num2;
	printf("Inserisci il primo numero: ");
	scanf(" %d", &num1);
	printf("\nInserisci il secondo numero: ");
	scanf(" %d", &num2);
	printf("Il massimo comun divisore è: %d\n", gcd(num1,num2));

}
