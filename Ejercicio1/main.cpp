//Librerias
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
//+++++++++++++++++++++++++++++++++++++++++++
using namespace std;
int inf = 1e28;
//Variables Globales
//distancia y despues nodo
vector<vector<pair<int,int>>> grafo,grafo2;
vector<int> distancia,distancia2;
vector<bool> visitado;
// La tupla va tener en la primer coordenada la distancioa y en la segunda el nodo
priority_queue<pair<int,int>> q;
// s nodo inicia , t nodo final, n nodos , m aristasw k bidirecce
int s,t,n,m,k;
int caminoMinimo=inf;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Dijkstra (){
    //Nunca uso la primer coordenada de la cola
    distancia.assign(n+1,inf);
    visitado.assign(n+1,false);
    distancia[0]=0;
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
    //Nunca uso la primer coordenada de la cola
    distancia2.assign(n+1,inf);
    visitado.assign(n+1,false);
    distancia2[0]=0;
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
    //if(caminoMinimo>distancia2[t] || caminoMinimo==0) caminoMinimo=distancia[t];
}
void Ejercicio1(){
    Dijkstra();
    Dijkstra2();

}
int main() {
    ios_base::sync_with_stdio (false) ;
    cin.tie(0) ;
    int w;cin>>w;
    while(w--){
        cin>>n>>m>>k>>s>>t;
        grafo.resize(n+1);
        grafo2.resize(n+1);
        for (int j = 0; j <m ; ++j) {
            int d,c,l;cin>>d>>c>>l;
            grafo[d].push_back(make_pair(c,l));
            grafo2[c].push_back(make_pair(d,l));
        }
        Ejercicio1();
        for (int j = 0; j <k ; ++j) {
            int d,c,l;cin>>d>>c>>l;
            caminoMinimo = distancia[d] + l +distancia2[c];
            if((d==s &&c==t)|| (d== t && c==s))caminoMinimo=min(caminoMinimo,l);


        }
        if(caminoMinimo==inf)caminoMinimo=-1;
        cout<<caminoMinimo<<endl;
        caminoMinimo=inf;
        grafo2.clear();
        grafo.clear();
        distancia.clear();
        distancia2.clear();
        visitado.clear();
    }
    return 0;
}
