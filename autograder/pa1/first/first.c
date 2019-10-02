#include <stdio.h>


int *sort(int *arr, int size);
int isEven(int i);
//int *sortwithPtr(int * arr, int size);

int main(int argc, char **argv) {
    if(argc < 2) {                      //ensure that file name is passed
        printf("Error\n");
        return 0;
    }

    int arr[20];                        //max size 20
    int size = 0;                       //actual size of array
    char * fName = argv[1];             //contain file name passed from terminal

    //create file pointer
    FILE *f;
    
    //open file
    f = fopen(fName, "r");    //will return null if file not accessible
    
    //scan from file
    while(!feof(f) && (size < 20)) {
        fscanf(f, "%d", &arr[size++]);
    }
    size = arr[0];                      //first element from file is used to determine size
    for(int i = 1; i <= size; i++) {    //get rid of first element in array
        arr[i - 1] = arr[i];
    }

    // Sort as per the specifications in assignment
    int *sortedArr = sort(arr, size);  //pointer to address of array[0]
    //int * sortedArr = sortwithPtr(arr, size);  //pointer to address of array[0]

    for(int i = 0; i < size; i++) {
        printf("%d\t", sortedArr[i]);
    }

    fclose(f);
}

/**
 * Method will be called from main and will:
 *  Use insertionSort to organize array
 *  Act on even numbers first, then odd numbers
 *
 * @arr     array to be sorted
 * @size    length of array
 */
int *sort(int * arr, int size) {
    int current;                        //curent element
    int prevIndex;                      //element preceding
    for(int i = 0; i < size; i++) {
        //check even/odd status
        if(!isEven(arr[i])) {           //element is odd if(returns 0)
            continue;                   //i will automatically increment
        }
        current = arr[i];               // *(arr+i)
        prevIndex = i - 1;
        int currentPtr = i;             //will be used to keep track of current as it gets swapped
        //insertionSort algorithm
        while(prevIndex >= 0) {         //iterate prevIndex to beginning
            if(!isEven(arr[prevIndex])) {
                // Swap prevIndex and current
                int temp = arr[prevIndex];// *(arr+prevIndex)
                arr[prevIndex] = arr[currentPtr]; 
                arr[currentPtr] = temp;

                currentPtr = currentPtr - 1;  //currentPtr will keep track of current value
                prevIndex = prevIndex - 1;
                //continue;             probably will not need due to else if
            } else if(arr[prevIndex] > current) { //if element is even
                arr[prevIndex + 1] = arr[prevIndex];
                prevIndex = prevIndex - 1;
            } else if(arr[prevIndex] <= current) {
                break;                  //end while loop here because all numbers should be sorted by here
                                        //if issue, replace break with prevIndex = prevIndex - 1;
                                        //this will iterate prevIndex down to 0 and brute force correctness
            }
        }
        arr[prevIndex + 1] = current;
    }
    /*AT THIS POINT, ALL EVENS HAVE BEEN SORTED IN ASCENDING ORDER*/
    //sort odd elements from arrSize to first observed even element
    for(int i = size - 1; i >= 0; i--) {
        if(isEven(arr[i])) {            //when even number encountered, no more odd elements in array
            break;
        }
        current = arr[i];               //store current element
        prevIndex = i - 1;              //this will compare against all other elements
        int lowestVal = current;        //keep track of lowest element encountered
        int lowestValPtr = i;           //keep track of lowest element position
        while(prevIndex >= 0) {
            if(isEven(arr[prevIndex])) {
                break;
            } else if(arr[prevIndex] > lowestVal) {
                prevIndex = prevIndex - 1;
            } else if(arr[prevIndex] <= lowestVal) {
                lowestVal = arr[prevIndex];
                lowestValPtr = prevIndex;
                prevIndex = prevIndex - 1;
            }
        }
        //swap the current element with the lowest odd number IFF a lower element was encountered
        if(current != lowestVal) {
            arr[lowestValPtr] = current;
            arr[i] = lowestVal;
        }
    }
    return arr;
}

/**
 * Method will be used to determine whether int is even or odd
 *
 * @i       element at array index
 * @return  0 if even, 1 if odd
**/
int isEven(int i) {
    if(i % 2 == 0){
        return 1;   //is even
    }
    return 0;       //is odd
}
