#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "FRAME.h"
#include "MIC.h"
using namespace std;

FRAME::FRAME()
{
    NF=NULL;
    LF=NULL;
    parameter=NULL;
}
FRAME::~FRAME()
{
    int i;
    printf("dest FRAME\n");
    delete parameter;
    for(i=0;i<complexity;i++)
    {
        delete [] concentration[i];
        delete [] initConcentration[i];
        delete [] dConcentration[i];
    }
    delete [] concentration;
    delete [] initConcentration;
    delete [] dConcentration;
    delete NF;

}
void FRAME::init(int N)
{
    int i,j;
    complexity=N;
    parameter=new PARA();
    parameter->init(complexity);
    loss=-1;
    concentration=new double*[complexity];
    initConcentration=new double*[complexity];
    dConcentration=new double*[complexity];
    for(i=0;i<complexity;i++)
    {
        concentration[i]=new double[Nx];
        initConcentration[i]=new double[Nx];
        dConcentration[i]=new double[Nx];

    }
    for(i=0;i<3;i++)
        isChangable[i]=0;
    for(i=3;i<kTF;i++)
        isChangable[i]=1;

    FILE *fp;
    fp=fopen("tmp_para_init.txt","w");
    fprintf(fp,"k:\n");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            fprintf(fp,"%f\t",parameter->k[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"a\n");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            fprintf(fp,"%f\t",parameter->a[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"A\n");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            fprintf(fp,"%f\t",parameter->A[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"b:\n");
    for(i=0;i<complexity;i++)
        fprintf(fp,"%f\t",parameter->b[i]);
    fprintf(fp,"\nc\n");
    for(i=0;i<complexity;i++)
        fprintf(fp,"%f\t",parameter->c[i]);
    fprintf(fp,"\n");
    fclose(fp);
}
void FRAME::copyFrame(FRAME *F)
{
    int i,j;
    complexity = F->complexity;
    init(complexity);
    loss = F->loss;
    parameter->copyPara(F->parameter);
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<Nx;j++)
        {
            initConcentration[i][j]=F->initConcentration[i][j];
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
            if((i==complexity-1)||(j==complexity-1))
            {
                P->k[i][j]=myRand(0,1);
                P->a[i][j]=myRand(-0.5,0.5);
                P->A[i][j]=myRand(-0.5,0.5);
            }
            else
            {
                P->k[i][j]=parameter->k[i][j];
                P->a[i][j]=parameter->a[i][j];
                P->A[i][j]=parameter->A[i][j];
            }
        }
        if(i==complexity-1)
        {
            P->b[i]=myRand(-0.5,0.5);
            P->c[i]=myRand(-0.5,0.5);
        }
        else
        {
            P->b[i]=parameter->b[i];
            P->c[i]=parameter->c[i];
        }
    }
    delete parameter;
    parameter=P;

    for(i=0;i<complexity-1;i++)
    {
        delete [] concentration[i];
        delete [] initConcentration[i];
        delete [] dConcentration[i];
    }
    delete [] concentration;
    delete [] initConcentration;
    delete [] dConcentration;

    concentration=new double*[complexity];
    initConcentration=new double*[complexity];
    dConcentration=new double*[complexity];
    for(i=0;i<complexity;i++)
    {
        concentration[i]=new double[Nx];
        initConcentration[i]=new double[Nx];
        dConcentration[i]=new double[Nx];

    }
}
void FRAME::nextStep()
{
    int i,j,m,n;
    double S,F,a,b,c,A;
    double **k=parameter->k;
    for(i=0;i<complexity;i++)
    {
        if(i<kTF)
        {
            if(isChangable[i]==0)
                continue;
        }
        for(j=0;j<Nx;j++)
        {
            dConcentration[i][j]=0;
            for(m=0;m<complexity;m++)
            {
                S=mySigmoid(concentration[m][j]-parameter->k[m][i]);
                a=5*mySigmoid(parameter->a[m][i]);
                ///A=mySigmoid(parameter->A[m][i]);
                F=a*S+(1-a)*(1-S)-(1-a);
                ///F=A*F;
                dConcentration[i][j]=dConcentration[i][j]+F;
            }
            b=0.1*mySigmoid(parameter->b[i]);
            c=0.1*mySigmoid(parameter->c[i]);
            dConcentration[i][j]=dConcentration[i][j]-b*concentration[i][j]+c;
            dConcentration[i][j]=dConcentration[i][j]*dt;
            ///diffision
        }
    }
    for(i=0;i<complexity;i++)
    {
        if(i<kTF)
        {
            if(isChangable[i]==0)
                continue;
        }
        for(j=0;j<Nx;j++)
        {
            concentration[i][j]=concentration[i][j]+dConcentration[i][j];
        }
    }

}
void FRAME::loadDataSet(double (*conData)[kTF][DNt][DNx])
{
    int i,j,m;
    double *q;
    q=new double[kTF];
    for(i=0;i<kTF;i++)
    {
        for(j=0;j<DNx;j++)
        {
            initConcentration[i][j]=(*conData)[i][0][j];
        }
    }
    if(complexity>kTF)
    {
        for(i=kTF;i<complexity;i++)
        {
            for(j=0;j<kTF;j++)
                q[j]=myRand(0,0.1);
            for(j=0;j<Nx;j++)
            {
                initConcentration[i][j]=0;
                for(m=0;m<kTF;m++)
                {
                    initConcentration[i][j]=initConcentration[i][j]+q[m]*initConcentration[m][j]/kTF;
                }
            }
        }
    }
    delete [] q;
}
double FRAME::optimization(DATASET condataset,int muType,int nTarget)
{
    printf("optimization in process (complexity=%d,nTarget=%d):\n",complexity,nTarget);
    double (*conData)[kTF][DNt][DNx];
    conData=&(condataset.wt);
    loadDataSet(conData);
    int i,j,oStep;
    double L0,L;
    double delta,lnRate;
    delta=0.001;
    lnRate=0.01;
///    for(i=0;i<complexity;i++)
///    {
///        for(j=0;j<Nx;j++)
///        {
///            concentration[i][j]=initConcentration[i][j];
///        }
///    }
    L0=evaluate(*conData,nTarget);
    L=evaluate(*conData,nTarget);
///    printf("L0:%f\t\ta33:%f\n",L0,parameter->a[3][3]);
    for(oStep=0;oStep<nopti;oStep++)
    {
        for(i=0;i<complexity;i++)
        {
            if(i<kTF)
            {
                if(isChangable[i]==0)
                    continue;
            }
            for(j=0;j<complexity;j++)
            {
                parameter->k[j][i]=parameter->k[j][i]+delta;
                L=evaluate(*conData,nTarget);
                parameter->k[j][i]=parameter->k[j][i]-delta;
                parameter->dk[j][i]=lnRate*(L-L0)/delta;

                parameter->a[j][i]=parameter->a[j][i]+delta;
                L=evaluate(*conData,nTarget);
///        if((i==3)&&(j==3))
///            printf("\tL33:%f\n",L);
                parameter->a[j][i]=parameter->a[j][i]-delta;
                parameter->da[j][i]=lnRate*(L-L0)/delta;

                parameter->A[j][i]=parameter->A[j][i]+delta;
                L=evaluate(*conData,nTarget);
                parameter->A[j][i]=parameter->A[j][i]-delta;
                parameter->dA[j][i]=lnRate*(L-L0)/delta;
            }
            parameter->b[i]=parameter->b[i]+delta;
            L=evaluate(*conData,nTarget);
            parameter->b[i]=parameter->b[i]-delta;
            parameter->db[i]=lnRate*(L-L0)/delta;
            parameter->c[i]=parameter->c[i]+delta;
            L=evaluate(*conData,nTarget);
            parameter->c[i]=parameter->c[i]-delta;
            parameter->dc[i]=lnRate*(L-L0)/delta;
        }
        for(i=0;i<complexity;i++)
        {
            if(i<kTF)
            {
                if(isChangable[i]==0)
                    continue;
            }
            for(j=0;j<complexity;j++)
            {
                parameter->k[j][i]=parameter->k[j][i]-parameter->dk[j][i];
                parameter->a[j][i]=parameter->a[j][i]-parameter->da[j][i];
                parameter->A[j][i]=parameter->A[j][i]-parameter->dA[j][i];
            }
            parameter->b[i]=parameter->b[i]-parameter->db[i];
            parameter->c[i]=parameter->c[i]-parameter->dc[i];
        }
        L0=evaluate(*conData,nTarget);
        loss=L0;
///        printf("%d:loss:%f\t\ta33:%f\n",oStep,loss,parameter->a[3][3]);
    }

}
double FRAME::evaluate(double conData[kTF][DNt][DNx],int nTarget)
{
    int tStep;
    int i,j,m;
    double lossV=0;
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<Nx;j++)
        {
            concentration[i][j]=initConcentration[i][j];
        }
    }
    for(m=0;m<nTarget;m++)
    {
        for(tStep=0;tStep<ndt;tStep++)
        {
            nextStep();
        }
        for(i=0;i<kTF;i++)
        {
            for(j=0;j<Nx;j++)
            {
                lossV=lossV+(concentration[i][j]-conData[i][m+1][j])*(concentration[i][j]-conData[i][m+1][j]);
            }
        }
    }

    return lossV;
}
void FRAME::saveProfile(int nTarget)
{
    int tStep;
    int i,j,m;
    FILE *fp;
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<Nx;j++)
        {
            concentration[i][j]=initConcentration[i][j];
        }
    }
    for(m=0;m<nTarget;m++)
    {
        for(tStep=0;tStep<ndt;tStep++)
        {
            nextStep();
        }
    }


    fp=fopen("tmp.txt","w");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<Nx;j++)
        {
            fprintf(fp,"%f\t",concentration[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);

    fp=fopen("tmp_ini.txt","w");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<Nx;j++)
        {
            fprintf(fp,"%f\t",initConcentration[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);

    fp=fopen("tmp_para.txt","w");
    fprintf(fp,"k:\n");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            fprintf(fp,"%f\t",parameter->k[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"a\n");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            fprintf(fp,"%f\t",parameter->a[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"A\n");
    for(i=0;i<complexity;i++)
    {
        for(j=0;j<complexity;j++)
        {
            fprintf(fp,"%f\t",parameter->A[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"b:\n");
    for(i=0;i<complexity;i++)
        fprintf(fp,"%f\t",parameter->b[i]);
    fprintf(fp,"\nc\n");
    for(i=0;i<complexity;i++)
        fprintf(fp,"%f\t",parameter->c[i]);
    fprintf(fp,"\n");
    fclose(fp);
}
double FRAME::mySigmoid(double x)
{
    return(1/(1+exp(-x)));
}
