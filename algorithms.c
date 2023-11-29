#include "algorithms.h"

/*Helper functions*/
void bubbleSortHelper(size_t numRequests,int* newArray){
    for(int i = 0; i < numRequests - 1; i++){
        for(int j = 0; j < numRequests - i - 1; j++){
            if(newArray[j] > newArray[j+1]){
                int temp = newArray[j];
                newArray[j] = newArray[j+1];
                newArray[j+1] = temp;
            }
        }
    }
}
void printArray(int *requestArray, int size){
    for(int i=0;i<size; i++){
        printf("%d ",requestArray[i]);
    }
    printf("\n");
}

int findPositionInArray(const int *array, int value, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}

void calculateDelays(const int *originalSequence, const int *computedSequence, int numRequests) {
    int longestDelay = 0;
    int totalDelay = 0;
    int delayedTracks = 0;

    for (int i = 1; i < numRequests; i++) {
        int originalPosition = findPositionInArray(originalSequence, computedSequence[i], numRequests);
        int computedPosition = i - 1; // Adjusted for the skipped head in the original sequence

        int delay = (computedPosition - originalPosition) + 1;
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
    printf("Total Delay: %d\n", totalDelay);
    printf("Delayed Tracks: %d\n", delayedTracks);
    printf("Average delay for tracks processed later than under FCFS: %.2f\n", averageDelay);
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
    printf("SSTF\n");
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
    printf("Sequence Order: ");
    printArray(seeksequence, numRequests);

    //prints both average and longest delay
    calculateDelays(requestArray, seeksequence, numRequests);

}

//SCAN disk scheduling algorithm
void scan(int *requestArray, size_t numRequests){
    printf("Scan\n");
    int currentIndex = 0;
    int head = requestArray[currentIndex];
    bool isGoingLeft = true;

    int totalNumTracksTraversed = 0;
    int longestDelay = 0; //Compared to FCFS
    int numDelayedTracks = 0;

    int newArray[numRequests];
    int numLess = 0;
    int numMore = 0;
    for(int i = 0; i < numRequests;i++){
        if(requestArray[i] < head){
            numLess++;
        }else{
            numMore++;
        }
        newArray[i] = requestArray[i];
    }

    int arrayLess[numRequests - numMore];
    int arrayMore[numRequests - numLess];
    int less = 0;
    int more = 0;
    //Sort array
    bubbleSortHelper(numRequests, newArray);

    for(int i = 0; i < numRequests;i++){
        if(newArray[i] <= head){
            arrayLess[less] = newArray[i];
            less++;
        }else{
            arrayMore[more] = newArray[i];
            more++;
        }
    }

    int processOrder[numRequests];
    processOrder[0] = requestArray[0];
    numMore = 0;
    numLess--;


    //Run until theres still a request left
    int j = 1;
    while(j < numRequests){

        //Going in decreasing order
        if(isGoingLeft){
            if(numLess >= 0){
                printf("Add less: %d\n", abs(head - 0));
                totalNumTracksTraversed += abs(head - 0);
            }
            while(numLess >= 0){
                processOrder[j] = arrayLess[numLess];
                // totalNumTracksTraversed += abs(processOrder[j] - head);

                head = processOrder[j];
                numLess--;
                j++;
            }
            head = 0;
            isGoingLeft = false;            

        } else{ //Going in increasing order

            if(more > 0){
                printf("Add more: %d\n", abs(head - 199));
                totalNumTracksTraversed += abs(head - 199);
            }
            while(more > 0){
                processOrder[j] = arrayMore[numMore];
                // totalNumTracksTraversed += abs(processOrder[j] - head);

                head = processOrder[j];
                numMore++;
                more--;
                j++;
            }
            // if(head != 199 && more <= 0){
            //     totalNumTracksTraversed += abs(199 - head);
            // }
            isGoingLeft = true;
            head = MAX_TRACK_NUMBER;
        }
    }
    printf("Sequence Order: ");
    printArray(processOrder, numRequests);
    printf("Total tracks traversed: %d\n", totalNumTracksTraversed);
    calculateDelays(requestArray, processOrder, numRequests);
}