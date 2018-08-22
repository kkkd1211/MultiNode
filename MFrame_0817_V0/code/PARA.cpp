#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "PARA.h"
#include "MIC.h"

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
        delete [] dk[i];
        delete [] a[i];
        delete [] da[i];
        delete [] A[i];
        delete [] dA[i];
    }
    delete [] k;
    delete [] dk;
    delete [] a;
    delete [] da;
    delete [] A;
    delete [] dA;
    delete [] b;
    delete [] db;
    delete [] c;
    delete [] dc;
}
void PARA::init(int n)
{
    N=n;
    k=new double*[N];
    dk=new double*[N];
    a=new double*[N];
    da=new double*[N];
    A=new double*[N];
    dA=new double*[N];
    b=new double[N];
    db=new double[N];
    c=new double[N];
    dc=new double[N];
    int i,j;
    for(i=0;i<N;i++)
    {
        k[i]=new double[N];
        dk[i]=new double[N];
        a[i]=new double[N];
        da[i]=new double[N];
        A[i]=new double[N];
        dA[i]=new double[N];
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            k[i][j]=myRand(0,1);
            dk[i][j]=0;
            a[i][j]=myRand(-0.5,0.5);
            da[i][j]=0;
            A[i][j]=myRand(-0.5,0.5);
            dA[i][j]=0;
        }
        b[i]=myRand(-0.5,0.5);
        db[i]=0;
        c[i]=myRand(-0.5,0.5);
        dc[i]=0;
    }

}
void PARA::copyPara(PARA *P)
{
    int i,j;
    N=P->N;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            k[i][j]=P->k[i][j];
            dk[i][j]=P->dk[i][j];
            a[i][j]=P->a[i][j];
            da[i][j]=P->da[i][j];
            A[i][j]=P->A[i][j];
            dA[i][j]=P->dA[i][j];
        }
        b[i]=P->b[i];
        db[i]=P->db[i];
        c[i]=P->c[i];
        dc[i]=P->dc[i];
    }
}


