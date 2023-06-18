#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
const long long inf = 10000000;

vector<tuple<int, int, int>> grafo,grafo2;
vector<int> distancia,distancia2;
//vector<long> distancia;
int s, t, n, m, k;
int caminoMinimo;

void BellmanFord() {
    distancia.assign(n + 1, inf);
   distancia[s] = 0;

    for (int i = 1; i < n; i++) {
        for (auto e : grafo) {
            int a, b, w;
            tie(a, b, w) = e;

            if (distancia[a] != inf && distancia[a] + w < distancia[b])
                distancia[b] = distancia[a] + w;
        }
    }

    caminoMinimo = distancia[t];
}
void BellmanFordInvertido() {
    distancia2.assign(n + 1, inf);
    distancia2[t] = 0;

    for (int i = 0; i < n; i++) {
        for (auto e : grafo2) {
            int a, b, w;
            tie(a, b, w) = e;

            if (distancia2[a] != inf && distancia2[a] + w < distancia2[b])
                distancia2[b] = distancia2[a] + w;
        }
    }
}
void Ejercicio1() {
    BellmanFord();
    BellmanFordInvertido();
    //cout << (caminoMinimo == inf ? -1 : caminoMinimo) << endl;
}

int main() {
    int w;//cin>>w;
    scanf("%d",&w);
    while(w--){
       // cin>>n>>m>>k>>s>>t;
        scanf("%d %d %d %d %d", &n, &m,&k,&s,&t);
        //grafo.resize(n+1);
       // grafo2.resize(n+1);
        for (int j = 0; j <m ; ++j) {
            int d,c,l;//cin>>d>>c>>l;
            scanf("%d %d %d", &d, &c,&l);
            grafo.push_back(make_tuple(d, c, l));
            grafo2.push_back(make_tuple(d, c, l));
        }
        Ejercicio1();
        for (int j = 0; j <k ; ++j) {
            int d,c,l;//cin>>d>>c>>l;
            scanf("%d %d %d", &d, &c,&l);
            int camino2= distancia[d] + l +distancia2[c];
            int camino = distancia[c] + l +distancia2[d];
            if((d==s &&c==t)|| (d== t && c==s))caminoMinimo=min(caminoMinimo,l);
            if(camino >0 && camino <caminoMinimo)caminoMinimo =camino;
            if(camino2 >0 && camino2 <caminoMinimo)caminoMinimo =camino2;

        }
        if(caminoMinimo==inf)caminoMinimo=-1;
        //cout<<caminoMinimo<<endl;
        printf("%d\n", caminoMinimo);
        caminoMinimo=inf;
        grafo2.clear();
        grafo.clear();
        distancia.clear();
        distancia2.clear();
    }
return 0;
}
