#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "FRAME.h"

using namespace std;

FRAME::FRAME()
{

}
FRAME::~FRAME()
{
    printf("dest FRAME\n");
    delete parameter;
}
void FRAME::init(int N)
{
    parameter=new PARA();
    parameter->init(N);
    complexity=N;
    loss=-1;
}
void FRAME::copyFrame(FRAME *F)
{
    complexity = F->complexity;
    loss = F->loss;
    int i,j;
    parameter=new PARA();
    parameter->init(complexity);
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            parameter->k[i][j]=F->parameter->k[i][j];
        }
    }
}
void FRAME::complexUp()
{
    complexity++;
    PARA *P = new PARA();
    P->init(complexity);
    int i,j;
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            if((i==complexity-1)||(j==complexity))
            {
                P->k[i][j]=myRand();
            }
            else
            {
                P->k[i][j]=parameter->k[i][j];
            }
        }
    }
    delete parameter;
    parameter=P;
}
double FRAME::myRand()
{
    return 0;
}
