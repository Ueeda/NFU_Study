#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct estrutura_paginas_virtuais{
	int valor;
	int idade;
	struct estrutura_paginas_virtuais *prox;
} virtualPage;

virtualPage *pag_ini, *pag, *pag_fim;
void manipulandoArquivo(char *nomeArq, int tamanhoFita, int nArquivo);
int existeFita(virtualPage *firstPage, int value);
int tamanhoAtualFita(virtualPage *firstPage);
void renovarIdade(virtualPage *firstPage, int value, int idadeMaxima);
virtualPage* getOlder(virtualPage **firstPage);
void envelhecerTodos(virtualPage *firstPage, int value);
void printLista(virtualPage *firstPage);

void main(){
	fflush(stdin);
	

	
	manipulandoArquivo("arquivos/arquivo1.txt", 4,1);
	manipulandoArquivo("arquivos/arquivo2.txt", 4,2);
	manipulandoArquivo("arquivos/arquivo3.txt", 64,3);
	manipulandoArquivo("arquivos/arquivo3.txt", 256,3);
	manipulandoArquivo("arquivos/arquivo3.txt", 1024,3);
	manipulandoArquivo("arquivos/arquivo3.txt", 2048,3);
	manipulandoArquivo("arquivos/arquivo4.txt", 64,4);
	manipulandoArquivo("arquivos/arquivo4.txt", 256,4);
	manipulandoArquivo("arquivos/arquivo4.txt", 1024,4);
	manipulandoArquivo("arquivos/arquivo4.txt", 2048,4);
}

void manipulandoArquivo(char *nomeArq, int tamanhoFita, int nArquivo){
	
	int tamanhoMax = tamanhoFita;
	int numeroArq = nArquivo;
	char ch[10];
	int valorAtual = 0;
	int pageFaults = 0;
	int req = 0;
	int pageQntd;
	int potencia;
	if(nArquivo == 1 || nArquivo == 2)
		 potencia= 3;
	if(nArquivo == 3 || nArquivo == 4)
		potencia = 7;
	int idadeMaisNovo = pow(2, (potencia - 1)); 
	int i, tamanhoAtual;
	
	FILE *arq;
	arq = fopen(nomeArq, "r");
	
	virtualPage *page, *head, *tail;
	virtualPage *currentPage, *firstPage, *lastPage, *older;
	
	page = malloc(sizeof(virtualPage));
	head = page;
	tail = page;
	fgets(ch, 9, arq);
	valorAtual = atoi(ch);
	req++;
	head->valor = valorAtual;
	head->idade = idadeMaisNovo;
	head->prox = NULL;
	
	
	while(!feof(arq)){
		//printLista(head);
		if (tamanhoMax == 64) {
            if (req % 20 == 0)
                envelhecerTodos(head, valorAtual);
        }
        else if (tamanhoMax == 256) {
            if (req % 100 == 0)
                envelhecerTodos(head, valorAtual);
        } 
        else if (tamanhoMax == 1024) {
            if (req % 400 == 0)
				envelhecerTodos(head, valorAtual);
        } 
        else if (tamanhoMax == 2048) {
            if (req % 800 == 0)
				envelhecerTodos(head, valorAtual);
        } 
        else {
			envelhecerTodos(head, valorAtual);
        }
		fgets(ch, 9, arq);
		valorAtual = atoi(ch);
		if(existeFita(head, valorAtual) == 0){
			if(tamanhoAtualFita(head) < tamanhoMax){
				page = malloc(sizeof(virtualPage));
				page->valor = valorAtual;
				page->idade = idadeMaisNovo;
				tail->prox = page;
				tail = page;
				page->prox = NULL;
			}
			else{
				older = getOlder(&head);
				//printf("older: %d", older);
				older->valor = valorAtual;
				older->idade = idadeMaisNovo;
				pageFaults++;
			}
		}
		else{
			renovarIdade(head, valorAtual, idadeMaisNovo);
		}
		//envelhecerTodos(head);
		
		req++;
	}
	liberarMemoria(head);
	
	
	printf("Arquivo %d, %5d paginas, %7d requisicoes: NFU: %5d Page Faults\n", numeroArq, tamanhoFita, req, pageFaults);
	
}

int existeFita(virtualPage *firstPage, int value){

	virtualPage *temp = firstPage;
	while(temp != NULL){
		if(temp->valor == value)
			return 1;
		temp = temp->prox;
	}
	return 0;	
}

int tamanhoAtualFita(virtualPage *firstPage){
	virtualPage *temp = firstPage;
	int cont = 0;
	while(temp != NULL){
		cont++;
		temp = temp->prox;
	}
	return cont;
}

void renovarIdade(virtualPage *firstPage, int value, int idadeMaxima){
	virtualPage *temp = firstPage;
	while(temp != NULL){
		if(temp->valor == value){
			temp->idade = temp->idade | idadeMaxima;
			break;
		}
		temp = temp->prox;
	}
	
}

void printLista(virtualPage *firstPage){
	virtualPage *temp = firstPage;
	virtualPage *old;
	while(temp != NULL){
		printf("%d(%d) ", temp->valor, temp->idade);
		temp = temp->prox;
	}
	printf("\n");
}

virtualPage* getOlder(virtualPage **firstPage){
	virtualPage *temp = (*firstPage);
	virtualPage *old = (*firstPage);
	while(temp != NULL){
		if(temp->idade < old->idade){
			old = temp;
		}
		temp = temp->prox;
	}
	return old;
}

void envelhecerTodos(virtualPage *firstPage, int value){
	virtualPage *temp = firstPage;
	while(temp != NULL){
		if(temp->idade != value)
			temp->idade = temp->idade >> 1;
		temp = temp->prox;
	}
}

void liberarMemoria(virtualPage *firstPage){
	virtualPage *temp;
	while(firstPage != NULL){
		temp = firstPage;
		firstPage = firstPage->prox;
		free(temp);
	}
}

