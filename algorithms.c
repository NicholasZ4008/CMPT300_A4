#include "algorithms.h"

/*Helper functions*/
void bubbleSortHelper(int* newArray, size_t numRequests){
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

void printArray(const int *requestArray,const int size){
    for(int i=0;i<size; i++){
        printf("%d ",requestArray[i]);
    }
    printf("\n");
}

int findPositionInArray(const int *array,const int value,const int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}

//Get delays of computed sequence
void calculateDelays(const int *originalSequence, const int *computedSequence, int numRequests) {
    int longestDelay = 0;
    int totalDelay = 0;
    int delayedTracks = 0;

    for (int i = 1; i < numRequests; i++) {
        int originalPosition = findPositionInArray(originalSequence, computedSequence[i], numRequests);
        int computedPosition = i - 1; // Adjusted for the skipped head in the original sequence

        //Add 1 for getting value instead of index
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

/*Disk scheduling implementations*/

//SSTF disk scheduling algorithm
void sstf(int *requestArray, int numRequests){
    printf("SSTF\n");

    // The head is always the first element in the requestArray
    int head = requestArray[0];
    int diff[numRequests-1][2]; // Array size is numRequests-1 because the head is not included

    for (int i = 0; i < numRequests-1; i++) {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }

    int totalSeekCount = 0; // To keep track of the total number of tracks traversed
    int seeksequence[numRequests];
    seeksequence[0] = head;

    for (int i = 0; i < numRequests-1; i++) {
        calculatedifference(requestArray+1, head, diff, numRequests-1); // requestArray+1 to skip the head
        int index = findMIN(diff, numRequests-1);
        diff[index][1] = 1;

        // Here we calculate the absolute distance moved by the head
        int distance = abs(head - requestArray[index + 1]);
        totalSeekCount += distance; // Add the distance to the total seek count

        // Accessed track is now new head
        head = requestArray[index + 1]; // index + 1 to adjust for the skipped head
        seeksequence[i+1] = head;
    }

    // Print the sequence
    printf("Sequence Order: ");
    printArray(seeksequence, numRequests);

    // Print the total number of tracks traversed
    printf("Total number of tracks traversed: %d\n", totalSeekCount);

    // prints both average and longest delay
    calculateDelays(requestArray, seeksequence, numRequests);
}

//SCAN disk scheduling algorithm
void scan(const int *requestArray,const size_t numRequests){
    printf("Scan\n");
    int head = requestArray[0];
    bool isGoingLeft = true;
    int totalNumTracksTraversed = 0;

    int newArray[numRequests]; //Sorted array

    //Counter used for memory safety and have correct size array
    int numLess = 0;
    int numMore = 0;
    //Clone array and get num of values greater than and less than head
    for(int i = 0; i < numRequests;i++){
        if(requestArray[i] < head){
            numLess++;
        }else if (requestArray[i] > head){
            numMore++;
        }
        newArray[i] = requestArray[i];
    }
    
    //Sort array
    bubbleSortHelper(newArray, numRequests);

    //Initialize arrays for greater and less than head
    int arrayLess[numRequests - numMore];
    int arrayMore[numRequests - numLess];
    int less = 0;
    int more = 0;


    //Setup array with values greater and less than head
    for(int i = 0; i < numRequests; i++){
        if(newArray[i] < head){
            arrayLess[less] = newArray[i];
            less++;
        }else if(newArray[i] > head){
            arrayMore[more] = newArray[i];
            more++;
        }
    }

    int processOrder[numRequests]; //Order of actual process
    processOrder[0] = requestArray[0];
    numLess--;
    numMore = 0;


    //Run until theres still a request left
    int j = 1;
    while(j < (numRequests - 1)){

        //Going in decreasing order
        if(isGoingLeft && numLess >= 0){
            while(numLess >= 0){
                processOrder[j] = arrayLess[numLess];
                totalNumTracksTraversed += abs(head - processOrder[j]);
                head = processOrder[j];
                numLess--;
                j++;
            }
            if(head > 0 && head == arrayLess[0] && j != numRequests){
                totalNumTracksTraversed += abs(head - 0);
            }
            head = 0;
            isGoingLeft = false;            

        } else{ //Going in increasing order

            while(more > 0){
                processOrder[j] = arrayMore[numMore];
                totalNumTracksTraversed += abs(head - processOrder[j]);
                head = processOrder[j];
                numMore++; //Update counters
                more--;
                j++;
            }
            //Update track count if head
            if(head < 199 && head == arrayMore[numMore]){
                totalNumTracksTraversed += abs(head - 199);
            }
            //Update direction
            isGoingLeft = true;
            head = MAX_TRACK_NUMBER;
        }
    }

    //Print results
    printf("Sequence Order: ");
    printArray(processOrder, numRequests);
    printf("Total tracks traversed: %d\n", totalNumTracksTraversed);
    calculateDelays(requestArray, processOrder, numRequests);
}