//Librerias
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
//+++++++++++++++++++++++++++++++++++++++++++
using namespace std;
long inf = 1e18;
//Variables Globales
//distancia y despues nodo
vector<vector<long>> grafo;
vector<vector<pair<long,bool>>> grafo2;
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
    caminoMinimo=distancia[t];
}
void Dijkstra2 (){
    //Nunca uso la primer coordenada de la cola
    distancia.assign(n+1,inf);
    visistado.assign(n+1,false);
    distancia[0]=0;
    distancia[s]=0;
    q.push(make_pair(0,s));
    long control=0;
    while (!q.empty()){
        long nodo =q.top().second;
        q.pop();
        if(visistado[nodo])continue;
        visistado[nodo]=true;
        for (long i = 0; i <grafo2[nodo].size() ; ++i) {
            if(grafo2[nodo][i].first==0)continue;
            if (grafo2[nodo][i].second && control>0)continue;
            if (grafo2[nodo][i].second)control++;
            long dist = grafo2[nodo][i].first;
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
    Dijkstra2();
    cout<<caminoMinimo<<endl;

}
int main() {
    long w;cin>>w;
    for (int i = 0; i < w; ++i) {
        cin>>n>>m>>k>>s>>t;
        vector<long> vacio;
        vacio.assign(n+1,0);
        vector<pair<long,bool>> vacio2;
        vacio2.assign(n+1, make_pair(0,false));
        grafo.assign(n+1,vacio);
        grafo2.assign(n+1,vacio2);
        for (int j = 0; j <m ; ++j) {
            long d,c,l;cin>>d>>c>>l;
            grafo[d][c]=l;
            grafo2[d][c]= make_pair(l,false);
        }
        for (int j = 0; j <k ; ++j) {
            long d,c,l;cin>>d>>c>>l;
            if(grafo2[d][c].first>l){
                grafo2[d][c]= make_pair(l, true);
                grafo2[c][d]= make_pair(l, true);
            }

        }
        Ejercicio1();
    }
    return 0;
}
