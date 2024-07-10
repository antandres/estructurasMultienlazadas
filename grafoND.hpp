#ifndef GRAFO_ND_H_
#define GRAFO_ND_H_
#include "grafo.hpp"
#include <list>


template <typename Elemento>
class GrafoNoDirigido: public Grafo<Elemento>
{
    public:
        void agregarArco(Elemento v1, Elemento v2, float peso);
        void eliminarArco(Elemento v, Elemento w);
        list<Elemento> vecinos(Elemento v);
        GrafoNoDirigido<int> mapear(vector<Elemento> *mapeo);

};

template <typename Elemento>
void GrafoNoDirigido<Elemento>::agregarArco(Elemento v1, Elemento v2, float peso)
{
    NodoVertice<Elemento> *actual, *objetivo = NULL;
    NodoArco<Elemento> *auxAct, *nuevo;
    if(v1 != v2)
    {
        actual = this->getPrimero();
        while((actual->getInfo() != v1)&&(actual->getProxVert() != NULL))
        {
            if(actual->getInfo() == v2)
            {
                objetivo = actual;
            }
            actual = actual->getProxVert();
        }
        if(actual->getInfo() != v1)
        {
            return;
        }

        if(objetivo == NULL)
        {
            objetivo = actual->getProxVert();
            if(objetivo == NULL)
            {
                return;
            }
            while((objetivo->getInfo() != v2)&&(objetivo->getProxVert() != NULL))
            {
                objetivo = objetivo->getProxVert();
            }
            if(objetivo->getInfo() != v2)
            {
                return;
            }
        }
        
        if(actual->getProxArc() == NULL)
        {
            nuevo = new NodoArco<Elemento>;
            nuevo->crear(peso, objetivo, NULL);
            actual->setProxArc(nuevo);
        }
        else
        {
            auxAct = actual->getProxArc();
            while((auxAct->getVertice() != objetivo)&&(auxAct->getProxArc() != NULL))
            {
                auxAct = auxAct->getProxArc();
            }
            if(auxAct->getVertice() != objetivo)
            {
                nuevo = new NodoArco<Elemento>;
                nuevo->crear(peso, objetivo, NULL);
                auxAct->setProxArc(nuevo);
            }
        }

        if(objetivo->getProxArc() == NULL)
        {
            nuevo = new NodoArco<Elemento>;
            nuevo->crear(peso, actual, NULL);
            objetivo->setProxArc(nuevo);
        }
        else
        {
            auxAct = objetivo->getProxArc();
            while((auxAct->getVertice() != actual)&&(auxAct->getProxArc() != NULL))
            {
                auxAct = auxAct->getProxArc();
            }
            if(auxAct->getVertice() == actual)
            {
                return;
            }
            else
            {
                nuevo = new NodoArco<Elemento>;
                nuevo->crear(peso, actual, NULL);
                auxAct->setProxArc(nuevo);
            }
        }
    }
}

template <typename Elemento>
void GrafoNoDirigido<Elemento>::eliminarArco(Elemento v, Elemento w)
{
    NodoVertice<Elemento> *actual, *objetivo = NULL;
    NodoArco<Elemento> *auxAct, *borrar;
    if(v != w)
    {
        actual = this->getPrimero();
        while((actual->getInfo() != v)&&(actual->getProxVert() != NULL))
        {
            if(actual->getInfo() == w)
            {
                objetivo = actual;
            }
            actual = actual->getProxVert();
        }
        if(actual->getInfo() != v)
        {
            return;
        }

        if(objetivo == NULL)
        {
            objetivo = actual->getProxVert();
            if(objetivo == NULL)
            {
                return;
            }
            while((objetivo->getInfo() != w)&&(objetivo->getProxVert() != NULL))
            {
                objetivo = objetivo->getProxVert();
            }
            if(objetivo->getInfo() != w)
            {
                return;
            }
        }
        
        if(actual->getProxArc() == NULL)
        {
            return;
        }
        else
        {
            if(actual->getProxArc()->getVertice() == objetivo)
            {
                borrar = actual->getProxArc();
                actual->setProxArc(borrar->getProxArc());
                delete borrar;
            }
            else
            {
                auxAct = actual->getProxArc();
                borrar = auxAct->getProxArc();
                while(borrar->getVertice() != objetivo && borrar != NULL)
                {
                    auxAct = borrar;
                    borrar = borrar->getProxArc();
                }
                if(borrar != NULL)
                {
                    auxAct->setProxArc(borrar->getProxArc());
                    delete borrar;
                }
            }
        }
        if(objetivo->getProxArc() == NULL)
        {
            return;
        }
        else
        {
            if(objetivo->getProxArc()->getVertice() == actual)
            {
                borrar = objetivo->getProxArc();
                objetivo->setProxArc(borrar->getProxArc());
                delete borrar;
            }
            else
            {
                auxAct = objetivo->getProxArc();
                borrar = auxAct->getProxArc();
                while(borrar->getVertice() != actual && borrar != NULL)
                {
                    auxAct = borrar;
                    borrar = borrar->getProxArc();
                }
                if(borrar != NULL)
                {
                    auxAct->setProxArc(borrar->getProxArc());
                    delete borrar;
                }
            }
        }
    }   
}

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
GrafoNoDirigido<int> GrafoNoDirigido<Elemento>::mapear(vector<Elemento> *mapeo){
    NodoVertice<Elemento> *actual = this->getPrimero();
    int i=0, dim=this->getCantVert();
    GrafoNoDirigido<int> grafo;
    NodoArco<Elemento> *arco;
    grafo.construir();
    //MAPEAR Y AGREGAR VERTICES AL GRAFO MAPEADO
    while(actual!=nullptr){
        mapeo->emplace_back(actual->getInfo());
        grafo.agregarVertice(i);
        actual=actual->getProxVert();
        i++;
    }

    //AGREGAR ARCOS AL GRAFO MAPEADO
    actual = this->getPrimero();
    i=0;
    while(actual != nullptr){
        arco = actual->getProxArc();
        while(arco != nullptr){
            int v = this->buscarMapeo(*mapeo, arco->getInfo(), dim);
            grafo.agregarArco(i,v, arco->getPeso());
            arco=arco->getProxArc();
        }
        actual=actual->getProxVert();
        i++;
    }

    return grafo;
}

#endif