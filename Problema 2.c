#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int cnt = 0, cntt=0;
int pre[300000];//tempos de entrada
int post[300000];
int pa[300000];

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

static void dfsR( Graph G, int v, int vetor[], int N) 
{ 
   vetor[v]=1;
   pre[v] = cnt++; 
   for (link a = G->adj[v]; a != NULL; a = a->next){
      int w = a->w;
      if (pre[w] == -1){
         //printf("w:%d v:%d n:%d vetor:%d\n", w, v, N, vetor[v]);
         pa[w]=v;
         if(w==N){
            vetor[w]=0;
            //printf("teste1\n");
         }
         else{
            vetor[w]=1;
            //printf("teste2 vetor:%d\n", vetor[v]);
            dfsR( G, w, vetor, N);
         }
      }
   }
   post[v]=cntt++;
}

void GRAPHdfs(Graph G) {
    int v;
    for (v = 0; v < G->V; ++v){
        pre[v] = -1;
    }
}


int main(){
   int N, M, u, v, i;
   scanf("%d %d", &N, &M); //N cidades e M estradas
   Graph pais = GRAPHinit(N+1);
   int pop[N+1]; //vetor com as populações das cidades
   int nao_visitados[N+1]; //posicao = vertice, 0=nao foi visitado, 1=foi visitado
   for(i=0;i<=N;i++){
      nao_visitados[i]=0;
   }
   for(i=0;i<M;i++){ //lendo as estradas
      scanf("%d %d", &u, &v); //u->v 
      GRAPHinsertArc(pais, u, v);
      GRAPHinsertArc(pais, v, u);
      pop[u] = pow(2, u);
      pop[v] = pow(2, v);
   }
   GRAPHdfs(pais);
   dfsR(pais, N-1, nao_visitados, N); //começa dfs pelo segundo maior vértice
   //somar os indices do vetor que tiver =0 + maior vértice
   int sum;
   for(i=0;i<=N;i++){
      //printf("%d ", nao_visitados[i]);
      if(nao_visitados[i]==0){
         sum = sum + i;
      }
   }
   printf("%d", sum);
   return 0;
}
