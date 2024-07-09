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
        void agregarArco(Elemento vertice1, Elemento vertice2, float peso); //PROBADO

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
        list<Elemento> DFS();
        list<Elemento> BFS();

    //IMPRIMIR
        void imprimirGrafo();
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
    this->primero = new NodoVertice<Elemento>;
    this->primero->crear(vertices.front(), NULL, NULL);
    vertices.pop_front();
    this->cantVertices = 1;
    aux = this->primero;
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
void Grafo<Elemento>::agregarArco(Elemento v1, Elemento v2, float peso)
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
            if(auxAct->getVertice() == objetivo)
            {
                return;
            }
            else
            {
                nuevo = new NodoArco<Elemento>;
                nuevo->crear(peso, objetivo, NULL);
                auxAct->setProxArc(nuevo);
            }
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

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
void Grafo<Elemento>::imprimirGrafo(){
    NodoVertice<Elemento> *v = this->primero;  
    while(v != NULL){
        cout<< v->getInfo()<<" = ";
        NodoArco<Elemento> *a = v->getProxArc();
        while(a != nullptr){
            //ESCRITURA DEL ARCO -> (origen,destino)[peso]
            cout<< "("<< v->getInfo() << ", "<< a->getVertice()->getInfo() << ")[" << a->getPeso() <<"]  ";
            a=a->getProxArc();
        }
        v=v->getProxVert();
        cout<<endl;    
    }
}

#endif