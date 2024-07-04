#ifndef GRAFO_H_
#define GRAFO_H_
#include "nodoVertice.hpp"
#include "nodoArco.hpp"
#include <list>
using namespace std;

template <typename Elemento>
class Grafo
{
    private:
        int cantVertices;
        NodoVertice<Elemento> * primero;
    public:
    //CONSTRUCTORES
        Grafo();
        Grafo(Elemento v);
        Grafo(list<Elemento> vertices);
    
    //AGREGAR
        void agregarVertice(Elemento v);
        void agregarArco(Elemento vertice1, Elemento vertice2);

    //ELIMINAR
        void eliminarArco(Elemento vertice1, Elemento vertice2);
        void eliminarVertice(Elemento v);

    //GETTERS Y VERIFICACIONES
        int getCantVert();
        NodoVertice<Elemento> * getPrimero();
        bool esNulo();

    //SETTERS
        void setCantVert();
        void setPrimero(NodoVertice<Elemento> * primero);

};

template <typename Elemento>
Grafo<Elemento>::Grafo()
{
    this->cantVertices = 0;
    this->primero = NULL;
}

template <typename Elemento>
Grafo<Elemento>::Grafo(Elemento v)
{
    this->cantVertices = 1;
    this->primero = new NodoVertice<Elemento>;
    this->primero->crear(v, NULL, NULL);
}

template <typename Elemento>
Grafo<Elemento>::Grafo(list<Elemento> vertices)
{
    NodoVertice<Elemento> * aux;
    if(this->cantVertices == 0)
    {
        this->primero = new NodoVertice<Elemento>;
        this->primero->crear(vertices.front(), NULL, NULL);
        vertices.pop_front();
        this->cantVertices = this->cantVertices + 1;
        aux = this->primero;
    }
    while(!vertices.empty())
    {
        aux->getProxVert() = new NodoVertice<Elemento>;
        aux->getProxVert()->crear(vertices.front(), NULL, NULL);
        vertices.pop_front();
        this->cantVertices = this->cantVertices + 1;
        aux = aux->getProxVert();
    }
}

template <typename Elemento>
void Grafo<Elemento>::agregarVertice(Elemento v)
{
    bool existe = false;
    NodoVertice<Elemento> * aux;
    if(this->cantVertices == 0)
    {
        this->Grafo(v);
    }
    else
    {
        aux = this->primero;
        while(aux->getProxVert() != NULL && !existe)
        {
            if(aux->getInfo == v)
            {
                existe = true;
            }
            aux = aux->getProxVert();
        }
        if(aux->getInfo() != v && !existe)
        {
            aux->getProxVert() = new NodoVertice<Elemento>;
            aux->getProxVert()->crear(v, NULL, NULL);
            this->cantVertices = this->cantVertices + 1;
        }
    }
}

template <typename Elemento>
int Grafo<Elemento>::getCantVert()
{
    return this->cantVertices;
}

template <typename Elemento>
NodoVertice<Elemento> *Grafo<Elemento>::getPrimero()
{
    return this->primero;
}

template <typename Elemento>
bool Grafo<Elemento>::esNulo()
{
    return this->cantVertices;
}

#endif