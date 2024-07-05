#include <iostream>
#include "grafo.hpp"
#include <list>
using namespace std;

int main()
{
    list<int> lista;
    lista.push_back(1);
    lista.push_back(2);
    Grafo <int> prueba;
    prueba.construir(2);
    //prueba.setCantVert(7);
    //prueba.agregarVertice(3);
   // prueba.agregarVertice(4);
    //prueba.agregarArco(3, 4);
    cout << prueba.getCantVert();
    return 0;
}