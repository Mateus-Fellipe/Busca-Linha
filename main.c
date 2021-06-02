// Testagem.

// Bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 1024

// Criação do struct lista.
typedef struct lista no;
struct lista{
  int c;
  no *prox;
};

// Prototpo das funções
void leituraNome(char *, char *);
void leituraArq(char [MAX][MAX], char [64]);
void percorre(char *, char *, no *);
int compara(char *, char *);
void append(int, no *);
int imprimeLista(no *);
void limpaLista(no *, int);

int main(){
  char nomeArq[64], *pNomeArq = &nomeArq[0];
  char nomeBusca[64], *pNomeBusca = &nomeBusca[0];
  char Matriz[MAX][MAX], *pMatriz = &Matriz[0][0];
  int tamList, teste;

  no *T;
  T = malloc(sizeof(no));
  T->prox = NULL;

  leituraNome(pNomeArq, pNomeBusca);
  leituraArq(Matriz, nomeArq);
  percorre(pMatriz, pNomeBusca, T);
  tamList = imprimeLista(T);
  limpaLista(T, tamList);
  return 0;
}


// Le o nome do arquivo e le a palavra para ser buscada
void leituraNome(char *pNomeArq, char *pNomeBusca){
  char str[64], *pStr = &str[0], c;
  int i, n = 2;

  while((c = getchar()) != '\n'){
    *pStr++ = c;
  }

  char *token = strtok(str, " ");
  while (token != NULL) {
    pStr = token;
    i = strlen(pStr);

    if(n == 2){
      while(i>0){*pNomeBusca++ = *pStr++; i--;}
    }
    else{
      while(i>0){*pNomeArq++ = *pStr++; i--;}
    }
    token = strtok(NULL, " ");
    n--;
  }
}

// Lê o arquivo e o aloca na matriz
void leituraArq(char Matriz[MAX][MAX], char nomeArq[64]){
  char *pMatriz = &Matriz[0][0], c;
  FILE *fp;
  int n;

  if((fp = fopen(nomeArq, "r")) == NULL){
    exit(1);
  }

  while((c = fgetc(fp)) != EOF){
    *pMatriz++ = c;
    n++;
  }
  fclose(fp);
}

//Percorre o arquivo como um todo
void percorre(char *pMatriz, char *pBusca, no *p){
  int n = strlen(pMatriz), linhas = 1, veri, ultimaLinha;

  while(n > 0){
    if(*pMatriz == '\n'){linhas++;}

    if(*pMatriz == *pBusca){
      veri = compara(pMatriz, pBusca);

      if((veri == 1) ){
        append(linhas, p);
        ultimaLinha = linhas;
      }
    }
    pMatriz++;
    n--;
  }
}

// Compara o termo de busca com as palavras do texto
int compara(char *pMatriz, char *pBusca){
  char *pVeri = pMatriz, *pReal = pBusca;
  int n = strlen(pReal) + 1;

  while (n > 0){
    if((isalpha(*pVeri)) && (n == 1)){
      return 0;}
    else if((*pVeri++ != *pReal++) && (n > 1)){
      return 0;}
    n--;
  }
  return 1;
}

// Coloca o número em uma lista
void append(int num, no *p){
  no *novoNo;
  novoNo = malloc(sizeof(no));
  novoNo->c = num;
  novoNo->prox = p->prox;
  p->prox = novoNo;
}

// Imprime a lista
int imprimeLista(no *final){
  no *imp;
  imp = final->prox;
  int i = 0;

  for(imp; imp != NULL; imp = imp->prox){
    printf("%i ", imp->c);
    i++;
  }
  printf("\n");
  return i;
}

// remove todos os elementos da lista
void limpaLista(no *final, int i){
  for(i; i>0; i--){
    no *lixo; //, lixo = final->prox;
    lixo = final->prox;
    final->prox = lixo->prox;
    free(lixo);
  }
}
