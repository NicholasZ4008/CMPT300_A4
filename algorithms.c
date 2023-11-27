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
// Function declaration for SSTF disk scheduling algorithm
void sstf(int *requestArray, size_t numRequests){

}

// Function declaration for SCAN disk scheduling algorithm
void scan(int *requestArray, size_t numRequests){
    printf("Scan\n");
    int currentIndex = 0;
    int head = requestArray[currentIndex];
    bool isGoingLeft = false;
    if(isGoingLeft){
        printf("Going LEFT first\n\n");
    }else{
        printf("Going RIGHT first\n\n");
    }
    int totalNumTracksTraversed = 0;
    int longestDelay = 0; //Compared to FCFS
    double averageDelay = 0;
    printf("Number of tracks: %ld\n", numRequests);
    printf("Head position: %d\n", head);

    int newArray[numRequests];
    int numLess = 0;
    int numMore = 0;
    for(int i = 0; i<numRequests;i++){
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
    printf("MIN value: %d\n", newArray[0]);
    printf("MAX val: %d\n", newArray[numRequests-1]);
    for(int i = 0; i<numRequests;i++){
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
                head = processOrder[j];
                numLess--;
                j++;
            }
            isGoingLeft = false;
            

        } else{ //Going in increasing order
            while(more > 0){
                processOrder[j] = arrayMore[numMore];
                totalNumTracksTraversed += abs(processOrder[j] - head);
                head = processOrder[j];
                numMore++;
                more--;
                j++;
            }
            isGoingLeft = true;
        }

        //Find distance from head to new value
        // totalNumTracksTraversed += abs(processOrder[j] - head);
    }

    printf("Seek Sequence: \n");
    for (int b = 0; b < numRequests; b++){
        printf("%d ", processOrder[b]);
        if(numRequests > 20){
            if(b % 10 ==0){
                printf("\n");
            }
        }
    }
    printf("\n");

    printf("Total number of tracks traversed: %d\n", totalNumTracksTraversed);
    double avgSeekDistance = (double) totalNumTracksTraversed/numRequests;
    printf("Average number of tracks traversed: %.2f\n", avgSeekDistance);
    // printf("Longest delay (compared to FCFS): %d\n", longestDelay);
}