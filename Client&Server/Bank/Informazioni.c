#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Informazioni.h"

int conto[]={0,1,2,3,4,5,6,7,8,9};
int saldo[]={1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};

int get_Conto(int v)
{return conto[v];}

int get_Saldo(int v)
{return saldo[v];}

int set_Versare(int c,int v)
{
    saldo[c]=saldo[c]+v;
    return saldo[c];
}

int set_Prelievo(int c,int v)
{
    saldo[c]=saldo[c]-v;
    return saldo[c];
}