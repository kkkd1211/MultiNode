#ifndef PARA_H
#define PARA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "MIC.h"
using namespace std;

class PARA;
class PARA
{
    public:
        PARA();
        ~PARA();

        void init(int n);
        void copyPara(PARA *P);


        int N;
        double **k;
        double **dk;
        double **a;
        double **da;
        double **A;
        double **dA;
        double *b;
        double *db;
        double *c;
        double *dc;


};



#endif
