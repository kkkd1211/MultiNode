#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "MN.h"

using namespace std;

MNODE::MNODE()
{
    nodeN=1;
    myInit();
}
MNODE::MNODE(int n)
{
    nodeN=n;
    myInit();
}
MNODE::~MNODE()
{
    printf("dest MNODE\n");
    int i;
    delete [] n;
    for(i=0;i<nodeN;i++)
    {
        delete [] e[i];
    }
    delete [] e;
}
void MNODE::myInit()
{
    int i;
    n=new NODE[nodeN];
    e=new EDGE*[nodeN];
    for(i=0;i<nodeN;i++)
        e[i]=new EDGE[nodeN];
}
