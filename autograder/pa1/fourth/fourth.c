#include <stdio.h>
#include <stdlib.h>

//method declarations
int getColumn (int index, int maxRow, int maxCol);
int getRow (int index, int maxRow, int maxCol);
void multiplyMatrix (int *matrix1, int *matrix2, int *matrix3, int maxRow1, int maxCol1, int maxRow2, int maxCol2);
void printMatrix (int *matrix1, int maxRow, int maxCol);
void freeMatrices (int *matrix1, int *matrix2, int *matrix3);

int main(int argc, char **argv) {
    //command line error detection
	if (argc < 2) {
        printf("error\n");
        return 0;
    }
	//matrices
    int *matrix1 = NULL;
    int *matrix2 = NULL;
    int *matrix3 = NULL;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("error\n");
        return 0;
    }
    
    int rows1;
    int cols1;
    int r = fscanf(f, "%d\t%d\n", &rows1, &cols1);

    if (r == 2) {
        matrix1 = (int*) malloc((rows1 * cols1)*sizeof(int));
    } else {
        printf("error\n");
        return 0;
    }
	//forming matrix1
    int i;
    for (i = 0; i < (rows1 * cols1); i++) {
        int column = getColumn(i, rows1, cols1);
        int ret;
        int k;
		//if on last column
        if (column + 1 == cols1) {
            ret = fscanf(f, "%d\n", &k);
        }
        else {
            ret = fscanf(f, "%d", &k);
        }
        
        if (ret == 1) {
            *(matrix1+ i) = k;
        } else {
            printf("error\n");
            freeMatrices(matrix1, matrix2, matrix3);
            return 0;
        }
    }

    int rows2;
    int cols2;
    r = fscanf(f, "\n\n%d %d\n", &rows2, &cols2);
    if (r == 2) {
        if (cols1 != rows2) {
			//cant multiply
            printf("bad-matrices\n");
            freeMatrices (matrix1, matrix2, matrix3);
            return 0;
        } else {
            matrix2 = (int*) malloc((rows2 * cols2)*sizeof(int));
        }
    } else {
        printf("error\n");
        freeMatrices (matrix1, matrix2, matrix3);
        return 0;
    }
	//forming matrix2
    for (i=0; i < (rows2 * cols2 ); i++) {
        int column = getColumn(i, rows2, cols2);
        int r;
        int iTemp;
        if (column + 1 == cols2) {
            r = fscanf(f, "%d\n", &iTemp);
        } else {
            r = fscanf(f, "%d", &iTemp);
        }
        if (r == 1) {
            *(matrix2+i) = iTemp;
        } else {
            printf("error\n");
            freeMatrices (matrix1, matrix2, matrix3);
            return 0;
        }
    }

	//cerate new matrix
    matrix3 = (int*) malloc((rows1 * cols2)*sizeof(int));
	//input values of new matrix
    multiplyMatrix (matrix1, matrix2, matrix3, rows1, cols1, rows2, cols2);
    printMatrix (matrix3, rows1, cols2);
    freeMatrices (matrix1, matrix2, matrix3);
    fclose(f);
    return 0;
}


int getRow (int index, int maxRow, int maxCol) {
    return index / maxCol;
}

int getColumn (int index, int maxRow, int maxCol) {
    return index % maxCol;
}


void multiplyMatrix (int *matrix1, int *matrix2, int *matrix3, int maxRow1, int maxCol1, int maxRow2, int maxCol2) {
    int i;
    int j;
    int k;
	//iterate by row
    for (i = 0; i < maxRow1; i++) {
		//iterate each col for each row
        for (j = 0; j < maxCol2; j++) {
            int sum = 0;
            for (k = 0; k < maxCol1; k++) {
                int index1 = (k + i * maxCol1);
                int index2 = (j + k * maxCol2);
                sum += (*(matrix1+ index1)) * (*(matrix2 + index2));
            }
            int index = (j + i * maxCol2);
            *(matrix3 + index) = sum;
        }
    }
}


void printMatrix (int *matrix1, int maxRow, int maxCol) {
	//iterate through matrix and print all
    int i;
    int j;
    for (i=0; i < maxRow; i++) {
        for (j=0; j < maxCol; j++) {
            int temp = j + i * maxCol;
            int value = *(matrix1+ temp);
            printf("%d", value);
            if (j != maxCol - 1) {
                printf("\t");
            }
            else {
                printf("\n");
            }
        }
    }
}

void freeMatrices (int *matrix1, int *matrix2, int *matrix3) {
    if (matrix1) {
        free(matrix1);
    }
    if (matrix2) {
        free(matrix2);
    }
    if (matrix3) {
        free(matrix3);
    }
}
