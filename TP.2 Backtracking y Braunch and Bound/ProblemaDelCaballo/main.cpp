#include <iostream>
#include <iomanip>

using namespace std;

//----------------------------Crear matriz---------------------------------------------------------

void crearMatriz(int ** & matriz,const int & columna,const int & fila)
{
    matriz = new int*[fila];
    for (int f = 0; f <= fila; f++)
        matriz[f] = new int[columna];
}

//----------------------------Cargar Matriz vacia-------------------------

void cargarMatriz(int ** & matriz,const int & columna,const int & fila)
{
    for(int i=1; i<=columna; i++)
        for(int j=1; j<=fila; j++)
            matriz[i][j]= 0 ;
}

//-------------------------------Imprimir matriz--------------------------------------------------

void mostrarMatriz(int **matriz, int columna, int fila)
{
    for (int f = 1; f <= fila; f++)
    {
        for (int c = 1; c <= columna; c++)
            cout <<setw(5) << matriz[f][c] << "  ";
        cout << "\n";
    }
    cout<< "-------------------------------------------------------" << endl;
}

//----------------------------------Problema caballo--------------------------------------
bool poda(pair<int,int> nuevacasilla, const int n, int **tablero)
{
    bool valido=false;
    if ((nuevacasilla.first>0)&&(nuevacasilla.first<=n))
        if((nuevacasilla.second>0)&&(nuevacasilla.second<=n))
            if (tablero[nuevacasilla.first][nuevacasilla.second]==0)
                valido=true;
    if (!valido)
        return false;
    else
        return true;

}

int movimiento(int **& tablero,pair<int,int> & nuevacasilla,int mov,const int arrfila[], const int arrcolumna[])
{
    nuevacasilla.first= nuevacasilla.first + arrfila[mov];
    nuevacasilla.second= nuevacasilla.second + arrcolumna[mov];
}
bool es_adyacente(pair<int,int> inic_casilla,pair<int,int> casilla, const int arrfila[], const int arrcolumna[])
{
    bool adyacente=false;
    for(int i=0;i<8;i++)
    {
        if((casilla.first + arrfila[i])== inic_casilla.first)
            if((casilla.second + arrcolumna[i])==inic_casilla.second)
                adyacente=true;
    }
    return adyacente;
}

bool RecorridoCaballo(pair<int,int> inic_casilla,pair<int,int> casilla, const int n, int nropisada,int **&tablero, const int arrfila[], const int arrcolumna[])
{
    tablero[casilla.first][casilla.second]=nropisada;
    if(nropisada==(n*n))
    {
        if (es_adyacente(inic_casilla,casilla,arrfila,arrcolumna))
            mostrarMatriz(tablero,n,n);
    }
    else
    {
        for(int mov=0;mov<8;mov++){
            pair<int,int> nuevacasilla= casilla;
            movimiento(tablero,nuevacasilla,mov,arrfila,arrcolumna);
            if(poda(nuevacasilla,n,tablero)==true)
            {
                RecorridoCaballo(inic_casilla,nuevacasilla,n,nropisada+1,tablero,arrfila,arrcolumna);
                tablero[nuevacasilla.first][nuevacasilla.second]=0;
            }
        }
    }
}

//-------------------------------- main ----------------------------------

int main()
{
    unsigned int a,b,n=0;
    int nropisada=1;
    int arrfila[8]={-1,-2,-2,-1,1,2,2,1};
    int arrcolumna[8]={2,1,-1,-2,-2,-1,1,2};
    int **tablero=0;
    cout << "Ingrese la cantidad de columnas/filas del tablero:  " ;
    cin >> n;
    crearMatriz(tablero,n+1,n+1);
    cargarMatriz(tablero,n+1,n+1);
    a=5;
    b=1;
    pair <int,int> casilla;
    casilla.first=a;
    casilla.second=b;
    pair <int,int> inic_casilla;
    inic_casilla.first=a;
    inic_casilla.second=b;
    RecorridoCaballo(inic_casilla,casilla,n,nropisada,tablero,arrfila,arrcolumna);
    return 0;
}
