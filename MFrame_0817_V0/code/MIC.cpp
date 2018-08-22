#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;


double myRand(double a,double b)
{
    double y;
    if(a>b)
    {
        y=a;
        a=b;
        b=y;
    }
    y=(b-a)*(rand()/2147483647.0)+a;
    return (y);
}
