#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "DATASET.h"
#include "MIC.h"

using namespace std;

void DATASET::loadData()
{
    double tmp;
    FILE *fp[kTF];
    int i,j,m;
    fp[0]=fopen("data/wt/bcd.txt","r");
    fp[1]=fopen("data/wt/cad.txt","r");
    fp[2]=fopen("data/wt/tll.txt","r");
    fp[3]=fopen("data/wt/hb.txt","r");
   /// fp[4]=fopen("data/wt/hb.txt","r");
   /// fp[5]=fopen("data/wt/kr.txt","r");
   /// fp[6]=fopen("data/wt/gt.txt","r");

    for(i=0;i<kTF;i++)
    {
        for(j=0;j<DNt;j++)
        {
            for(m=0;m<DNx;m++)
            {
                tmp=fscanf(fp[i],"%lf\t",&wt[i][j][m]);
            }
            tmp=fscanf(fp[i],"\n");
        }
        fclose(fp[i]);
    }
}
