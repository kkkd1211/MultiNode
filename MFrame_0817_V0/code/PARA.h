#ifndef PARA_H
#define PARA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>


using namespace std;

class PARA;
class PARA
{
    public:
        PARA();
        ~PARA();

        void init(int n);

        int N;
        double **k;
};



#endif
