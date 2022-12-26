#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
 int num;
 char mus[50];
 struct Node *prox;
}; 
typedef struct Node node;

int tam;

void inicia(node *LISTA);
int menu(void);
char opcao(node *LISTA, char op);
node *criaNo();
void insereFim(node *LISTA);
void insereInicio(node *LISTA);
void exibe(node *LISTA);
void libera(node *LISTA);
void insere (node *LISTA);
node *retiraInicio(node *LISTA);
node *retiraFim(node *LISTA);
node *retira(node *LISTA);


int main(void)
{
 node *LISTA = (node *) malloc(sizeof(node));
 if(!LISTA){
  printf("Sem memoria disponivel!\n");
  exit(1);
 }else{
 inicia(LISTA);
 int opt;
 
 do{
  opt=menu();
  opcao(LISTA,opt);
 }while(opt);

 free(LISTA);
 return 0;
 }
}

void inicia(node *LISTA)
{
 LISTA->prox = NULL;
 tam=0;
}

int menu(void)
{
char opt;
 printf("------------------//-----------------\n");
 printf("Bem vindo ao seu Player Music!!!\n");
 printf("------------------//-----------------\n\n");
 printf("Escolha a opcao\n");
 printf("a. Sair\n");
 printf("b. Zerar playlist\n");
 printf("c. Exibir playlist\n");
 printf("d. Adicionar musica no inicio\n");
 printf("e. Adicionar musica no final\n");
 printf("f. Escolher onde inserir\n");
 printf("g. Retirar do inicio\n");
 printf("h. Retirar do fim\n");
 printf("i. Escolher de onde tirar\n");
 printf("Opcao: "); scanf("%s", &opt);
 
 return opt;
}

char opcao(node *LISTA, char op)
{
 node *tmp;
 switch(op){
  case 'a':
   libera(LISTA);
   break;
   
  case 'b':
   libera(LISTA);
   inicia(LISTA);
   break;
  
  case 'c':
   exibe(LISTA);
   break;
  
  case 'd':
   insereInicio(LISTA);
   break;  
   
  case 'e':
   insereFim(LISTA);
   break;
   
  case 'f':
   insere(LISTA);
   break;
  
  case 'g':
   tmp= retiraInicio(LISTA);
   printf("Retirado: %3s\n\n", tmp->mus);
   break;
   
  case 'h':
   tmp= retiraFim(LISTA);
   printf("Retirado: %3s\n\n", tmp->mus);
   break;

  case 'i':
   tmp= retira(LISTA);
   printf("Retirado: %3s\n\n", tmp->mus);
   break;
  
  default:
   printf("Comando invalido\n\n");
 }
}

int vazia(node *LISTA)
{
 if(LISTA->prox == NULL)
  return 1;
 else
  return 0;
}

node *aloca()
{
 node *novo=(node *) malloc(sizeof(node));
 if(!novo){
  printf("Sem memoria disponivel!\n");
  exit(1);
 }else{
  printf("Nova música: "); scanf("%s", &novo->mus);
  return novo;
 }
}


void insereFim(node *LISTA)
{
 node *novo=aloca();
 novo->prox = NULL;
 
 if(vazia(LISTA))
  LISTA->prox=novo;
 else{
  node *tmp = LISTA->prox;
  
  while(tmp->prox != NULL)
   tmp = tmp->prox;
  
  tmp->prox = novo;
 }
 tam++;
}

void insereInicio(node *LISTA)
{
 node *novo=aloca(); 
 node *oldHead = LISTA->prox;
 
 LISTA->prox = novo;
 novo->prox = oldHead;
 
 tam++;
}

void exibe(node *LISTA)
{
 system("clear");
 if(vazia(LISTA)){
  printf("Lista vazia!\n\n");
  return ;
 }
  node *tmp;
 tmp = LISTA->prox;
 printf("Lista:\n");
 int count;
 for(count=1 ; count < tam ; count++)
 while( tmp != NULL){
  printf("%5d-> %5s\n", count++, tmp->mus);
  tmp = tmp->prox;
 }
 printf("\n\n");
}

void libera(node *LISTA)
{
 if(!vazia(LISTA)){
  node *proxNode,
     *atual;
  
  atual = LISTA->prox;
  while(atual != NULL){
   proxNode = atual->prox;
   free(atual);
   atual = proxNode;
  }
 }
}

void insere(node *LISTA)
{
 int pos,
  count;
 printf("Qual musica, [de 1 ate %d] voce deseja inserir: ", tam);
 scanf("%d", &pos);
 
 if(pos>0 && pos <= tam){
  if(pos==1)
   insereInicio(LISTA);
  else{
   node *atual = LISTA->prox,
     *anterior=LISTA; 
   node *novo=aloca();
     
   for(count=1 ; count < pos ; count++){
     anterior=atual;
     atual=atual->prox;
   }
   anterior->prox=novo;
   novo->prox = atual;
   tam++;
  }
   
 }else
  printf("Musica invalida\n\n");  
}

node *retiraInicio(node *LISTA)
{
 if(LISTA->prox == NULL){
  printf("Lista ja esta vazia\n");
  return NULL;
 }else{
  node *tmp = LISTA->prox;
  LISTA->prox = tmp->prox;
  tam--;
  return tmp;
 }
    
}

node *retiraFim(node *LISTA)
{
 if(LISTA->prox == NULL){
  printf("Lista ja vazia\n\n");
  return NULL;
 }else{
  node *ultimo = LISTA->prox,
    *penultimo = LISTA;
    
  while(ultimo->prox != NULL){
   penultimo = ultimo;
   ultimo = ultimo->prox;
  }
    
  penultimo->prox = NULL;
  tam--;
  return ultimo;  
 }
}

node *retira(node *LISTA)
{
 int opt,
  count;
 printf("Que musica, [de 1 ate %d] voce deseja retirar?: ", tam);
 scanf("%d", &opt);
 
 if(opt>0 && opt <= tam){
  if(opt==1)
   return retiraInicio(LISTA);
  else{
   node *atual = LISTA->prox,
     *anterior=LISTA; 
     
   for(count=1 ; count < opt ; count++){
    anterior=atual;
    atual=atual->prox;
   }
   
  anterior->prox=atual->prox;
  tam--;
  return atual;
  }
   
 }else{
  printf("Comando invalido\n\n");
  return NULL;
 }
}
