#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "EDGE.h"

using namespace std;

EDGE::EDGE()
{
    pp.isChangable=0;
}
EDGE::~EDGE()
{
    printf("dest EDGE\n");
}
