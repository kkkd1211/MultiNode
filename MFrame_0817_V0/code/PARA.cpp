#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "PARA.h"

using namespace std;

PARA::PARA()
{

}
PARA::~PARA()
{
    printf("dest PARA\n");
    int i;
    for(i=0;i<N;i++)
    {
        delete [] k[i];
    }
    delete [] k;
}
void PARA::init(int n)
{
    N=n;
    k=new double*[N];
    int i,j;
    for(i=0;i<N;i++)
    {
        k[i]=new double[N];
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            k[i][j]=0;
        }
    }

}
