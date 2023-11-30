#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdlib.h> // For size_t
#include <stdio.h>
#include <stdbool.h>

// Define any necessary constants
// For example, the maximum track number if needed
#define MAX_TRACK_NUMBER 200

//SSTF disk scheduling algorithm
void sstf(int *requestArray, int n);

// Function declaration for SCAN disk scheduling algorithm
void scan(const int *requestArray,const size_t numRequests);
void printArray(const int *requestArray,const int size);

#endif // ALGORITHM_H
