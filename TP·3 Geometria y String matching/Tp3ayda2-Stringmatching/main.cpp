#include <iostream>
#include <math.h>

using namespace std;

void RabinKarp(int texto[],int patron[],int n,int m,int q,int d)
{
    int t=0;
    int p=0;
    int x=0;
    x=(pow(d,m-1))+1;
    int h =x%q;
    int fracasos=0;
    for(int i=0;i<m;i++)
    {
        p=(d*p + patron[i])%q;
        t=(d*t + texto[i])%q;
    }
    for(int s=0;s<(n-m);s++)
    {
        if(p==t)
        {
            bool coincide=false;
            int i=0;
            while((i<m)&&(!coincide))
            {
                if(patron[i]!=texto[s+i])
                    {
                        coincide=true;
                        fracasos=fracasos + 1;
                    }
                i++;
            }
            if(!coincide)
                cout << "se encontro en el texto el patron con un corrimiento de " << s << " en el texto." << endl;
        }
        if (s<(n-m))
        {
            t=(d*(t-texto[s]*h)+ texto[s+m])%q;
            if(t<0)
                t=t+q;
        }
    }
    cout<< "el total de fracasos fue de: "<< fracasos << endl;
}

int main()
{
    int n=31;
    int m=5;
    int texto[]={1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3};
    int patron[]={8,9,1,2,3};
    int q=13;
    int d=10;
    RabinKarp(texto,patron,n,m,q,d);
    return 0;

}
