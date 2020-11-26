#include <stdio.h>
#include <stdlib.h>

int get(unsigned short x, int n);
//int palindrome(unsigned short x, int max, int min);

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("error\n");
        return 0;
    }
    unsigned short x = atoi(argv[1]);
    
    int i;
    for(i = 0; i <= 7; i++) {
//        get corresponding values
        int a = get(x, i);
        int b = get(x, (15 - i));
//        compare using truth table logic
//        if a == b, XOR returns 0, else 1 (a != b)
        int match = a ^ b;
        if(match ^ 0) {
            printf("Not-Palindrome\n");
            return 0;
        }
    }
//    if entire for-loop was executed, is palindrome
    printf("Is-Palindrome\n");
    return 0;
    
}

int get(unsigned short x, int n) {
//    right shift number n times and & 1
    int nthBit = (x >> n) & 1;
    return nthBit;
}

//int palindrome(unsigned short x, int max, int min) {
//    if(max == min) {
//        return 1;
//    }
////    get highest bit
//    int a = get(x, max);
////    get lowest bit
//    int b = get(x, min);
////    truth table logic
//    int match = a & b;
////    if a != b, return 0 (not palindrome)
//    if(match == 0)
//        return 0;
////    else recurse
//    max--;
//    min++;
//    palindrome(x, max, min);
//}
