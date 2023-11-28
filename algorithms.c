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
void scan(int *requestArray, size_t numRequests){
    printf("Scan\n");
    int currentIndex = 0;
    int head = requestArray[currentIndex];
    bool isGoingLeft = false;

    int totalNumTracksTraversed = 0;
    int longestDelay = 0; //Compared to FCFS
    int delaySum = 0;
    int numDelayedTracks = 0;
    printf("Number of tracks: %ld\n", numRequests);
    printf("Head position: %d\n", head);

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

    int j = 1;

    //Run until theres still a request left
    while(j < numRequests){

        //Going in decreasing order
        if(isGoingLeft){
            //If current value less than head
            while(numLess >= 0){
                processOrder[j] = arrayLess[numLess];
                totalNumTracksTraversed += abs(processOrder[j] - head);

                int fcfsIndex = j - numLess;
                if(fcfsIndex > 0){
                    int fcfsDelay = abs(fcfsIndex - head);
                    delaySum += fcfsDelay;
                    numDelayedTracks++;
                }


                head = processOrder[j];
                numLess--;
                j++;
            }
            isGoingLeft = false;
            

        } else{ //Going in increasing order
            while(more > 0){
                processOrder[j] = arrayMore[numMore];
                totalNumTracksTraversed += abs(processOrder[j] - head);

                int fcfsIndex = j - numLess;
                if(fcfsIndex > 0){
                    int fcfsDelay = abs(fcfsIndex - head);
                    delaySum += fcfsDelay;
                    numDelayedTracks++;
                }

                head = processOrder[j];
                numMore++;
                more--;
                j++;
            }
            isGoingLeft = true;
        }
    }

    printf("Seek Sequence: \n");
    for (int b = 0; b < numRequests; b++){
        printf("%d ", processOrder[b]);
        if(numRequests > 20){
            if(b % 10 == 0){
                printf("\n");
            }
        }
    }
    printf("\n\n");

    printf("Total number of tracks traversed: %d\n", totalNumTracksTraversed);
    double avgSeekDistance = (double) totalNumTracksTraversed/numRequests;
    printf("Average number of tracks traversed: %.2f\n", avgSeekDistance);
    double avgDelay = numDelayedTracks > 0 ? (double) delaySum / numDelayedTracks : 0;
    printf("Avd delay track: %f\n", avgDelay);
    printf("Longest delay (compared to FCFS): %d\n", longestDelay);
}