#ifndef GRAFO_H_
#define GRAFO_H_
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
        void construir(); //PROBADO
        void construir(Elemento v); //PROBADO
        void construir(list<Elemento> vertices); //PROBADO
    
    //AGREGAR
        void agregarVertice(Elemento v); //PROBADO
        void agregarArco(Elemento vertice1, Elemento vertice2);

    //ELIMINAR
        void eliminarArco(Elemento vertice1, Elemento vertice2);
        void eliminarVertice(Elemento v);

    //GETTERS Y VERIFICACIONES
        int getCantVert();
        NodoVertice<Elemento> * getPrimero();
        bool esNulo();

    //SETTERS
        void setCantVert(int n);
        void setPrimero(NodoVertice<Elemento> * primero);

    //LISTAS
        list<Elemento> vecinos();
        list<Elemento> DFS();
        list<Elemento> BFS();
};

template <typename Elemento>
void Grafo<Elemento>::construir()
{
    this->cantVertices = 0;
    this->primero = NULL;
}

template <typename Elemento>
void Grafo<Elemento>::construir(Elemento v)
{
    this->cantVertices = 1;
    this->primero = new NodoVertice<Elemento>;
    this->primero->crear(v, NULL, NULL);
}

template <typename Elemento>
void Grafo<Elemento>::construir(list<Elemento> vertices)
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
        aux->setProxVert(new NodoVertice<Elemento>);
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
        this->primero = new NodoVertice<Elemento>;
        this->primero->setInfo(v);
        this->cantVertices = this->cantVertices + 1;
    }
    else
    {
        aux = this->primero;
        while(aux->getProxVert() != NULL && !existe)
        {
            if(aux->getInfo() == v)
            {
                existe = true;
            }
            aux = aux->getProxVert();
        }
        if(aux->getInfo() != v && !existe)
        {
            aux->setProxVert(new NodoVertice<Elemento>);
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
    return !this->cantVertices;
}

template <typename Elemento>
void Grafo<Elemento>::setCantVert(int n)
{
    this->cantVertices = n;
}

template <typename Elemento>
void Grafo<Elemento>::setPrimero(NodoVertice<Elemento> * primero)
{
    this->primero = primero;
}

#endif