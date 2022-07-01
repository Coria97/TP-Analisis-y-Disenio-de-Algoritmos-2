#include <iostream>
#include <list>
#include <queue>
using namespace std;

//------------------------------Problema de la mochila con branch and bound---------------------------------


struct estado {
    int asignacion[6];
    float capacidad_actual;
    float beneficio_actual;
    float cota;
    bool operator< (const estado & otroestado) const
    {
        return(cota < (otroestado.cota));
    }
    int ultobj;
};

bool poda(estado expandir, float sol, int capacidad)
{
    if(expandir.capacidad_actual<=capacidad)
        if (expandir.cota>=sol)
            if(expandir.beneficio_actual>=sol)
                return false;
            else
                return true;
        else
            return true;
    else
        return true;
}
void mostrararreglo(int arr[],int cantobj)
{
    for(int i=0; i<cantobj;i++)
        cout<< arr[i] << "  " ;
    cout<< " " <<endl;
}

void expandir(list<estado> & hijos,estado en_expansion,int cantobj,float peso[],float beneficio[],int capacidad,float BsobreP[])
{
        for(int i=en_expansion.ultobj;i<cantobj-1;i++)
        {
            float cotaaux=0;
            estado aux;
            aux.capacidad_actual=0;
            aux.beneficio_actual=0;
            aux.cota= 0;
            aux.ultobj=0;
            for(int j=0; j<cantobj-1;j++)
                aux.asignacion[j]=0;
            if(en_expansion.asignacion[i]==0)
            {
                aux.capacidad_actual=en_expansion.capacidad_actual + peso[i];
                aux.beneficio_actual=en_expansion.beneficio_actual + beneficio[i];
                for(int j=0;j<cantobj;j++)
                    if((j!=i)&&(cotaaux< BsobreP[j]))
                        cotaaux=BsobreP[j];
                aux.cota= beneficio[i] + ((capacidad-peso[i])*cotaaux);
                aux.ultobj=i+1;
                for(int j=0; j<cantobj;j++)
                    aux.asignacion[j]=en_expansion.asignacion[j];
                aux.asignacion[i]=1;
                hijos.push_back(aux);
            }
        }
}

bool es_solucion(estado aux,float peso[],int capacidad,int cantobj)
{
    bool a=false;
    if(aux.capacidad_actual==capacidad)
        a=false;
    else
    {
        for(int i=aux.ultobj;i<cantobj;i++)
        {
            if(( aux.capacidad_actual + peso[i] )<= capacidad)
                a=true;
        }
    }
    return a;
}

void imprimir(priority_queue<estado> vivos)
{
    while(!vivos.empty())
    {
        estado aux= vivos.top();
        cout << aux.cota << endl;
        vivos.pop();
    }
}

void mochila(int capacidad,int cantobj,float peso[],float beneficio[],float BsobreP[] ,estado inicial,estado & solucion)
{
    float sol=0;
    priority_queue<estado> vivos;
    vivos.push(inicial);
    bool encontro=false;
    while(!vivos.empty())
        {
            estado en_expansion=vivos.top();
            vivos.pop();
            if(!poda(en_expansion,sol,capacidad))
                {
                    list<estado> hijos;
                    expandir(hijos,en_expansion,cantobj,peso,beneficio,capacidad,BsobreP);
                    list<estado>:: iterator it=hijos.begin();
                    while(it!=hijos.end())
                    {
                        estado aux=*it;
                        if(!poda(aux,sol,capacidad))
                        {
                            if(!es_solucion(aux,peso,capacidad,cantobj))
                                {
                                    solucion=aux;
                                    sol=it->beneficio_actual;
                                }
                            else
                            {
                                vivos.push(aux);
                            }
                        }
                        it++;
                    }
                    hijos.clear();
                }
            }
}

int main()
{
    int capacidad=11;
    int cantobj=6;
    float peso[cantobj]={7,6,5,2,1,0};
    float beneficio[cantobj]={28,22,18,6,1,0};
    float BsobreP[cantobj]={4,3.67,3.60,3,1,0};
    estado inicio;
    estado solucion;
    for(int i=0;i<cantobj;i++)
        inicio.asignacion[i]=0;
    inicio.beneficio_actual=0;
    inicio.capacidad_actual=0;
    inicio.cota=0;
    inicio.ultobj=0;
    mochila(capacidad,cantobj,peso,beneficio,BsobreP,inicio,solucion);
    cout<<"mejor beneficio: " << solucion.beneficio_actual << endl;
    cout<< "los objetos que estan en la mochila son: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i=0;i<cantobj-1;i++)
        if(solucion.asignacion[i]==1)
        {
            cout << "objeto: " << i << endl;
            cout << "peso del objeto: " << peso[i] << endl;
            cout << "beneficio del objeto: " << beneficio[i] << endl;
            cout << "-----------------------------------------------" << endl;
        }
    return 0;
}
