#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sigmoidNode.h"
#include "NN.h"
#include "siglayer.h"

using namespace std;
double MY_pow(double x,int n);
int main(int argc,char *argv[])
{
    char type[3];
    int dataNO;
    int ErrMax;
    sscanf(argv[1],"%c%c",&type[0],&type[1]);
    type[2]='\0';
    sscanf(argv[2],"%d",&dataNO);
    sscanf(argv[3],"%d",&ErrMax);
    srand((unsigned)((unsigned)time(NULL)*(1+dataNO)+dataNO));
    if(access("singleExpression",0)!=0)
        mkdir("singleExpression",0777);
    if(access("singleStructure",0)!=0)
        mkdir("singleStructure",0777);
    NN VNN;
    VNN.NNInit();
    VNN.readData(type);
    //VNN.yieldNetworkProfile("kni_14_24.txt","hb_15_26.txt");
    //VNN.setTargetGene(gapGene);
    //VNN.readStructure("struct.txt");
    VNN.training(100000000);
    VNN.yieldNetworkProfile(1,type,dataNO);
    dataNO=dataNO*-1;
    VNN.yieldNetworkProfile(0,type,dataNO);
    //crit=VNN.yieldProfile(type,gapGene,dataNO,ErrMax);
    //if(crit!=-1)
    //    VNN.saveStructure(type,gapGene,dataNO);
    return 0;
}
