/* Ejercicio 1 del trabajo practico 3 de la materia algoritmos y estructuras de datos 3
 * Para este ejercicio se tomo como referencia el algoritmo de Dijkstra
 * dado por la catedra en la clase 12 de camino minimo
 */

//Librerias
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
//+++++++++++++++++++++++++++++++++++++++++++
using namespace std;
int inf = 10000000;
//Variables Globales
//				nodo -distancia
vector<vector<pair<int,int>>> grafo,grafo2;
vector<int> distancia,distancia2;
vector<bool> visitado;
// La tupla va tener en la primer coordenada la distancia y en la segunda el nodo
priority_queue<pair<int,int>> q;
// s nodo inicia , t nodo final, n nodos , m aristas , k bidirecce
int s,t,n,m,k;
int caminoMinimo=inf;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Dijkstra (){
    //Hacemos dijkstra de s a t 
    distancia.assign(n+1,inf);
    visitado.assign(n+1,false);
    distancia[s]=0;
    q.push(make_pair(0,s));
    while (!q.empty()){
        int nodo =q.top().second;
        q.pop();
        if(visitado[nodo])continue;
        visitado[nodo]=true;
        for (auto u : grafo[nodo]) {
            if(u.second==0)continue;
            int dist = u.second;
            int vecino=u.first;
            if (distancia[nodo]+dist < distancia[vecino]) {
                distancia[vecino] = distancia[nodo]+dist;
                q.push({-distancia[vecino],vecino});
            }
        }
    }
    caminoMinimo=distancia[t];
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Dijkstra2 (){
    //Hacemos dijkstra de t a s 
    distancia2.assign(n+1,inf);
    visitado.assign(n+1,false);
    distancia2[t]=0;
    q.push(make_pair(0,t));
    while (!q.empty()){
        int nodo =q.top().second;
        q.pop();
        if(visitado[nodo])continue;
        visitado[nodo]=true;
        for (auto u : grafo2[nodo]) {
            if(u.second==0)continue;
            int dist = u.second;
            int vecino=u.first;
            if (distancia2[nodo]+dist < distancia2[vecino]) {
                distancia2[vecino] = distancia2[nodo]+dist;
                q.push({-distancia2[vecino],vecino});
            }
        }
    }
}
void Ejercicio1(){
    Dijkstra();
    Dijkstra2();
}

int main() {
    int w;cin>>w;
    while(w--){ //Lectura de cada test
        cin>>n>>m>>k>>s>>t;
        grafo.resize(n+1);
        grafo2.resize(n+1);
		//Leo las aristas del grafo 
        for (int j = 0; j <m ; ++j) {
            int d,c,l;cin>>d>>c>>l;
            grafo[d].push_back(make_pair(c,l));
            grafo2[c].push_back(make_pair(d,l));
        }
        Ejercicio1();
		//Por cada camino bidireccional veo cuando quedaria la distancia y si es inferior a la que tenia la guardo
        for (int j = 0; j <k ; ++j) {
            int d,c,l;cin>>d>>c>>l;
            int camino2= distancia[d] + l +distancia2[c];
            int camino = distancia[c] + l +distancia2[d];
            if((d==s &&c==t)|| (d== t && c==s))caminoMinimo=min(caminoMinimo,l);
            if(camino >0 && camino <caminoMinimo)caminoMinimo =camino;
            if(camino2 >0 && camino2 <caminoMinimo)caminoMinimo =camino2;

        }
		//Si no hay camino guardo -1
        if(caminoMinimo==inf)caminoMinimo=-1;
		//Imprimo el resultado 
        cout<<caminoMinimo<<endl;
		//Reseteo las variables globlales
        caminoMinimo=inf;
        grafo2.clear();
        grafo.clear();
        distancia.clear();
        distancia2.clear();
        visitado.clear();
    }
    return 0;
}
