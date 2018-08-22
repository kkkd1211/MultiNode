#ifndef FRAME_H
#define FRAME_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "PARA.h"
#include "DATASET.h"
#include "MIC.h"
using namespace std;

class FRAME;
class FRAME
{
    public:
        FRAME();
        ~FRAME();

        void init(int N);
        void copyFrame(FRAME *F);
        void complexUp();
        double optimization(DATASET condataset,int muType,int nTarget);
        void saveProfile(int nTarget);
        void nextStep();
        void loadDataSet(double (*conData)[kTF][DNt][DNx]);
        double evaluate(double conData[kTF][DNt][DNx],int nTarget);

        PARA *parameter;
        double **initConcentration;
        double **concentration;
        double **dConcentration;
        int isChangable[kTF];
        int complexity;
        double loss;

        FRAME *NF;
        FRAME *LF;

        double mySigmoid(double x);
};



#endif
