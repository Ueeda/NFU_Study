#include <stdio.h>
#include <stdlib.h>

typedef struct estrutura_paginas_virtuais{
	int valor;
	int idade;
	struct estrutura_paginas_virtuais *prox;
} virtualPage;

virtualPage *pag_ini, *pag, *pag_fim;
void manipulandoArquivo(char *nomeArq, int tamanhoFita, int nArquivo);
int idadeMax(int tamanhoFita);

void main(){
	int fat = idadeMax(4);
	printf("%d", fat);
	/*manipulandoArquivo("arquivos/arquivo1.txt", 4,1);
	manipulandoArquivo("arquivos/arquivo2.txt", 4,2);
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
	int numeroArq = nArquivo;
	char ch[10];
	int valorAtual = 0;
	int pageFaults = 0;
	int idadeMax = idadeMax(tamanhoMax);
	
}

int idadeMax(int tamanhoFita){
	int i, fat;
	for(i = 0; i < (tamanhoFita - 1); i++){
		fat += 2 ^i	;	
	}
	
	return fat;
}
