#include <stdio.h>
#include <ctype.h>




char* charMatch(char src, char* currentRegPos);
char* cercaRegexp(char *src, char *regexp);



int main() {
    printf("%s\n", cercaRegexp("aaaaaciao", "aaac"));

    return 0;
}



char *charMatch(char src, char *currentRegPos) {
    /*
        Controlla se il carattere src rispecchia i criteri definiti dal primo metacarattere
        della regex currentRegPos

        Se vi è una corrispondenza ritorna un puntatore alla posizione nella regex dell'ultimo carattere di cui è
        composto il metacarattere analizzato, altrimenti ritorna NULL.
    */
    if(*currentRegPos == '.')
        return currentRegPos;
    else if(*currentRegPos == '['){
        if(*(currentRegPos+1) == '^'){

            currentRegPos++;
            while(*(++currentRegPos) != ']'){
                if(*currentRegPos == src)
                    return NULL;
            }
            return currentRegPos;
        }else {
            int found = NULL;
            while (*(++currentRegPos) != ']') {
                if (*currentRegPos == src)
                    found = 1;

            }
            if(found)
                return currentRegPos;
        }

    }

    else if(*currentRegPos == '\\'){
        if(*(++currentRegPos) == 'a'){
            if(islower(src))
                return currentRegPos;
            else return 0;
        }
        if(*(currentRegPos) == 'A'){
            if(isupper(src))
                return currentRegPos;
            else return NULL;
        }
    }

    else if(*currentRegPos == src)
        return currentRegPos;
    return NULL;
}

char *cercaRegexp(char *src, char *regexp) {

    char* currRegExp = regexp;
    int dist = 0;
    while(*src != '\0') {
        if (*currRegExp == '\0')
            return src - dist;
        if (!(currRegExp = charMatch(*src, currRegExp))) {
            if(currRegExp == regexp)
                src++;
            else{
                src -= (dist - 1);
            }
            currRegExp = regexp;
            dist = 0;
        } else {
            currRegExp++;
            dist++;
            src++;
        }
// "aaaciao"       "-aaciao"
    }
    if(*currRegExp != '\0')
        return NULL;
    else return src - dist;

}
