#include <iostream>
#include <stdlib.h>

using namespace std;

//-----------------------------problema de las n reinas con poda------------------------

int poda (int reinas[],int nroreina)
{
    int j=0;
    while (j<nroreina)
    {
        int a= reinas[nroreina] - reinas[j];
        if((reinas[j]==reinas[nroreina])||((nroreina-j)== abs(a)))
           return 1;
        j++;
    }
    return 0;
}

void backreinas (int reinas[],int nroreina,int n,int & contador)
{
    if(nroreina==n)
    {
        for(int i=0;i<n;i++)
            cout<<"la reina numero: " << i+1 << " en la fila: " << i+1 << "  " << "en la columna: "<< reinas[i]+1 << endl;
        cout << ".............................................." << endl;
        contador= contador +1;
    }
    else
    {
        int columna=0;
        while (columna < n)
            {
                reinas[nroreina]= columna;
                if (!poda(reinas,nroreina))
                   backreinas(reinas,nroreina+1,n,contador);
                columna++;
            }
    }
}

//----------------------------------------problema de las nreinas sin poda------------------------------

void backreinas_sinpoda (int reinas[],int nroreina,int n,int & contador)
{
    if(nroreina==n)
    {
        contador=contador+1;
        bool sol=false;
        for(int i=0;i<nroreina;i++)
        {
            if(poda(reinas,i))
                sol=true;
        }
        if(!sol)
        {
            for(int i=0;i<n;i++)
                cout<< "en la fila: " << i+1 << "  " << "en la columna: "<< reinas[i]+1 << endl;
            cout << ".............................................." << endl;
        }
    }
    else
    {
        int columna=0;
        while (columna < n)
            {
                reinas[nroreina]= columna;
                backreinas_sinpoda(reinas,nroreina+1,n,contador);
                columna++;
            }
    }
}


int main()
{
    int n;
    cout << "ingrese la cantidad de reinas : " << endl;
    cin >> n;
    cout << "---------------Back reinas con poda--------------------"<< endl;
    int reinas[n];
    for(int i=0;i < n; i++)
        reinas[n]=-1;
    int contadorA=0;
    backreinas(reinas,0,n,contadorA);
    cout << "---------------Back reinas sin poda--------------------"<< endl;
    int contadorB=0;
    for(int i=0;i < n; i++)
        reinas[n]=-1;
    backreinas_sinpoda(reinas,0,n,contadorB);
    cout << "total de soluciones encontradas con poda: " << contadorA << endl;
    cout << "total de soluciones encontradas sin poda: " << contadorB << endl;
    return 0;
}
