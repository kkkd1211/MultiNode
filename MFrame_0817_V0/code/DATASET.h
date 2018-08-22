#ifndef DATASET_H
#define DATASET_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "MIC.h"
using namespace std;

class DATASET;
class DATASET
{
    public:
        double wt[kTF][DNt][DNx];
        double bp[kTF][DNt][DNx];
        double bm[kTF][DNt][DNx];
        double np[kTF][DNt][DNx];
        double nm[kTF][DNt][DNx];
        double tm[kTF][DNt][DNx];

        void loadData();
};



#endif
