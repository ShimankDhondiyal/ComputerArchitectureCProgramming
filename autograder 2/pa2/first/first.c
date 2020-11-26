#include <stdio.h>

int set(unsigned short x, int n, int v);
int comp(unsigned short x, int n);
int get(unsigned short x, int n);

int main(int argc, char *argv[]) {
//    command line check
    if(argc < 2){
        printf("error\n");
        return 0;
    }
//    get file name
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        printf("error\n");
        return 0;
    }
//    get original number
    unsigned short x;
    fscanf(f, "%hu\n", &x);
//    scan rest of deocument
    char str[5];
    int n;
    int v;
    int junk;   //second number to be discarded
    while (!feof(f)) {
        fscanf(f, "%s\t", str);
//        string is "get"
        if(str[0] == 'g') {
            fscanf(f, "%d\t%d\n", &n, &junk);
            int bit = get(x, n);
            printf("%d\n", bit);
        }
//        string is "comp"
        else if(str[0] == 'c') {
            fscanf(f, "%d\t%d\n", &n, &junk);
            x = comp(x, n);
            printf("%hu\n", x);
        }
//        string is "set"
        else if(str[0] == 's') {
            fscanf(f, "%d\t%d\n", &n, &v);
            x = set(x, n, v);
            printf("%hu\n", x);
        }
//        string does not match
        else {
            printf("error\n");
            return 0;
        }
    }
    
}

//return nth bit of unsigned short x
int get(unsigned short x, int n) {
//    right shift number n times and & 1
    int nthBit = (x >> n) & 1;
    return nthBit;
}

//pass x to method, return adjusted int to replace current x
//should change to use pointers
int set(unsigned short x, int n, int v) {
    int newBit = (x & (~(1 << n))) | (v << n);
    return newBit;
}

//pass x to method, return new value with bit adjusted, replace current x
//should change with pointers
int comp(unsigned short x, int n) {
    int newInt = x ^ (1 << n);
    return newInt;
}
