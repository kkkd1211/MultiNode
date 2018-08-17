#ifndef MIC_H
#define MIC_H

#define edgeParaN 2
#define maxNodeN 10

#define Nx 100
#define Nt 60

using namespace std;
class PARA;
class PARA
{
    public:
        PARA();
        ~PARA();
        double k;
        int isChangable;
};
class DATA;
class DATA
{
    public:
        DATA();
        ~DATA();
        double c[Nx];
};


#endif
