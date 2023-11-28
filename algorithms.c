#include "algorithms.h"

void printArray(int *requestArray, int size){
    for(int i=0;i<size; i++){
        printf("%d ",requestArray[i]);
    }
    printf("\n");
}

void calculateDelays(const int *originalSequence, const int *computedSequence, int numRequests) {
    int longestDelay = 0;
    int totalDelay = 0;
    int delayedTracks = 0;

    for (int i = 1; i < numRequests; i++) {
        int originalPosition = findPositionInArray(originalSequence, computedSequence[i], numRequests);
        int computedPosition = i - 1; // Adjusted for the skipped head in the original sequence

        int delay = computedPosition - originalPosition;
        if (delay > 0) {
            totalDelay += delay;
            delayedTracks++;
        }
        if (delay > longestDelay) {
            longestDelay = delay;
        }
    }

    double averageDelay = delayedTracks > 0 ? (double)totalDelay / delayedTracks : 0;

    printf("Longest delay compared to FCFS: %d\n", longestDelay);
    printf("Average delay for tracks processed later than under FCFS: %.2f\n", averageDelay);
}

int findPositionInArray(const int *array, int value, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
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
    int diff[numRequests-1][2]; // Array size is numRequests-1 because the head is not included


    for (int i = 0; i < numRequests-1; i++) {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }

    int seekcount = 0;
    int seeksequence[numRequests];
    seeksequence[0] = head;

    for (int i = 0; i < numRequests-1; i++) {
        
        calculatedifference(requestArray+1, head, diff, numRequests-1); // requestArray+1 to skip the head
        int index = findMIN(diff, numRequests-1);
        diff[index][1] = 1;

        // Increase the total count
        seekcount += diff[index][0];

        // Accessed track is now new head
        head = requestArray[index + 1]; // index + 1 to adjust for the skipped head
        seeksequence[i+1] = head;
    }

    // Print the sequence
    printf("Original Sequence: ");
    printArray(requestArray, numRequests);

    printf("Sequence Order: ");
    printArray(seeksequence, numRequests);

    printf("Tracks Traversed: %d\n", numRequests);

    //prints both average and longest delay
    calculateDelays(requestArray, seeksequence, numRequests);

}

//SCAN disk scheduling algorithm
void scan(int *requestArray, size_t numRequests, int startTrack){
    
}