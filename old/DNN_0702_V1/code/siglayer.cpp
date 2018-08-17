#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "siglayer.h"
#include "NN.h"
using namespace std;

LAYER::LAYER()
{
}
void LAYER::layerInit(int NoN,int pN,int LT)
{
    nodeN=NoN;
    preN=pN;
    layerType=LT;
    int i;
    for(i=0;i<nodeN;i++)
    {
        node[i].nodeInit(preN,layerType);
    }
}
void LAYER::flow(const double I[])
{
    double input[maxNode];
    int i,j;

    for(i=0;i<preN;i++)
    {
        input[i]=I[i];
    }
    for(i=0;i<nodeN;i++)
    {
        node[i].flow(input);
        output[i]=node[i].output;
    }
}//flow();
void LAYER::deriv(const double DO[])
{
    int i,j;
    for(i=0;i<nodeN;i++)
    {
        node[i].deriv(DO[i]);
    }
    for(i=0;i<preN;i++)
    {
        DI[i]=0;
        for(j=0;j<nodeN;j++)
        {
            DI[i]=DI[i]+node[i].DI[j];
        }
    }
}//deriv();
void LAYER::update(double lnRate)
{
    int i;
    for(i=0;i<nodeN;i++)
    {
        node[i].update(lnRate);
    }
}
void LAYER::saveStructure(const char file[])
{
    int i;
    for(i=0;i<nodeN;i++)
        node[i].saveStructure(file);
}
void LAYER::readStructure(FILE *fp)
{
    int i;
    for(i=0;i<nodeN;i++)
        node[i].readStructure(fp);
}


void LAYER::checkGradient(const double input[])
{
    printf("layer check gradient...\n");
    int i;
    for(i=0;i<nodeN;i++)
        node[i].checkGradient(input);
}
