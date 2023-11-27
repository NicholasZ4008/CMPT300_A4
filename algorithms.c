#include "algorithms.h"

void printOriginalArrayElems(int *requestArray, int size){
    printf("Original array elements: ");

    for(int i=0;i<size; i++){
        printf("%d ,",requestArray[i]);
    }
    printf("\n");
}

void calculatedifference(int requestArray[], int head, int diff[][2], int n)
{
    for(int i = 0; i < n; i++){
        diff[i][0] = abs(head - requestArray[i]);
    }
}

int findMIN(int diff[][2], int n){
    int index = -1;
    int minimum = 1e9;
   
    for(int i = 0; i < n; i++){
        if (!diff[i][1] && minimum > diff[i][0])
        {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

//SSTF disk scheduling algorithm
void sstf(int *requestArray, int numRequests){

    if (numRequests <= 1) {
        return;
    }

    // The head is always the first element in the requestArray
    int head = requestArray[0];

    // Create array of differences and flags
    int diff[numRequests-1][2]; // Array size is numRequests-1 because the head is not included
    for (int i = 0; i < numRequests-1; i++) {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }

    // Count total number of seek operations
    int seekcount = 0;

    // Stores sequence in which disk access is done
    int seeksequence[numRequests];

    for (int i = 0; i < numRequests-1; i++) {
        seeksequence[i] = head;
        calculatedifference(requestArray+1, head, diff, numRequests-1); // requestArray+1 to skip the head
        int index = findMIN(diff, numRequests-1);
        diff[index][1] = 1;

        // Increase the total count
        seekcount += diff[index][0];

        // Accessed track is now new head
        head = requestArray[index + 1]; // index + 1 to adjust for the skipped head
    }
    seeksequence[numRequests-1] = head;

    //print the number of requests
    printf("Total number of seek operations = %d\n", seekcount);

    // Print the sequence
    printOriginalArrayElems(requestArray, numRequests);
}

//SCAN disk scheduling algorithm
void scan(int *requestArray, size_t numRequests, int startTrack){
    
}