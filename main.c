#include <stdio.h>
#include <stdlib.h>

/* A estrutura abaixo define o registro do arquivo que deverá ser lido  */
typedef struct estrutura_paginas_virtuais{
    int valor;
	int idadePagina;
    struct estrutura_paginas_virtuais *prox;
} stPagVirtual;

stPagVirtual *pag_ini, *pagina, *pag_fim;

void manipulandoArquivo(char *nomeArq, int tamanhoFita, int nArquivo);
int idadeMaxCalc(int tamanhoFita);
int verificaFita(stPagVirtual *firstNode, int value);
void retiraVelho(stPagVirtual ** firstNode);
void adicionarFita(stPagVirtual **pagina, stPagVirtual **lastPage);
int envelheceFita(stPagVirtual **firstNode);

void main(){
	
	manipulandoArquivo("arquivos/arquivo1.txt", 4,1);
	/*manipulandoArquivo("arquivos/arquivo2.txt", 4,2);
	manipulandoArquivo("arquivos/arquivo3.txt", 64,3);
	manipulandoArquivo("arquivos/arquivo3.txt", 256,3);
	manipulandoArquivo("arquivos/arquivo3.txt", 1024,3);
	manipulandoArquivo("arquivos/arquivo3.txt", 2048,3);
	manipulandoArquivo("arquivos/arquivo4.txt", 64,4);
	manipulandoArquivo("arquivos/arquivo4.txt", 256,4);
	manipulandoArquivo("arquivos/arquivo4.txt", 1024,4);
	manipulandoArquivo("arquivos/arquivo4.txt", 2048,4);*/
	
}

void manipulandoArquivo(char *nomeArq, int tamanhoFita, int nArquivo){
	int tamanhoMax = tamanhoFita;
	int numeroArquivo = nArquivo;
	char ch[10];
	int valorAtual = 0;
	int pagefaults = 0;
	int idadeMax = idadeMaxCalc(tamanhoMax);
	int i;
	int req = 0;
	
	stPagVirtual *currentPage, *firstPage, *lastPage;	
	FILE *arq;
	
	arq = fopen(nomeArq, "r");
	pagina = malloc(sizeof(stPagVirtual));
	pag_ini = pagina;
	pag_fim = pagina;
	fgets(ch, 9, arq);
	valorAtual = atoi(ch);
	pag_ini->valor = valorAtual;
	pag_ini->idadePagina = 0;
	pag_ini->prox = NULL;
	
	
	while(!feof(arq))
	{
		fgets(ch,9,arq);
		if(!feof(arq)){
			valorAtual = atoi(ch);
			pagina = malloc(sizeof(stPagVirtual));	
			pagina->valor = valorAtual;
			pag_fim->prox = pagina;
			pag_fim = pagina;
			pagina->prox = NULL;
			pagina->idadePagina = 0;
		}
	}
	
	pagina = pag_ini;
	
	currentPage = (stPagVirtual *)malloc(sizeof(stPagVirtual));
	currentPage->valor = pagina->valor;
	currentPage->prox = NULL;
	currentPage->idadePagina = pagina->idadePagina;
	firstPage = (stPagVirtual*)currentPage;
	lastPage = pagina;
	
	int tamanhoMemoria = 1;
	
	while(pagina != NULL){
		if(verificaFita(firstPage, pagina->valor) == 0){
			if(tamanhoMemoria == tamanhoMax){
				retiraVelho(&firstPage);
				pagefaults++;
				tamanhoMemoria--;
			}
			envelheceFita(&firstPage);
			pagina->idadePagina = idadeMax | pagina->idadePagina;
			adicionarFita(&pagina, &lastPage);
			tamanhoMemoria++;
		}
		req++;
		pagina = pagina->prox;
	}
	
	printf("Arquivo %d, %5d paginas, %7d requisicoes: FIFO: %5d Page Faults", numeroArquivo, tamanhoMax, req, pagefaults);
	fclose(arq);
}

int idadeMaxCalc(int tamanhoFita){
	int i, fat;
	for(i = 0; i < (tamanhoFita - 1); i++){
		fat += 2 ^i	;	
	}
	
	return fat;
}

int verificaFita(stPagVirtual *firstNode, int value){
	stPagVirtual *temp;
	if (!firstNode == NULL) {
		stPagVirtual * firstNodeB = firstNode;
		temp = (stPagVirtual *)malloc(sizeof(stPagVirtual));
		temp = firstNodeB;
		while (temp != NULL) {
			if (temp->valor == value)
				return 1;
			temp = temp->prox;
		}
	}
	return 0;
}

int envelheceFita(stPagVirtual **firstNode){
	stPagVirtual *temp;
	if (!firstNode == NULL) {
		while (temp != NULL) {
			temp->idadePagina = temp->idadePagina >> 1;
		}
	}
	return 0;
}

void retiraVelho(stPagVirtual ** firstNode) {
	stPagVirtual *temp, *velho, *ant;
	
	if (!firstNode == NULL) {
		stPagVirtual *firstNodeB = (*firstNode);
		temp = (stPagVirtual *)malloc(sizeof(stPagVirtual));
		temp = firstNodeB;
		velho = temp;
		while (temp != NULL) {
			if(velho->idadePagina < temp->idadePagina)
				velho = temp;
			ant = temp;
			temp = temp->prox;
		}
		//stPagVirtual *newTemp = (*temp)->prox;
		ant->prox = temp->prox;
	}
}

void adicionarFita(stPagVirtual **pagina, stPagVirtual **lastPage){
	stPagVirtual *temp;
	temp = (*lastPage);
	temp->prox = (*pagina);
	lastPage = pagina;
}
