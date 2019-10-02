#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    
    //char *output = (char*) malloc(argc * sizeof(char));
    
    int i;
    for(i = 0; i < (argc - 1); i++) {
        //iterate string by string (arg by arg)
        char *current = argv[i + 1];
        int length = strlen(current);
        
        //iterate word by word given length
        int j;
        for(j = 0; j < length; j++) {
            //read char and if vowel, print
            if (current[j] == 'a'
                || current[j] == 'e'
                || current[j] == 'i'
                || current[j] == 'o'
                || current[j] == 'u'
                || current[j] == 'A'
                || current[j] == 'E'
                || current[j] == 'I'
                || current[j] == 'O'
                || current[j] == 'U') {
                printf("%c", current[j]);
            }
        }
    }
    printf("\n");
}