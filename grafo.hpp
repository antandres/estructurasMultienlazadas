#ifndef GRAFO_H_
#define GRAFO_H_
#include "nodoArco.hpp"
#include <vector>
#include <list>
using namespace std;

template <typename Elemento>
class Grafo
{
    private:
        int cantVertices;
        NodoVertice<Elemento> * primero;

        //METODOS PRIVADOS
        list<Elemento> predecesores(NodoVertice<Elemento> *v);
        
    public:
    //CONSTRUCTORES
        void construir(); //PROBADO
        void construir(Elemento v); //PROBADO
        void construir(list<Elemento> vertices); //PROBADO
    
    //AGREGAR
        void agregarVertice(Elemento v); //PROBADO
        void agregarArco(Elemento vertice1, Elemento vertice2, float peso); //PROBADO

    //ELIMINAR
        void eliminarArco(Elemento v, Elemento w); //PROBADO
        void eliminarVertice(Elemento v);

    //GETTERS Y VERIFICACIONES
        int getCantVert(); //PROBADO
        NodoVertice<Elemento> * getPrimero(); //PROBADO
        float getPesoArco(Elemento v, Elemento w); //PROBADO
        bool esNulo(); //PROBADO
        bool existeArco(Elemento v, Elemento w); //PROBADO
        NodoVertice<Elemento> * getVertice(Elemento v);

    //SETTERS
        void setCantVert(int n); //PROBADO
        void setPrimero(NodoVertice<Elemento> * primero); //PROBADO
        void setPesoArco(Elemento v, Elemento w, float nuevoPeso); //PROBADO

    //LISTAS
        list<Elemento> sucesores(Elemento v);
        list<Elemento> predecesores(Elemento v);

    //IMPRIMIR
        void imprimirGrafo();

    //MAPEO
        int buscarMapeo(vector<Elemento> arreglo, Elemento elem, int dim);
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
void Grafo<Elemento>::eliminarArco(Elemento v, Elemento w)
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
    }   
}

template <typename Elemento>
void Grafo<Elemento>::eliminarVertice(Elemento v)
{
    NodoVertice<Elemento> *inicio = this->primero, *objetivo = nullptr;
    list<Elemento> conexiones;
    if(inicio != nullptr){
        conexiones = this->sucesores(v);
        while(!conexiones.empty()){
            this->eliminarArco(v,conexiones.front());
            conexiones.pop_front();
        }
        conexiones = this->predecesores(v);
        while(!conexiones.empty()){
            this->eliminarArco(conexiones.front(),v);
            conexiones.pop_front();
        }
        
        if(inicio->getInfo() == v){
            objetivo = inicio;
            this->primero = objetivo->getProxVert();
            objetivo->setProxVert(nullptr);

        }else{
            //ENCONTRAR VERTICE V
            while((inicio->getProxVert() != nullptr) && (inicio->getProxVert()->getInfo() != v)){
                inicio = inicio->getProxVert();
            }

            objetivo = inicio->getProxVert();

            if(objetivo == nullptr) return; //SI NO EXISTE EL VERTICE SALE DEL METODO

            inicio->setProxVert(objetivo->getProxVert());
            objetivo->setProxVert(nullptr);
        }
        delete objetivo;
        this->cantVertices = this->cantVertices - 1;
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
float Grafo<Elemento>::getPesoArco(Elemento v, Elemento w)
{
    NodoVertice<Elemento> *actual;
    NodoArco<Elemento> *aux;
    actual = this->primero;
    bool existe = false;
    if(actual != NULL)
    {
        while(!existe && (actual != NULL))
        {
            if(actual->getInfo() == v)
            {
                existe = true;
            }
            else
            {
            actual = actual->getProxVert();
            }
        }
        if(existe)
        {
            existe = false;
            aux = actual->getProxArc();
            if(aux != NULL)
            {
                while(!existe && (aux != NULL))
                {
                    if(aux->getInfo() == w)
                    {
                        existe = true;
                    }
                    else
                    {
                        aux = aux->getProxArc();
                    }
                }
                if(existe)
                {
                    return aux->getPeso();
                }
            }
        }
    }
    return -1;
}

template <typename Elemento>
bool Grafo<Elemento>::esNulo()
{
    return !this->cantVertices;
}

template <typename Elemento>
bool Grafo<Elemento>::existeArco(Elemento v, Elemento w)
{
    NodoVertice<Elemento> *actual;
    NodoArco<Elemento> *aux;
    actual = this->primero;
    bool existe = false;
    if(actual != NULL)
    {
        while(!existe && (actual != NULL))
        {
            if(actual->getInfo() == v)
            {
                existe = true;
            }
            else
            {
            actual = actual->getProxVert();
            }
        }
        if(existe)
        {
            existe = false;
            aux = actual->getProxArc();
            if(aux != NULL)
            {
                while(!existe && (aux != NULL))
                {
                    if(aux->getInfo() == w)
                    {
                        existe = true;
                    }
                    else
                    {
                        aux = aux->getProxArc();
                    }
                }
                if(existe)
                {
                    return true;
                }
            }
        }
    }
    return false;
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

template <typename Elemento>
void Grafo<Elemento>::setPesoArco(Elemento v, Elemento w, float nuevoPeso)
{
    NodoVertice<Elemento> *actual;
    NodoArco<Elemento> *aux;
    actual = this->primero;
    bool existe = false;
    if(actual != NULL)
    {
        while(!existe && (actual != NULL))
        {
            if(actual->getInfo() == v)
            {
                existe = true;
            }
            else
            {
            actual = actual->getProxVert();
            }
        }
        if(existe)
        {
            existe = false;
            aux = actual->getProxArc();
            if(aux != NULL)
            {
                while(!existe && (aux != NULL))
                {
                    if(aux->getInfo() == w)
                    {
                        existe = true;
                    }
                    else
                    {
                        aux = aux->getProxArc();
                    }
                }
                if(existe)
                {
                    aux->setPeso(nuevoPeso);
                }
            }
        }
    }
}

template <typename Elemento>
list<Elemento> Grafo<Elemento>::sucesores(Elemento v)
{
    list<Elemento> result;
    NodoVertice<Elemento> *actual;
    NodoArco<Elemento> *arco;
    if(this->primero != NULL)
    {
        actual = this->primero;
        while(actual->getProxVert() != NULL && (actual->getInfo() != v))
        {
            actual = actual->getProxVert();
        }
        if(actual->getInfo() == v)
        {
            arco = actual->getProxArc();
            while(arco != NULL)
            {
                result.push_back(arco->getInfo());
                arco = arco->getProxArc();
            }
        }
    }
    return result;
}

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
list<Elemento> Grafo<Elemento>::predecesores(NodoVertice<Elemento> *v){
    list<Elemento> lista;
    NodoVertice<Elemento> *inicio = this->primero;
    NodoArco<Elemento> *ady;
    if (v != nullptr){
        while (inicio != nullptr){
            if(inicio != v){
                ady = inicio->getProxArc();
                while(ady != nullptr){
                    NodoVertice<Elemento> *conexion = ady->getVertice();
                    //Si el vertice adyacente es el nodo buscado, se añade a la lista
                    if(conexion == v){
                        lista.push_back(inicio->getInfo());
                    }
                    ady=ady->getProxArc();
                }
            }
            inicio=inicio->getProxVert();
        }
    }

    return lista;
}

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
list<Elemento> Grafo<Elemento>::predecesores(Elemento v){
    return this->predecesores(this->getVertice(v));            
}

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
NodoVertice<Elemento> * Grafo<Elemento>::getVertice(Elemento v){
    NodoVertice<Elemento> *actual = this->primero;
    while(actual != nullptr){
        if(actual->getInfo() == v){
            return actual;
        }else{
            actual = actual->getProxVert();
        }
    }
    return nullptr;
}

//IMPORTADA DE OTRA LIBRERIA
template<typename Elemento>
int Grafo<Elemento>::buscarMapeo(vector<Elemento> arreglo, Elemento elem, int dim){
    int i = 0;
    for(i=0;i<dim;i++){
        if(arreglo.at(i) == elem){
            return(i);
        }
    }
    return -1;
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