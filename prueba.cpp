#include <iostream>
#include "grafo.hpp"
#include <list>
using namespace std;

int main()
{
    list<int> lista;
   /* lista.push_back(1);
    lista.push_back(2);
    lista.push_back(3);
    lista.push_back(4);
    lista.push_back(5);
    lista.push_back(6);*/
    Grafo <int> prueba;
    prueba.construir();
    //prueba.setCantVert(7);
    prueba.agregarVertice(3);
    prueba.agregarVertice(4);
    prueba.agregarArco(3, 4, 0);
    prueba.agregarArco(4, 3, 2);
    prueba.imprimirGrafo();
   // prueba.agregarVertice(4);
    //prueba.agregarArco(3, 4);
    //cout << prueba.getPrimero()->getProxArc()->getVertice()->getInfo(); // 
    return 0;
}