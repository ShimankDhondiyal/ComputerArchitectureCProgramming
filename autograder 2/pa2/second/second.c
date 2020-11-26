#include <stdio.h>
#include <stdlib.h>

int numberOfOnes(int num);
int main(int argc, char *argv[]) {
//    command line check
    if(argc < 2) {
        printf("errror\n");
        return 0;
    }
    unsigned short arg = atoi(argv[1]);
    
    //parity: whether number contains even or odd number of 1 bits
    int count = 0;
    int i;
    unsigned short argCopy = arg;
    for(i = 0;i < (sizeof(int) * 8); i++) {
        count += argCopy & 1;
        argCopy = argCopy >> 1;
    }
//    if count % 2 == 0, even, else odd
    
    //number of 1 bit paris present
    unsigned int numberPairs = 0;
    unsigned int maskPosition = 0;
    
    while(maskPosition < 16) {
        if(((arg >> maskPosition) & 3) == 3) {
           numberPairs += 1;
           maskPosition += 2;
        }
        else {
           maskPosition += 1;
        }
    }
    if(count % 2 == 0) {
        printf("Even-Parity\t%d\n", numberPairs);
    }
    else if(count % 2 == 1) {
        printf("Odd-Parity\t%d\n", numberPairs);
    }
    return 0;
}
