#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
int inf = 10000000;
vector<int> distancia,distancia2;
int s,t,n,m,k;
int caminoMinimo=inf;
class Tupla {
public:
    int first;
    int second;
    Tupla () {}

    Tupla(int coste, int nodo) {
        this->first = coste;
        this->second = nodo;
    }
    friend bool operator>(Tupla t1, Tupla t2) {
        return t1.first > t2.first;
    }
    friend bool operator<(Tupla t1, Tupla t2) {
        return t1.first < t2.first;
    }
};

template <class V> class FibonacciHeap;

template <class V> struct node {
private:
    node<V>* prev;
    node<V>* next;
    node<V>* child;
    node<V>* parent;
    V value;
    int degree;
    bool marked;
public:
    friend class FibonacciHeap<V>;
    node<V>* getPrev() {return prev;}
    node<V>* getNext() {return next;}
    node<V>* getChild() {return child;}
    node<V>* getParent() {return parent;}
    V getValue() {return value;}
    bool isMarked() {return marked;}

    bool hasChildren() {return child;}
    bool hasParent() {return parent;}
};

template <class V> class FibonacciHeap {
protected:
    node<V> *heap;
public:
    FibonacciHeap() {
        heap = _empty();
    }

    virtual ~FibonacciHeap() {
        if (heap) {
            _deleteAll(heap);
        }
    }

    node<V> *insert(V value) {
        node<V> *ret = _singleton(value);
        heap = _merge(heap, ret);
        return ret;
    }

    void merge(FibonacciHeap& other) {
        heap=_merge(heap,other.heap);
        other.heap=_empty();
    }

    bool isEmpty() {
        return heap == NULL;
    }

    V removeMinimum() {
        node<V> *old = heap;
        heap = _removeMinimum(heap);
        V ret = old->value;
        delete old;
        return ret;
    }

    V getMinimum() {
        return heap->value;
    }

private:
    node<V> *_empty() {
        return NULL;
    }

    node<V>* _singleton(V value) {
        node<V>* n=new node<V>;
        n->value=value;
        n->prev=n->next=n;
        n->degree=0;
        n->marked=false;
        n->child=NULL;
        n->parent=NULL;
        return n;
    }

    node<V>* _merge(node<V>* a,node<V>* b) {
        if(a==NULL)return b;
        if(b==NULL)return a;
        if(a->value>b->value) {
            node<V>* temp=a;
            a=b;
            b=temp;
        }
        node<V>* an=a->next;
        node<V>* bp=b->prev;
        a->next=b;
        b->prev=a;
        an->prev=bp;
        bp->next=an;
        return a;
    }

    void _deleteAll(node<V>* n) {
        if(n!=NULL) {
            node<V>* c=n;
            do {
                node<V>* d=c;
                c=c->next;
                _deleteAll(d->child);
                delete d;
            } while(c!=n);
        }
    }

    void _addChild(node<V>* parent,node<V>* child) {
        child->prev=child->next=child;
        child->parent=parent;
        parent->degree++;
        parent->child=_merge(parent->child,child);
    }

    void _unMarkAndUnParentAll(node<V>* n) {
        if(n==NULL)return;
        node<V>* c=n;
        do {
            c->marked=false;
            c->parent=NULL;
            c=c->next;
        }while(c!=n);
    }

    node<V>* _removeMinimum(node<V>* n) {
        _unMarkAndUnParentAll(n->child);
        if(n->next==n) {
            n=n->child;
        } else {
            n->next->prev=n->prev;
            n->prev->next=n->next;
            n=_merge(n->next,n->child);
        }
        if(n==NULL)return n;
        node<V>* trees[64]={NULL};

        while(true) {
            if(trees[n->degree]!=NULL) {
                node<V>* t=trees[n->degree];
                if(t==n)break;
                trees[n->degree]=NULL;
                if(n->value<t->value) {
                    t->prev->next=t->next;
                    t->next->prev=t->prev;
                    _addChild(n,t);
                } else {
                    t->prev->next=t->next;
                    t->next->prev=t->prev;
                    if(n->next==n) {
                        t->next=t->prev=t;
                        _addChild(t,n);
                        n=t;
                    } else {
                        n->prev->next=t;
                        n->next->prev=t;
                        t->next=n->next;
                        t->prev=n->prev;
                        _addChild(t,n);
                        n=t;
                    }
                }
                continue;
            } else {
                trees[n->degree]=n;
            }
            n=n->next;
        }
        node<V>* min=n;
        node<V>* start=n;
        do {
            if(n->value<min->value)min=n;
            n=n->next;
        } while(n!=start);
        return min;
    }

};

void dijkstra(int s, vector<int> & d, vector<vector<pair<int,int>>> &grafo) {
    vector<int> p;
    p.resize((2 * n) + 1, -1);

    d[s] = 0; //asigna distancia de s
    //FibonacciHeap<pii, vector<pii>> q; //min-heap de <distancias, vertices a esa distancia>
    FibonacciHeap<Tupla> q;
    q.insert({0, s}); //coloca el primer vÃ©rtice en el heap
    while (!q.isEmpty()) {
        //comienza desde la cabeza del heap siempre, es decir el minimo camino posible
        int v = q.getMinimum().second;
        int d_v = q.getMinimum().first;
        q.removeMinimum();
        /* d[v] tiene guardadas las distancias minimas que encontro hasta ahora, si explorando v encuentra
         * otra distancia necesariamente va a ser peor que la que esta guardada en d[v]
         */
        if (d_v != d[v])
            continue;

        for (auto edge : grafo[v]) {
            int to = edge.first; //a quien llega
            int len = edge.second; //peso de la arista

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
                /* actualiza las posiciones en el heap cuando mejora el camino mÃ­nimo y registra el camino
                 * mÃ­nimo desde s en el vector d
                 */
            }
        }
    }

}

int main() {
    int w;cin>>w;
    vector<vector<pair<int,int>>> grafo,grafo2;
    while(w--){ //Lectura de cada test
        cin>>n>>m>>k>>s>>t;
        grafo.resize(n+1);
        grafo2.resize(n+1);
        distancia.assign(n+1,inf);
        distancia2.assign(n+1,inf);
        //Leo las aristas del grafo
        for (int j = 0; j <m ; ++j) {
            int d,c,l;cin>>d>>c>>l;
            grafo[d].push_back(make_pair(c,l));
            grafo2[c].push_back(make_pair(d,l));
        }
        dijkstra(s,distancia,grafo);
        caminoMinimo=distancia[t];
        dijkstra(t,distancia2,grafo2);
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
    }
    return 0;
}
