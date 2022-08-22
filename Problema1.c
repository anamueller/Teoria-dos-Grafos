#include <stdio.h>
#include <stdlib.h>

int cnt = 0, cntt=0;
int pre[30000]; //tempos de entrada
int post[30000]; //tempos de saida
int pa[30000]; //vetor de vertices
int vv[30000];
int sc[30000];//componentes

typedef struct node *link;

struct node { 
   int w; 
   link next; 
};

struct graph {
   int V; 
   int A; 
   link *adj; 
};

typedef struct graph *Graph;

static link NEWnode( int w, link next) { 
   link a = malloc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   int v;
   for (v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

link NEW (int v, link next){ 
    link x = malloc (sizeof *x);
    x->w = v;
    x->next = next;
    return x;
}

void GRAPHinsertArc( Graph G, int v, int w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->A++;
}

static void dfsR( Graph G, int v) 
{ 
   pre[v] = cnt++; 
   for (link a = G->adj[v]; a != NULL; a = a->next){
       int w = a->w;
       if (pre[w] == -1){
           pa[w]=v;
           dfsR( G, w);
       }
    }
    post[v]=cntt++;
}

void GRAPHdfs(Graph G) {
    int v;
    for (v = 0; v < G->V; ++v){
        pre[v] = -1;
    }
    for (v = 0; v < G->V; ++v){
        if (pre[v] == -1){
            dfsR( G, v); // começa nova etapa
        }
    }
}

Graph GRAPHreverse( Graph G) //tranverso do grafo
{
    int v;
   Graph GR = GRAPHinit( G->V);
   for (v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHinsertArc( GR, a->w, v);
   return GR;
}

static void dfsRstrongCompsK( Graph G, int v, int *sc, int k) 
{ 
   sc[v] = k; //componentes de cada vertice
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (sc[a->w] == -1) 
         dfsRstrongCompsK( G, a->w, sc, k);
}

void freelist(link lst) {
   if (lst != NULL) {
      freelist( lst->next);
      free( lst);
   }
}

void GRAPHdestroy( Graph G) {
   int v;
   for (v = 0; v < G->V; ++v){
      freelist( G->adj[v]);
   }
   free( G->adj);
   free( G);
}  

void GRAPHstrongCompsK( Graph G, int *sc) 
{
   // fase 1:
   Graph GR = GRAPHreverse(G);
   int v; 
   for (v = 0; v < GR->V; ++v) pre[v] = -1;
   for (v = 0; v < GR->V; ++v) 
      if (pre[v] == -1)
         dfsR( GR, v); 
   for (v = 0; v < GR->V; ++v) 
      vv[post[v]] = v;
   // vv[0..V-1] é permutação de GR em pós-ordem
   // fase 2:
   for (v = 0; v < G->V; ++v) sc[v] = -1;
   int k = 0;
   for (int i = G->V-1; i >= 0; --i) {
      v = vv[i];
      if (sc[v] == -1) { // nova etapa
         dfsRstrongCompsK( G, v, sc, k);
         k++;
      }
   }
   GRAPHdestroy( GR);
}

int GRAPHsearch(int v, int w){
   if(sc[v]==sc[w]){ //estao no mesmo componente logo se seguem direta ou indiretamente
      return 1;
   }
   return 0; // nao estao no mesmo componente
}

int main(){
   int N, M, u, v, P, i;
   scanf("%d %d", &N, &M); //N usuarios e M interações
   Graph twitter = GRAPHinit(N);
   for(i=0;i<M;i++){ //lendo as interações
      scanf("%d %d", &u, &v); //u->v
      GRAPHinsertArc(twitter, u, v);
   }
   GRAPHstrongCompsK(twitter, sc);
   scanf("%d", &P);
   int answer[P];
   for(i=0;i<P;i++){
      scanf("%d %d", &u, &v); //responder se é indiretamente/diratamente ou nao é nada
      answer[i] = GRAPHsearch(u, v);
   }
   for(i=0;i<P;i++){
      printf("%d\n", answer[i]);
   }
   return 0;
}

//anotar componente no vertice
