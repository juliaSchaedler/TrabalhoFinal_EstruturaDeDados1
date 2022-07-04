#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 53
//Fazer uma tabela hash onde os indices estão numa lista encadeada e cada indice leva para uma outra lista encadeada, que deve ser utilizada para a ordenação o quicksort, que leva ponteiros nos lugar de vetores


//Representação de Elementos em Lista encadeada Dupla
typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    char dado[50]; 
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
Elemento* criaElemento(char*);
ListaHash* criaListaHash();
void criaHash(ListaHash*);
void insereListaHash(ListaHash*,int);
Lista* retornaLista(ListaHash* ,int);
void insereElementoHash(ListaHash* ,int ,char*);
void percorreListaHash (ListaHash*,int);
Elemento* encontraNodo(Lista*, char*);
void removerElementoHash (ListaHash*,int,char*);
void quantidadeElementosHash(ListaHash* );
int insereElementoNaLista(Lista*, Elemento*, char*);
char* removeElementoDaLista(Lista*, Elemento*);
void percorreLista(Lista*);
void percorreListaNoOutroSentido(Lista*);
void limpaLista(Lista*);
Elemento* pesquisaNaLista(Lista*, char*);
int tabelaHash(char* dado);
void insereArquivoTXT(ListaHash*,FILE* );
void pesquisaNome(ListaHash* ,char* );
void troca (Elemento*, Elemento*);
Elemento* ultimoNodo(ListaHash* listaHash, int key);
Elemento* separa(Elemento* ,Elemento* );
void quickSort(Elemento*, Elemento*);
void ordenaLista(ListaHash*, int);

// ------------ Importando funções da lista encadeada dupla -----------//

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
Elemento* criaElemento(char* dado){
    Elemento* nodo;
    nodo = (Elemento*) malloc(sizeof(Elemento));
    if (nodo == NULL)
        return NULL;
    else {
        nodo->next = NULL;
        nodo->prev = NULL;
        strcpy(nodo->dado,dado);
        //nodo->dado = dado;
    }  
    return nodo;
}

// ---------------- Implementando a tabela Hash com l.e.d. ---------------//

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
int insereElementoNaLista(Lista* lista, Elemento* pivo, char* dado){  
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
void insereElementoHash(ListaHash* listahash,int key,char* dado){
  Lista* lista = retornaLista(listahash, key);
  
  insereElementoNaLista(lista,lista->tail,dado);
  
}

//imprime os elementos de uma lista especifica
void percorreListaHash (ListaHash* listahash,int key){
  Lista* lista = retornaLista(listahash, key);
  percorreLista(lista);
}

//remove um elemento especifico de uma lista especifica
void removerElementoHash (ListaHash* listahash,int key, char* dado){
  Lista* lista = retornaLista(listahash, key);
  Elemento* nodo = encontraNodo(lista,dado);

  if(nodo != NULL){
    removeElementoDaLista(lista, nodo);
  }else{
    printf("Nodo não encontrado");
  }
  
}

//retorna a quantidade de nomes em uma lista/chave
void quantidadeElementosHash(ListaHash* listaHash){
  Lista* aux;
    aux = listaHash->head;
    
    while(aux != NULL){
        printf("%i\n", aux->size);
        aux = aux->next;
    }
  
}

Elemento* encontraNodo(Lista* lista, char* dado){
  Elemento* aux;
    aux = lista->head;
    
    while(aux != NULL){
        if(strcmp(aux->dado,dado) == 0){
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
char* removeElementoDaLista(Lista* lista, Elemento* aux){
  char dado[50];
  //char* dado ="aa\0";
  
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
    //dado = aux->dado;
    //strncpy(dado,aux->dado, string);
    
    strcpy(dado,aux->dado);
    free(aux);
    lista->size++;
    return *dado;         
  } else {
    printf("Auxiliar é nulo ou número não existe na lista");
     //caso não consiga remover
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
        printf("%s\n", aux->dado);
        aux = aux->next;
    }
}


//percorre a lista no sentido tail->head
void percorreListaNoOutroSentido(Lista* lista){
    Elemento* aux;
    aux = lista->tail;
    
    while(aux != NULL){
        printf(" %s, ", aux->dado);
        aux = aux->prev;
    }
}

//percorre a lista para encontrar um elemento especifico
Elemento* pesquisaNaLista(Lista* lista, char* dado){
    Elemento* aux;
    aux = lista->head; 
    while(aux != NULL){
        if (strcmp(aux->dado, dado) == 0){
          
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}



void insereArquivoTXT(ListaHash* listaHash,FILE* file){
	
	char  string[50];
	char  *aux;
											
	do{
		fscanf(file,"%s",string);
		//aux = incrementaString(string);		
					
		//insereNodo(lista,string,indicaPosicao(aux));
    insereElementoHash(listaHash ,tabelaHash(string) ,string);
			
	}while(fgets(string,50,file) != NULL);	
}

int tabelaHash(char* dado){
  int	i;
	float hash = 0;
	
	for(i = 0;i<strlen(dado);i++)
		hash = 3 * hash + (int)dado[i];
	
	return (int)hash % TAM;
}

void pesquisaNome(ListaHash* listaHash,char* dado){

  int key = tabelaHash(dado);

  Lista* lista = retornaLista(listaHash, key);
  Elemento* nodo = encontraNodo(lista,dado);

  if(nodo != NULL){
    printf("Nome encontrado na lista %i\n",lista->key);
  }else{
    printf("Nodo não encontrado");
  }
}


// --------------- Implementando o Quicksort com l.e.d. ---------------//


void troca (Elemento* a, Elemento* b){
  char  aux[50];
	
	strcpy(aux,a->dado);
	strcpy(a->dado,b->dado);									
	strcpy(b->dado,aux);
}


Elemento* ultimoNodo(ListaHash* listaHash, int key){

  Lista* lista = retornaLista(listaHash, key);
  Elemento* aux = lista->head;
  
  
  while(aux && aux->next){
    aux = aux->next;
  }
  quickSort(lista->head, aux);
}

Elemento* separa(Elemento* l,Elemento* h){
  //char aux[50];

  Elemento* i = l->prev;
  Elemento* j;

  for(j = l; j != h; j = j->next ){
    if(strcmp(j->dado,h->dado)<= 0){
      i = (i == NULL) ? l : i->next;
      troca(i, j);
    }
  }

  i = (i == NULL) ? l : i->next;
/*
  if(i == NULL){
    i = l;
  }else{
    i = i->next;
  }*/

  
  troca(i, h);
  return i;
}

/* Considera o último elemento como pivo e coloca esse elemento-pivo no lugar correto da lista, e coloca dos os elementos menores que o pivo na esquerda e os maiores na direita */

void quickSort(Elemento* l, Elemento* h){
  Elemento* aux;

  if(h != NULL && l != h && h->next != l){
    aux = separa(l,h);
    quickSort(l, aux->prev);
    quickSort(aux->next, h);
  }
}



void ordenaLista(ListaHash* listaHash, int key){
  
  Lista* lista = retornaLista(listaHash, key);
  Elemento* nodo = lista->tail;
  quickSort(lista->head, nodo);
}



int main(void) {
  
  printf("Hello World\n");
  ListaHash* listaHash = criaListaHash();
  criaHash(listaHash);

  FILE *file = fopen("nomes.txt", "r"); 

  insereArquivoTXT(listaHash,file);
    
  /*insereElementoHash(listaHash ,25 ,"gfdg");
  insereElementoHash(listaHash ,25 ,"ggggg");
  insereElementoHash(listaHash ,25 ,"fggg");
  insereElementoHash(listaHash ,25 ,"aaaaa");
  insereElementoHash(listaHash ,25 ,"nhaaa");
  insereElementoHash(listaHash ,25 ,"fggfh");
  insereElementoHash(listaHash ,25 ,"rrrr");
  insereElementoHash (listaHash,25 ,"gfdgd");*/
  
  //percorreListaHash (listaHash,25);
  //removerElementoHash(listaHash,25,"aaaaa");
  printf("nhaaaaaaa\n\n");

  //percorreListaHash (listaHash,25);
  
  //quantidadeElementosHash(listaHash);
  pesquisaNome(listaHash,"TIAGO");

  
  ordenaLista(listaHash, 6);
  //percorreListaHash (listaHash,6);

  //removerElementoHash(listaHash,6,"TIAGO");
  //percorreListaHash (listaHash,6);
  return 0;
}