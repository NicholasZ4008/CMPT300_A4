#include <string.h>
#include <time.h>
#include "algorithms.h"

const int MAX_ARRAY_SIZE = 50;

//Helper to check for unique array values
bool isUnique(int* array, int length, int value){
    for(int i = 0; i < length; i++){
        if(array[i] == value){
            return false;
        }
    }
    return true;
}

//Function calls for both random and inputted array
void outputs_and_function_calls(int* array, int length){
    printf("Head: %d\n", array[0]);
    printf("Tracks To Traverse: %d\n", length);
    printf("\n");
    scan(array, length);
    printf("\n");
    sstf(array, length);
}

int main(int argc, char *argv[]) {
    //User inputted array
    if (argc > 1) {
        //Setup for reading input
        char* inputArray = argv[1];
        if(inputArray == NULL){
            printf("Nothing inputted.\nTerminating program...\n");
            return -2;
        }
        int arraySize = 1;
        int* numberInput = (int*) malloc(arraySize * sizeof(int));

        //Total number of ints read
        int numsRead = 0;
        //Need to seperate with ,
        char* seperator = strtok(inputArray, ",");
        
        //Loop until end of strings reached
        while(seperator != NULL){
            numberInput[numsRead++] = atoi(seperator);
            //Increase size of array if more space needed
            if(numsRead == arraySize){
                arraySize *= 2;
                numberInput = (int*) realloc(numberInput, arraySize*sizeof(int));
            }
            seperator = strtok(NULL, ",");
        }

        //Not enough value inputted to be processed
        if(numsRead < 3){
            printf("There must be atleast 3 numbers. Check input.\nTerminating program...\n");
            free(numberInput);
            return -2;
        }

        printf("Original Sequence: ");
        for(int j = 0; j < numsRead; j++){
            if(numberInput[j] < 0 || numberInput[j] > 199){
                printf("\nIncorrect value \"%d\" given.\nTerminating program...\n", numberInput[j]);
                free(numberInput);
                return -1;
            }
            printf("%d ", numberInput[j]);
        }

        outputs_and_function_calls(numberInput, numsRead);
        free(numberInput);
        
    } else {
        // Generate at least 50 unique random integers between 0 and 199
        srand((unsigned int)time(NULL));
        int randArr[MAX_ARRAY_SIZE]; //Update const at top of file to change

        //Populate array
        for(int i = 0; i < MAX_ARRAY_SIZE;){
            int randNum = rand() % (MAX_TRACK_NUMBER);
            if(isUnique(randArr, i, randNum)){
                randArr[i] = randNum;
                i++;
            }
        }

        printf("Original Sequence: \n");
        printArray(randArr, MAX_ARRAY_SIZE);

        outputs_and_function_calls(randArr, MAX_ARRAY_SIZE);      

    }
    return 0;
}
