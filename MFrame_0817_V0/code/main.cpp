#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "FRAME.h"
#include "PARA.h"
#include "DATASET.h"
#include "MIC.h"

using namespace std;

int main()
{
    //srand((unsigned)((unsigned)time(NULL)*(1+dataNO)+dataNO));
    srand((unsigned)((unsigned)time(NULL)));
    DATASET dataset;
    dataset.loadData();
    FRAME *F1;
    F1=new FRAME();
    F1->init(5);
    F1->optimization(dataset,0,1);
///    F1->optimization(dataset,0,2);
///    F1->optimization(dataset,0,3);
///    F1->optimization(dataset,0,4);
///    F1->optimization(dataset,0,5);
    F1->saveProfile(1);
    delete F1;
    return 0;
}
