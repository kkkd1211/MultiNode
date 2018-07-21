#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "node.h"

using namespace std;

NODE::NODE()
{
    C=0;
    dC=0;
    dt=0.001;
}
double NODE::regulate(double c,const double para[])
{
    double a=MY_sigmod(para[0],1);
    double k=para[1];
    double M;
    if(a>0.5)
        M=1/a;
    else
        M=1/(1-a);
    double S=MY_sigmod(c-k,M);
    double F=a*S+(1-a)*(1-S);
    dC=dC+F*dt;
}
double NODE::MY_sigmod(double x,double mm)
{
    double tmp;
    tmp=mm*1/(1+exp(-x));
    return tmp;
}

