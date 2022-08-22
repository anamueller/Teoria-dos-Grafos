#include <stdio.h>
#include <stdlib.h>
     
#define TAM 20
#define inf 999999
int ordem[TAM][TAM];
int i,j,k, u, v;
     
/*Carac do grafo:
- direcionado
- poderado
- arestas paralelas
- grafo completo (com arestas paralelas em todos os pontos)
- qual moeda eh melhor começar?
- multiplicar arestas paralelas?
- guardar a multiplicação será que é suficiente?
- floy warshall
- multiplicar inves de somar
- alço externo até n
- pegar max inves de min
*/
     
typedef struct grafo{
    float matriz[TAM][TAM];
} grafo;
    
typedef struct grafo *Graph;
    
Graph GRAPHinit(int V) { 
    Graph G = malloc( sizeof *G);
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            G->matriz[i][j]=0;
        }
    }
    return G;
}
    
void insertArc(int u, int v, float peso, Graph G){
    if(G->matriz[u][v]==0){
        G->matriz[u][v] = peso;
    }
}
    
void imprimir(float m[][TAM], int n){
    for(u=0;u<n;u++){ //imprimindo os pesos
        printf("\n");
        for(v=0;v<n;v++){
            printf("%f ", m[u][v]);
        }
    }
}
    
void imprimir2(int m[][TAM], int n){
    for(u=0;u<n;u++){ //imprimindo os pesos
        printf("\n");
        for(v=0;v<n;v++){
            printf("%d ", m[u][v]);
        }
    }
}

void resultado(int path[][TAM], int c, int f){
    if(path[c][f]==f){
        printf("%d", f+1);
        return;
    }
    printf("%d ", c+1);
    printf("%d ", path[c][f]+1);
    path[c][f]=f;
    resultado(path, path[c][f], path[c][f]);
    
}

int checa(float m[][TAM], int n){
    for(i=0;i<n;i++){
        if(m[i][i]>1.01){
            return 1; //achou
        }
    }
    return 0; //nao achou
}
    
    
void FloyWarshall(float matriz[][TAM], int n){
    float lucro[TAM][TAM];
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            lucro[i][j] = matriz[i][j];
            if (i==j){
                ordem[i][j]=-1;
            }
            else{
                ordem[i][j] = i;
            }
        }
    }
    //printf("inicialização:\n");
    //imprimir2(ordem, n);
    //imprimir(lucro, n);

    for (k = 0; k < n; k++){ //n° da troca que está sendo feita
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                if (lucro[i][k] * lucro[k][j] > lucro[i][j]){
                    lucro[i][j] = lucro[i][k] * lucro[k][j];
                    ordem[i][j] = ordem[k][j];
                    //printf("\nk:%d i:%d j:%d\n", k, i, j);
                    //imprimir2(ordem,n);
                    //imprimir(lucro,n);
                    //printf("\n");
    
                    if(checa(lucro, n)==1 && k>=1){
                        //printf("achou %f\n",  lucro[i][j]);
                        resultado(ordem, i, j);
                        return;
                    }
                }
            }
        }
    }
    printf("Impossible");
}
    
int main(){
    int N;
    float peso;
    scanf("%d", &N); //N moedas
    Graph moedas = GRAPHinit(N);
    for(i=0;i<N;i++){ //lendo os pesos
        for(j=0;j<N;j++){
            if(i==j){
                insertArc(i, j, 1, moedas);
            }
            else{
                scanf("%f", &peso); //peso 
                insertArc(i, j, peso, moedas);
            }
        }
    }
    FloyWarshall(moedas->matriz, N);
    return 0;
}
