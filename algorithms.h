#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdlib.h>
#include <stdlib.h>

//assignment declared track number
#define MAX_TRACK_NUMBER 200

//SSTF disk scheduling algorithm
void sstf(int *requestArray, int n);

//SCAN disk scheduling algorithm
void scan(int *requestArray, size_t numRequests, int startTrack);

#endif // ALGORITHM_H
