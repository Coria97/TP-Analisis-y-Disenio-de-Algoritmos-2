#include <iostream>
#include "punto.h"
#include "segmento.h"
#include <list>

#include <windows.h>
#include <mmsystem.h>

using namespace std;



void imprimir(list<punto> listapuntos)
{
    list<punto>::iterator it=listapuntos.begin();
    while (it!=listapuntos.end())
    {
        cout << "(" << it->coordx() << ", " << it->coordy() << ")" << endl;
        it++;
    }
}
//---------------------------------ejercicio 1 --------------------------------------------

void carga_puntos(list<punto> & listapuntos)
{
    punto p1(6,3);
    punto p2(7,6);
    punto p3(1,6);
    punto p4(-2,3);
    punto p5(1,1);
    punto p6(3,-2);
    punto p7(9,0);
    listapuntos.push_back(p1);
    listapuntos.push_back(p2);
    listapuntos.push_back(p3);
    listapuntos.push_back(p4);
    listapuntos.push_back(p5);
    listapuntos.push_back(p6);
    listapuntos.push_back(p7);
    listapuntos.push_back(p1);
}

float calcular_area(list<punto> listapuntos,const punto aux)
{
    list<punto> :: iterator it= listapuntos.begin();
    float area=0;
    punto a=aux;
    while(it!=listapuntos.end())
    {
        punto b=*it;
        area= area + (0.5 * a.prod_cruzado(b));
        a=*it;
        it++;
    }
    area= area + (0.5 * a.prod_cruzado(aux));
    if (area<0)
        area=area*(-1);
    return area;
}


//---------------------------------ejercicio 2 --------------------------------------------
void buscar_menor_punto_en_y(list<punto> listapuntos,punto & menor)
{
    list<punto>::iterator it=listapuntos.begin();
    while (it!=listapuntos.end())
    {
        punto aux=*it;
        if ((aux.coordy()) < (menor.coordy()))
            menor=*it;
        it++;
    }
}
void buscar_mayor_punto_en_y(list<punto> listapuntos,punto & mayor)
{
    list<punto>::iterator it=listapuntos.begin();
    while (it!=listapuntos.end())
    {
        punto aux=*it;
        if ((aux.coordy()) > (mayor.coordy()))
            mayor=*it;
        it++;
    }
}

void mejor_punto_cadena_der(const punto & p0, const punto & p1,const punto & p2,punto & posible_punto)
{
    if (p1!=p2)
    {
        punto aux1=p1;
        punto aux2=p2;
        aux1-p0;
        aux2-p0;
        if ((aux1.prod_cruzado(aux2)) > 0)
            posible_punto = p1;
        else
        {
            if ((aux1.prod_cruzado(aux2)) < 0)
                posible_punto = p2;
            else
            {
                if ((aux1.coordy()) > (aux2.coordy()))
                    posible_punto=p1;
                else
                    posible_punto=p2;
            }
        }
    }
    else
        posible_punto=p1;
}

void mejor_punto_cadena_izq(const punto & p0, const punto & p1,const punto & p2,punto & posible_punto)
{
    if (p1!=p2)
    {
        punto aux1=p1;
        punto aux2=p2;
        aux1-p0;
        aux2-p0;
        if ((aux1.prod_cruzado(aux2)) > 0)
            posible_punto = p1;
        else
        {
            if ((aux1.prod_cruzado(aux2)) < 0)
                posible_punto = p2;
            else
            {
                if ((aux1.coordy()) < (aux2.coordy()))
                    posible_punto=p1;
                else
                    posible_punto=p2;
            }
        }
    }
    else
        posible_punto=p1;
}

void jarvis (list<punto> listapuntos, list<punto> & convexhull)
{
    punto menor(9999,9999);
    punto mayor(-9999,-9999);
    buscar_menor_punto_en_y(listapuntos,menor);
    buscar_mayor_punto_en_y(listapuntos,mayor);
    list<punto>:: iterator it=listapuntos.begin();
    punto p1=*it;
    it++;
    punto p2=*it;
    if(p1==menor)
    {
        it++;
        p1=*it;
    }
    else
        if(p2==menor)
        {
            it++;
            p2=*it;
        }
    punto actual=menor;
    punto posible_punto(0,0);
    //calculo cadena derecha
    while (actual!=mayor)
    {
        it=listapuntos.begin();
        while (it!=listapuntos.end())
        {
            mejor_punto_cadena_der(actual, p1,p2, posible_punto);
            p1=posible_punto;
            p2=*it;
            it++;
        }
        actual=p1;
        convexhull.push_back(actual);
    }
    //calculo cadena izquierda
    while (actual!=menor)
    {
        it=listapuntos.begin();
        while (it!=listapuntos.end())
        {
            mejor_punto_cadena_izq(actual, p1, p2, posible_punto);
            p1=posible_punto;
            p2=*it;
            it++;
        }
        actual=p1;
        convexhull.push_back(actual);
    }
}

void inicializa (list<punto> & nube)
{
    punto p1(-10,-1);
    punto p2(-10,0);
    punto p3(-7,8);
    punto p4(-4,6);
    punto p5(2,6);
    punto p6(6,4);
    punto p7(8,6);
    punto p8(7,-2);
    punto p9(4,-6);
    punto p10(8,-7);
    punto p11(0,0);
    punto p12(3,-2);
    punto p13(6,-10);
    punto p14(0,-6);
    punto p15(-9,-5);
    punto p16(-8,-2);
    punto p17(-8,0);
    punto p18(-10,3);
    punto p19(-2,2);
    punto p20(-10,4);
    nube.push_front(p1);
    nube.push_front(p2);
    nube.push_front(p3);
    nube.push_front(p4);
    nube.push_front(p5);
    nube.push_front(p6);
    nube.push_front(p7);
    nube.push_front(p8);
    nube.push_front(p9);
    nube.push_front(p10);
    nube.push_front(p11);
    nube.push_front(p12);
    nube.push_front(p13);
    nube.push_front(p14);
    nube.push_front(p15);
    nube.push_front(p16);
    nube.push_back(p17);
    nube.push_back(p18);
    nube.push_back(p19);
    nube.push_back(p20);
}

int main()
{
    list<punto> poligono;
    //-------- ej1---------
    carga_puntos(poligono);
    punto referencia(-2,-2);
    cout << "el area del poligono calculandola a partir del punto referencia es de: " << calcular_area(poligono,referencia) << endl;

    //-------- ej2---------
    list<punto> nube;
    list<punto> convexhull;
    inicializa(nube);
    jarvis(nube,convexhull);
    cout << "los puntos que pertenecen al convexhull son: " << endl;
    imprimir(convexhull);
    return 0;
}
