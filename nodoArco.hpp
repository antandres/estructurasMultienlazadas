#ifndef NODOARCO_H_
#define NODOARCO_H_
#include "nodoVertice.hpp"

template <typename Elemento>
class NodoArco
{
    private:
        float peso;
        NodoVertice<Elemento> *vertice;
        NodoArco<Elemento> *proxArc;
    public:
        void construir();
        void crear(float peso, NodoVertice<Elemento> *vertice, NodoArco<Elemento> *proxArc);
        float getPeso();
        NodoVertice<Elemento> * getVertice();
        NodoArco<Elemento> * getProxArc();
        void setPeso(float peso);
        void setVertice(NodoVertice<Elemento> * vertice);
        void setProxArc(NodoArco<Elemento> * proxArc);
};

template <typename Elemento>
void NodoArco<Elemento>::construir()
{
    this->peso = 0;
    this->proxArc = NULL;
    this->vertice = NULL;
}

template <typename Elemento>
void NodoArco<Elemento>::crear(float peso, NodoVertice<Elemento> *vertice, NodoArco<Elemento> *proxArc)
{
    this->peso = peso;
    this->proxArc = proxArc;
    this->vertice = vertice;
}

template <typename Elemento>
float NodoArco<Elemento>::getPeso()
{
    return this->peso;
}

template <typename Elemento>
NodoVertice<Elemento> * NodoArco<Elemento>::getVertice()
{
    return this->vertice;
}

template <typename Elemento>
NodoArco<Elemento> * NodoArco<Elemento>::getProxArc()
{
    return this->proxArc;
}

template <typename Elemento>
void NodoArco<Elemento>::setPeso(float peso)
{
    this->peso = peso;
}

template <typename Elemento>
void NodoArco<Elemento>::setVertice(NodoVertice<Elemento> * vertice)
{
    this->vertice = vertice;
}

template <typename Elemento>
void NodoArco<Elemento>::setProxArc(NodoArco<Elemento> * arco)
{
    this->proxArc = arco;
}

#endif