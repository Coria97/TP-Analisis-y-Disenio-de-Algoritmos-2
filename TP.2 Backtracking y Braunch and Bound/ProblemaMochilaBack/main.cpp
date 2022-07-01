#include <iostream>

using namespace std;

//------------------------------Problema de la mochila con backtracking---------------------------------

void backmocila(int capacidad,int cantobj,float peso[],float beneficio[],int objactual,int capacidadactual,int solucion[],int  solucionactual[],float & maxben,float benact)
{
    if (objactual==cantobj)
    {
        if(capacidadactual<= capacidad)
        {
            if (maxben<benact)
            {
                maxben=benact;
                for(int i=0;i<cantobj;i++)
                    solucion[i]=solucionactual[i];
            }
        }
    }
    else
        while (objactual<cantobj)
        {
            for(int i=0;i<=1;i++)
            {
                if (i==0)
                {
                    solucionactual[objactual]=i;
                    backmocila(capacidad,cantobj,peso,beneficio,objactual+1,capacidadactual,solucion,solucionactual,maxben,benact);
                    solucionactual[objactual]=-1;
                }
                else
                    if(i==1)
                    {
                        solucionactual[objactual]=i;
                        benact= benact + beneficio[objactual];
                        capacidadactual= capacidadactual + peso[objactual];
                        backmocila(capacidad,cantobj,peso,beneficio,objactual+1,capacidadactual,solucion,solucionactual,maxben,benact);
                        solucionactual[objactual]=-1;
                        benact= benact - beneficio[objactual];
                        capacidadactual= capacidadactual - peso[objactual];
                    }
            }
            solucionactual[objactual]=0;
            objactual++;
        }
}


int main()
{
    float maxben= 0;
    float benact=0;
    int capacidad=11;
    int capacidadactual=0;
    int cantobj = 5;
    int objactual=0;
    float peso[cantobj]={7,6,5,2,1};
    float beneficio[cantobj]={28,22,18,6,1};
    int solucion[cantobj]={-1,-1,-1,-1};
    int solucionactual[cantobj]={-1,-1,-1,-1};
    backmocila(capacidad,cantobj,peso,beneficio,objactual,capacidadactual,solucion,solucionactual,maxben,benact);
    cout << "El benefificio maximo es de= " << maxben << endl;
    cout << "-------------------------------------------------------------------------------"<< endl;
    for(int i=0;i<cantobj;i++)
    {
        if(solucion[i]!=0)
        {
            cout << "el objeto que esta dentro de la mochila es= " << i << " ,su peso es de= " ;
            cout << peso[i] << " y su beneficio es de  " << beneficio[i] << endl;
            cout << "-------------------------------------------------------------------------------"<< endl;
        }
    }
    return 0;
}
