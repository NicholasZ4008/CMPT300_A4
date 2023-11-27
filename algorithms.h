#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdlib.h> // For size_t
#include <stdio.h>
#include <stdbool.h>

// Define any necessary constants
// For example, the maximum track number if needed
#define MAX_TRACK_NUMBER 200

// Function declaration for SSTF disk scheduling algorithm
void sstf(int *requestArray, size_t numRequests);

// Function declaration for SCAN disk scheduling algorithm
void scan(int *requestArray, size_t numRequests);

#endif // ALGORITHM_H
