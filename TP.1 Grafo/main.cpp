#include <iostream>
#include "GrafoD.h"
#include "GrafoND.h"
#include "sets.h"
#include <assert.h>

using namespace std;


//----------------------------Crear matriz---------------------------------------------------------

void crearMatriz(int ** & matriz, int columna, int fila)
{
    matriz = new int*[fila];
    for (int f = 0; f <= fila; f++)
        matriz[f] = new int[columna];
}

//-------------------------------imprimir matriz--------------------------------------------------

void mostrarMatriz(int ** matriz, int columna, int fila)
{
    for (int f = 1; f <= fila; f++)
    {
        for (int c = 1; c <= columna; c++)
            cout << matriz[f][c] << " ";
        cout << "\n";
    }
}


//--------------------------------dijkstra ND------------------------------------------------------

void mostrarcamino(int p[],int k)
{
    int j=p[k];
    if(p[k]>0)
    {
        mostrarcamino(p,j);
        cout<< j <<"--------->";
    }

}

void dijkstraND(const GrafoND<int> & g, int origen, int **  costo,int puerto[])
{
    int n=g.cantidadVertices();
    int solucion[n];
    for(int i=0; i<=n; i++)
        solucion[i]=0;
    solucion[origen]=1;
    int p[n];
    int d[n];
    p[origen]=-1;
    d[origen]=0;
    for(int i=0; i<=n; i++)
    {
        if (i!=origen)
        {
            d[i]=costo[origen][i];
            p[i]=origen;
        }
    }
    int w;
    int menorvalor=999;
    for(int k=1; k<n; k++)
    {
        for(int j=1; j<=n; j++)
        {
            if(menorvalor>d[j])
            {
                if(solucion[j]==0)
                {
                    menorvalor=d[j];
                    w=j;
                }
            }
        }
        menorvalor=99;
        solucion[w]=1;
        for(int i=1; i<=n; i++)
        {
            if(g.existeArista(w,i))
            {
                if(solucion[i]==0)
                {
                    if(d[i]>d[w]+costo[w][i])
                    {
                        d[i]=d[w]+costo[w][i];
                        p[i]=w;
                    }
                }
            }
        }
    }
    cout<<"arreglo de predecesores: ";
    for (int f=1; f<=n; f++)
    {
        cout<<p[f]<< "  " ;
    }
    cout<<""<< endl;
    cout<<"arreglo de distancia: ";
    for (int f=1; f<=n; f++)
    {
        cout<<d[f]<< "  " ;
    }
    cout<<""<< endl;
    cout<< "el camino de menor costo hasta el puente es de:  " ;
    if((d[2]<d[7])&&(d[2]<d[4]))
    {
        mostrarcamino(p,2);
        cout<< "2"<< endl;
        cout<< "su costo es de: " << d[2]<<endl;
    }

    else if((d[4]<d[7])&&(d[4]<d[2]))
    {
        mostrarcamino(p,4);
        cout<< "4"<< endl;
        cout<< "su costo es de: " << d[4]<< endl;
    }
    else if((d[7]<d[2])&&(d[7]<d[4]))
    {
        mostrarcamino(p,7);
        cout<< "7"<<endl;
        cout<< "su costo es de: " << d[7]<< endl;
    }
}


//--------------------------------kruskal----------------------------------------------------------

struct nodo
{
    int origen;
    int destino;
    int costo;
};

void insertordenado(list<nodo> & aristas, nodo n)
{
    if (aristas.size()<=0)
    {
        aristas.push_back(n);
        cout << "arista a agregar en la lista" << "(" << n.origen << "," << n.destino << "," << n.costo << ")" << endl;
    }
    else
    {
        bool agrego=false;
        nodo aux;
        list<nodo>::iterator it=aristas.begin();
        while((it!=aristas.end()) && (agrego==false))
        {
            aux=*it;
            if(aux.costo>n.costo)
            {
                cout << "arista a agregar en la lista" << "(" << n.origen << "," << n.destino << "," << n.costo << ")" << endl;
                aristas.insert(it,n);
                agrego=true;
            }
            else
                it++;
        }
        if((agrego==false)&&(it==aristas.end()))
        {
            aristas.push_back(n);
            cout << "arista a agregar en la lista" << "(" << n.origen << "," << n.destino << "," << n.costo << ")" << endl;
        }
    }
}

void kruskal(const GrafoND<int> & g)
{
    int k= g.cantidadVertices();
    int ** matriz=0;
    crearMatriz(matriz,k,k);
    for (int f = 1; f <= k; f++)
        for (int c = 1; c <= k; c++)
            if (f==c)
                matriz[f][c]=1;
            else
                matriz[f][c]=0;
    mostrarMatriz(matriz,k,k);
    nodo n;
    nodo aux;
    list<nodo> arbol;
    list<nodo> aristas;
    list< typename GrafoND<int>::Arista> adyacentes;
    typename list< typename GrafoND<int>::Arista>::iterator ady;
    sets componentes(k);
    for(int i=1; i<=k; i++)
    {
        adyacentes.clear();
        g.devolverAdyacentes(i,adyacentes);
        ady=adyacentes.begin();
        while(ady!=adyacentes.end())
        {
            if ((matriz[i][ady->devolverAdyacente()]==0)&&(matriz[ady->devolverAdyacente()][i]==0))
            {
                matriz[i][ady->devolverAdyacente()]=1;
                matriz[ady->devolverAdyacente()][i]=1;
                n.origen=i;
                n.destino=ady->devolverAdyacente();
                n.costo=ady->devolverCosto();
                cout << "vertice origen:  " << i<< endl;
                cout << "vertice destino:  " << ady->devolverAdyacente()<< endl;
                cout << "vertices costo:  " << ady->devolverCosto()<< endl;
                insertordenado(aristas,n);
                cout << "--------------------------"<< endl;
            }
            ady++;
        }
    }
    list<nodo>::iterator itl=aristas.begin();
    while(itl!=aristas.end())
    {
        aux=*itl;
        cout<< aux.origen;
        cout<<"  <------------>  ";
        cout<< aux.destino;
        cout<< "  costo de la arista:  ";
        cout<< aux.costo << endl;
        itl++;
    }
    list<nodo>::iterator it= aristas.begin();
    while(it!=aristas.end())
    {
        aux=*it;
        aristas.pop_front();
        it=aristas.begin();
        if (componentes.Connected(aux.origen,aux.destino)==false)
        {
            int origen=componentes.Find(aux.origen);
            int destino=componentes.Find(aux.destino);
            arbol.push_back(aux);
            componentes.Union(origen,destino);
        }
    }
    list<nodo>::iterator itA=arbol.begin();
    int costototal=0;
    cout << "el arbol de recubrimiento minimo es:  "<< endl;
    while(itA!=arbol.end())
    {
        aux=*itA;
        cout<< aux.origen;
        cout<<"  <------------>  ";
        cout<< aux.destino;
        cout<< "  costo de la arista:  ";
        cout<< aux.costo << endl;
        itA++;
        costototal=costototal+aux.costo;
    }
    cout << "su costo minimo es de:"  << costototal<<endl;
    cout << "la cantidad de componentes del arbol es de:" << componentes.Count()<< endl;
}

//----------------------------Recorrer Grafo -------------------------------------------------------

template<typename C> ostream & operator << (ostream & salida, const GrafoD<C> & Grafo)
{
    // Recorremos todos los vertices
    list<int> vertices;
    Grafo.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();

    while (v != vertices.end())
    {
        salida << "    " << *v << "\n";
        // Recorremos todos los adyacentes de cada vertice
        list< typename GrafoD<C>::Arco> adyacentes;
        Grafo.devolverAdyacentes(*v, adyacentes);
        typename list< typename GrafoD<C>::Arco>::iterator ady = adyacentes.begin();
        while (ady != adyacentes.end())
        {
            salida << "   " <<  *v << "->"  << ady->devolverAdyacente() << " (" << ady->devolverCosto () << ")\n";
            ady++;
        }
        v++;
    }
    return salida;
}

//----------------------------Cargar Matriz de costo para grafo no dirigido-------------------------

void cargarcostoND(const GrafoND<int> &g,int ** & costo)
{
    int n=g.cantidadVertices();
    for (int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            costo[i][j]= 99 ;
    }
    for(int o=1; o<=n; o++)
    {
        for(int d=1; d<=n; d++)
        {
            if(o!=d)
            {
                if(g.existeArista(o,d))
                {
                    costo[o][d]=g.costoArista(o,d);
                    costo[d][o]=g.costoArista(d,o);
                }
            }
        }
    }
    cout<< "Matriz costo"<< endl;
    mostrarMatriz(costo,n,n);
}

//----------------------------Cargar Matriz de costo para grafo dirigido----------------------------

void cargarcostoD(const GrafoD<int> &g,int ** & costo)
{
    int n=g.cantidadVertices();
    for (int i=0; i<=n; i++)
    {
        for(int j=0; j<=n; j++)
            costo[i][j]=999;
    }
    for(int o=1; o<=n; o++)
    {
        for(int d=1; d<=n; d++)
        {
            if(g.existeArco(o,d))
            {
                costo[o][d]=g.costoArco(o,d);
            }
        }
    }
    cout<< "Matriz costo"<< endl;
    mostrarMatriz(costo,n,n);
}

//------------------------------------Floyd---------------------------------------------------------

void floyd(int ** & A,int ** & costo,int ** & P,int n)
{
    unsigned int i,j,k;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            if (i==j)
            {
                A[i][j]=0;
                P[i][j]=0;
            }
            else
            {
                A[i][j]=costo[i][j];
                P[i][j]=0;
            }
        }
    for(k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
            {
                if(A[i][k]+A[k][j]<A[i][j])
                {
                    A[i][j]=A[i][k]+A[k][j];
                    P[i][j]=k;
                }
            }
    cout<<"Matriz A final "<<endl;
    mostrarMatriz(A,n,n);
    cout<< "Matriz Predecesores" << endl;
    mostrarMatriz(P,n,n);
}

//------------------------------------Prim----------------------------------------------------------

void prim(int ** & costo,int n)
{
    int w;
    int menorvalor= 999;
    int menorcosto[n];
    int mascercano[n];
    int solucion[n];
    solucion[1]=1;
    for(int i=2; i<=n; i++)
    {
        menorcosto[i]=999;
        solucion[i]=0;
    }
    for(int i=2; i<=n; i++)
    {
        menorcosto[i]=costo[1][i];
        mascercano[i]=1;
    }
    for(int i=2; i<=n; i++)
    {
        for(int j=2; j<=n; j++)
        {
            if(menorvalor>menorcosto[j])
                if (solucion[j]==0)
                {
                    menorvalor=menorcosto[j];
                    w=j;
                }
        }
        menorvalor=99;
        solucion[w]=1;
        for(int k=2; k<=n; k++)
        {
            if(solucion[k]==0)
                if (costo[w][k]<menorcosto[k])
                {
                    menorcosto[k]=costo[w][k];
                    mascercano[k]=w;
                }
        }
    }
    for(int i=2; i<=n; i++)
    {
        cout << "vertice  " << i << "  ";
        cout << "padre:  " << mascercano[i] << "  ";
        cout << "con costo:  " << menorcosto[i] << endl;
    }
    for(int i=2; i<=n; i++)
        cout << solucion[i]<< "  ";

}

//------------------------------------Dijkstra------------------------------------------------------

void dijkstra(const GrafoD<int> & g, int origen, int **  costo)
{
    int n=g.cantidadVertices();
    int solucion[n+1];
    for(int k=0; k<n+1; k++)
        solucion[k]=0;
    solucion[origen]= 1;
    int p[n+1];
    int d[n+1];
    p[origen]=-1;
    d[origen]=0;
    for(int i=0; i<n+1; i++)
    {
        if (i!=origen)
        {
            d[i]=costo[origen][i];
            p[i]=origen;
        }
    }
    int w;
    int menorvalor=99;
    for(int k=1; k<n; k++)
    {
        for(int j=1; j<n+1; j++)
        {
            if(menorvalor>d[j])
            {
                if(solucion[j]==0)
                {
                    menorvalor=d[j];
                    w=j;
                }
            }
        }
        menorvalor=99;
        solucion[w]=1;
        for(int i=1; i<n+1; i++)
        {
            if((g.existeArco(w,i))&&(solucion[i]==0))
            {
                if(d[i]>d[w]+costo[w][i])
                {
                    d[i]=d[w]+costo[w][i];
                    p[i]=w;
                }
            }
        }
    }
    cout<<""<< endl;
    for (int f=1; f<=n; f++)
    {
        cout<<p[f]<< "  " ;
    }
    cout<<""<< endl;
    for (int f=1; f<=n; f++)
    {
        cout<<d[f]<< "  " ;
    }
    cout<<""<< endl;
}

//------------- DFS CON ORIGEN Y DESTINO ENCUENTRA TODOS LOS CAMINOS---------------------------------

void dfsoriydest(const GrafoD<int> &g,int origen,int destino,int m[], list<int> listacamino,int costo,bool & encontro)
{
    listacamino.push_back(origen);
    m[origen]=1;
    if (origen==destino)
    {
        list<int>::iterator itC= listacamino.begin();
        cout << "el costo del camino es: " << costo << endl;
        cout << "el camino es de: ";
        while(itC!=listacamino.end())
        {
            cout<< *itC << " " ;
            itC++;
        }
        encontro=true;
        cout<< "  " << endl;
        cout<< "  " << endl;
    }
    else
    {
        list< typename GrafoD<int>::Arco> adyacentes;
        g.devolverAdyacentes(origen, adyacentes);
        typename list< typename GrafoD<int>::Arco>::iterator ady = adyacentes.begin();
        while (ady!=adyacentes.end())
        {
            if ((m[ady->devolverAdyacente()]== 0))
            {
                int nuevoorigen=ady->devolverAdyacente();
                costo=costo + ady->devolverCosto();
                dfsoriydest(g,nuevoorigen,destino,m,listacamino,costo,encontro);
                costo=costo - ady->devolverCosto();
            }
            ady++;
        }
    }
    m[origen]=0;
    listacamino.pop_back();

}

void dfsfor (const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    g.devolverVertices(listavertices);
    int n=listavertices.size();
    int m[n];
    for(int i=1; i<n+1; i++)
        m[i]=0;
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese 2 vertices deseados de los siguientes: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    int origen,destino=0;
    cout << endl;
    cin >> origen >> destino;
    int costo=0;
    bool encontro= false;
    if ((g.existeVertice(origen))&&(g.existeVertice(destino)))
    {
        dfsoriydest(g,origen,destino,m,listacamino,costo,encontro);
        if (!encontro)
            cout<< "no hay un camino"<< endl;
    }
    else
        cout<< "los vertices no existen" << endl;

}

//---------------------------------------DFS----------------------------------------------------------

void dfs(const GrafoD<int> &g,int origen,int p[],char m[],int matrizdescubrimiento[][3],int &tiempo)
{

    tiempo=tiempo+1;
    m[origen]='G';
    matrizdescubrimiento[origen][1]= tiempo;
    list< typename GrafoD<int>::Arco> adyacentes;
    g.devolverAdyacentes(origen, adyacentes);
    typename list< typename GrafoD<int>::Arco>::iterator ady = adyacentes.begin();
    cout<< "los adyacentes que contiene el vertice" << "  " << origen << "  " << "son:   " ;
    if (ady==adyacentes.end())
        cout<< "no contiene vertices adyacentes " ;
    else
        while(ady!=adyacentes.end())
        {
            cout << ady->devolverAdyacente() << "  ";
            ady++;
        }
    ady=adyacentes.begin();
    int verady;
    while (ady!=adyacentes.end())
    {
        verady=ady->devolverAdyacente();;
        if ((m[verady]!= 'G')&&(m[verady]!= 'N'))
        {
            p[verady]=origen;
            cout<< "  "<< endl;
            cout<<"Se continua la exploracion del grafo a partir del vertice:" <<"  "<< verady << endl;
            dfs(g,verady,p,m,matrizdescubrimiento,tiempo);
            ady++;
        }
        else
            ady++;
    }
    m[origen]='N';
    tiempo=tiempo+1;
    matrizdescubrimiento[origen][2]=tiempo;

}

void dfsforest(const GrafoD<int> &g)
{
    list<int> vertices;
    g.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    int tam=vertices.size();
    char m[tam+1];
    int p[tam+1];
    int tiempo=0;
    int matrizdescubrimiento[tam+1][3]; // EN LA COLUMNA 0 EL VERTICE, 1 TIEMPO DE DESCUBRIMIENTO, 2 TIEMPO DE FINALIZACION
    for(int i=1; i<tam+1; i++)
        m[i]='B';
    for(int i=1; i<tam+1; i++)
        p[i]=-1;
    for(int f=1; f<tam+1; f++)
    {
        for(int c=0; c<3; c++)
        {
            if (c==0)
                matrizdescubrimiento[f][c]=*v;
            else
                matrizdescubrimiento[f][c]=-1;
        }
        v++;
    }
    v=vertices.begin();
    cout<<"la matriz descubrimiento esta inicializada en:" << endl;
    for(int f=1; f<tam+1; f++)
    {
        for(int c=0; c<3; c++)
        {
            if (c==0)
                cout << matrizdescubrimiento[f][c] << " ";
            if (c==1)
                cout <<"[" << matrizdescubrimiento[f][c];
            if (c==2)
                cout << ", " <<matrizdescubrimiento[f][c] << "]";
        }
        cout << "  "<< endl;
    }

    cout<<"el arreglo marca esta inicializado en:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< m[i]<<"  ";
    cout<< "  "<< endl;
    cout<<"el arreglo padres esta inicializado en:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< p[i]<<"  ";
    cout<< "  "<< endl;
    while(v!=vertices.end())
    {
        if (m[*v]== 'B')
        {
            int origen=*v;
            cout<< "  " << endl;
            cout<<"Se comienza una nueva exploracion del grafo a partir del vertice:" <<"  "<< origen << endl;
            dfs(g,origen,p,m,matrizdescubrimiento,tiempo);
        }
        else
            v++;
    }
    cout<< endl << endl <<"la matriz descubrimiento finalizada es:" << endl;
    for(int f=1; f<tam+1; f++)
    {
        for(int c=0; c<3; c++)
        {
            if (c==0)
                cout << matrizdescubrimiento[f][c] << " ";
            if (c==1)
                cout <<"[" << matrizdescubrimiento[f][c];
            if (c==2)
                cout << ", " <<matrizdescubrimiento[f][c] << "] ";
        }
        cout << "  "<< endl;
    }
    cout<<"el arreglo marca finalizado es:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< m[i]<<"  ";
    cout<< "  "<< endl;
    cout<<"el arreglo padres esta finalizado es:" << endl;
    for(int i=1; i<-tam+1; i++)
        cout<< p[i]<<"  ";
    cout<< "  "<< endl;

}

//---------------------------------------BFS----------------------------------------------------------

void bfs(const GrafoD<int> & g,int origen,int descubrimiento[],int padre[], int marca[])
{
    marca[origen]=1;
    descubrimiento[origen]=0;
    padre[origen]=-1;
    list<int> fila;
    fila.push_front(origen);
    list< typename GrafoD<int>::Arco> listady;
    list< typename GrafoD<int>::Arco>::iterator itA;
    int aux;
    GrafoD<int>::Arco ady;
    while(!fila.empty())
    {
        aux = fila.back();
        fila.pop_back();
        g.devolverAdyacentes(aux,listady);
        for(itA=listady.begin(); itA!=listady.end(); itA++)
        {
            ady = *itA;
            if (marca[ady.devolverAdyacente()]==0)
            {
                marca[ady.devolverAdyacente()]=1;
                padre[ady.devolverAdyacente()]=aux;
                descubrimiento[ady.devolverAdyacente()]=descubrimiento[aux]+1;
                fila.push_front(ady.devolverAdyacente());
            }
        }
        marca[aux]=2;
    }
}

void bfsforest(const GrafoD<int> & g)
{
    list<int> vertices;
    g.devolverVertices(vertices);
    int cantvertices=vertices.size();
    int descubrimiento[cantvertices];
    int padre[cantvertices];
    int marca[cantvertices];
    int origen;
    for(int i=1; i<=cantvertices+1; i++)
    {
        descubrimiento[i]=-1;
        padre[i]=-1;
        marca[i]=0;
    }
    list<int>::iterator itV = vertices.begin();
    itV = vertices.begin();
    while (itV != vertices.end())
    {
        origen= *itV;
        if (marca[*itV] == 0)
        {
            bfs(g,origen,descubrimiento,padre,marca);
            cout<< endl << "Arbol BFS con: " << *itV << endl << endl;
            for (int i=1; i<cantvertices+1; i++)
                cout << "vertice("<<i<< ") "<<"desc(" << descubrimiento[i] << ") padre(" << padre[i] << ") marca(" << marca[i] <<")"<< endl;
            for(int i=1; i<cantvertices+1; i++)
            {
                descubrimiento[i]=-1;
                padre[i]=-1;
                marca[i]=0;
            }
        }
        itV++;
    }
}

//-----------------------------Buscar camino de menor costo-------------------------------------------

void buscarecursivamenorcosto(const GrafoD<int> &g,int origen,int destino,list<int> listacamino,list<int> &mejorlistacamino,int visitados[],int costo,int & mejorcosto)
{
    listacamino.push_back(origen);
    visitados[origen]=1;
    list< typename GrafoD<int>::Arco> listady;
    g.devolverAdyacentes(origen,listady);
    list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
    if ((origen==destino))
    {
        list<int>::iterator itC= listacamino.begin();
        if (mejorcosto== 0)
        {
            mejorcosto=costo;
            mejorlistacamino.clear();
            while(itC!=listacamino.end())
            {
                mejorlistacamino.push_back(*itC);
                itC++;
            }
        }
        else if (mejorcosto>costo)
        {
            mejorcosto=costo;
            mejorlistacamino.clear();
            while(itC!=listacamino.end())
            {
                mejorlistacamino.push_back(*itC);
                itC++;
            }
        }
    }
    else
    {
        while(itA!=listady.end())
        {
            int i=itA->devolverAdyacente();
            costo=costo + itA->devolverCosto();
            if (visitados[i]==0)
                buscarecursivamenorcosto(g,i,destino,listacamino,mejorlistacamino,visitados,costo,mejorcosto);
            costo=costo - itA->devolverCosto();
            itA++;
        }
    }
    visitados[origen]=0;
    listacamino.pop_back();
}

void buscarcaminosmenorcosto(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    list<int> mejorlistacamino;
    g.devolverVertices(listavertices);
    int n=listavertices.size();
    int visitados[n];
    for(int i=1; i<n+1; i++)
        visitados[i]=0;
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese el vertice origen: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    cout << " " << endl;
    int origen,destino,costo,mejorcosto=0;
    cin>>origen;
    for (int i=1; i<n+1; i++)
    {
        destino=i;
        buscarecursivamenorcosto(g,origen,destino,listacamino,mejorlistacamino,visitados,costo,mejorcosto);
        list<int>::iterator itC= mejorlistacamino.begin();
        if (mejorcosto==0)
        {
            cout << "no existe un camino entre  "  << origen << "  y  " << destino << endl;
        }
        else
        {
            cout << "entre   " << origen << "  y  " << destino << endl;
            cout << "el costo del mejor camino es:" << " " << mejorcosto << endl;
            cout << "y el camino es:  " ;
            while(itC!=mejorlistacamino.end())
            {
                cout<< *itC << " " ;
                itC++;
            }
            mejorcosto=0;
            cout << "  "<< endl;
        }
    }
}

//---------------------------------------BUSCAR UN SOLO CAMINO-----------------------------------------

void buscarecursiva(const GrafoD<int> &g, int origen,const int destino,list<int> &listacamino,int visitados[])
{
    cout << "entra con: " << origen << endl;
    listacamino.push_back(origen);
    visitados[origen]=1;
    if (origen== destino)
    {
        cout << "el camino es : " << "  ";
        list<int>::iterator itC=listacamino.begin();
        while (itC!=listacamino.end())
        {
            cout <<*itC<<" ";
            itC++;
        }
        cout << endl;
    }
    else
    {
        list< typename GrafoD<int>::Arco> listady;
        g.devolverAdyacentes(origen,listady);
        list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
        if (itA==listady.end())
            cout<<"no contiene mas adyacentes"<< endl;
        else
        {
            itA=listady.begin();
            while(itA!=listady.end())
            {
                int i=itA->devolverAdyacente();
                if (visitados[i]==0)
                    buscarecursiva(g,i,destino,listacamino,visitados);
                itA++;
            }
        }
    }
    visitados[origen]=0;
    listacamino.pop_back();
}

void buscarcaminos(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    g.devolverVertices(listavertices);
    int n=listavertices.size();
    int visitados[n];
    for(int i=1; i<n+1; i++)
        visitados[i]=0;
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese 2 vertices el primero que ingrese sera el origen y el siguiente el destino: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    int origen,destino=0;
    cout << endl;
    cin >> origen >> destino;
    if ((g.existeVertice(origen))&&(g.existeVertice(destino)))
        buscarecursiva(g,origen,destino,listacamino,visitados);
    else
        cout<< "los vertices no existen" << endl;
}

//----------------------------------Busca camino evitando n vertices ---------------------------------

void evitarrecursivo(const GrafoD<int> &g, int origen,const int destino,list<int> &listacamino,int visitados[],list<int>& evitados)
{
    listacamino.push_back(origen);
    if (origen== destino)
    {
        list<int>::iterator itC=listacamino.begin();
        while (itC!=listacamino.end())
        {
            cout <<*itC<<" ";
            itC++;
        }
        cout << endl;
    }
    list<int>::iterator itE=evitados.begin();
    bool checkeo=true;
    while (itE!=evitados.end())
    {
        if (*itE!=origen)
            itE++;
        else
        {
            itE=evitados.end();
            checkeo=false;
        }
    }
    if((checkeo)&&(origen!= destino))
    {
        list< typename GrafoD<int>::Arco> listady;
        g.devolverAdyacentes(origen,listady);
        list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
        int i=0;
        while(itA!=listady.end())
        {
            i=itA->devolverAdyacente();
            evitarrecursivo(g,i,destino,listacamino,visitados,evitados);
            itA++;
        }
    }
    listacamino.pop_back();
}

void evitarcaminos(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    g.devolverVertices(listavertices);
    int visitados[listavertices.size()];
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese 2 vertices deseados de los siguientes: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    int origen,destino=0;
    cout << endl;
    cin >> origen >> destino;
    cout << "Ingrese los vertices que desea evitar (-1 para finalizar)" << endl;
    int i=0;
    list<int> evitados;
    while(i!=-1)
    {
        cin >> i;
        if (i!=-1)
            evitados.push_back(i);
    }
    list<int>::iterator itE= evitados.begin();
    bool distintos=true;
    while (itE!=evitados.end())
    {
        if((*itE!=origen)&&(*itE!=destino))
            itE++;
        else
        {
            itE=evitados.end();
            distintos=true;
        }
    }
    if (distintos)
        evitarrecursivo(g,origen,destino,listacamino,visitados,evitados);
}

//----------------------------------Cargar grafo para Tp1 --------------------------------------------

void CargoGrafoTp1 (GrafoD<int> & g)
{
    g.agregarVertice(1);
    g.agregarVertice(3);
    g.agregarVertice(5);
    g.agregarVertice(7);
    g.agregarVertice(8);
    g.agregarVertice(9);
    g.agregarVertice(11);
    g.agregarVertice(12);

    //Rojos
    g.agregarVertice(2);
    g.agregarVertice(4);
    g.agregarVertice(6);
    g.agregarVertice(10);

    //Arcos
    g.agregarArco(1,2,1);
    g.agregarArco(1,7,5);
    g.agregarArco(2,3,3);
    g.agregarArco(4,3,4);
    g.agregarArco(5,3,7);
    g.agregarArco(5,7,2);
    g.agregarArco(6,5,1);
    g.agregarArco(6,8,15);
    g.agregarArco(7,11,3);
    g.agregarArco(8,4,10);
    g.agregarArco(8,5,2);
    g.agregarArco(8,12,1);
    g.agregarArco(9,8,2);
    g.agregarArco(10,6,4);
    g.agregarArco(10,7,9);
    g.agregarArco(10,9,20);
    g.agregarArco(11,10,2);
    g.agregarArco(11,12,3);

}

//---------------------------------Cargo grafo de prueba para dijkstra-------------------------------

void CargoGrafoDijkstra( GrafoD<int> & g)
{
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);
    g.agregarArco(1,2,10);
    g.agregarArco(1,5,100);
    g.agregarArco(1,4,30);
    g.agregarArco(2,3,50);
    g.agregarArco(3,5,10);
    g.agregarArco(4,3,20);
    g.agregarArco(4,5,60);

}

//---------------------------------cargo grafo para floyd -------------------------------------------

void CargoGrafoFloyd (GrafoD<int> & g)
{
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarArco(1,2,10);
    g.agregarArco(1,3,30);
    g.agregarArco(1,4,1);
    g.agregarArco(2,1,1);
    g.agregarArco(3,1,1);
    g.agregarArco(3,2,6);
    g.agregarArco(3,4,50);
    g.agregarArco(4,1,20);
    g.agregarArco(4,2,1);
}

//---------------------------------cargo grafo para tp2-----------------------------------------------

void CargoGrafoTp2(GrafoND<int> & g)
{
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);
    g.agregarVertice(6);
    g.agregarVertice(7);
    g.agregarVertice(8);
    g.agregarVertice(9);
    g.agregarVertice(10);
    g.agregarVertice(11);
    g.agregarVertice(12);
    g.agregarVertice(13);
    g.agregarArista(1,8,14);
    g.agregarArista(2,8,20);
    g.agregarArista(2,10,50);
    g.agregarArista(3,5,12);
    g.agregarArista(3,7,10);
    g.agregarArista(3,9,5);
    g.agregarArista(4,6,10);
    g.agregarArista(5,8,10);
    g.agregarArista(5,9,13);
    g.agregarArista(6,7,8);
    g.agregarArista(6,9,20);
    g.agregarArista(6,10,2);
    g.agregarArista(7,9,7);
    g.agregarArista(8,9,5);
    g.agregarArista(11,12,15);
    g.agregarArista(11,13,10);
    g.agregarArista(12,13,1);
}

//----------------------------------Cargo grafo nd para prim------------------------------------------

void CargoGrafoPrim (GrafoND<int> & g)
{
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);
    g.agregarVertice(6);
    g.agregarArista(1,2,3);
    g.agregarArista(1,5,10);
    g.agregarArista(2,3,5);
    g.agregarArista(2,5,1);
    g.agregarArista(3,4,2);
    g.agregarArista(3,6,10);
    g.agregarArista(4,6,4);
    g.agregarArista(5,4,8);
    g.agregarArista(5,6,20);
}

//----------------------------------Cargar grafo para Kruskal --------------------------------------------

void CargoGrafoKruskal (GrafoND<int> & g)
{
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);
    g.agregarVertice(6);
    g.agregarArista(1,2,6);
    g.agregarArista(1,3,1);
    g.agregarArista(1,4,5);
    g.agregarArista(2,3,5);
    g.agregarArista(2,5,3);
    g.agregarArista(3,4,5);
    g.agregarArista(3,5,6);
    g.agregarArista(3,6,4);
    g.agregarArista(4,6,2);
    g.agregarArista(5,6,6);
}

//----------------------------------   M A I N  ------------------------------------------------------

int main(int argc, char **argv)
{
    //modifique el algoritmo de kruskal para que en una sola ejecucion determine los arboles de recubrimiento del ejemplo e imprima la cantidad de componentes
    //cargo un nuevo grafo d para tp1
    GrafoD<int> f;
    CargoGrafoTp1(f);
    // cargo un nuevo grafo d para dijkstra
    GrafoD<int> h;
    CargoGrafoDijkstra(h);
    // cargo un nuevo grafo d para floyd
    GrafoD<int> j;
    CargoGrafoFloyd(j);
    //cargo un nuevo grafo nd de tp2
    GrafoND<int> c;
    CargoGrafoTp2(c);
    //cargo un nuevo grafo ND para prim
    GrafoND<int> e;
    CargoGrafoPrim(e);
    //cargo un nuevo grafo ND para Kruskal

    // trabajo parte 2

    kruskal(c);
    /*Kruskal ejemplo en clases
    GrafoND<int> k;
    CargoGrafoKruskal(k);
    kruskal(k);
    */
    /* Floyd ejemplo en clases
        int n= j.cantidadVertices();
        int ** costo=0;
        int ** A=0;
        int ** P=0;
        crearMatriz(A,n,n);
        crearMatriz(P,n,n);
        crearMatriz(costo,n,n);
        cargarcostoD(j,costo);
        floyd(A,costo,P,n);
        return 0;
    */
    /* Prim ejemplo en clases
        int n=e.cantidadVertices();
        int ** costo=0;
        crearMatriz(costo,n,n);
        cargarcostoND(e,costo);
        prim(costo,n);
    */
    /* Dijkstra ejemplo en clases
        int ** costo=0;
        int n=h.cantidadVertices();
        crearMatriz(costo,n,n);
        cargarcostoD(h,costo);
        dijkstra(h,1,costo);
    */
}
