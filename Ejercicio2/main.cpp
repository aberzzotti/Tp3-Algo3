/* Ejercicio 2 del trabajo practico 3 de la materia algoritmos y estructuras de datos 3
 * Para este ejercicio se tomo como referencia el algoritmo de flujo maximo
 * compartido por la catedra de la siguiente pagina 
 *https://cp-algorithms.com/graph/edmonds_karp.html#implementation
 */
//Librerias
#include <iostream>
#include <vector>
#include <queue>
//++++++++++++++++++++++++++++++++++++++++
using namespace std;
int INF = 1000000;
//Variables Globales
int n,m;
vector<vector<int>> capacity;
vector<vector<int>> adj;
//Algorirmo de bfs
//++++++++++++++++++++++++++++++++++++++++
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}
//algoritmo de flujo maximo
//++++++++++++++++++++++++++++++++++++++++
int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
//++++++++++++++++++++++++++++++++++++++++
int main() {
    //cin >>n>>m;
    while(true){
		//Por temas de tiempo del juez se uso scanF y printF para la lectura y escritura 
        scanf("%d %d", &n, &m);
        if (n==0) break;

        adj.resize(n+2);
        capacity.resize(n+2,vector<int>(n+2, 0));
        int s = 0;
        int t = n+1;

        for (int i = 0; i <n ; i++) {
            int x;
            scanf("%d", &x);
            if(x==0){
                //kruskal
                adj[0].push_back(i+1);
                capacity[0][i+1]=1;
              
            }else{
                //prim
                adj[i+1].push_back(n+1);
                capacity[i+1][n+1]=1;
            }
        }
        for (int i = 0; i <m ; i++) {
            //amigos entre nodos 
            int a,b;
            scanf("%d %d", &a, &b);
            capacity[a][b]=1;
            capacity[b][a]=1;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        printf("%d\n", maxflow(s, t));
        adj.clear();
        capacity.clear();
    }
    return 0;
}
