#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "sigmoidNode.h"
#include "NN.h"
using namespace std;

sigmoidNode::sigmoidNode()
{
}
void sigmoidNode::nodeInit(int preN,int NT)
{
    NI=preN;
    nodeType=NT;
    int i;
    for(i=0;i<NI;i++)
    {
        k[i]=2*(rand()/2147483647.0)-1;
    }
}
double sigmoidNode::flow(const double I[])
{
    double input[maxNode];
    double s=0;
    int i;
    for(i=0;i<NI;i++)
    {
        input[i]=I[i];
        s=s+k[i]*input[i];
    }
    output=MY_sigmod(s,1.0);

    double dOds=output*(1-output);
    for(i=0;i<NI;i++)
    {
        dOdk[i]=dOds*input[i];
        dOdI[i]=dOds*k[i];
    }
    return(output);
}//flow();
void sigmoidNode::deriv(double DO)
{
    int i;
    for(i=0;i<NI;i++)
    {
        DI[i]=dOdI[i]*DO;
        Dk[i]=dOdk[i]*DO;
    }
}//deriv();
void sigmoidNode::update(double lnRate)
{
    int i;
    for(i=0;i<NI;i++)
    {
        k[i]=k[i]-lnRate*Dk[i];
    }
}
double sigmoidNode::MY_sigmod(double x,double mm)
{
    double tmp;
    tmp=mm*1/(1+exp(-x));
    return tmp;
}

void sigmoidNode::saveStructure(const char file[])
{
    int i;
    FILE *fp;
    fp=fopen(file,"a");
    for(i=0;i<NI;i++)
    {
        fprintf(fp,"%f\t",k[i]);
    }
    fprintf(fp,"\n");
    fclose(fp);
}
void sigmoidNode::readStructure(FILE *fp)
{
    int i;
    for(i=0;i<NI;i++)
    {
        fscanf(fp,"%lf\t",&k[i]);
    }
    fscanf(fp,"\n");
}

void sigmoidNode::checkGradient(const double II[])
{
    printf("node checking...\n");
    int i;
    double V0,V,input[maxNode];
    for(i=0;i<NI;i++)
        input[i]=II[i];
    V0=flow(input);
    printf("dO/dk:\n");
    for(i=0;i<NI;i++)
    {
        printf("%.10f\t",dOdk[i]);
    }
    printf("\n");
    for(i=0;i<NI;i++)
    {
        k[i]=k[i]+k_epsilon2;
        V=flow(input);
        printf("%.10f\t",(V-V0)/k_epsilon2);
        k[i]=k[i]-k_epsilon2;
    }
    printf("\n");
    printf("dO/dI:\n");
    for(i=0;i<NI;i++)
    {
        printf("%.10f\t",dOdI[i]);
    }
    printf("\n");
    for(i=0;i<NI;i++)
    {
        input[i]=input[i]+k_epsilon2;
        V=flow(input);
        printf("%.10f\t",(V-V0)/k_epsilon2);
        input[i]=input[i]-k_epsilon2;
    }
    printf("\n");
}//checkGrandient

