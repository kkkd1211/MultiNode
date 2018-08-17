#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "NN.h"


using namespace std;

NN::NN()
{
}
void NN::NNInit()
{
    L[0].layerInit(20,TFNO,0);
    L[1].layerInit(20,20,0);
    L[NHL-1].layerInit(4,20,0);
}
void NN::flow(const double I[])
{
    int i;
    L[0].flow(I);
    for(i=1;i<NHL;i++)
    {
        L[i].flow(L[i-1].output);
    }
    for(i=0;i<4;i++)
    {
        output[i]=L[NHL-1].output[i]-0.6*I[i];
    }
}
void NN::deriv(const double DO[])
{
    L[NHL-1].deriv(DO);
    int i;
    for(i=NHL-2;i>=0;i--)
    {
        L[i].deriv(L[i+1].DI);
    }
}
void NN::update(double lnRate)
{
    int i;
    for(i=0;i<NHL;i++)
    {
        L[i].update(lnRate);
    }
}
void NN::yieldNetworkProfile(int initMethod,const char type[],int dataNO)
{
    int i,j,k,t,x;
    double profile[Nt][Nx][8];
    double input[maxNode];
    double disErr=0;
    for(i=0;i<Nt;i++)
    {
        for(j=0;j<Nx;j++)
        {
            for(k=4;k<8;k++)
                profile[i][j][k]=dataset[i][j][k];
            for(k=0;k<4;k++)
                profile[i][j][k]=0;
        }
    }
    if(initMethod==1)
    {
        for(i=0;i<Nx;i++)
        {
            for(j=0;j<4;j++)
                profile[0][i][j]=dataset[0][i][j];
        }
    }
    for(i=1;i<Nt;i++)
    {
        for(j=0;j<Nx;j++)
        {
            for(k=0;k<8;k++)
            {
                input[k]=profile[i-1][j][k];
            }
            flow(input);
            for(k=0;k<4;k++)
            {
                profile[i][j][k]=profile[i-1][j][k]+L[NHL-1].output[k];
                disErr=disErr+(profile[i][j][k]-dataset[i][j][k])*(profile[i][j][k]-dataset[i][j][k]);
            }
        }
    }
    FILE *fp;
    char expressFileN[50];
    char expressFolderN[50];
    char errorFile[50];
    sprintf(expressFolderN,"singleExpression/%s",type);
    if(access(expressFolderN,0)!=0)
        mkdir(expressFolderN,0777);
    sprintf(expressFolderN,"singleExpression/%s/%d",type,dataNO);
    if(access(expressFolderN,0)!=0)
        mkdir(expressFolderN,0777);
    sprintf(errorFile,"singleExpression/Err%s.txt",type);
    fp=fopen(errorFile,"a");
    fprintf(fp,"%d\t%f\n",dataNO,disErr);
    fclose(fp);
    for(i=0;i<4;i++)
    {
        sprintf(expressFileN,"%s/gene%d_P.txt",expressFolderN,i);
        fp=fopen(expressFileN,"w");
        for(x=0;x<Nx;x++)
        {
            for(t=0;t<Nt;t++)
            {
                fprintf(fp,"%f\t",profile[t][x][i]);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
    }
}
void NN::training(int stepMax)
{
    printf("trainning...\n");
    double lnRate=0.5;
    double DlnRate=0.49/stepMax;
    int step;
    int i,t,x;
    double IN[TFNO];
    double tgV[4];
    double DO[4];
    double test;
    for(step=0;step<stepMax;step++)
    {
        t=(int)(Nt*(rand()/2147483647.0))-1;
        x=(int)(Nx*(rand()/2147483647.0));
        for(i=0;i<TFNO;i++)
            IN[i]=dataset[t][x][i];
        for(i=0;i<4;i++)
            tgV[i]=dataset[t+1][x][i]-dataset[t][x][i];
        flow(IN);
        test=0;
        for(i=0;i<4;i++)
        {
            output[i]=L[NHL-1].output[i];
            DO[i]=output[i]-tgV[i];
            test=test+DO[i];
        }
        if(test!=test)
        {
            printf("test!=test...\n");
            break;
        }
        deriv(DO);
        update(lnRate);
        lnRate-=DlnRate;
    }
///    printf("%d\t%d\t%f\n",t,x,dataset[t][x][0]);
///    printf("%f\t%f\t%f\t%f\n\n",IN[0],IN[1],IN[2],IN[3]);
    for(i=0;i<NHL;i++)
        L[i].checkGradient(IN);

    printf("trainning...done!\n");
    //network.checkGradient(IN,c0l,c0,c0r,c0d);
}//training
void NN::readData(const char type[2])
{
printf("reading %s...",type);
    char filekni[50];
    char filehb[50];
    char filekr[50];
    char filegt[50];
    char filebcd[50];
    char filecad[50];
    char filetll[50];
    char filetsl[50];
    sprintf(filekni,"data/%s/kni.txt",type);
    sprintf(filehb,"data/%s/hb.txt",type);
    sprintf(filekr,"data/%s/kr.txt",type);
    sprintf(filegt,"data/%s/gt.txt",type);
    sprintf(filebcd,"data/%s/bcd.txt",type);
    sprintf(filecad,"data/%s/cad.txt",type);
    sprintf(filetll,"data/%s/tll.txt",type);
    sprintf(filetsl,"data/%s/tsl.txt",type);
    FILE *fkni,*fhb,*fkr,*fgt,*fbcd,*fcad,*ftll,*ftsl;
    fkni=fopen(filekni,"r");
    fhb=fopen(filehb,"r");
    fkr=fopen(filekr,"r");
    fgt=fopen(filegt,"r");
    fbcd=fopen(filebcd,"r");
    fcad=fopen(filecad,"r");
    ftll=fopen(filetll,"r");
    ftsl=fopen(filetsl,"r");
    int i,j;
    for(i=0;i<Nt;i++)
    {
        for(j=0;j<Nx;j++)
        {
            fscanf(fkni,"%lf ",&dataset[i][j][0]);
            fscanf(fhb,"%lf ",&dataset[i][j][1]);
            fscanf(fkr,"%lf ",&dataset[i][j][2]);
            fscanf(fgt,"%lf ",&dataset[i][j][3]);
            fscanf(fbcd,"%lf ",&dataset[i][j][4]);
            fscanf(fcad,"%lf ",&dataset[i][j][5]);
            fscanf(ftll,"%lf ",&dataset[i][j][6]);
            fscanf(ftsl,"%lf ",&dataset[i][j][7]);
        }
    }
    fclose(fkni);
    fclose(fhb);
    fclose(fkr);
    fclose(fgt);
    fclose(fbcd);
    fclose(fcad);
    fclose(ftll);
    fclose(ftsl);
printf("done!\n");
}//readData
void NN::saveStructure(const char type[2],int gapGene,int dataNO)
{
    FILE *fp;
    char strucFileN[50];
    char strucFolderN[50];
    sprintf(strucFolderN,"singleStructure/%s",type);
    if(access(strucFolderN,0)!=0)
        mkdir(strucFolderN,0777);
    sprintf(strucFolderN,"singleStructure/%s/gap%d",type,gapGene);
    if(access(strucFolderN,0)!=0)
        mkdir(strucFolderN,0777);
    sprintf(strucFileN,"%s/struct%d.txt",strucFolderN,dataNO);
    fp=fopen(strucFileN,"w");
    fclose(fp);
    int i;
    for(i=0;i<NHL;i++)
        L[i].saveStructure(strucFileN);
}
void NN::readStructure(const char file[])
{
    FILE *fp;
    fp=fopen(file,"r");
    int i;
    for(i=0;i<NHL;i++)
        L[i].readStructure(fp);
    fclose(fp);
}





