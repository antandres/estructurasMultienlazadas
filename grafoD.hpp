#ifndef GRAFO_D_H_
#define GRAFO_D_H_
#include <vector>
#include <list>
#include "grafo.hpp"

template <typename Elemento>
class GrafoDirigido: public Grafo<Elemento>
{
    public:
    //MAPEADO
        GrafoDirigido<int> mapear(vector<Elemento> *mapeo);
        
    //LISTAS
        list<Elemento> listaDFS(Elemento inicio);
        list<Elemento> listaBFS(Elemento inicio);
};

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
GrafoDirigido<int> GrafoDirigido<Elemento>::mapear(vector<Elemento> *mapeo){
    NodoVertice<Elemento> *actual = this->getPrimero();
    int i=0, dim=this->getCantVert();
    GrafoDirigido<int> grafo;
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

template <typename Elemento>
list<Elemento> GrafoDirigido<Elemento>::listaDFS(Elemento inicio)
{
    vector<Elemento> mapeo;
    GrafoDirigido<int> mapeado = this->mapear(&mapeo);
    list<int> recorrido;
    vector<bool> visitados;
    int i = 0;
    for(i; i < this->getCantVert(); i++)
    {
        visitados.emplace_back(false);
    }
    int v = this->buscarMapeo(mapeo, inicio, mapeado.getCantVert());
    visitados.at(v) = true;
    mapeado.DFS(v, &visitados, &recorrido);
    
    list<Elemento> recorridoFinal;
    while(!recorrido.empty())
    {
        recorridoFinal.push_back(mapeo.at(recorrido.front()));
        recorrido.pop_front();
    }
    return recorridoFinal;
}

template <typename Elemento>
list<Elemento> GrafoDirigido<Elemento>::listaBFS(Elemento inicio)
{
    vector<Elemento> mapeo;
    GrafoDirigido<int> mapeado = this->mapear(&mapeo);
    list<int> recorrido;
    vector<bool> visitados;
    int i = 0;
    for(i; i < this->getCantVert(); i++)
    {
        visitados.emplace_back(false);
    }
    int v = this->buscarMapeo(mapeo, inicio, mapeado.getCantVert());
    mapeado.BFS(v, &visitados, &recorrido);
    
    list<Elemento> recorridoFinal;
    while(!recorrido.empty())
    {
        recorridoFinal.push_back(mapeo.at(recorrido.front()));
        recorrido.pop_front();
    }
    return recorridoFinal;
}


#endif