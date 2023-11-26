#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MIN_INT_ARRAY = 0;
const int MAX_INT_ARRAY = 199;

int main(int argc, char *argv[]) {
    if (argc > 1) {//argv[0] is ./DSSimul
        // Parse argv[1] for track numbers
        // ...

        //Setup for reading input
        char* inputArray = argv[1];
        int arraySize = 1;
        int* numberInput = (int*) malloc(arraySize * sizeof(int));

        //Total number of ints read
        int numsRead = 0;
        //Need to seperate with ,
        char* seperator = strtok(inputArray, ",");
        
        //Loop until end of strings reached
        while(seperator != NULL){
            numberInput[numsRead++] = atoi(seperator);

            //Increment size of array if theres still need
            if(numsRead == arraySize){
                arraySize *= 2;
                numberInput = (int*) realloc(numberInput, arraySize*sizeof(int));
            }
            seperator = strtok(NULL, ",");
        }

        /*TEMPORARY JUST FOR TESTING*/
        printf("Printing input: ");
        for(int j = 0; j < numsRead;j++){
            printf("%d ", numberInput[j]);
        }
        printf("\n");
        /*END TEMPORARY*/

        free(numberInput);

    } else {
        // Generate at least 50 unique random integers between 0 and 199
        // ...
    }
    return 0;
}
