#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 53
//Fazer uma tabela hash onde os indices estão numa lista encadeada e cada indice leva para uma outra lista encadeada, que deve ser utilizada para a ordenação o quicksort, que leva ponteiros nos lugar de vetores


//Representação de Elementos em Lista encadeada Dupla
typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    int dado; 
} Elemento;

//Representação de Lista encadeada Dupla, mesma coisa que a simples
typedef struct sLista{
    Elemento *head;
    Elemento *tail;
    struct sLista *next;
    struct sLista *prev;
    int size;
    int key;
} Lista;

//LISTA DE LISTAS
typedef struct listaHash{
    Lista *head;
    Lista *tail;
    int size;
} ListaHash;

//Prototipação
Lista* criaLista(int);
Elemento* criaElemento(int);
ListaHash* criaListaHash();
void criaHash(ListaHash*);
void insereListaHash(ListaHash*,int);
Lista* retornaLista(ListaHash* ,int);
void insereElementoHash(ListaHash* ,int ,int);
void percorreListaHash (ListaHash*,int);
Elemento* encontraNodo(Lista*, int);
void removerElementoHash (ListaHash*,int,int);
int insereElementoNaLista(Lista*, Elemento*, int);
int removeElementoDaLista(Lista*, Elemento*);
void percorreLista(Lista*);
void percorreListaNoOutroSentido(Lista*);
void limpaLista(Lista*);
Elemento* pesquisaNaLista(Lista*, int);


// ------ Importando funções da lista encadeada dupla ------//

//função cria lista e desloca memória para ela
Lista* criaLista(int key){
    Lista* lista;
    lista = (Lista*) malloc(sizeof(Lista));
    if (lista == NULL)
        return NULL;
    else {
        lista->head = NULL;
        lista->tail = NULL;
        lista->next = NULL;
        lista->prev = NULL;
        lista->size = 0;
        lista->key = key;
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
// ------------- Implementando a tabela Hash com l.e.d. ---------//

//função cria uma lista de listas e desloca memória para ela
ListaHash* criaListaHash(){
    ListaHash* listaHash;
    listaHash = (ListaHash*) malloc(sizeof(ListaHash));
    if (listaHash == NULL)
        return NULL;
    else {
        listaHash->head = NULL;
        listaHash->tail = NULL;
        listaHash->size = 0;
    }
    
    return listaHash;
}

//função cria e inicializa a tabela Hash
void criaHash(ListaHash* listaHash){
  int i;
  for(i =0 ;i < TAM; i++){
      insereListaHash(listaHash,i);
  }
}

//insere as listas encadeadas na tabela Hash
void insereListaHash(ListaHash* listaHash,int key){
  Lista* novaLista = criaLista(key);

  if(novaLista != NULL){
    if(listaHash->size == 0){
      listaHash->head = novaLista;
      listaHash->tail = novaLista;
    }else{
      listaHash->tail->next = novaLista;
      novaLista->prev = listaHash->tail;
      listaHash->tail = novaLista;
    }
    listaHash->size++;
  }
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

//insere elementos na tabela hash
void insereElementoHash(ListaHash* listahash,int key,int dado){
  Lista* lista = retornaLista(listahash, key);
  
  insereElementoNaLista(lista,lista->tail,dado);
  
}

void percorreListaHash (ListaHash* listahash,int key){
  Lista* lista = retornaLista(listahash, key);
  percorreLista(lista);
}

void removerElementoHash (ListaHash* listahash,int key,int dado){
  Lista* lista = retornaLista(listahash, key);
  Elemento* nodo = encontraNodo(lista,dado);

  if(nodo != NULL){
    removeElementoDaLista(lista, nodo);
  }else{
    printf("Nodo não encontrado");
  }
  
}

void quantidadeElementosHash(ListaHash* listaHash){

  
}

Elemento* encontraNodo(Lista* lista, int dado){
  Elemento* aux;
    aux = lista->head;
    
    while(aux != NULL){
        if(aux->dado == dado){
          return aux;
        }
        aux = aux->next;
    }
}

Lista* retornaLista(ListaHash* listahash,int key){
  Lista* lista = listahash->head;
  int i;
  for(i = 0; i < TAM; i++){
    if(key == lista->key){
      return lista;
    }
    lista = lista->next;
  }
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










int main(void) {
  printf("Hello World\n");
  ListaHash* listaHash = criaListaHash();
  criaHash(listaHash);

  insereElementoHash(listaHash ,25 ,78);
  insereElementoHash(listaHash ,25 ,38);
  insereElementoHash(listaHash ,25 ,79);
  insereElementoHash(listaHash ,25 ,45);
  insereElementoHash(listaHash ,25 ,78);
  insereElementoHash(listaHash ,25 ,36);
  insereElementoHash(listaHash ,25 ,89);
  insereElementoHash (listaHash ,25 ,12);
  
  percorreListaHash (listaHash,25);

  removerElementoHash(listaHash,25,36);
  printf("nhaaaaaaa\n\n");

  percorreListaHash (listaHash,25);
  
  
  return 0;
}