#ifndef MN_H
#define MN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>


#include "MIC.h"
#include "edge.h"
#include "node.h"
using namespace std;


class mNode;
class mNode
{
    public:
        mNode();
    private:
        EDGE e[maxNodeN][maxNodeN];
        NODE n[maxNodeN];
        int nodeN;

}
#endif
