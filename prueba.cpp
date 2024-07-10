#include <iostream>
#include "grafoND.hpp"
#include "grafoD.hpp"
#include <list>
#include <vector>
using namespace std;

int main()
{
    list<string> lista;
    vector<string> arreglo;

    //LLENADO DE LISTA
   /* lista.push_back(1);
    lista.push_back(2);
    lista.push_back(3);
    lista.push_back(4);
    lista.push_back(5);
    lista.push_back(6);*/


    GrafoNoDirigido <string> prueba;
    GrafoNoDirigido<int> mapeado;
    prueba.construir();
    //prueba.setCantVert(7);
    prueba.agregarVertice("hola");
    prueba.agregarVertice("andres");
    prueba.agregarVertice("games");
    prueba.agregarArco("games", "hola", 8);
    prueba.agregarArco("games", "andres", 4);
    lista = prueba.vecinos("andres");
    //mapeado = prueba.mapear(&arreglo);
    //mapeado.imprimirGrafo();


    //lista = prueba.vertices();
    //prueba.agregarArco(4, 3, 0);
    //prueba.imprimirGrafo();
    cout << endl << lista.front() << " ";
    lista.pop_front();
    /*cout << endl << lista.front() << " ";
    /ista.pop_front();
    cout << endl << lista.front();*/
   // prueba.agregarVertice(4); 
    //prueba.agregarArco(3, 4);
    //cout << prueba.getPrimero()->getProxArc()->getVertice()->getInfo(); //  
    return 0;
}