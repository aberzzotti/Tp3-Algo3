//Librerias
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
//+++++++++++++++++++++++++++++++++++++++++++
using namespace std;
long inf = numeric_limits<long>::max();
//Variables Globales
//distancia y despues nodo
vector<vector<long>> grafo;
vector<tuple<long,long,long>> CaminosNuevos;
vector<long> distancia;
vector<bool> visistado;
// La tupla va tener en la primer coordenada la distancioa y en la segunda el nodo
priority_queue<pair<long,long>> q;
// s nodo inicia , t nodo final, n nodos , m aristasw k bidirecce
long s,t,n,m,k;
long caminoMinimo;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Dijkstra (){
    //Nunca uso la primer coordenada de la cola
    distancia.assign(n+1,inf);
    visistado.assign(n+1,false);
    distancia[0]=0;
    distancia[s]=0;
    q.push(make_pair(0,s));
    while (!q.empty()){
        long nodo =q.top().second;
        q.pop();
        if(visistado[nodo])continue;
        visistado[nodo]=true;
        for (long i = 0; i <grafo[nodo].size() ; ++i) {
            if(grafo[nodo][i]==0)continue;
            long dist = grafo[nodo][i];
            long vecino=i;
            if (distancia[nodo]+dist<distancia[vecino]){
                distancia[vecino] = distancia[nodo]+dist;
                q.push(make_pair(distancia[vecino],vecino));

            }
        }
    }
    if(caminoMinimo>distancia[t] || caminoMinimo==0) caminoMinimo=distancia[t];
}
void Ejercicio1(){
    Dijkstra();
    for (int i = 0; i < k; ++i) {
        tuple<long,long,long> arista=CaminosNuevos[i];
        long anterior =grafo[get<0>(arista)][get<1>(arista)];
        long anterior2 =grafo[get<1>(arista)][get<0>(arista)];
        grafo[get<0>(arista)][get<1>(arista)]=get<2>(arista);
        grafo[get<1>(arista)][get<0>(arista)]=get<2>(arista);
        Dijkstra();
        grafo[get<0>(arista)][get<1>(arista)]=anterior;
        grafo[get<1>(arista)][get<0>(arista)]=anterior2;
    }
}
int main() {
    long w;cin>>w;
    for (int i = 0; i < w; ++i) {
        cin>>n>>m>>k>>s>>t;
        vector<long> vacio;
        vacio.assign(n+1,0);
        grafo.assign(n+1,vacio);
        //distancia.resize(n);
        for (int j = 0; j <m ; ++j) {
            long d,c,l;cin>>d>>c>>l;
            grafo[d][c]=l;
        }
        for (int j = 0; j <k ; ++j) {
            long d,c,l;cin>>d>>c>>l;
            CaminosNuevos.push_back(make_tuple(d,c,l));

        }
    }
    Ejercicio1();
    cout<<caminoMinimo<<endl;
    return 0;
}
