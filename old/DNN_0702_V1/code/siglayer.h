#ifndef SIGLAYER
#define SIGLAYER

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include "sigmoidNode.h"
using namespace std;
class LAYER;
class LAYER
{
    public:
        LAYER();
        void layerInit(int NoN,int pN,int LT);
        void flow(const double I[]);
        void deriv(const double DO[]);
        void update(double lnRate);
        void saveStructure(const char file[]);
        void readStructure(FILE *fp);
        void checkGradient(const double input[]);

        double output[maxNode];
        double DI[maxNode];

    private:
        int nodeN;
        int preN;
        int layerType;


        sigmoidNode node[maxNode];

};

#endif//
