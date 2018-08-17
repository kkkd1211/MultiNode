#ifndef FRAME_H
#define FRAME_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>


using namespace std;

class FRAME;
class FRAME
{
    public:
        FRAME();
        ~FRAME();

        void init(int N);
        void copyFrame(FRAME *F);
        void complexUp();
        double myRand();

        PARA *parameter;
        int complexity;
        double loss;

};



#endif
