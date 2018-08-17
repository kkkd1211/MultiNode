#ifndef SIGNODE
#define SIGNODE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#define maxNode 20
//#include "NN.h"

using namespace std;
class sigmoidNode;
class sigmoidNode
{
    public:
        sigmoidNode();
        void nodeInit(int preN,int NT);
        double flow(const double I[]);
        void deriv(double DO);
        void update(double lnRate);
        void saveStructure(const char file[]);
        void readStructure(FILE *fp);
        void checkGradient(const double II[]);

        double output;
        double dOdI[maxNode];
        double DI[maxNode];

    private:
        int NI;
        int nodeType;
        double k[maxNode];
        double dOdk[maxNode];
        double Dk[maxNode];

        double MY_sigmod(double x,double mm);
};

#endif//
