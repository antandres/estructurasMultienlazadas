#include <iostream>
#include "grafoND.hpp"
#include <list>
#include <vector>
using namespace std;

int main()
{
    list<string> lista;
    vector<int> arreglo({1, 2, 3});
   /* lista.push_back(1);
    lista.push_back(2);
    lista.push_back(3);
    lista.push_back(4);
    lista.push_back(5);
    lista.push_back(6);*/
    GrafoNoDirigido <string> prueba;
    prueba.construir();
    //prueba.setCantVert(7);
    prueba.agregarVertice("hola");
    prueba.agregarVertice("andres");
    prueba.agregarVertice("games");
    prueba.agregarArco("games", "hola", 8);
    prueba.agregarArco("games", "andres", 4);
    lista = prueba.predecesores("games");
    //prueba.agregarArco(4, 3, 0);
    prueba.imprimirGrafo();
    cout << endl << lista.front() << " ";
    lista.pop_front();
    cout << endl << lista.front();
   // prueba.agregarVertice(4); 
    //prueba.agregarArco(3, 4);
    //cout << prueba.getPrimero()->getProxArc()->getVertice()->getInfo(); //  
    return 0;
}