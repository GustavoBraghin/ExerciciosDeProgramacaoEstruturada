#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Gustavo da Silva Braghin
//uc19201375

struct tProduto {
	int codigo; // chave de ordenação
	char descricao[30];
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

struct tDescritor {
	struct tNo *ini;
	struct tNo *fim;
};

//*** MENU *******************************************************
int menu(void) {
    int op;
    printf("\n\n*** MENU ***\n\n");
    printf("1. Inclusao\n");
    printf("2. Consulta\n");
    printf("3. Listagem\n");
    printf("4. Alteracao\n");
    printf("5. Exclusao\n");
    printf("0. Sair\n\n");
    printf("Escolha sua opcao: ");
    scanf("%d", &op);
    return op;
}

//*** INICIALIZAR ************************************************
void inicializar(struct tDescritor *lst){
	(*lst).ini = (*lst).fim = NULL;
}

//*** Inclusao *****************************************************************
void incluir(struct tDescritor *lst, struct tNo *novo) {
	struct tNo *p = (*lst).ini, *q;
	
	if (p == NULL) { // vazia/unico
		novo->prox = novo;
		(*lst).ini = (*lst).fim = novo;
	}
	else { //inicio,meio,fim
		if (novo->dado.codigo < (*lst).ini->dado.codigo) { // inicio
			novo->prox = (*lst).ini;
			(*lst).fim->prox = novo;
			(*lst).ini = novo;			
		}
		else { // fim e meio
			if (novo->dado.codigo > (*lst).fim->dado.codigo) { // fim
				(*lst).fim->prox = novo;
				novo->prox = (*lst).ini;
				(*lst).fim = novo;
			}
			else { // meio
				while (novo->dado.codigo > p->dado.codigo){
					q = p; //ANTERIOR
					p = p->prox;
				}
				q->prox = novo;
				novo->prox = p;				
			}
		}
	}
}

//*** CONSULTAR ****************************************************
void consultar(struct tDescritor lst, int codigo){
	
	struct tNo *p = (lst).ini;
	
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	do{
		
		if(p->dado.codigo == codigo){
			printf("%d - %s\n", p->dado.codigo, p->dado.descricao);
			return;
		}
		p = p->prox;
	}while(p != (lst).ini);
	
	printf("Codigo nao encontrado!\n");	
}

//*** LISTAR ****************************************************
void listar(struct tDescritor lst){
	
	struct tNo *p = (lst).ini;
	
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	do{
		printf("%d - %s\n", p->dado.codigo, p->dado.descricao);
		p = p->prox;
	}while(p != (lst).ini);
	
}

//*** ALTERAR ****************************************************
void alterar(struct tDescritor *lst, int codigo){
	
	struct tNo *p = (*lst).ini;
	
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	do{
		
		if(p->dado.codigo == codigo){
			
			printf("Digite nova descricao: ");
			fflush(stdin);
			gets(p->dado.descricao);
			
			printf("\nDescricao alterada com sucesso\n");
			return;
		}
		
		p = p->prox;
	}while(p != (*lst).ini);
	
	printf("Codigo nao encontrado!\n");	
}

//*** EXCLUIR **********************************************
void excluir(struct tDescritor *lst, int codigo){

	struct tNo *p = (*lst).ini, *vitima=NULL;
		
	//lista vazia
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	//achar vítima
	do{
		
		if(p->dado.codigo == codigo){
			vitima = p;
		}
		
		p = p->prox;
	}while(p != (*lst).ini);
	
	//Codigo não encontrado
	if(vitima == NULL){
		printf("codigo nao encontrado!\n");
		return;
	}
	
	if(((*lst).ini == vitima) && (vitima->prox == vitima)){  //Unico
		(*lst).ini = NULL;
		(*lst).fim = NULL;
	}else{
		
		if((*lst).ini == vitima){ //primeiro
			(*lst).ini = vitima->prox;
			(*lst).fim->prox = (*lst).ini;			
		}else{
		
			p = (*lst).ini;
			
			while(p->prox != vitima){ //anterior
				p = p->prox;
			}
			
			if((*lst).fim == vitima){ //Ultimo
				(*lst).fim = p;
				(*lst).fim->prox = (*lst).ini;
				
			}else{ //MEIO			
				p->prox = vitima->prox;			
			}
			
		}
	}
	free(vitima);
	printf("Excluido com sucesso!\n");	
}


//*** DESTRUIR ****************************************************
void destruir(struct tDescritor *lst){
	
	struct tNo *q = (*lst).ini, *p;
	
	do{
		p = q;
		q = q->prox;
		if(p == (*lst).fim){
			break;
		}
		free(p);
	}while(q != NULL);
	
	free(p);
}

main(){
	
	struct tDescritor lista;
	struct tNo *p;
	int opcao, codigo;
	
	inicializar(&lista);
		
	do{
		
		opcao = menu();
		
		switch (opcao){
			
			case 1:				
				printf("\n\n*** Inclusao ***\n\n");
                p = malloc(sizeof(struct tNo)); // Criar um no
                printf("Digite o codigo...: ");
                scanf("%d", &(p->dado.codigo));
                printf("Digite a descricao: ");
                fflush(stdin);
                gets(p->dado.descricao);
                incluir(&lista, p); // Incluir o no com produto criado na lista
	            break;
	            
	       	case 2:
	        	printf("\n\n*** Consulta ***\n\n");
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                // Pesquisar um produto com este codigo
                consultar(lista,codigo);
	            break;                
	            
	        case 3:
	        	printf("\n\n*** Listagem ***\n\n");
                listar(lista); // Listar (mostrar na tela) todos os produtos
	            break;
	            
	        case 4:
	        	printf("\n\n*** Alteracao ***\n\n");
                // Consultar pelo codigo e, caso encontre, permitir
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
				// alterar apenas a descricao.
				// Nao a codigo, pois é chave!
				alterar(&lista,codigo);
	            break;
	            
	        case 5:
	        	printf("\n\n*** Exclusao ***\n\n");
                // Consultar pelo codigo e, caso encontre, excluir o no da lista.
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                    
                excluir(&lista,codigo);                    
	            break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
	}while(opcao != 0);
	
	destruir(&lista);	
}
