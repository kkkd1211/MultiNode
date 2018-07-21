#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "MIC.h"
using namespace std;

class NODE;
class NODE
{
    public:
        NODE();
        double regulate(double c,const double para[]);
        int type;
        double C;

    private:
        double dC;
        double dt;
        double MY_sigmod(double x,double mm);
}


#endif
