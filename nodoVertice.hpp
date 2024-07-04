#ifndef NODOVERTICE_H_
#define NODOVERTICE_H_
#include "nodoArco.hpp"

template <typename Elemento>
class NodoVertice
{
    private:
        Elemento info;
        NodoVertice<Elemento> *proxVert;
        NodoArco<Elemento> *proxArc;
    public:
        NodoVertice();
        NodoVertice(Elemento e);
        void crear(Elemento e, NodoVertice<Elemento>* proxVert, NodoArco<Elemento> * proxArc);
        Elemento getInfo();
        NodoVertice<Elemento> * getProxVert();
        NodoArco<Elemento> * getProxArc();
        void setInfo(Elemento e);
        void setProxVert(NodoVertice<Elemento> *vertice);
        void setProxArc(NodoArco<Elemento> *arco);

};

template <typename Elemento>
NodoVertice<Elemento>::NodoVertice()
{
    this->info = " ";
    this->proxArc = NULL;
    this->proxVert = NULL;
}

template <typename Elemento>
NodoVertice<Elemento>::NodoVertice(Elemento e)
{
    this->info = e;
    this->proxArc = NULL;
    this->proxVert = NULL;
}

template <typename Elemento>
void NodoVertice<Elemento>::crear(Elemento e, NodoVertice<Elemento>* proxVert, NodoArco<Elemento>* proxArc)
{
    this->info = e;
    this->proxVert = proxVert;
    this->proxArc = proxArc;
}

template <typename Elemento>
Elemento NodoVertice<Elemento>::getInfo()
{
    return this->info;
}

template <typename Elemento>
NodoVertice<Elemento> * NodoVertice<Elemento>::getProxVert()
{
    return this->proxVert;
}

template <typename Elemento>
NodoArco<Elemento> * NodoVertice<Elemento>::getProxArc()
{
    return this->proxArc;
}

template <typename Elemento>
void NodoVertice<Elemento>::setInfo(Elemento e)
{
    this->info = e;
}

template <typename Elemento>
void NodoVertice<Elemento>::setProxVert(NodoVertice<Elemento> * vertice)
{
    this->proxVert = vertice;
}

template <typename Elemento>
void NodoVertice<Elemento>::setProxArc(NodoArco<Elemento> * arco)
{
    this->proxArc = arco;
}

#endif