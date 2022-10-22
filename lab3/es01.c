#include <stdio.h>



int isMajor(int* a, int l, int r, int value){
    int n = (r-l)/2+1;
    int count = 0;
    for(int i =l; i < r; i++) {
        if (a[i] == value)
            count++;
        if(count >= n)
            return 1;
    }
    return 0;
}




int majoritySubs(int* a, int l, int r){
    int k = l + (r-l)/2;

    if(r == (l+1)){
        return a[l];

    }

    int lm = majoritySubs(a, l, k);
    int rm = majoritySubs(a,k,r);

    if(lm == rm)
        return lm;
    else{
        if(isMajor(a, l,r,lm))
            return lm;
        else if (isMajor(a,l,r,rm))
            return rm;
        else
            return -1;
    }


}

int majority(int* a, int N){
    return majoritySubs(a, 0, N);
}

int main() {
    int test[7] = {0,1,9,0,0, 0,1};
    printf("%d", majority(test,7));

    return 0;
}

