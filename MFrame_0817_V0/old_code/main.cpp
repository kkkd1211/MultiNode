#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "MIC.h"
#include "MN.h"
#include "EDGE.h"
#include "NODE.h"

int main()
{
    MNODE *frame=new MNODE(2);
    printf("%d\n\n",frame->e[1][1].pp.isChangable);
    delete frame;
    printf("main end\n");
    return 0;
}
