#ifndef GRAFOND_H
#define GRAFOND_H
#include <list>
#include <map>

using namespace std;

template <typename C> class GrafoND
{
public:
	class Arista
	{
	public:
		Arista();
		Arista(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
    protected:

	private:
		int vertice;
		C costo;
	}; // class Arista

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	GrafoND();
	GrafoND(const GrafoND & otroGrafo);

	~GrafoND();

	GrafoND & operator = (const GrafoND & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;

	// Devuelve la cantidad de vértices del grafo
	int cantidadVertices() const;

	bool existeVertice(int vertice) const;

	bool existeArista(int origen, int destino) const;

	// PRE CONDICION: existeArista(origen, destino)
	int costoArista(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<Arista> & adyacentes) const;

	void agregarVertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArista(v, vertice) && !existeArista(vertice, v)
	bool eliminarVertice(int vertice);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArista(origen, destino)
	//return true si se pudo eliminar el arco y falso en caso contrario
	bool agregarArista(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArista(origen, destino)
	bool eliminarArco(int origen, int destino);

	// PRE CONDICION: existeArista(origen, destino)
	void modificarcostoArista(int origen, int destino, const C & costo);

	void vaciar();
protected:


private:
	/*
	 Definir la estructura interna
	 */
    map<int, map<int, C> > grafo;

}; // class Grafo

/*
 Arista
 */

template <typename C> GrafoND<C>::Arista::Arista()
{
}

template <typename C> GrafoND<C>::Arista::Arista(int adyacente, const C & costo)
{
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C> int GrafoND<C>::Arista::devolverAdyacente() const
{
    return vertice;
}

template <typename C> const C & GrafoND<C>::Arista::devolverCosto() const
{
    return costo;
}

template <typename C> GrafoND<C>::GrafoND()
{

}

template <typename C> GrafoND<C>::GrafoND(const GrafoND & otroGrafo)
{
    this->operator=(otroGrafo);
}

template <typename C> GrafoND<C>::~GrafoND()
{

}

template <typename C> GrafoND<C> & GrafoND<C>::operator = (const GrafoND & otroGrafo)
{
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()) {
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
    return *this;
}

template <typename C> bool GrafoND<C>::estaVacio() const
{
    return (grafo.empty());
}

template <typename C> int GrafoND<C>::cantidadVertices() const
{
    return (grafo.size());
}

template <typename C> bool GrafoND<C>::existeVertice(int vertice) const
{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C> bool GrafoND<C>::existeArista(int origen, int destino) const
{
    bool result = false;
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            result = true;
    }
    return result;
}

template <typename C> void GrafoND<C>::devolverVertices(list<int> & vertices) const
{
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end())
    {
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C> void GrafoND<C>::devolverAdyacentes(int origen, list<Arista> & adyacentes) const
{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arista(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C> void GrafoND<C>::agregarVertice(int vertice)
{
    if (grafo.find(vertice) == grafo.end()) {
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C> bool GrafoND<C>::agregarArista(int origen, int destino, const C & costo)
{

    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if ( (itV != grafo.end() ) && existeVertice(destino)){
        itV->second[destino] = costo;
        itV=grafo.find(destino);
        if((itV!=grafo.end())&& existeVertice(origen))
            itV->second[origen] = costo;
        return true;
        }
    else return false;
}

template <typename C> void GrafoND<C>::vaciar()
{
    grafo.clear();
}

template <typename C> bool GrafoND<C>::eliminarVertice(int vertice)
{
    if (existeVertice(vertice))
    {
        grafo.erase(vertice);
        typename map<int, map<int, C> >::iterator itV = grafo.begin();
        typename map<int, C> ::iterator itA = itV->second.begin();
        while (itV!=grafo.end())
        {
            itA = itV->second.begin();
            while (itA!=itV->second.end())
            {
                if (itA->first==vertice)
                    itV->second.erase(itA);
                itA++;
            }
            itV++;
        }
        return true;
    }
   else  return false;
}

template <typename C> bool GrafoND<C>::eliminarArco(int origen, int destino)
{
    if ((existeVertice(origen)) && (existeVertice(destino)) && (existeArista(origen,destino)))
    {
        typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
        typename map<int, C>::iterator itA = itV->second.find(destino);
        itV->second.erase(itA);
        return true;
    }
    else return false;
}

template <typename C> int GrafoND<C>::costoArista(int origen, int destino) const
{
    if ((existeVertice(origen)) && (existeVertice(destino)) && (existeArista(origen,destino)))
    {
        typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        return itA->second;
    }
    else return -1;
}

template <typename C> void GrafoND<C>::modificarcostoArista(int origen, int destino, const C & costo)
{
    if ((existeVertice(origen)) && (existeVertice(destino)) && (existeArista(origen,destino)))
    {
        typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
        typename map<int, C>::iterator itA = itV->second.find(destino);
        itA->second = costo;
    }

}

#endif
