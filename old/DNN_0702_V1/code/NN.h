#ifndef NNClass
#define NNClass
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>



#define TFNO 7
#define NHL 3

#include "siglayer.h"


#define Nx 100
#define Nt 55
#define k_epsilon 0.000001
#define k_epsilon2 0.0000000001
#define kkk printf("kkk!!!\n");
#define kkk2 printf("kkk2!!!\n");
using namespace std;

class NN;
class NN
{
    public:
        NN();
        void NNInit();
        void flow(const double I[]);
        void deriv(const double DO[]);
        void update(double lnRate);
        void readData(const char type[2]);
        void training(int step);
        void yieldNetworkProfile(int initMethod,const char type[],int dataNO);
        void saveStructure(const char type[2],int gapGene,int dataNO);
        void readStructure(const char file[]);
    private:
        LAYER L[NHL];
        double output[4];

        double dataset[Nt][Nx][8];
};
#endif


