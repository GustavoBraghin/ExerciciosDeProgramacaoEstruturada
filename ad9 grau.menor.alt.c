// Sintese
//   objetivo "Arvore Binaria de Busca"
//   autor "Edson F. da Fonseca & Turma de ED de ES de 2020/2"
//   data "04/09/2020"
#include <stdio.h>
#include <stdlib.h>

//*** Declaracoes de tipos *****************************************************
struct tNo {
	int alt;
	struct tNo *esq;
	int dado;
	struct tNo *dir;
};

//*** Prototipos de funcoes ****************************************************
int menu(void);
void incluir(struct tNo**, struct tNo*);
void preorder(struct tNo*);
void inorder(struct tNo*);
void posorder(struct tNo*);
struct tNo *consultar(struct tNo*, int);
int grau(struct tNo *chave);
struct tNo *menor(struct tNo *chave);
int altura(struct tNo*, struct tNo *chave, int alt);
struct tNo *maiorDireita(struct tNo **no);
void excluir(struct tNo**, int dadoV);
void destruir(struct tNo **raiz);

//*** Bloco Principal **********************************************************
int main(void) {
	struct tNo *arvore=NULL, *p, *aux;
	int opcao, codigo, grauC, altC;
	
	do {
        opcao = menu();
        switch (opcao) {
               case 1: 
                    printf("\n\n*** Inclusao ***\n\n");
                    p = (struct tNo *)malloc(sizeof(struct tNo));
                    printf("Digite um valor: ");
                    scanf("%d", &(p->dado));
                    incluir(&arvore, p);
	                break;
	                
               case 2: 
                    printf("\n\n*** Consulta ***\n\n");
                    printf("Digite o codigo: ");
                    scanf("%d", &codigo);
                    p = consultar(arvore, codigo);
                    if (p != NULL){
	               		printf("Achei\n");
	               		grauC = grau(p);
	               		printf("grau - %i\n", grauC);
	               		aux = menor(p);
	               		printf("menor - %i\n", aux->dado);
	               		altC=0;
	               		altC = altura(arvore, p, altC);
	               		printf("altura - %i\n", altC);
	               	}else
	               		printf("Nao encontrado!\n");
	                break;
	                
               case 3:
                    printf("\n\n*** Pre order ***\n\n");
                    preorder(arvore); // Listar (mostrar na tela) todos os produtos
	                break;
	                
               case 4: 
               		printf("\n\n*** In order ***\n\n");
                    inorder(arvore); // Listar (mostrar na tela) todos os produtos
	                break;
	                
	            case 5:
	            	printf("\n\n*** Pos order ***\n\n");
                    posorder(arvore); // Listar (mostrar na tela) todos os produtos
	                break;
	                
	            case 6:
                    printf("\n\n*** Exclusao ***\n\n");
                    printf("Digite o codigo a ser excluido: ");
                    scanf("%d", &codigo);
                    excluir(&arvore, codigo);
	                break;
        }
    } while (opcao != 0);
    destruir(&arvore);
	return 0;
}

//*** Menu *********************************************************************
int menu(void) {
    int op;
    printf("\n\n*** MENU ***\n\n");
	printf("1. Inclusao\n");
	printf("2. Consulta\n");
    printf("3. caminhamento preorder\n");
    printf("4. caminhamento inorder\n");
    printf("5. caminhamento porordem\n");
	printf("6. Exclusao\n");
	printf("7. Representar\n");
	printf("0. Sair\n\n");
    printf("Escolha sua opcao: ");
    scanf("%d", &op);
    return op;
}

//*** Inclusao *****************************************************************
void incluir(struct tNo **raiz, struct tNo *novo) {
	if ((*raiz) == NULL) {
		(*raiz) = novo;
		novo->esq = novo->dir = NULL;
	}
	else {
		if (novo->dado < (*raiz)->dado)
			incluir(&(*raiz)->esq, novo);
		else
			incluir(&(*raiz)->dir, novo);
	}
}

//*** Consultar ****************************************************************
struct tNo *consultar(struct tNo *raiz, int chave) {
	if (raiz == NULL)
		return NULL;
	if (raiz->dado == chave)
		return raiz;
	if (chave < raiz->dado)
		return consultar(raiz->esq, chave);
	else
		return consultar(raiz->dir, chave);
}

//*** grau ********************************************************************
int grau(struct tNo *chave){
	int filhos=0;
	
	if(chave->esq != NULL)
		filhos++;
	if(chave->dir != NULL)
		filhos++;
	
	return filhos;
}

//*** menor ********************************************************************
struct tNo *menor(struct tNo *chave){
	
	if(chave->esq != NULL){
		return menor(chave->esq);
	}else{
		return chave;
	}	
	
}

//*** altura ********************************************************************
int altura(struct tNo *raiz, struct tNo *chave, int alt){
	
	if(raiz == NULL){
		return 0;
	}
	
	if(raiz->dado == chave->dado)
		return alt;
	if(chave->dado < raiz->dado){
		if(raiz->esq != NULL){
			alt++;
			return altura(raiz->esq, chave, alt);
		}
	}
	
	if(chave->dado > raiz->dado){
		if(raiz->dir != NULL){
			alt++;
			return altura(raiz->dir, chave, alt);
		}
	}
}

//*** preorder *****************************************************************
void preorder(struct tNo *raiz) {

    if(raiz != NULL){
       	printf("\n%i", raiz->dado);
       	preorder(raiz->esq);
       	preorder(raiz->dir);
   	}
}

//*** inorder *****************************************************************
void inorder(struct tNo *raiz) {
	
    if(raiz != NULL){
   		inorder(raiz->esq);
   		printf("\n%i", raiz->dado);
       	inorder(raiz->dir);
   	}
}

//*** posorder *****************************************************************
void posorder(struct tNo *raiz) {
	
    if(raiz != NULL){
       	posorder(raiz->esq);
       	posorder(raiz->dir);
       	printf("\n%i", raiz->dado);
   	}
}

//*** Exclusao *****************************************************************
void excluir(struct tNo **raiz, int dadoV) {

	struct tNo *vitima;

    if((*raiz) == NULL){
       printf("Numero nao existe na arvore!");
       getch();
       return;
    }
    
    if(dadoV < (*raiz)->dado){
       excluir(&(*raiz)->esq, dadoV);
    }else{
    	
       if(dadoV > (*raiz)->dado){
          excluir(&(*raiz)->dir, dadoV);          
        }else{
	// se nao é menor nem maior, logo, é o numero que estou procurando!
       
          vitima = (*raiz);
		            
          if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)){         // se não houver filhos...
                free(vitima);
                (*raiz) = NULL; 
                printf("Excluido\n");
				getch();
            }else{
			             
				if ((*raiz)->esq == NULL){	// só tem o filho da direita
                	(*raiz) = (*raiz)->dir;
                	vitima->dir = NULL;
                	free(vitima); 
					vitima = NULL;
					printf("Excluido\n");
					getch();
            	}else{            
                	if ((*raiz)->dir == NULL){	//só tem filho da esquerda
                	    (*raiz) = (*raiz)->esq;
                	    vitima->esq = NULL;
                	    free(vitima); 
						vitima = NULL;
						printf("Excluido\n");
						getch();		
                	}else{	//tem filho nos dois lados
                		(*raiz) = (*raiz)->esq;
                		(*raiz)->dir = vitima->dir;
						free(vitima);
						vitima = NULL;
						printf("Excluido\n");
						getch();
					}
				}
        	}
		}
	}
}

//*** representar - parenteses aninhados *****************************************************************
void representar(struct tNo *raiz) {
	
    if(raiz != NULL){
       	printf("(%i, ", raiz->dado);
       	posorder(raiz->esq);
       	posorder(raiz->dir);
       	printf(")");
    }
}

//*** Destruir *****************************************************************
void destruir(struct tNo **raiz) {

	while ((*raiz) != NULL) {
		destruir(&(*raiz)->esq);
		destruir(&(*raiz)->dir);
		free(*raiz);
	}
}
//*** FIM **********************************************************************
