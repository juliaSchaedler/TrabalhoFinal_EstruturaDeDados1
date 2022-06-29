#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fazer uma tabela hash onde os indices estão numa lista encadeada e cada indice leva para uma outra lista encadeada, que deve ser utilizada para a ordenação o quicksort, que leva ponteiros nos lugar de vetores


//Representação de Elementos em Lista encadeada Dupla
typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    int dado; 
} Elemento;

//Representação de Lista encadeada Dupla, mesma coisa que a simples
typedef struct {
    Elemento *head;
    Elemento *tail;
    int size;
} Lista;

//Prototipação
Lista* criaLista();
Elemento* criaElemento(int);
int insereElementoNaLista(Lista*, Elemento*, int);
int removeElementoDaLista(Lista*, Elemento*);
void percorreLista(Lista*);
void percorreListaNoOutroSentido(Lista*);
void limpaLista(Lista*);
Elemento* pesquisaNaLista(Lista*, int);


// ------ Importando funções da lista encadeada dupla ------//

//função cria lista e desloca memória para ela
Lista* criaLista(){
    Lista* lista;
    lista = (Lista*) malloc(sizeof(Lista));
    if (lista == NULL)
        return NULL;
    else {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
    
    return lista;
}

// função cria elemento e desloca memória para ele
Elemento* criaElemento(int dado){
    Elemento* nodo;
    nodo = (Elemento*) malloc(sizeof(Elemento));
    if (nodo == NULL)
        return NULL;
    else {
        nodo->next = NULL;
        nodo->prev = NULL;
        nodo->dado = dado;
    }  
    return nodo;
}

//função insere elementos na lista dupla
int insereElementoNaLista(Lista* lista, Elemento* pivo, int dado){  
  Elemento* novo = criaElemento(dado);

  if(pivo == NULL && lista->size != 0){
      return -1; //só aceita pivo nulo na inserção do primeiro elemento       
  }

  if(lista->size == 0){ //verifica se a lista está vazia
    lista->head = novo;
    lista->tail = novo;  
    
  }else{
    novo->next = pivo->next; //se não tiver, só add elementos na sequência
    novo->prev = pivo;

    if(pivo->next == NULL){
      lista-> tail = novo;
    }else{
      pivo->next->prev = novo;
    }

    pivo->next = novo;
    
  }
  
  lista->size++;
  return 0;
}

//função de remover elementos da lista
int removeElementoDaLista(Lista* lista, Elemento* aux){
  int dado;
  if(aux!= NULL && lista->size != 0){
    if(aux == lista->head){
      lista->head = aux->next;
      
      if(lista->head == NULL){
        lista->tail = NULL;
        
      }else{
        aux->next->prev = NULL;
      }
      
    }else{
      aux->prev->next = aux->next;
      
      if(aux->next == NULL){
        lista->tail = aux->prev;
        
      }else{
        aux->next->prev = aux->prev;
      }
    }
    dado = aux->dado;
    free(aux);
    lista->size++;
    return dado;         
  } else {
     return printf("Auxiliar é nulo ou número não existe na lista");  //caso não consiga remover
  } 
}

//função limpa a lista e libera memória
void limpaLista(Lista* lista){
    while(lista->head != NULL){
        removeElementoDaLista(lista, lista->head); //função remove não aceita null
    }
    
    free(lista);
}

//percorre a lista no sentido head->tail
void percorreLista(Lista* lista){
    Elemento* aux;
    aux = lista->head;
    
    while(aux != NULL){
        printf("%i, ", aux->dado);
        aux = aux->next;
    }
}

//percorre a lista no sentido tail->head
void percorreListaNoOutroSentido(Lista* lista){
    Elemento* aux;
    aux = lista->tail;
    
    while(aux != NULL){
        printf(" %i, ", aux->dado);
        aux = aux->prev;
    }
}

//percorre a lista para encontrar um elemento especifico
Elemento* pesquisaNaLista(Lista* lista, int dado){
    Elemento* aux;
    aux = lista->head;
    
    while(aux != NULL){
        if (aux->dado == dado){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}




// ------ Implementando o Quicksort com l.e.d. ------//

// ------ Implementando a tabela Hash com l.e.d. ------//








int main(void) {
  printf("Hello World\n");
  return 0;
}