#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "MIC.h"

using namespace std;
PARA::PARA()
{
    printf("para init!\n");
}
PARA::~PARA()
{
    printf("dest PARA\n");
}
