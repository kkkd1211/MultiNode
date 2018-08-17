#ifndef MN_H
#define MN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>


#include "MIC.h"
#include "EDGE.h"
#include "NODE.h"
using namespace std;


class MNODE;
class MNODE
{
    public:
        MNODE();
        MNODE(int n);
        ~MNODE();
//    private:
        void myInit();


        EDGE **e;
        NODE *n;
        int nodeN;

};
#endif
